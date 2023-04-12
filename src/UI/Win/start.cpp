//
// Created by HuiYi on 2023/4/9.
//
#include "winmain.h"
#include "config/config.h"
#include "utils/files.hpp"
#include "XCLogin.h"
#include "lib/source_xcgui.h"
#include "IEverAPI/IEverAPI.h"

namespace Win {
	void Start() {
		// 写出相关文件
		if (!Utils::Files::FileIfExists("xcgui.dll")) {
			if (!Utils::Files::WriteByteToFile("xcgui.dll",
			                                   resource::XCGUI_dll, resource::XCGUI_dll_len)) {
				throw std::runtime_error("初始化库: xcgui.dll 失败!");
			}
		}
		// 加载配置
		auto conf = Base::Config::Initialization("config.json");
		XInitXCGUI(true);
		XC_LoadResource(L"res/resource.res");
		// 远程模式
		if (conf->GetConfig("type", CONNECT_TYPE_REMOTE) == CONNECT_TYPE_REMOTE) {
			conf->GetConfig("ssl",false)?
			Client::IEverAPI::Initialization(("https://"+conf->GetConfig("host")).c_str()):
			Client::IEverAPI::Initialization(("http://"+conf->GetConfig("host")).c_str());
			Win::XCLogin loginWin;
			loginWin.Show();
		}

		XRunXCGUI();
		XExitXCGUI();

	}
}