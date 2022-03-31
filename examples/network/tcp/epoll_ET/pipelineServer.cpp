#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <unistd.h>

#define MAXLINE 10

#ifndef CLANG_TIDY
int main(int argc, char *argv[])
{
	int efd, i;
	int pfd[2];
	pid_t pid;
	char buf[MAXLINE], ch = 'a';

	pipe(pfd);
	pid = fork();
	if (pid == 0) {
		close(pfd[0]);
		while (true) {
			for (i = 0; i < MAXLINE/2; i++)
				buf[i] = ch;
			buf[i-1] = '\n';
			ch++;

			for (; i < MAXLINE; i++)
				buf[i] = ch;
			buf[i-1] = '\n';
			ch++;

			write(pfd[1], buf, sizeof(buf));
			sleep(2);
		}
		close(pfd[1]);
	} else if (pid > 0) {
		struct epoll_event event ={0};
		struct epoll_event reEvent[10];
		int res, len;
		close(pfd[1]);

		efd = epoll_create(10);
		/* event.events = EPOLLIN; */
		event.events = EPOLLIN | EPOLLET;		/* ET 边沿触发 ，默认是水平触发 */
		event.data.fd = pfd[0];
		epoll_ctl(efd, EPOLL_CTL_ADD, pfd[0], &event);

		while (true) {
			res = epoll_wait(efd, reEvent, 10, -1);
			printf("res %d\n", res);
			if (reEvent[0].data.fd == pfd[0]) {
				len = read(pfd[0], buf, MAXLINE/2);
				write(STDOUT_FILENO, buf, len);
			}
		}
		close(pfd[0]);
		close(efd);
	} else {
		perror("fork");
		exit(-1);
	}
	return 0;
}
#endif