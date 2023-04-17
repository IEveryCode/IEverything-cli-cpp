//
// Created by HuiYi on 2023/4/9.
//
#ifndef LEVER_UTILS_WIN_H
#define LEVER_UTILS_WIN_H

#include "baseinclude.h"
#include "string"
namespace Utils{
	/*!
 * 信息弹窗函数
 * @param hWnd
 * @param content
 * @param title
 */
	inline void PopMessage(ULONG64 hWnd,const std::string&content,const std::string& title="信息"){
		#ifdef _WIN32
		MessageBoxA(HWND(hWnd),content.c_str(),title.c_str(),MB_OK);
		#else
		#endif
	}
	/*!
* 错误弹窗函数
* @param hWnd
* @param content
* @param title
*/
	inline void PopFail(ULONG64 hWnd,const std::string&content,const std::string& title="错误"){
		#ifdef _WIN32
		MessageBoxA(HWND(hWnd),content.c_str(),title.c_str(),MB_ERR_INVALID_CHARS);
		#else
		#endif
	}

}


#endif