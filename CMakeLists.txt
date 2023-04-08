cmake_minimum_required(VERSION 3.25)
project(lEver)

# C++17规范
set(CMAKE_CXX_STANDARD 17)

# 设置引用库
include_directories(src/client/ws)
include_directories( lib )
file(GLOB SOURCES src/client/ws/*.cpp)

# 链接库

if(CMAKE_HOST_UNIX)
    # UNIX
elseif(CMAKE_HOST_WIN32)
    # WINDOWS
    LINK_LIBRARIES(-lws2_32)
else()
    # 未进行兼容测试的系统
endif()

# 编译文件
add_executable(lEver ${SOURCES} main.cpp)

