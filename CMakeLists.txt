cmake_minimum_required(VERSION 3.25)
project(lEver)

# C++17规范
set(CMAKE_CXX_STANDARD 17)

# 设置引用库

include_directories(lib)
include_directories(src/client)
include_directories(src/base)
include_directories( lib )
# 导入cpp源文件
file(GLOB_RECURSE SOURCES_SRC src/*.cpp)
file(GLOB_RECURSE SOURCES_LIB lib/*.cpp)
# 链接源文件表
SET( SOURCE_DATA ${SOURCES_SRC} ${SOURCES_LIB})


# 链接库
# ===================icu=========================
#LINK_LIBRARIES(
#        -licuuc
#        -licuio
#        -licuin
#        -licudt
#        -licutu
#)
# data, i18n, io, le, lx, test, tu and uc
# find_package(ICU REQUIRED data)
# target_link_libraries(lEver ${ICU_LIBRARIES})
# ===================icu=========================
# ===================boost=========================
find_package(Boost REQUIRED COMPONENTS
        # regex
        filesystem
        )
if(NOT Boost_FOUND)
    message("Not found Boost")
endif ()
include_directories(${Boost_INCLUDE_DIRS})

# ===================boost=========================

if(CMAKE_HOST_UNIX)
    # UNIX
elseif(CMAKE_HOST_WIN32)
    # WINDOWS
    # 解决中文乱码
    add_compile_options(-fexec-charset=GBK -finput-charset=UTF-8)
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
# target_compile_definitions(lEver PRIVATE _UNICODE UNICODE)
target_link_libraries(lEver ${Boost_LIBRARIES})

# 编译后事件
if(CMAKE_HOST_UNIX)
    # UNIX
elseif(CMAKE_HOST_WIN32)
    # windows

    # resource.res
    add_custom_command(TARGET lEver POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/src/UI/Win/lib/res/resource.res
            ${CMAKE_BINARY_DIR}/res/resource.res
            COMMENT "Copying login.xml to build directory"
            )
    # login.xml
    add_custom_command(TARGET lEver POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/src/UI/Win/lib/res/login.xml
            ${CMAKE_BINARY_DIR}/res/login.xml
            COMMENT "Copying login.xml to build directory"
            )
else()
    # 未进行兼容测试的系统
endif()

