#include <iostream>
#include "utils/coding.hpp"
#include "utils/pop.hpp"
#include "winmain.h"

int main() {
	try {

		Win::Start();

	} catch (std::runtime_error const &e) {
		Utils::PopFail(0, e.what(), "错误");
	} catch (std::exception const &e) {
		Utils::PopFail(0, e.what(), "错误");
	} catch (...) {
		Utils::PopFail(0, "未经处理的错误", "错误");
	}
	return 0;
}
