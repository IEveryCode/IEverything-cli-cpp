//
// Created by HuiYi on 2023/4/17.
//

#ifndef LEVER_CLIPBOARDMONITOR_H
#define LEVER_CLIPBOARDMONITOR_H
#ifdef _WIN32
#include "windows.h"
#else
#endif

namespace Base{
	/*!
 * 剪切板监听器
 */
	class ClipboardMonitor {
	public:

		/*!
	 * 初始化配置单例,配置方案为
	 * @param fileName json配置文件名
	 * @throw
	 */
		static ClipboardMonitor* Initialization(ULONG64 hwnd);

		/*!
		 * 获取单例
		 * @return 单例指针
		 */
		static ClipboardMonitor* GetInstance();

		/*!
		 * 释放单例
		 */
		static void Free();
		static ULONG64 GetHWND();
	private:
		ClipboardMonitor(ULONG64 hwnd);
		~ClipboardMonitor();
		static ClipboardMonitor*m_initPtr;
		static ULONG64 m_hWnd;
	};
}


#endif //LEVER_CLIPBOARDMONITOR_H
