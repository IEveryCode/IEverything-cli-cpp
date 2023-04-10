//
// Created by HuiYi on 2023/4/9.
//

#include "XCLogin.h"


void Win::XCLogin::Show(HXCGUI hParent) {
	m_hWindow =  (HWINDOW)XC_LoadLayoutEx(L"res/login.xml", NULL, hParent, NULL, NULL);
	XWnd_Show(m_hWindow, true);
}