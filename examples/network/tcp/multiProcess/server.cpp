/*******************************************************************************
    @file      client.cpp
    @brief     多进程并发模型  服务端
    @details


 使用多进程并发服务器时要考虑以下几点：
1.父进程最大文件描述个数(父进程中需要close关闭accept返回的新文件描述符)
2.系统内创建进程个数(与内存大小相关)
3.进程创建过多是否降低整体服务性能(进程调度)

    @date      26.01.2022
    @copyright © Yu DaiChen , 2022. All right reserved.
*******************************************************************************/

/* server.c */
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h>
#include "wrap.h"

#define MAX_LINE 1024
#define SERV_PORT 8080

void do_sigchild(int num)
{
	while (waitpid(0, NULL, WNOHANG) > 0)
	{}
}

int main(void)
{
	struct sockaddr_in servaddr, cliaddr;
	socklen_t cliaddr_len;
	int listenfd, connfd;
	char buf[MAX_LINE];
	char str[INET_ADDRSTRLEN];
	int i, n;
	pid_t pid;

	struct sigaction newact;
	newact.sa_handler = do_sigchild;
	sigemptyset(&newact.sa_mask);
	newact.sa_flags = 0;
	sigaction(SIGCHLD, &newact, NULL);

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	Bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	Listen(listenfd, 20);

	printf("Accepting connections ...\n");
	while (1)
	{
		cliaddr_len = sizeof(cliaddr);
		connfd = Accept(listenfd, (struct sockaddr *) &cliaddr, &cliaddr_len);

		pid = fork();
		if (pid == 0)
		{
			Close(listenfd);
			while (1)
			{
				n = Read(connfd, buf, MAX_LINE);
				if (n == 0)
				{
					printf("the other side has been closed.\n");
					break;
				}
				printf("received from %s at PORT %d\n",
				       inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),
				       ntohs(cliaddr.sin_port));
				for (i = 0; i < n; i++)
				{
					buf[i] = toupper(buf[i]);
				}
				Write(connfd, buf, n);
			}
			Close(connfd);
			return 0;
		} else if (pid > 0)
		{
			Close(connfd);
		} else
		{
			perr_exit("fork");
		}
	}
	Close(listenfd);
	return 0;
}