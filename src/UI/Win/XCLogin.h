//
// Created by HuiYi on 2023/4/9.
//

#ifndef LEVER_XCLOGIN_H
#define LEVER_XCLOGIN_H

#include "lib/source_xcgui.h"

namespace Win {
	class XCLogin {
	public:
		/*!
		 * 创建窗口
		 * @param hParent 父窗口句柄
		 */
		void Create(HXCGUI hParent= nullptr);
		void Show(bool show=true);
	private:
		int Event_Close(BOOL* intercept);
		int Event_Login(BOOL*intercept);

		static HWINDOW m_hWindow;//窗口句柄
		static HWINDOW m_hParent;//父窗口句柄
		static HELE m_loginButton;//登录按钮
		static HELE m_loginUsername;//登录用户名编辑框
		static HELE m_loginPassword;//登录密码编辑框
	};
}

#endif //LEVER_XCLOGIN_H
