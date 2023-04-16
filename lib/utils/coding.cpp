//
// Created by HuiYi on 2023/4/16.
//
#include "coding.hpp"

#ifdef _WIN32

#include "windows.h"

#else

#endif
namespace Utils::Coding {
	std::wstring A2W(const std::string &str) {
#ifdef _WIN32
		if (!str.size())
			return L"";

		int nCharCount = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0) + 1;
		WCHAR *pBuffer = new WCHAR[nCharCount];
		pBuffer[nCharCount - 1] = L'\0';

		MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), pBuffer, nCharCount);
		std::wstring _wstr = pBuffer;
		delete[] pBuffer;

		return _wstr;
#else

#endif

	}

	std::string W2A(const std::wstring& wstr) {
		#ifdef _WIN32
		if ( !wstr.size() )
			return "";

		int nCharCount = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0,	NULL, NULL) + 1;
		CHAR* pBuffer = new CHAR[nCharCount];
		pBuffer[nCharCount-1] = '\0';

		WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), pBuffer, nCharCount, NULL, NULL);
		std::string _str = pBuffer;
		delete [] pBuffer;

		return _str;
		#else

		#endif

	}

	std::string UTF82A(const std::string& str) {
		#ifdef _WIN32
		if ( !str.size() )
			return "";

		int nCharCount = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.size(), NULL, 0) + 1;
		WCHAR* pBuffer = new WCHAR[nCharCount];
		pBuffer[nCharCount-1] = L'\0';

		MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.size(), pBuffer, nCharCount);
		std::wstring _wstr = pBuffer;
		delete [] pBuffer;

		nCharCount = WideCharToMultiByte(CP_ACP, 0, _wstr.c_str(), _wstr.size(), NULL, 0, NULL, NULL) + 1;
		CHAR* pAnsiBuffer = new CHAR[nCharCount];
		pAnsiBuffer[nCharCount-1] = '\0';

		WideCharToMultiByte(CP_ACP, 0, _wstr.c_str(), _wstr.size(), pAnsiBuffer, nCharCount, NULL, NULL);
		std::string _str = pAnsiBuffer;
		delete [] pAnsiBuffer;

		return _str;
		#else

		#endif
	}
}

