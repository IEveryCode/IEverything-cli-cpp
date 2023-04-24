//
// Created by HuiYi on 2023/4/17.
//

#ifndef LEVER_CLIPBOARDMONITOR_H
#define LEVER_CLIPBOARDMONITOR_H
#ifdef _WIN32
#include "windows.h"
#else
#endif

namespace Base::Clipboar{

	enum ClipboarDataType {
		// 文本
		ClipboarDataType_Text,
		// 图片
		ClipboarDataType_Image,

		ClipboarDataType_File,
		ClipboarDataType_Unknown
	};

	struct ClipboardData {
		ClipboarDataType Type=ClipboarDataType_Text;
		std::string Data;

		ClipboardData(){ Type=ClipboarDataType_Text;Data=""; }
		ClipboardData(const std::string &a);
		ClipboardData(const std::wstring &a);
		ClipboardData& operator=(const std::wstring& other);
		ClipboardData& operator=(const std::string& other);
		bool operator==(const ClipboardData& other) const ;
		bool operator==(const std::string& other) const ;
		bool operator!=(const ClipboardData& other) const;

	};

	typedef void (*ClipboardEventCallback)(const ClipboardData &data);

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
		static ClipboardMonitor* Initialization(ULONG64 hWnd,ClipboardEventCallback callFunc= nullptr);

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

		static ClipboardEventCallback GetCallFunc();
	private:
		ClipboardMonitor(ULONG64 hwnd,ClipboardEventCallback callBack);
		~ClipboardMonitor();
		static ClipboardMonitor*m_initPtr;
		static ULONG64 m_hWnd;
		static ClipboardEventCallback m_callFunc;
	};
}


#endif //LEVER_CLIPBOARDMONITOR_H
