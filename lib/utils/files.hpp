
#ifndef LEVER_UTILS_FILES_H
#define LEVER_UTILS_FILES_H
#include <iostream>
#include <fstream>
#include <sstream>

/*!
 * 将文件内容读入到string
 * @param filename 文件名
 * @return 文件数据
 */
inline std::string ReadFileToString(const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error: could not open file " << filename << std::endl;
		return "";
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

/*!
 * 将数据写入文件,不存在时会创建,数据流会覆盖文件原本的内容
 * @param filename 欲写入的文件名
 * @param data 欲写入的数据
 * @throw runtime_error 操作文件错误时会抛出错误信息
 */
inline void WriteStringToFile(const std::string& filename,const std::string& data){
	std::ofstream outfile(filename, std::ios::out | std::ios::trunc);
	if (!outfile.is_open()) {
		throw std::runtime_error("fail to open file.");
	}
	outfile << data;
	outfile.close();
}

#endif