//
// Created by HuiYi on 2023/4/17.
//

#include "XCMain.h"
#include "XCLogin.h"
#include "IEverAPI/IEverAPI.h"
#include "config/config.h"
#include "clipboard/ClipboardMonitor.h"

namespace Win {
	LONG_PTR m_oldPtr=0;
	LRESULT XCMainOnWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

		return CallWindowProcW((WNDPROC) m_oldPtr, hwnd, uMsg, wParam, lParam);
	}

	HWINDOW XCMain::m_hWindow = nullptr;//窗口句柄

	void XCMain::Show(bool show){ XWnd_Show(m_hWindow, show); }

	void XCMain::Create(HXCGUI hParent) {
		bool lShow=true;
		// 加载布局
		m_hWindow = (HWINDOW) XC_LoadLayoutEx(L"res/main.xml", nullptr, hParent, nullptr, nullptr);
		// 注册窗口事件
		// 窗口关闭
		XWnd_RegEventCPP(m_hWindow, WM_CLOSE, &XCMain::OnClose);
		// 窗口过程消息
		// XWnd_RegEventCPP(m_hWindow, XWM_WINDPROC, &XCMain::OnWndProc);
		m_oldPtr = SetWindowLongPtrW(XWnd_GetHWND(m_hWindow), GWLP_WNDPROC, (LONG_PTR) &XCMainOnWndProc);
		auto conf = Base::Config::GetInstance();
		// 远程模式
		if (conf->GetConfig("type", CONNECT_TYPE_REMOTE) == CONNECT_TYPE_REMOTE) {
			lShow = false;
			auto api = conf->GetConfig("ssl", false) ?
			           Client::IEverAPI::Initialization("https://" + conf->GetConfig("host")) :
			           Client::IEverAPI::Initialization("http://" + conf->GetConfig("host"));
			Win::XCLogin loginWin;
			loginWin.Create(m_hWindow);
		}

		// 注册组件

		// 载入窗口
		XWnd_Show(m_hWindow, lShow);
	}

	int XCMain::OnClose(BOOL*){
		Base::ClipboardMonitor::Free();
		return 0;
	}
	void XCMain::StartListening(){
		auto cli = Base::ClipboardMonitor::Initialization((ULONG64) XWnd_GetHWND(m_hWindow));
	}
}