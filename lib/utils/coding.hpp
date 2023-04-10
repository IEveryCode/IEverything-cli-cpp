//
// Created by HuiYi on 2023/4/10.
//

#ifndef LEVER_CODING_HPP
#define LEVER_CODING_HPP

#include <cstring>
#include <vector>
#include <string>

#ifdef _WIN32
#include "windows.h"
#else

#endif

namespace Utils::Coding {
	/*!
	 * 将ANSI文本转为Unicode文本
	 * @param str ANSI文本
	 * @return 返回转码之后的文本
	 */
	inline std::wstring A2W(const std::string& str) {
		#ifdef _WIN32
		if ( !str.size() )
			return L"";

		int nCharCount = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0) + 1;
		WCHAR* pBuffer = new WCHAR[nCharCount];
		pBuffer[nCharCount-1] = L'\0';

		MultiByteToWideChar(CP_ACP, 0,	str.c_str(), str.size(), pBuffer, nCharCount);
		std::wstring _wstr = pBuffer;
		delete [] pBuffer;

		return _wstr;
		#else

		#endif

	}

	/*!
	 * 将Unicode文本转为ANSI文本
	 * @param wstr unicode文本
	 * @return 返回转码之后的文本
	 */
	inline std::string W2A(const std::wstring& wstr) {
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


}

#endif //LEVER_CODING_HPP
