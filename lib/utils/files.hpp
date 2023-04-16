
#ifndef LEVER_UTILS_FILES_H
#define LEVER_UTILS_FILES_H
#include <iostream>

namespace Utils::Files{
	typedef unsigned char BYTE_T;

/*!
 * 将文件内容读入到string
 * @param filename 文件名
 * @return 文件数据
 */
	std::string ReadFileToString(const std::string& filename);

/*!
 * 将数据写入文件,不存在时会创建,数据流会覆盖文件原本的内容
 * @param filename 欲写入的文件名
 * @param data 欲写入的数据
 * @throw runtime_error 操作文件错误时会抛出错误信息
 */
	void WriteStringToFile(const std::string& filename,const std::string& data);

	/*!
	 * 将BYTE数组写到文件内,写入方式为覆盖写入,当文件不存在时会自动创建
	 * @param filename 文件名
	 * @param buffer 数组地址
	 * @param len 数据长度
	 * @return 成功返回 true,失败返回false
	 */
	bool WriteByteToFile(const std::string& filename,const BYTE_T* buffer,size_t len);

	/*!
	 * 判断指定文件是否存在
	 * @param filename 欲判断的文件名
	 * @return 当文件存在时返回true
	 */
	bool FileIfExists(const std::string& filename);

}


#endif