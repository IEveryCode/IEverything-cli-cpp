//
// Created by HuiYi on 2023/4/17.
//

#ifndef LEVER_XCMAIN_H
#define LEVER_XCMAIN_H

#include "lib/source_xcgui.h"

namespace Win {
	class XCMain {
	public:

		/*!
		 * 创建窗口
		 * @param hParent 父窗口句柄
		 */
		void Create(HXCGUI hParent = nullptr);

		int OnCreate(BOOL*);
		int OnClose(BOOL*);

		void Show(bool show=false);
		/*!
		 * 开始监听剪贴板
		 */
		void StartListening();
	private:

		static HWINDOW m_hWindow;//窗口句柄

		int OnWndProc(UINT message, WPARAM wParam, LPARAM lParam, BOOL *pbHandled);
	};
}

#endif //LEVER_XCMAIN_H
