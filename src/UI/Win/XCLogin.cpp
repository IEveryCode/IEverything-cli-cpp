//
// Created by HuiYi on 2023/4/9.
//

#include "XCLogin.h"
#include "IEverAPI/IEverAPI.h"
#include "utils/coding.hpp"
#include "utils/pop.hpp"
#include "config/config.h"
#include "iostream"

int Win::XCLogin::Event_Login(BOOL*intercept){
	try {
		auto con = Base::Config::Initialization(Base::Config::CONFIG_FILENAME);
		auto cli = Client::IEverAPI::Initialization(con->GetConfig("host"));
		auto username = Utils::Coding::W2A(XEdit_GetText_Temp(m_loginUsername));
		auto passwd = Utils::Coding::W2A(XEdit_GetText_Temp(m_loginPassword));

		cli->Login(username, passwd);
		return 0;
	} catch (std::runtime_error const &e){

		MessagePop((ULONG64)XWnd_GetHWND(m_hWindow), e.what(), "错误");
		return -1;
	} catch (std::exception const &e){
		std::cout<<e.what();
		MessagePop((ULONG64)XWnd_GetHWND(m_hWindow), e.what(), "错误");
		return -1;
	}
}

void Win::XCLogin::Show(HXCGUI hParent) {
	// 加载布局
	m_hWindow =  (HWINDOW)XC_LoadLayoutEx(L"res/login.xml", nullptr, hParent, nullptr, nullptr);
	// 注册组件
	// 登录用户名编辑框
	m_loginUsername = (HELE)XC_GetObjectByID(m_hWindow,10011);
	// 登录密码编辑框
	m_loginPassword = (HELE)XC_GetObjectByID(m_hWindow,10012);
	XEdit_EnablePassword(m_loginPassword,TRUE);
	// 登录按钮与登录事件
	m_loginButton = (HELE)XC_GetObjectByID(m_hWindow,10001);
	XEle_RegEventCPP(m_loginButton, XE_BNCLICK, &Win::XCLogin::Event_Login);

	// 载入窗口
	XWnd_Show(m_hWindow, true);

}