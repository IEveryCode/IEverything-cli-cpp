//
// Created by HuiYi on 2023/4/9.
//

#ifndef LEVER_XCLOGIN_H
#define LEVER_XCLOGIN_H

#include "lib/source_xcgui.h"

namespace Win {
	class XCLogin {
	public:
		void Show(HXCGUI hParent= nullptr);

	private:

		int Event_Login(BOOL*intercept);

		HWINDOW m_hWindow = nullptr;//窗口句柄
		HELE m_loginButton= nullptr;//登录按钮
		HELE m_loginUsername= nullptr;//登录用户名编辑框
		HELE m_loginPassword= nullptr;//登录密码编辑框
	};
}

#endif //LEVER_XCLOGIN_H
