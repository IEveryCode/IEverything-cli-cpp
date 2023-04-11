//
// Created by HuiYi on 2023/4/9.
//

#include "XCLogin.h"
#include "IEverAPI/IEverAPI.hpp"

int Win::XCLogin::Event_Login(BOOL*intercept){
	auto cli = Client::IEverAPI::Initialization("http://127.0.0.1:18080");

	return 0;
}

void Win::XCLogin::Show(HXCGUI hParent) {
	// 加载布局
	m_hWindow =  (HWINDOW)XC_LoadLayoutEx(L"res/login.xml", nullptr, hParent, nullptr, nullptr);
	// 注册组件
	// 登录按钮与登录事件
	m_loginButton = (HELE)XC_GetObjectByID(m_hWindow,10001);
	XEle_RegEventCPP(m_loginButton, XE_BNCLICK, &Win::XCLogin::Event_Login);

	// 载入窗口
	XWnd_Show(m_hWindow, true);

}