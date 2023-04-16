//
// Created by HuiYi on 2023/4/16.
//
#include "files.hpp"
#include <fstream>
#include <sstream>

namespace Utils::Files{

/*!
 * 将文件内容读入到string
 * @param filename 文件名
 * @return 文件数据
 */
	std::string ReadFileToString(const std::string& filename) {
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
void WriteStringToFile(const std::string& filename,const std::string& data){
		std::ofstream outfile(filename, std::ios::out | std::ios::trunc);
		if (!outfile.is_open()) {
			throw std::runtime_error("fail to open file.");
		}
		outfile << data;
		outfile.close();
	}

	/*!
	 * 将BYTE数组写到文件内,写入方式为覆盖写入,当文件不存在时会自动创建
	 * @param filename 文件名
	 * @param buffer 数组地址
	 * @param len 数据长度
	 * @return 成功返回 true,失败返回false
	 */
	bool WriteByteToFile(const std::string& filename,const BYTE_T* buffer,size_t len){
		std::ofstream output(filename,  std::ios::out | std::ios::binary);
		if (!output.is_open()) { // 检查文件是否打开成功
			return false;
		}
		output.write(reinterpret_cast<const char*>(buffer), std::streamsize(len));
		if (output.fail()) { // 检查写入是否出错
			output.close();
			return false;
		}
		output.close();
		return true;
	}

	/*!
	 * 判断指定文件是否存在
	 * @param filename 欲判断的文件名
	 * @return 当文件存在时返回true
	 */
	bool FileIfExists(const std::string& filename){
		std::ifstream file(filename);
		return file.good();
	}

}