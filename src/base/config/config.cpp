//
// Created by HuiYi on 2023/4/9.
//

#include "config.h"
#include "utils/files.hpp"

namespace Base {
	Config *Config::m_init = nullptr;
	const char *Config::CONFIG_FILENAME = "config.json";

	Config *Config::GetInstance() { return m_init; }

	Config *Config::Initialization(const std::string &fileName) {
		// 如果已经初始化过了，直接返回
		if (m_init == nullptr) {
			// 如果没有初始化过，初始化
			m_init = new Config(fileName);
		}
		return m_init;
	}

	Config::Config(const std::string &fileName) {
		// 读取配置文件
		std::string data(Utils::Files::ReadFileToString(fileName));
		// 如果配置文件为空，写入默认配置
		if (data.empty()) {
			// 默认配置
			data = CONFIG_ROW;
			// 写入配置文件
			Utils::Files::WriteStringToFile(fileName, data);
		}
		// 解析配置文件
		m_jsonData = nlohmann::json::parse(data, nullptr, true, true);
	}

	nlohmann::json &Config::GetProtoPtr() { return m_jsonData; }


	std::string Config::GetConfig(const std::string &objName, const std::string &defaultStr) {
		return m_jsonData.value<std::string>(objName, defaultStr);
	}

	void Config::Save() {
		Utils::Files::WriteStringToFile(Config::CONFIG_FILENAME, m_jsonData.dump());
	}

}

