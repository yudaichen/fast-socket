# 简单例子
add_executable ( ${APP_NAME} ${CMAKE_SOURCE_DIR}/examples/network/main.cpp ${ALL_SRCS}
                 ${CMAKE_SOURCE_DIR}/examples/network/testLinuxApi/test_thread.hpp
                 ${CMAKE_SOURCE_DIR}/examples/network/testLinuxApi/test_process.hpp
                 ${CMAKE_SOURCE_DIR}/examples/network/testLinuxApi/test_process_communication.hpp
                 ${CMAKE_SOURCE_DIR}/examples/network/testLinuxApi/test_socket.hpp
                 ${CMAKE_SOURCE_DIR}/examples/network/testLinuxApi/test_daemon.hpp )

# 多线程服务端例子
add_executable ( cbServer
                 ${CMAKE_SOURCE_DIR}/examples/network/CAndB/server.cpp )

# 多线程客户端例子
add_executable ( cbClient
                 ${CMAKE_SOURCE_DIR}/examples/network/CAndB/client.cpp )

# 多线程服务端例子
add_executable ( thread_server
                 ${CMAKE_SOURCE_DIR}/examples/network/select/server.cpp
                 ${CMAKE_SOURCE_DIR}/examples/network/wrapError/wrap.h
                 ${CMAKE_SOURCE_DIR}/examples/network/wrapError/wrap.cpp )

# 多线程客户端例子
add_executable ( thread_client
                 ${CMAKE_SOURCE_DIR}/examples/network/select/client.cpp
                 ${CMAKE_SOURCE_DIR}/examples/network/wrapError/wrap.h
                 ${CMAKE_SOURCE_DIR}/examples/network/wrapError/wrap.cpp )