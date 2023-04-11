//
// Created by HuiYi on 2023/4/11.
//

#ifndef LEVER_URL_HPP
#define LEVER_URL_HPP

#include <boost/url.hpp>
#include <iostream>

namespace Utils::Url {

	struct Model {
		// 链接的协议
		std::string Proto;
		// 链接的端口
		int Port;
		// 主机
		std::string Host;
		// 请求地址
		std::string Path;
		// 查询参数
		std::string Query;
		// 片段(#后面的参数)
		std::string Fragment;
	};

	Model Parse(const std::string &url) {
		auto u = boost::url(url.c_str());
		std::string tmp;
		Model result;
		result.Proto = u.scheme();
		tmp = u.port();
		result.Port = stoi(tmp);
		result.Host = u.host();
		result.Path = u.path();
		result.Query = u.query();
		result.Fragment = u.fragment();
		return result;
	}

//	/*!
//	 * 获取Url的协议
//	 * @param url 被解析的Url
//	 * @return 返回协议文本
//	 */
//	std::string GetProto(const std::string&url){
//		auto u = boost::url(url.c_str());
//		if (u.scheme()=="http"){
//			return "http";
//		}
//		if (u.scheme()=="https"){
//			return "https";
//		}
//		return u.scheme();
//	};
//
//	/*!
//	 * 解析链接的端口
//	 * @param url 被解析的Url
//	 * @return 返回链接端口号
//	 */
//	int GetPort(const std::string&url){
//		std::string u = boost::url(url.c_str()).port();
//		return atoi(u.c_str());
//	};
}

#endif //LEVER_URL_HPP
