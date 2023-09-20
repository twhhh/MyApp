#pragma once
#include <curl/curl.h>
#include <stdlib.h>
#include <openssl/md5.h>
#include <nlohmann/json.hpp>
#include <memory>

#pragma comment(lib, "libcurld.lib")
#pragma comment(lib, "libcrypto.lib")
namespace tw {
class BaiduTransfer
{
public:
	using ptr = std::shared_ptr<BaiduTransfer>;
	BaiduTransfer(const std::string& appId
		, const std::string& pwd
		, const std::string& language = "English");
	~BaiduTransfer();
	void setLanguage(const std::string& language) { m_language = language; }
	const std::string& getLanguage() const { return m_language; }
	bool getTransferError() const { return m_translateError; }
	std::string transferResult(const std::wstring& t);
private:
	void init();
	std::string formatLanguage();
	static size_t CurlCallBack(void* contents, size_t size, size_t nmemb, std::string* output);
	std::string parseResponse();
private:
	std::string m_responseString = ""; //每次翻译后的response字符串
	std::string m_language = "";//翻译语言
	CURL* m_curl;
	CURLcode m_CurlRes;
	bool m_translateError = false;
	bool m_isInit = false;
	std::string m_AppID = "";  //百度翻译APPId
	std::string m_password = "";//百度翻译密钥
};
}


