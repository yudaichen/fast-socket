/*******************************************************************************
    @file      client.cpp
    @brief     多进程并发模型  客户端
    @details

    @date      26.01.2022
    @copyright © Yu DaiChen , 2022. All right reserved.
*******************************************************************************/

/* client.c */
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

int main(int argc, char *argv[])
{
	struct sockaddr_in servaddr;
	char buf[MAX_LINE];
	int sockfd, n;

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
	servaddr.sin_port = htons(SERV_PORT);

	Connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	while (fgets(buf, MAX_LINE, stdin) != NULL) {
		Write(sockfd, buf, strlen(buf));
		n = Read(sockfd, buf, MAX_LINE);
		if (n == 0) {
			printf("the other side has been closed.\n");
			break;
		} else
			Write(STDOUT_FILENO, buf, n);
	}
	Close(sockfd);
	return 0;
}