//
// Created by HuiYi on 2023/4/9.
//

#ifndef LEVER_CONFIG_H
#define LEVER_CONFIG_H

#include "config_row.h"
#include "nlohmann/json.hpp"


namespace Base {
	class Config {
	public:
		static const char* CONFIG_FILENAME;

		/*!
		 * 初始化配置单例,配置方案为
		 * @param fileName json配置文件名
		 * @throw
		 */
		static Config* Initialization(const std::string& fileName);

		/*!
	 * 获取单例
	 * @return 单例指针
	 */
		static Config* GetInstance();

		/*!
		 *
		 * @param fileName  json配置文件名
		 */
		explicit Config(const std::string& fileName);

		/*!
		 * 获取json数据
		 * @return
		 */
		nlohmann::json& GetProtoPtr();

		/*!
	 * 读取配置
	 * @param objName 配置节名称
	 * @param defaultStr 当节不存在时返回的默认文本
	 * @return 返回节内容
	 */
	 template<class T>
		T GetConfig(const std::string& objName,const T& defaultData){
			return m_jsonData.value<T>(objName, defaultData);
		};
		/*!
		 * 读取配置
		 * @param objName 配置节名称
		 * @param defaultStr 当节不存在时返回的默认文本
		 * @return 返回节内容
		 */
		std::string GetConfig(const std::string& objName,const std::string& defaultStr="");

		/*!
		 * 保存配置
		 * 错误处理：如果保存失败，会抛出异常
		 */
		void Save();

	private:
		static Config* m_init;
		nlohmann::json m_jsonData;
	};
}


#endif //LEVER_CONFIG_H
