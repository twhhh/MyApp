#include "Translate.h"
#include "util.h"
#include <iostream>
#include <chrono>
namespace tw {

Translate::Translate(const std::string& srcFile
    , const std::string& appId
    , const std::string& pwd
    , const std::string& language
    , bool translateAll) {
	if (srcFile.empty()) {
		m_result = TWResult::RESULT_FAIL;
		return;
	}
	m_srcFile = srcFile;
	m_language = language;
    m_translateAll = translateAll;
	if (m_doc.LoadFile(m_srcFile.c_str()) != tinyxml2::XML_SUCCESS) {
        m_result = TWResult::RESULT_LOADFILEERROR;
		return;
	}
    m_transfer = std::make_shared<BaiduTransfer>(appId, pwd, m_language);
    if (m_transfer == nullptr) {
        m_result = TWResult::RESULT_FAIL;
        return;
    }
    of.open("translate_" + m_language + ".txt", std::ios::trunc);
    if (!of.is_open()) {
        m_result = TWResult::RESULT_SAVETXTFILEERROR;
        return;
    }
    m_result = TWResult::RESULT_SUCCESS;
}

TWResult::emResult Translate::start() {
    tinyxml2::XMLElement* TS = m_doc.RootElement(); //获取根元素
    tinyxml2::XMLElement* context = TS->FirstChildElement("context"); //获取第一个名为context的子元素，不填默认为第一个子元素
    while (context) {
        tinyxml2::XMLElement* contextChildElement = context->FirstChildElement("message");
        auto last = std::chrono::steady_clock::now(); //记录上次发送时间，保证两次翻译为100ms
        bool firstEnter = true;
        while (contextChildElement) {
            tinyxml2::XMLElement* src = contextChildElement->FirstChildElement("source");
            const char* txt;
            txt = src->GetText();//获取标签内容
 
            bool needTransfer = false;
            tinyxml2::XMLElement* tsl = contextChildElement->FirstChildElement("translation");
            const tinyxml2::XMLAttribute* arr = tsl->FindAttribute("type");
            if (arr != nullptr) {
                if (arr->Value() == "unfinished") {
                    needTransfer = true;
                }
            }
            if (m_translateAll || needTransfer) {
                std::wstring input = CharToWStr(txt);
                int retryCount = 0;
                while (true) {
                    auto now = std::chrono::steady_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - last);
                    if (!firstEnter && duration.count() <= 120) {
                        Sleep(120 - duration.count());
                    }
                    if (firstEnter) {
                        firstEnter = false;
                    }
                    std::string output = m_transfer->transferResult(input);
                    last = std::chrono::steady_clock::now();
                    if (m_transfer->getTransferError()){
                        if ((output == "52001" || output == "52002") && retryCount < 3) {
                            retryCount++;
                            continue;
                        }
                        else {
                            //翻译失败
                            if (of.is_open()) {
                                of << input  << std::endl;
                            }
                            m_translateFailCount++;
                        }
                        retryCount = 0;
                        break;
                    }
                    else {
                        std::wstring trans = CharToWStr(output.c_str());
                        tsl->SetText(WStrToChar(trans).c_str());
                        if (arr) {
                            tsl->DeleteAttribute("type");
                        }
                        //翻译成功
                        if (of.is_open()) {
                            of << input << L"  " << trans << std::endl;
                        }
                        m_translateSuccessCount++;
                        break;
                    }
                }
            }
            contextChildElement = contextChildElement->NextSiblingElement();
        }
        context = context->NextSiblingElement();
    }
    std::string saveFile("translate_" + m_language + ".ts");
    if (m_doc.SaveFile(saveFile.c_str()) != tinyxml2::XML_SUCCESS) { //保存修改后的东西
        m_result = TWResult::RESULT_SAVEFILEERROR;
    }
    else {
        std::cout << "translate :" << m_translateSuccessCount << " successfully" << std::endl;
        std::cout << "translate :" << m_translateFailCount << " fail" << std::endl;
        m_result = TWResult::RESULT_SUCCESS;
    }
    return m_result;
}

TWResult::emResult Translate::setLanguage(const std::string& language){
    if (m_transfer) {
        m_transfer->setLanguage(language);
        return TWResult::RESULT_SUCCESS;
    }
    else {
        return TWResult::RESULT_FAIL;
    }
}
}
