//
// Created by HuiYi on 2023/4/11.
//

#include "IEverAPI.h"
#include "httplib.h"
#include "utils/url.hpp"
#include "nlohmann/json.hpp"

Client::IEverAPI *Client::IEverAPI::m_ptr = nullptr;

Client::IEverAPI *Client::IEverAPI::Initialization(const std::string &host) {
    if (m_ptr == nullptr) {
        m_ptr = new Client::IEverAPI(host);
    }
    return m_ptr;
}

Client::IEverAPI::IEverAPI(const std::string &host) {
    auto pUrl = Utils::Url::Parse(host);
    m_host = pUrl.Host;
    m_ssl = pUrl.Proto == "https";
    m_port = pUrl.Port;
}

std::string Client::IEverAPI::GetUrl() {
    return m_ssl ? "https://" : "http://" + m_host +
                                ((m_port == 80 || m_port == 443) ? "" : ":" + std::to_string(m_port));
}

void Client::IEverAPI::Login(const std::string &username, const std::string &passwd) {
    static std::string path = "/api/user/login";
    nlohmann::json json;
    json["username"] = username;
    json["passwd"] = passwd;
    try {
        if (m_ssl) {
            httplib::SSLClient cli(m_host, m_port);
            auto res = cli.Post(path, json.dump(), "application/json");
            if(!res){
                throw std::runtime_error("网络错误");
            }
            json = nlohmann::json::parse(res->body, nullptr, true, false);
        } else {
            httplib::Client cli(m_host, m_port);
            auto res = cli.Post(path, json.dump(), "application/json");
            if(!res){
                throw std::runtime_error("网络错误");
            }
            json = nlohmann::json::parse(res->body, nullptr, true, false);
        }
        // 检查返回值
        if (json["err"] != 0) {
            throw std::runtime_error(json["msg"] == "null" ? "未知错误" : json["msg"]);
        }
        // 保存token
        m_token = json["data"]["token"];
        m_refreshToken = json["data"]["refreshToken"];

    } catch (...) {
        throw std::runtime_error("网络错误");
    }

}