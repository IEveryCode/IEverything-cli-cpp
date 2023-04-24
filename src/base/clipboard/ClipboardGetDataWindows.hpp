//
// Created by HuiYi on 2023/4/24.
//

#ifndef LEVER_CLIPBOARDGETDATAWINDOWS_HPP
#define LEVER_CLIPBOARDGETDATAWINDOWS_HPP

#include "windows.h"
#include <boost/algorithm/string.hpp>
#include <chrono>

namespace Base::Clipboar {

	bool openClipboard() {
		bool isopen = OpenClipboard((HWND) ClipboardMonitor::GetInstance()->GetHWND());
		int forMax = 10;
		for (int i = 0; i < forMax; ++i) {
			isopen = OpenClipboard((HWND) ClipboardMonitor::GetInstance()->GetHWND());
			if (isopen) {
				break;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		return isopen;
	}

	std::wstring ClipboardGetTextW() {
		std::wstring result;
		if (IsClipboardFormatAvailable(CF_UNICODETEXT)) {
			auto hClip = GetClipboardData(CF_UNICODETEXT);
			if (hClip) {
				auto pchData = GlobalLock(hClip);
				if (pchData) {
					result = (wchar_t *) pchData;
				}
				GlobalUnlock(hClip);
			}
		}
		return result;
	}

	std::string ClipboardGetTextA() {
		std::string result;
		if (IsClipboardFormatAvailable(CF_TEXT)) {
			auto hClip = GetClipboardData(CF_TEXT);
			if (hClip) {
				auto pchData = GlobalLock(hClip);
				if (pchData) {
					result = (char *) pchData;
				}
				GlobalUnlock(hClip);
			}
		}
		return result;
	}

	ClipboardData ClipboardGetData() {
		ClipboardData result;

		if (!openClipboard()) {
			return result;
		}
		// 相关文档
		// https://learn.microsoft.com/zh-cn/windows/win32/dataxchg/standard-clipboard-formats
		if (IsClipboardFormatAvailable(CF_UNICODETEXT)) {
			result = ClipboardGetTextW();
		} else if (IsClipboardFormatAvailable(CF_TEXT)) {
			result = ClipboardGetTextA();
		}
		CloseClipboard();
		return result;
	}

	LONG_PTR m_oldPtr = 0;

	static ClipboardData g_oldClipBoardText;

	LRESULT WINAPI ClipboardEventMessageProcess(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		if (uMsg == WM_CLIPBOARDUPDATE) {
			auto data = ClipboardGetData();
			if (g_oldClipBoardText != data) {
				auto t_m = data.Data;
				boost::algorithm::trim(t_m);
				if (t_m.length() > 0) {
					g_oldClipBoardText = ClipboardData(data);
					//std::cout << "ClipboardEventMessageProcess: " << newClipBoardText.Data << std::endl;
					auto call = ClipboardMonitor::GetInstance()->GetCallFunc();
					if (call != nullptr) {
						call(g_oldClipBoardText);
					}
				}
			}
		}
		return CallWindowProcW((WNDPROC) m_oldPtr, hwnd, uMsg, wParam, lParam);
	}
}

#endif //LEVER_CLIPBOARDGETDATAWINDOWS_HPP
