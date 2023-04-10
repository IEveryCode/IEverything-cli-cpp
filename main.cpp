#include <iostream>
#include "utils/coding.hpp"
#include "utils/pop.hpp"
#include "winmain.h"

int main() {
  try{

		Win::Start();

  }catch (std::runtime_error const & e) {
	  MessagePop(0,e.what(),"错误");
    //std::cout << e.what() << std::endl;
  }
  return 0;
}
