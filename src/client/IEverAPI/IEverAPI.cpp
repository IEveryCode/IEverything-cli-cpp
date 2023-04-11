//
// Created by HuiYi on 2023/4/11.
//

#include "IEverAPI.hpp"
#include "httplib.h"
#include "utils/url.hpp"

Client::IEverAPI *Client::IEverAPI::m_ptr = nullptr;

Client::IEverAPI* Client::IEverAPI::Initialization(const char*host) {
	if (m_ptr == nullptr) {
		m_ptr = new Client::IEverAPI(host);
	}
	return m_ptr;
}
Client::IEverAPI::IEverAPI(const char*host){
	auto pUrl = Utils::Url::Parse(host);

}

void Client::IEverAPI::Login(const char*username,const char*passwd) {

	//httplib::Client cli("https://cpp-httplib-server.yhirose.repl.co");

}