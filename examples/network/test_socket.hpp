/*******************************************************************************
    @file      test_socket.hpp
    @brief     unix 进程
    @details

    @date      22.02.2022
    @copyright © Yu DaiChen , 2022. All right reserved.
*******************************************************************************/
#ifdef __linux__
#ifndef FAST_SOCKET_TEST_SOCKET_H
#define FAST_SOCKET_TEST_SOCKET_H


#include <sys/types.h>
#include <sys/socket.h>
#include <cstdio>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <fcntl.h>
#include <sys/shm.h>
#include <iostream>
#include <thread>
#include <list>

#define PORT 7000
#define IP "127.0.0.1"

int s;

struct sockaddr_in servaddr;

socklen_t len;

std::list<int> li;//用list来存放套接字，没有限制套接字的容量就可以实现一个server跟若干个client通信

[[noreturn]] void getConn()
{
	while (true)
	{
		int conn = accept(s, (struct sockaddr *) &servaddr, &len);
		li.push_back(conn);
		printf("%d\n", conn);
	}
}

[[noreturn]] void getData()
{
	struct timeval tv{};
	tv.tv_sec = 10;//设置倒计时时间
	tv.tv_usec = 0;
	while (true)
	{
		std::list<int>::iterator it;
		for (it = li.begin(); it != li.end(); ++it)
		{
			fd_set rfds;
			FD_ZERO(&rfds);
			int maxfd = 0;
			int retval = 0;
			FD_SET(*it, &rfds);
			if (maxfd < *it)
			{
				maxfd = *it;
			}
			retval = select(maxfd + 1, &rfds, NULL, NULL, &tv);
			if (retval == -1)
			{
				printf("select error\n");
			} else if (retval == 0)
			{
				//printf("not message\n");
			} else
			{
				char buf[1024];
				memset(buf, 0, sizeof(buf));
				int len = recv(*it, buf, sizeof(buf), 0);
				printf("%s", buf);
			}
		}
		sleep(1);

	}
}

[[noreturn]] void sendMess()
{
	while (true)
	{
		char buf[1024];
		fgets(buf, sizeof(buf), stdin);
		printf("you are send %s", buf);
		std::list<int>::iterator it;
		for (it = li.begin(); it != li.end(); ++it)
		{
			send(*it, buf, sizeof(buf), 0);
		}
	}
}

[[noreturn]] void start_test_socket()
{
	//new socket
	s = socket(AF_INET, SOCK_STREAM, 0);
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = inet_addr(IP);
	if (bind(s, (struct sockaddr *) &servaddr, sizeof(servaddr)) == -1)
	{
		perror("bind");
		exit(1);
	}
	if (listen(s, 20) == -1)
	{
		perror("listen");
		exit(1);
	}
	len = sizeof(servaddr);

	//thread : while ==>> accpet
	std::thread t(getConn);
	t.detach();//detach的话后面的线程不同等前面的进程完成后才能进行，如果这里改为join则前面的线程无法判断结束，就会
	//一直等待，导致后面的线程无法进行就无法实现操作
	//printf("done\n");
	//thread : input ==>> send
	std::thread t1(sendMess);
	t1.detach();
	//thread : recv ==>> show
	std::thread t2(getData);
	t2.detach();
	int i = 0;
	while (true)//做一个死循环使得主线程不会提前退出
	{
		std::cout << i++ << std::endl;
	}
}
/*这个跟前面的不一样的地方是，把获得连接套接字getConn和发送信息sendMess和接收信息getData放在三个函数中，创建
的三个线程分别对应处理三个函数，就可以使得server能跟若干个client通信*/

#endif //FAST_SOCKET_TEST_SOCKET_H
#endif // __linux__