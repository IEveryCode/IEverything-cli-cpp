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

		HWINDOW m_hWindow = nullptr;
		HELE m_loginButton= nullptr;
	};
}

#endif //LEVER_XCLOGIN_H
