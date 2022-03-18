#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>

#define MAXLINE 80
#define SERV_PORT 6666

int main(int argc, char *argv[])
{
	struct sockaddr_in serverAddress;
	char buf[MAXLINE];
	int sockFileDescriptor, n;
	char *str;

	if (argc != 2)
	{
		fputs("usage: ./client message\n", stderr);
		exit(1);
	}
	str = argv[1];

	sockFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);
	serverAddress.sin_port = htons(SERV_PORT);

	connect(sockFileDescriptor, (struct sockaddr *) &serverAddress, sizeof(serverAddress));

	write(sockFileDescriptor, str, strlen(str));

	n = read(sockFileDescriptor, buf, MAXLINE);
	printf("Response from server:\n");
	write(STDOUT_FILENO, buf, n);
	close(sockFileDescriptor);
	return 0;


}