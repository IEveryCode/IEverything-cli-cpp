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
		 * 登录后端
		 * @param username
		 * @param passwd
		 */
		void Login(const std::string&username,const std::string&passwd);

	private:
		static IEverAPI* m_ptr;//单例指针
		bool m_ssl=false;//是否启用ssl
		std::string m_host;//服务器地址
	};
}

#endif //LEVER_IEVERAPI_H
