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

	/*!
	 * 解析url
	 * @param url 链接
	 * @return 返回解析后的Model
	 */
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
}

#endif //LEVER_URL_HPP
