//
// Created by HuiYi on 2023/4/9.
//
#include "winmain.h"
#include "config/config.h"
#include "windows.h"
#include "XCLogin.h"
#include "lib/source_xcgui.h"

namespace Win{
	void Start(){
		// 加载配置
		auto conf = Base::Config::Initialization("config.json");
		MessageBoxA(0,"ok",0,0);
//		// 远程模式
//		if (conf->GetConfig("type",CONNECT_TYPE_REMOTE)==CONNECT_TYPE_REMOTE){ }

	}
}