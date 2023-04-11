//
// Created by HuiYi on 2023/4/11.
//

#ifndef LEVER_IEVERAPI_HPP
#define LEVER_IEVERAPI_HPP

//namespace std{
//	class string;
//}

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
		static IEverAPI* Initialization(const char*host);

		IEverAPI(const char*host);

		/*!
		 * 登录后端
		 * @param username
		 * @param passwd
		 */
		void Login(const char*username,const char*passwd);

	private:
		static IEverAPI* m_ptr;
	};
}

#endif //LEVER_IEVERAPI_HPP
