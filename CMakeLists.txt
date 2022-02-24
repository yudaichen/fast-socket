#########################################基于vcpkg构建#######################################################
if ( WIN32 )
	cmake_minimum_required ( VERSION 3.22.1 )
else ()
	cmake_minimum_required ( VERSION 3.16.3 )
endif ()
set ( APP_NAME fastSocket )
project ( ${APP_NAME} )
# 构建类型
set ( CMAKE_BUILD_TYPE "RELEASE" )

# 此语句等价于 cmake -CMAKE_TOOLCHAIN_FILE = E:/repository/c++/vcpkg-2021.05.12/scripts/buildsystems/vcpkg.cmake
if ( WIN32 )
	set ( CMAKE_TOOLCHAIN_FILE "E:/repository/c++/vcpkg-2021.05.12/scripts/buildsystems/vcpkg.cmake" )
	if ( DEFINED ENV{VCPKG_DEFAULT_TRIPLET} AND NOT DEFINED VCPKG_TARGET_TRIPLET )
		set ( VCPKG_TARGET_TRIPLET "$ENV{VCPKG_DEFAULT_TRIPLET}" CACHE STRING "" )
	endif ()
endif ()


#c++ 14设置
set ( CMAKE_CXX_STANDARD 14 )
if ( CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang" )
	message ( "-std=c++14" )
	set ( CMAKE_CXX_FLAGS "-std=c++14 $ENV{CXXFLAGS}" )
	if ( CMAKE_BUILD_TYPE MATCHES "DEBUG|Debug|debug" )
		set ( CMAKE_CXX_FLAGS_DEBUG "-O0 -Wall -g2 -ggdb" )
	endif ()
	find_package ( OpenMP REQUIRED )
	if ( OPENMP_FOUND )
		message ( "OPENMP FOUND" )
		set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}" )
		set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}" )
		set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS} " )
		set ( CMAKE_SHARE_LINKER_FLAGS "${CMAKE_SHARE_LINKER_FLAGS} ${OpenMP_SHARE_LINKER_FLAGS}" )
	endif ()
else ()
	if ( CMAKE_SYSTEM_NAME MATCHES "Windows" )
		set ( my_std_pre "/std:" )
	else ()
		set ( my_std_pre "-std=14" )
	endif ()

	set ( basic_cxx14 "c++14" )
	set ( str_cxx14 "${my_std_pre}${basic_cxx14}" )

	include ( CheckCXXCompilerFlag )
	check_cxx_compiler_flag ( "${str_cxx14}" _cpp_14_flag_supported )
	if ( _cpp_14_flag_supported )
		set ( CMAKE_CXX_STANDARD 14 )
	endif ()

endif ()


# 包含头文件目录
include_directories ( include )
include_directories ( src )
include_directories ( test )

# 用于递归添加头文件
function ( include_sub_directories_recursively root_dir )

	if ( IS_DIRECTORY ${root_dir} )   # 当前路径是一个目录吗，是的话就加入到包含目录
		#MESSAGE("CURRENT DIR PATH: " ${root_dir})
		#屏蔽一些特殊目录
		if ( NOT ( ${root_dir} MATCHES ".vscode|.vs|release" ))
			#MESSAGE("include dir: " ${root_dir})
			include_directories ( ${root_dir} )
		endif ()
	endif ()

	file ( GLOB ALL_SUB RELATIVE ${root_dir} ${root_dir}/* ) # 获得当前目录下的所有文件，让如ALL_SUB列表中
	foreach ( sub ${ALL_SUB} )
		if ( IS_DIRECTORY ${root_dir}/${sub} )
			include_sub_directories_recursively ( ${root_dir}/${sub} ) # 对子目录递归调用，包含
		endif ()
	endforeach ()
endfunction ()

include_sub_directories_recursively ( ${CMAKE_CURRENT_SOURCE_DIR}/include )
file ( GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp )
file ( GLOB_RECURSE INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp )

set ( ALL_SRCS ${SOURCE_FILES} ${INCLUDE_FILES} )

if ( WIN32 )
	find_package ( Boost REQUIRED COMPONENTS system thread filesystem atomic log )
	if ( NOT Boost_FOUND )
		message ( FATAL_ERROR "Not found Boost" )
	else ()
		message ( STATUS "boost include path is : ${Boost_INCLUDE_DIR}" )
		message ( STATUS "boost libraries is : ${BOOST_LIBRARIES}" )
		message ( STATUS "boost libraries dir is : ${Boost_LIBRARY_DIRS}" )

		include_directories ( ${Boost_INCLUDE_DIRS} )
		link_directories ( ${Boost_LIBRARY_DIR_RELEASE} )
		set ( BOOSTLIBS ${Boost_LIBRARIES} PARENT_SCOPE )
		if ( CMAKE_SYSTEM_NAME MATCHES "Windows" )
			link_libraries ( ${BOOSTLIBS} )
		elseif ( CMAKE_SYSTEM_NAME MATCHES "Linux" )
			link_libraries ( boost_log boost_system boost_thread boost_filesystem boost_atomic boost_date_time boost_chrono boost_regex )
		endif ()
	endif ()
else ()
	set ( BOOST_ROOT "/usr/include/boost" )
	#添加头文件搜索路径
	include_directories ( /usr/include )
	#添加库文件搜索路径
	link_directories ( /usr/lib/x86_64-linux-gnu )
	link_libraries ( boost_log boost_system boost_thread boost_filesystem boost_atomic boost_date_time boost_chrono boost_regex )
endif ()

# 添加其他支持
link_libraries(pthread)

add_executable ( ${APP_NAME} ${CMAKE_SOURCE_DIR}/examples/main.cpp ${ALL_SRCS}
                 ${CMAKE_SOURCE_DIR}/examples/test_thread.hpp
                 ${CMAKE_SOURCE_DIR}/examples/test_process.hpp
                 ${CMAKE_SOURCE_DIR}/examples/test_process_communication.hpp
                 ${CMAKE_SOURCE_DIR}/examples/test_socket.hpp)


install ( TARGETS ${APP_NAME}
          RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}
          )