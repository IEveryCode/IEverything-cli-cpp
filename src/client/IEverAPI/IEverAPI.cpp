//
// Created by HuiYi on 2023/4/11.
//

#include "IEverAPI.h"
#include "httplib.h"
#include "utils/url.hpp"

Client::IEverAPI *Client::IEverAPI::m_ptr = nullptr;

Client::IEverAPI* Client::IEverAPI::Initialization(const std::string&host) {
	if (m_ptr == nullptr) {
		m_ptr = new Client::IEverAPI(host);
	}
	return m_ptr;
}
Client::IEverAPI::IEverAPI(const std::string&host){
	auto pUrl = Utils::Url::Parse(host);
	m_host = pUrl.Host;
	m_ssl = pUrl.Proto == "https";

}

void Client::IEverAPI::Login(const std::string&username,const std::string&passwd) {

	//httplib::Client cli("https://cpp-httplib-server.yhirose.repl.co");

}