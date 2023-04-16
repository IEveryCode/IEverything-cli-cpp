//
// Created by HuiYi on 2023/4/10.
//

#ifndef LEVER_CODING_HPP
#define LEVER_CODING_HPP

#include <string>


namespace Utils::Coding {
	/*!
	 * 将ANSI文本转为Unicode文本
	 * @param str ANSI文本
	 * @return 返回转码之后的文本
	 */
	std::wstring A2W(const std::string& str) ;

	/*!
	 * 将Unicode文本转为ANSI文本
	 * @param wstr unicode文本
	 * @return 返回转码之后的文本
	 */
	std::string W2A(const std::wstring& wstr) ;

	/*!
	 * 将UTF8文本转为ANSI文本
	 * @param str UTF8文本
	 * @return 返回转码之后的文本
	 */
	std::string UTF82A(const std::string& str);

}




#endif //LEVER_CODING_HPP
