#include "BaiduTransfer.h"
#include <iostream>

#include "util.h"
namespace tw {
size_t BaiduTransfer::CurlCallBack(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

std::string BaiduTransfer::formatLanguage() {
    if (m_language == "English") {
        return "en";
    }
    if (m_language == "Chinese") {
        return "zh";
    }
    if (m_language == "Japanese") {
        return "jp";
    }
    if (m_language == "German") {
        return "de";
    }
    if (m_language == "French") {
        return "fra";
    }
    if (m_language == "Polish") {
        return "pl";
    }
    return "en";
}

std::string BaiduTransfer::parseResponse() {
    std::string rs;
    try {
        nlohmann::json jsonData = nlohmann::json::parse(m_responseString);

        if (jsonData.find("error_code") != jsonData.end()) {
            m_translateError = true;
            std::string error_code = jsonData["error_code"];
            std::string error_msg = jsonData["error_msg"];
            rs = error_code + ":" + error_msg;
        }
        for (const auto& entry : jsonData["trans_result"]) {
            std::string src = entry["src"];
            std::string dst = entry["dst"];
            std::cout << "std::string dst " << dst << std::endl;
            m_translateError = false;
            rs = dst;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "JSON parsing error: " << e.what() << std::endl;
    }
    m_responseString.clear();
    m_responseString = "";
    return rs;
}

BaiduTransfer::BaiduTransfer(const std::string& appId
    , const std::string& pwd
    , const std::string& language) 
    : m_AppID(appId)
    , m_password(pwd)
    , m_language(language) {
    init();
}

BaiduTransfer::~BaiduTransfer() {
    if (m_curl) {
        curl_easy_cleanup(m_curl);
    }
}

void BaiduTransfer::init() {
    if (m_isInit) {
        return;
    }
    if (m_AppID.empty() || m_password.empty()) {
        m_isInit = false;
        std::cout << "error : m_AppID.empty() || m_password.empty() !" << std::endl;
        return;
    }
    m_isInit = true;
    m_curl = curl_easy_init();

    if (m_curl) {
        curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, BaiduTransfer::CurlCallBack);
        curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &m_responseString);
    }
    else {
        m_isInit = false;
        std::cout << "curl_easy_init error!" << std::endl;
        return;
    }
}

std::string BaiduTransfer::transferResult(const std::wstring& t) {
    if (m_isInit == false) {
        std::cout << "m_isInit == false" << std::endl;
        return "";
    }
    if (m_curl) {
        char myurl[1000] = "http://api.fanyi.baidu.com/api/trans/vip/translate?";
        const char* appid = m_AppID.c_str();    //replace myAppid with your own appid
        std::string str = WStrToChar(t);
        std::cout << str << std::endl;
        const char* q = str.c_str();          //replace apple with your own text to be translate, ensure that the input text is encoded with UTF-8!
        const char* from = "zh";          //replace en with your own language type of input text          //replace zh with your own language type of output text
        char salt[60];
        int a = rand();
        sprintf_s(salt, "%d", a);
        const char* secret_key = m_password.c_str();   //replace mySecretKey with your own mySecretKey
        char sign[120] = "";
        strcat_s(sign, appid);
        strcat_s(sign, q);
        strcat_s(sign, salt);
        strcat_s(sign, secret_key);
        printf("%s\n", sign);
        unsigned char md[16];
        int i;
        char tmp[3] = { '\0' }, buf[33] = { '\0' };
        MD5((unsigned char*)sign, strlen(sign), md);
        for (i = 0; i < 16; i++) {
            sprintf_s(tmp, "%2.2x", md[i]);
            strcat_s(buf, tmp);
        }
        printf("%s\n", buf);
        strcat_s(myurl, "appid=");
        strcat_s(myurl, appid);
        strcat_s(myurl, "&q=");
        strcat_s(myurl, q);
        strcat_s(myurl, "&from=");
        strcat_s(myurl, from);
        strcat_s(myurl, "&to=");
        strcat_s(myurl, formatLanguage().c_str());
        strcat_s(myurl, "&salt=");
        strcat_s(myurl, salt);
        strcat_s(myurl, "&sign=");
        strcat_s(myurl, buf);
        printf("%s\n", myurl);
        curl_easy_setopt(m_curl, CURLOPT_URL, myurl);
        m_CurlRes = curl_easy_perform(m_curl);

        /* Check for errors */
        if (m_CurlRes != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(m_CurlRes));
            return "Send URL ERROR";
        }
        else {
            //std::cout << "response: " << responseString << std::endl;
            return parseResponse();
        }
    }
    return "Init Error";
}
}
