cmake_minimum_required(VERSION 3.25)
project(lEver)

# C++17规范
set(CMAKE_CXX_STANDARD 17)

# 设置引用库
include_directories(src/client/ws)
include_directories( lib )
# 导入cpp源文件
file(GLOB_RECURSE SOURCES_SRC src/*.cpp)
file(GLOB_RECURSE SOURCES_LIB lib/*.cpp)
# 链接源文件表
SET( SOURCE_DATA ${SOURCES_SRC} ${SOURCES_LIB})

# 链接库
if(CMAKE_HOST_UNIX)
    # UNIX
elseif(CMAKE_HOST_WIN32)
    # WINDOWS

    # 在gcc/g++或ld中加上这个参数, 就可以不用libgcc_s_dw2-1.dll
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc")
    # 在g++或ld中加上这个参数, 就可以不用libstdc++-6.dll
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++")
    # 在gcc/g++或ld中加上这个参数, 對所有的库都会采用静态链接的方式
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

    # lib搜索路径
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        # 64-bit
        link_directories(src/UI/Win/lib/x64)
    else()
        # 32-bit
        link_directories(src/UI/Win/lib/x86)
    endif()

    # 链接win库
    LINK_LIBRARIES(-lws2_32)
    LINK_LIBRARIES(-lXCGUI)

    # 导入头
    include_directories(src/UI/Win)
    # 导入cpp代码源
    file(GLOB_RECURSE SOURCES_WIN src/UI/Win/*.cpp)
    file(GLOB_RECURSE SOURCES_WIN_LIB src/UI/Win/lib/*.cpp)
    SET( SOURCE_DATA ${SOURCE_DATA} ${SOURCES_WIN} ${SOURCES_WIN_LIB})


else()
    # 未进行兼容测试的系统
endif()


# 编译代码
add_executable(lEver ${SOURCE_DATA} main.cpp)

# 编译后事件
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    # 64-bit
    if(CMAKE_HOST_UNIX)
        # UNIX
    elseif(CMAKE_HOST_WIN32)
        # windows

    else()
        # 未进行兼容测试的系统
    endif()

else()
    # 32-bit

endif()

