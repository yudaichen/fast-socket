file(GLOB_RECURSE WRAP ${CMAKE_SOURCE_DIR}/examples/network/tcp/wrapError/*)

# tcp udp编译开关
set(TCP ON)
set(UDP ON)

if (TCP)
    # 简单例子
    add_executable(sample_examples ${CMAKE_SOURCE_DIR}/examples/network/tcp/main.cpp ${ALL_SRCS}
            ${CMAKE_SOURCE_DIR}/examples/network/tcp/testLinuxApi/test_thread.hpp
            ${CMAKE_SOURCE_DIR}/examples/network/tcp/testLinuxApi/test_process.hpp
            ${CMAKE_SOURCE_DIR}/examples/network/tcp/testLinuxApi/test_process_communication.hpp
            ${CMAKE_SOURCE_DIR}/examples/network/tcp/testLinuxApi/test_socket.hpp
            ${CMAKE_SOURCE_DIR}/examples/network/tcp/testLinuxApi/test_daemon.hpp)

    # 一对一连接
    add_executable(cbServer
            ${CMAKE_SOURCE_DIR}/examples/network/tcp/oneToOne/server.cpp)

    # 一对一连接
    add_executable(cbClient
            ${CMAKE_SOURCE_DIR}/examples/network/tcp/oneToOne/client.cpp)

    # 多线程服务端例子
    add_executable(thread_server
            ${CMAKE_SOURCE_DIR}/examples/network/tcp/select/server.cpp
            ${CMAKE_SOURCE_DIR}/examples/network/tcp/wrapError/wrap.h
            ${CMAKE_SOURCE_DIR}/examples/network/tcp/wrapError/wrap.cpp)

    # 多线程客户端例子
    add_executable(thread_client
            ${CMAKE_SOURCE_DIR}/examples/network/tcp/select/client.cpp
            ${CMAKE_SOURCE_DIR}/examples/network/tcp/wrapError/wrap.h
            ${CMAKE_SOURCE_DIR}/examples/network/tcp/wrapError/wrap.cpp)

    # select
    add_executable(select_client ${WRAP}
            ${CMAKE_SOURCE_DIR}/examples/network/tcp/select/client.cpp
            )

    add_executable(select_server ${WRAP}
            ${CMAKE_SOURCE_DIR}/examples/network/tcp/select/server.cpp
            )

    #epoll
    add_executable(poll_client ${WRAP}
            ${CMAKE_SOURCE_DIR}/examples/network/tcp/poll/client.cpp
            )

    add_executable(poll_server ${WRAP}
            ${CMAKE_SOURCE_DIR}/examples/network/tcp/poll/server.cpp
            )

    #epoll
    add_executable(epoll_client ${WRAP}
            ${CMAKE_SOURCE_DIR}/examples/network/tcp/epoll/client.cpp
            )

    add_executable(epoll_server ${WRAP}
            ${CMAKE_SOURCE_DIR}/examples/network/tcp/epoll/server.cpp
            )

    #edge-triggered 边缘触发 io就绪后，处理一次后，发现没处理完，没有修改状态，系统也不会继续通知
    add_executable(epoll_et_pipeline ${WRAP}
            ${CMAKE_SOURCE_DIR}/examples/network/tcp/epoll_ET/pipelineServer.cpp
            )

    # c/s架构 edge-triggered 边缘触发
    add_executable(epoll_et_server ${WRAP}
            ${CMAKE_SOURCE_DIR}/examples/network/tcp/epoll_ET/server.cpp
            )

    add_executable(epoll_et_client ${WRAP}
            ${CMAKE_SOURCE_DIR}/examples/network/tcp/epoll_ET/client.cpp
            )

    # c/s非阻塞架构 edge-triggered 边缘触发
    add_executable(epoll_ET_non_block_server ${WRAP}
            ${CMAKE_SOURCE_DIR}/examples/network/tcp/epoll_ET_non_block/server.cpp
            )

    add_executable(epoll_ET_non_block_client ${WRAP}
            ${CMAKE_SOURCE_DIR}/examples/network/tcp/epoll_ET_non_block/client.cpp
            )

endif () #TCP

if (UDP)
    #简单udp例子
    add_executable(simple_client ${WRAP}
            ${CMAKE_SOURCE_DIR}/examples/network/udp/simpleCS/client.cpp
            )

    add_executable(simple_server ${WRAP}
            ${CMAKE_SOURCE_DIR}/examples/network/udp/simpleCS/server.cpp
            )

    #组播udp例子
    add_executable(group_client ${WRAP}
            ${CMAKE_SOURCE_DIR}/examples/network/udp/group/client.cpp
            )

    add_executable(group_server ${WRAP}
            ${CMAKE_SOURCE_DIR}/examples/network/udp/group/server.cpp
            )

endif () #UDP
