//
// Created by HuiYi on 2023/4/11.
//

#ifndef LEVER_IEVERAPI_H
#define LEVER_IEVERAPI_H

#include <string>

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
		static IEverAPI* Initialization(const std::string&host);

		IEverAPI(const std::string&host);

		/*!
		 * 用户登录
		 * @param username 用户名
		 * @param passwd    密码
		 */
		void Login(const std::string&username,const std::string&passwd);

	private:
		static IEverAPI* m_ptr;//单例指针

		bool m_ssl=false;//是否启用ssl
		std::string m_host;//服务器地址
        int m_port=80;//服务器端口

        std::string m_token;//登录token
        std::string m_refreshToken;//刷新token

        std::string GetUrl();
	};
}

#endif //LEVER_IEVERAPI_H
