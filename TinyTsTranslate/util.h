#pragma once
#include <Windows.h>
#include <cwchar>
#include <string>
namespace tw {
std::wstring CharToWStr(const char* c);
std::string WStrToChar(const std::wstring& wstr);
}
