//
// Created by HuiYi on 2023/4/11.
//

#ifndef LEVER_IEVERAPI_H
#define LEVER_IEVERAPI_H

#include "nlohmann/json.hpp"
#include "thread"

namespace Client {
	/*!
	 * IEver后端通信api
	 */
	class IEverAPI {
	public:
		/*!
		 * 获取实例
		 * @param 服务器地址
		 * @return 返回实例对象指针
		 */
		static IEverAPI *Initialization(const std::string &host);

		/*!
		 * 获取实例
		 * @return 返回实例对象指针
		 */
		static IEverAPI *GetInstance();

		IEverAPI(const std::string &host);

		/*!
		 * 用户登录
		 * @param username 用户名
		 * @param passwd    密码
		 */
		void Login(const std::string &username, const std::string &passwd);

		/*!
		 * 用户登出
		 */
		void Logout();

		/*!
		 * 检查token是否有效
		 * @param exception 是否抛出异常
		 * @return 无效返回false
		 */
		bool CheckToken(bool exception=false);

		/*!
		 * 是否已经登录
		 * @return 已登录返回true
		 */
		bool IfLogin();

	private:
		static IEverAPI *m_ptr;//单例指针

		bool m_ssl = false;//是否启用ssl
		std::string m_host;//服务器地址
		int m_port = 80;//服务器端口

		std::string m_token;//登录token
		std::string m_refreshToken;//刷新token
		bool m_ifLogin = false;//是否登录
		std::thread* m_checkTokenThread = nullptr;//登录后轮询线程

		std::string GetUrl();

		/*!
		 * 检查返回值
		 * @param respBody 返回文本数据
		 * @return 成功返回data内数据
		 * 失败抛出异常 */
		static nlohmann::json CheckResult(const std::string& respBody);
	};
}

#endif //LEVER_IEVERAPI_H
