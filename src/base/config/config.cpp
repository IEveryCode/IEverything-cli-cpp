//
// Created by HuiYi on 2023/4/9.
//

#include "config.h"
#include "utils/files.hpp"


namespace Base {
	Config* Config::m_init=nullptr;
	Config *Config::Initialization(const std::string &fileName) {
		if (m_init == nullptr) {
			m_init = new Config(fileName);
		}
		return m_init;
	}

	Config::Config(const std::string& fileName){
		std::string data(Utils::Files::ReadFileToString(fileName));
		if (data.empty()) {
			data = CONFIG_ROW;
			Utils::Files::WriteStringToFile(fileName,data);
		}
		m_jsonData = nlohmann::json::parse(data,nullptr, true, true);
	}

	nlohmann::json& Config::GetProtoPtr() { return m_jsonData; }

	std::string Config::GetConfig(const std::string& objName,const std::string& defaultStr) {
		return m_jsonData.value<std::string>(objName,defaultStr);
	}

}