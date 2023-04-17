//
// Created by HuiYi on 2023/4/17.
//
#include <chrono>
#include <thread>
#include "iostream"
#include "ClipboardMonitor.h"
#include "utils/pop.hpp"


namespace Base {

	#ifdef _WIN32
	bool openClipboard(){
		bool isopen = OpenClipboard ((HWND)ClipboardMonitor::GetInstance()->GetHWND());
		int forMax = 10;
		for (int i = 0; i < forMax; ++i) {
			isopen = OpenClipboard ((HWND)ClipboardMonitor::GetInstance()->GetHWND());
			if (isopen){
				break;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds (100));
		}
		return isopen;
	}
	std::wstring ClipboardGetTextW () {
		std::wstring result ;
		if (openClipboard()) {
			if(IsClipboardFormatAvailable (CF_UNICODETEXT)){
				auto hClip = GetClipboardData (CF_UNICODETEXT);
				if (hClip) {
					auto pchData = GlobalLock (hClip);
					if(pchData){
						result = (wchar_t*)pchData;
					}
					GlobalUnlock (hClip);
				}
			}
			CloseClipboard ();
		}
		return result;
	}

	std::string ClipboardGetTextA () {
		std::string result ;
		if (openClipboard()) {
			if(IsClipboardFormatAvailable (CF_TEXT)){
				auto hClip = GetClipboardData (CF_TEXT);
				if (hClip) {
					auto pchData = GlobalLock (hClip);
					if(pchData){
						result = (char*)pchData;
					}
					GlobalUnlock (hClip);
				}
			}
			CloseClipboard ();
		}
		return result;
	}

	LONG_PTR m_oldPtr = 0;

	LRESULT WINAPI ClipboardEventMessageProcess(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		if (uMsg == WM_CLIPBOARDUPDATE) {
			CoInitialize(NULL);
			std::wcout<<ClipboardGetTextW() << std::endl;
			std::cout << "剪切板被改变" << std::endl;
			CoUninitialize();
		}
		return CallWindowProcW((WNDPROC) m_oldPtr, hwnd, uMsg, wParam, lParam);
	}


	#else
	#endif

	ULONG64 ClipboardMonitor::m_hWnd = 0;
	ClipboardMonitor *ClipboardMonitor::m_initPtr = nullptr;

	ClipboardMonitor *ClipboardMonitor::Initialization(ULONG64 hwnd) {
		if (m_initPtr == nullptr) {
			m_initPtr = new ClipboardMonitor(hwnd);
		}
		return m_initPtr;
	}

	ClipboardMonitor *ClipboardMonitor::GetInstance() { return m_initPtr; }

	ULONG64 ClipboardMonitor::GetHWND(){return m_hWnd;}

	ClipboardMonitor::ClipboardMonitor(ULONG64 hwnd) {
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