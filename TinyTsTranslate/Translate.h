#pragma once
#include <string>
#include <Windows.h>
#include <cwchar>
#include <memory>
#include <fstream>
#include "tinyxml2.h"
#include "BaiduTransfer.h"
namespace tw {
class TWResult {
public:
	enum emResult
	{
		RESULT_SUCCESS = 0,
		RESULT_FAIL,
		RESULT_SAVEFILEERROR,
		RESULT_LOADFILEERROR,
		RESULT_SAVETXTFILEERROR,


	};
	static std::string ToString(emResult r) {
	}
};
class Translate {
public:
	using ptr = std::shared_ptr<Translate>;
	Translate(const std::string& srcFile
		, const std::string& appId
		, const std::string& pwd
		, const std::string& language = "English", bool translateAll = false);
	TWResult::emResult start();
	TWResult::emResult setLanguage(const std::string& language);
	int getTranslateSuccessCount() const { return m_translateSuccessCount; }
	int getTranslateFailCount() const { return m_translateFailCount; }

private:
	TWResult::emResult m_result = TWResult::RESULT_FAIL;
	std::string m_srcFile = "";//翻译文件路径
	std::string m_language = "";//翻译语言
	tinyxml2::XMLDocument m_doc;
	BaiduTransfer::ptr m_transfer = nullptr;
	bool m_translateAll = true;
	int m_translateSuccessCount = 0;
	int m_translateFailCount = 0;
	std::wofstream of;
};
}

