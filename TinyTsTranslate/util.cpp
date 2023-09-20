#include "util.h"
#include <codecvt>
#include <locale>
namespace tw {
    std::wstring CharToWStr(const char* c) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::wstring rt = converter.from_bytes(c);
        return rt;
    }

    std::string WStrToChar(const std::wstring& wstr) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::string rt = converter.to_bytes(wstr);
        return rt;
    }
}