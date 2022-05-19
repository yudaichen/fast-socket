#########################################基于vcpkg构建#######################################################
if (WIN32)
    cmake_minimum_required(VERSION 3.22.1)
else ()
    cmake_minimum_required(VERSION 3.16.3)
endif ()
set(APP_NAME my_test_dev)
project(${APP_NAME})


# 编译优化
option(optimization "compile optimization" ON)

# 子项目编译开关编译
option(MAIN "compile main" ON)
option(DESIGN_PATTERN "compile main" OFF)
option(NETWORK "compile network" OFF)
option(OPEN_CUDA "compile cuda " OFF)

#包含cmake工具包 默认与项目根目录同级
set(FAST_CMAKE_DIR "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${FAST_CMAKE_DIR}")

#包含工具文件
include(utils)

# 此语句等价于 cmake -CMAKE_TOOLCHAIN_FILE = E:/repository/c++/vcpkg-2021.05.12/scripts/buildsystems/vcpkg.cmake
if (WIN32)
    set(CMAKE_TOOLCHAIN_FILE "E:/repository/c++/vcpkg-2021.05.12/scripts/buildsystems/vcpkg.cmake")
    if (DEFINED ENV{VCPKG_DEFAULT_TRIPLET} AND NOT DEFINED VCPKG_TARGET_TRIPLET)
        set(VCPKG_TARGET_TRIPLET "$ENV{VCPKG_DEFAULT_TRIPLET}" CACHE STRING "")
    endif ()
endif ()

if (optimization)

    #c++ 14设置
    #-----------c++ 14 start----------
    # 设置指定的C++编译器版本是必须的，如果不设置，或者为OFF，则指定版本不可用时，会使用上一版>本。
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    # 指定为C++14 版本
    set(CMAKE_CXX_STANDARD 14)
    #-----------c++ 14 end-------------

    # 构建类型
    if (NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Release")
    else ()
        set(CMAKE_BUILD_TYPE "Debug")
    endif ()

    # clang 编译器优化
    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        list(APPEND CXX_FLAGS "-Wno-null-dereference")
        list(APPEND CXX_FLAGS "-Wno-sign-conversion")
        list(APPEND CXX_FLAGS "-Wno-unused-local-typedef")
        list(APPEND CXX_FLAGS "-Wthread-safety")
        list(REMOVE_ITEM CXX_FLAGS "-rdynamic")
    endif ()
    string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

    # 编译优化选项
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g2 -ggdb")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
    #[[set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
    set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)]]
endif ()



if (OPEN_CUDA)

    find_package(CUDA)

    if (${CUDA_FOUND})
        include_directories(${CUDA_INCLUDE_DIRS})
        link_directories($ENV{CUDA_PATH}/lib/x64)
        message(${CUDA_INCLUDE_DIRS})
    else ()
        message(STATUS "cuda not found!")
    endif ()
endif ()

# 链接库
if (WIN32)
    find_package(Boost REQUIRED COMPONENTS system thread filesystem atomic log)
    if (NOT Boost_FOUND)
        message(FATAL_ERROR "Not found Boost")
    else ()
        message(STATUS "boost include path is : ${Boost_INCLUDE_DIR}")
        message(STATUS "boost libraries is : ${BOOST_LIBRARIES}")
        message(STATUS "boost libraries dir is : ${Boost_LIBRARY_DIRS}")

        include_directories(${Boost_INCLUDE_DIRS})
        link_directories(${Boost_LIBRARY_DIR_RELEASE})
        #set ( BOOSTLIBS ${Boost_LIBRARIES} PARENT_SCOPE )
        if (CMAKE_SYSTEM_NAME MATCHES "Windows")
            link_libraries(${BOOSTLIBS})
        elseif (CMAKE_SYSTEM_NAME MATCHES "Linux")
            link_libraries(boost_log boost_system boost_thread boost_filesystem boost_atomic boost_date_time boost_chrono boost_regex)
        endif ()
    endif ()
else ()
    set(BOOST_ROOT "/usr/include/boost")
    #添加头文件搜索路径
    include_directories(/usr/include)
    #添加库文件搜索路径
    #ubuntu
    link_directories(/usr/lib/x86_64-linux-gnu)

    #cygwin
    #link_directories(/usr/lib)
    link_libraries(boost_log boost_system boost_thread boost_filesystem boost_atomic boost_date_time boost_chrono boost_regex glog)
    # 添加其他支持
    link_libraries(pthread dl)
endif ()


if (MAIN)
    # 包含头文件目录
    include_directories(include)

    # 递归包含头文件目录
    include_sub_directories_recursively(${CMAKE_CURRENT_SOURCE_DIR}/include)

    # 整合cpp
    file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)
    file(GLOB_RECURSE INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)

    # 归一化
    set(ALL_SRCS ${SOURCE_FILES} ${INCLUDE_FILES})

    # gcc -c ${CMAKE_SOURCE_DIR}/src/server.cpp ${ALL_SRCS} -o ${name}
    add_executable(${APP_NAME}-server ${CMAKE_SOURCE_DIR}/main/server.cpp ${ALL_SRCS})
    add_executable(${APP_NAME}-client ${CMAKE_SOURCE_DIR}/main/client.cpp ${ALL_SRCS})
    add_executable(${APP_NAME}-test ${CMAKE_SOURCE_DIR}/main/test.cpp ${ALL_SRCS})
endif ()

# 包含设计模式
if (DESIGN_PATTERN)
    include_sub_directories_recursively(${CMAKE_CURRENT_SOURCE_DIR}/examples/designPattern)
    include(designPattern)
endif ()

# 包含网络,网络是linux平台
if (NETWORK)
    if (NOT WIN32)
        include_sub_directories_recursively(${CMAKE_CURRENT_SOURCE_DIR}/examples/network)
        include(network)
    endif ()
endif ()




