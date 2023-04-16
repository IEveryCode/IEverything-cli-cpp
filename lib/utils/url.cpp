//
// Created by HuiYi on 2023/4/16.
//
#include "url.hpp"
#include <boost/url.hpp>
namespace Utils::Url {

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
		if (result.Proto=="https"){tmp = u.port()==""?"443":u.port();}
		else{tmp = u.port()==""?"80":u.port();}
		result.Port = stoi(tmp);
		result.Host = u.host();
		result.Path = u.path();
		result.Query = u.query();
		result.Fragment = u.fragment();
		return result;
	}
}