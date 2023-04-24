//
// Created by HuiYi on 2023/4/17.
//

#include <thread>
#include "iostream"
#include "ClipboardMonitor.h"
#include "utils/pop.hpp"
#include "utils/coding.hpp"
#ifdef _WIN32
#include "ClipboardGetDataWindows.hpp"
#else
#endif


namespace Base::Clipboar {
	ClipboardData::ClipboardData(const std::string &a) {
		Type = ClipboarDataType_Text;
		Data = a;
	};

	ClipboardData::ClipboardData(const std::wstring &a) {
		Type = ClipboarDataType_Text;
		Data = Utils::Coding::W2A(a);
	}

	ClipboardData &ClipboardData::operator=(const std::wstring &other) {
		Type = ClipboarDataType_Text;
		Data = Utils::Coding::W2A(other);
		return *this;
	}

	ClipboardData &ClipboardData::operator=(const std::string &other) {
		Type = ClipboarDataType_Text;
		Data = other;
		return *this;
	}

	bool ClipboardData::operator==(const std::string &other) const { return Data == other; }

	bool ClipboardData::operator==(const ClipboardData &other) const { return Type == other.Type && Data == other.Data; }

	bool ClipboardData::operator!=(const ClipboardData &other) const { return !(*this == other); }


	ULONG64 ClipboardMonitor::m_hWnd = 0;
	ClipboardMonitor *ClipboardMonitor::m_initPtr = nullptr;
	ClipboardEventCallback ClipboardMonitor::m_callFunc = nullptr;

	ClipboardMonitor *ClipboardMonitor::Initialization(ULONG64 hWnd, ClipboardEventCallback callFunc) {
		if (m_initPtr == nullptr) {
			m_initPtr = new ClipboardMonitor(hWnd, callFunc);
		}
		return m_initPtr;
	}

	ClipboardMonitor *ClipboardMonitor::GetInstance() { return m_initPtr; }

	ULONG64 ClipboardMonitor::GetHWND() { return m_hWnd; }

	ClipboardEventCallback ClipboardMonitor::GetCallFunc() {
		return m_callFunc;
	}

	ClipboardMonitor::ClipboardMonitor(ULONG64 hwnd, ClipboardEventCallback callFunc) {
		m_hWnd = hwnd;
		auto rBool = AddClipboardFormatListener((HWND) hwnd);
		if (!rBool) {
			Utils::PopFail(hwnd, "绑定剪切板事件失败!", "错误");
			exit(-1);
		}
		m_oldPtr = SetWindowLongPtrW((HWND) hwnd, GWLP_WNDPROC, (LONG_PTR) &ClipboardEventMessageProcess);
		if (!m_oldPtr) {
			Utils::PopFail(hwnd, "注册监听器失败!", "错误");
			exit(-1);
		}
		m_callFunc = callFunc;
	}

	void ClipboardMonitor::Free() {
		if (m_initPtr) {
			delete m_initPtr;
			m_initPtr = nullptr;
			std::cout << "释放剪切板监听器成功!" << std::endl;
		}
	}

	ClipboardMonitor::~ClipboardMonitor() {
		RemoveClipboardFormatListener((HWND) m_hWnd);
	}

}