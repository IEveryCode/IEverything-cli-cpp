//
// Created by HuiYi on 2023/4/9.
//
#include "winmain.h"
#include "XCLogin.h"
#include "IEverAPI/IEverAPI.h"
#include "utils/coding.hpp"
#include "utils/pop.hpp"
#include "config/config.h"
#include "iostream"

namespace Win {
	HWINDOW XCLogin::m_hWindow = nullptr;//窗口句柄
	HWINDOW XCLogin::m_hParent = nullptr;//父窗口句柄
	HELE XCLogin::m_loginButton = nullptr;//登录按钮按钮
	HELE XCLogin::m_loginUsername = nullptr;//登录用户名编辑框
	HELE XCLogin::m_loginPassword = nullptr;//登录密码编辑框

	void XCLogin::Show(bool show) { XWnd_Show(m_hWindow, show); }

	int XCLogin::Event_Close(BOOL *intercept) {
		auto cli = Client::IEverAPI::GetInstance();
		if (!cli->IfLogin()) {
			exit(0);
		}
		XWnd_Show(m_hParent, true);
		Win::g_wMain.StartListening();
		return 0;
	}

	int XCLogin::Event_Login(BOOL *intercept) {
		try {
			auto con = Base::Config::GetInstance();
			auto cli = Client::IEverAPI::GetInstance();
			auto username = Utils::Coding::W2A(XEdit_GetText_Temp(m_loginUsername));
			auto passwd = Utils::Coding::W2A(XEdit_GetText_Temp(m_loginPassword));

			cli->Login(username, passwd);
			SendMessageA(XWnd_GetHWND(m_hWindow), WM_CLOSE, 0, 0);
			return 0;
		} catch (std::runtime_error const &e) {

			Utils::PopFail((ULONG64) XWnd_GetHWND(m_hWindow), e.what(), "错误");
			return -1;
		} catch (std::exception const &e) {
			std::cout << e.what();
			Utils::PopFail((ULONG64) XWnd_GetHWND(m_hWindow), e.what(), "错误");
			return -1;
		}
	}

	void XCLogin::Create(HXCGUI hParent) {
		m_hParent = (HWINDOW) hParent;
		// 加载布局
		m_hWindow = (HWINDOW) XC_LoadLayoutEx(L"res/login.xml", nullptr, hParent, nullptr, nullptr);
		// 注册窗口事件
		XWnd_RegEventCPP(m_hWindow, WM_CLOSE, &XCLogin::Event_Close);
		// 注册组件
		// 登录用户名编辑框
		m_loginUsername = (HELE) XC_GetObjectByID(m_hWindow, 10011);
		// 登录密码编辑框
		m_loginPassword = (HELE) XC_GetObjectByID(m_hWindow, 10012);
		XEdit_EnablePassword(m_loginPassword, TRUE);
		// 登录按钮与登录事件
		m_loginButton = (HELE) XC_GetObjectByID(m_hWindow, 10001);
		XEle_RegEventCPP(m_loginButton, XE_BNCLICK, &Win::XCLogin::Event_Login);
		XWnd_Show(m_hWindow, true);

	}
}
