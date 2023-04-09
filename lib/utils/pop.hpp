//
// Created by HuiYi on 2023/4/9.
//
#ifndef LEVER_UTILS_WIN_H
#define LEVER_UTILS_WIN_H

#include "baseinclude.h"

/*!
 * 抽象化弹窗函数
 * @param hWnd
 * @param content
 * @param title
 * @param type
 */
void MessagePop(ULONG64 hWnd,const std::string&content,const std::string& title,UINT type=0){
	#ifdef _WIN32
		MessageBoxA(HWND(hWnd),content.c_str(),title.c_str(),type);
	#else
	#endif
}

#endif