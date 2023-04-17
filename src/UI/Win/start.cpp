//
// Created by HuiYi on 2023/4/9.
//
#include <thread>
#include "winmain.h"
#include "config/config.h"
#include "utils/files.hpp"
#include "lib/source_xcgui.h"


namespace Win {
	XCMain g_wMain;

	void Start() {
		// 写出相关文件
		if (!Utils::Files::FileIfExists("xcgui.dll")) {
			if (!Utils::Files::WriteByteToFile("xcgui.dll",
			                                   resource::XCGUI_dll, resource::XCGUI_dll_len)) {
				throw std::runtime_error("初始化库: xcgui.dll 失败!");
			}
		}
		// 加载配置
		Base::Config::Initialization(Base::Config::CONFIG_FILENAME);
		XInitXCGUI(true);
		XC_LoadResource(L"res/resource.res");


		g_wMain.Create();

		XRunXCGUI();
		XExitXCGUI();

	}
}