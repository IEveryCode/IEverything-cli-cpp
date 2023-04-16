//
// Created by HuiYi on 2023/4/9.
//

#include "config.h"
#include "utils/files.hpp"


Base::Config *Base::Config::m_init = nullptr;
const char* Base::Config::CONFIG_FILENAME="config.json";

Base::Config *Base::Config::Initialization(const std::string &fileName) {
	if (m_init == nullptr) {
		m_init = new Config(fileName);
	}
	return m_init;
}

Base::Config::Config(const std::string &fileName) {
	std::string data(Utils::Files::ReadFileToString(fileName));
	if (data.empty()) {
		data = CONFIG_ROW;
		Utils::Files::WriteStringToFile(fileName, data);
	}
	m_jsonData = nlohmann::json::parse(data, nullptr, true, true);
}

nlohmann::json &Base::Config::GetProtoPtr() { return m_jsonData; }


std::string Base::Config::GetConfig(const std::string &objName, const std::string &defaultStr) {
	return m_jsonData.value<std::string>(objName, defaultStr);
}

