//
// Created by HuiYi on 2023/4/11.
//

#include "IEverAPI.h"
#include "ws/WsClient.h"
#include "httplib.h"
#include "utils/url.hpp"
#include "utils/coding.hpp"

namespace Client {

	std::shared_ptr<WsClient> g_WsClient;

	IEverAPI *IEverAPI::m_ptr = nullptr;

	nlohmann::json IEverAPI::CheckResult(const std::string &respBody) {
		auto respJson = nlohmann::json::parse(respBody);
		// 检查返回值
		if (respJson["error"] != 0) {
			throw std::runtime_error(Utils::Coding::UTF82A(respJson["msg"].is_null() ? "网络错误" : respJson["msg"]));
		}
		return respJson["data"];
	}

	IEverAPI *IEverAPI::GetInstance() { return m_ptr; }

	IEverAPI *IEverAPI::Initialization(const std::string &host) {
		if (m_ptr == nullptr) {
			m_ptr = new Client::IEverAPI(host);
		}
		return m_ptr;
	}

	IEverAPI::IEverAPI(const std::string &host) {
		auto pUrl = Utils::Url::Parse(host);
		m_host = pUrl.Host;
		m_ssl = pUrl.Proto == "https";
		m_port = pUrl.Port;
	}

	std::string IEverAPI::GetUrl() {
		return m_ssl ? "https://" : "http://" + m_host +
		                            ((m_port == 80 || m_port == 443) ? "" : ":" + std::to_string(m_port));
	}

	void IEverAPI::Login(const std::string &username, const std::string &passwd) {
		static std::string path = "/api/user/login";
		nlohmann::json json;
		json["username"] = username;
		json["passwd"] = passwd;

		if (m_ssl) {
			httplib::SSLClient cli(m_host, m_port);
			auto res = cli.Post(path, json.dump(), "application/json");
			if (res.error() != httplib::Error::Success) {
				throw std::runtime_error(httplib::to_string(res.error()));
			}
			json = CheckResult(res->body);
		} else {
			httplib::Client cli(m_host, m_port);
			auto res = cli.Post(path, json.dump(), "application/json");
			if (res.error() != httplib::Error::Success) {
				throw std::runtime_error(httplib::to_string(res.error()));
			}
			json = CheckResult(res->body);
		}
		// 保存token
		m_token = json["token"];
		m_refreshToken = json["refreshToken"];
		m_ifLogin = true;
		if (!m_checkTokenThread) {

			// 创建一个线程轮询检查token是否过期
			m_checkTokenThread = new std::thread([this]() {
				std::cout << "check token:begin" << std::endl;
				while (true) {
					std::this_thread::sleep_for(std::chrono::seconds(30));
					try {
						IEverAPI::GetInstance()->CheckToken();
						std::cout << "check token:ok" << std::endl;
					} catch (std::exception &e) {
						std::cout << "check token:" << e.what() << std::endl;
						this->Logout();
					}
				}
			});

		}
		if (!m_connectWsThread) {
			// 创建一个连接交互线程
			m_connectWsThread = new std::thread([this]() {
				std::stringstream wsUrl;
				wsUrl << "ws://" << m_host;
				if (m_port != 80 && m_port != 443) {
					wsUrl << ":" << std::to_string(m_port);
				}
				wsUrl << "/api/clipbrd/connect";
				std::cout << "connect: " << wsUrl.str() << std::endl;
				g_WsClient.reset(new WsClient(wsUrl.str()));
				g_WsClient->SetAuth(m_token);
				g_WsClient->Run();
			});
		}
	}

	bool IEverAPI::IfLogin() { return m_ifLogin; }

	void IEverAPI::Logout() {
		// 先使用refreshToken刷新token
		// TODO: 待完成
		// ...
		m_ifLogin = false;
		// token过期
		m_ifLogin = false;
		// TODO: 这应该是向主窗口发送消息，让主窗口弹出登录窗口

	}

	bool IEverAPI::CheckToken(bool exception) {
		static std::string path = "/api/user/check_token";
		try {
			if (m_ssl) {
				httplib::SSLClient cli(m_host, m_port);
				auto res = cli.Get(path);
				if (res.error() != httplib::Error::Success) {
					throw std::runtime_error(httplib::to_string(res.error()));
				}
				CheckResult(res->body);
			} else {
				httplib::Client cli(m_host, m_port);
				auto res = cli.Get(path);
				if (res.error() != httplib::Error::Success) {
					throw std::runtime_error(httplib::to_string(res.error()));
				}
				CheckResult(res->body);
			}
		} catch (std::exception &e) {
			if (exception) {
				throw e;
			}
			return false;
		}
		return true;
	}


}


