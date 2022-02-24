/*******************************************************************************
    @file      ipc.cpp
    @brief     unix 进程通讯六种方式
    @details


    @date      26.01.2022
    @copyright © Yu DaiChen , 2022. All right reserved.
*******************************************************************************/

#ifdef __linux__
#ifndef FAST_SOCKET_TEST_PROCESS_COMMUNICATION_H
#define FAST_SOCKET_TEST_PROCESS_COMMUNICATION_H

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

/**
 * @brief 管道
 * int pipe(int pipe[2]);
 * pipe[0]是读取数据的描述字
 * pipe[1]是写数据的描述字
 *
 * 管道pipe只能用于两个进程间的通信，而且两个进程需要有同源性，必须由同一个进程所派生出来的
 */
void start_test_pipe()
{
	printf("Test\n");
	pid_t pid; //定义一个进程ID
	char buf[1024]; //容器
	int fd[2]; //其中fd[0]是读取数据的描述字，fd[1]是写数据的描述字
	if (pipe(fd) < 0)
	{
		printf("pipe erroe!");
		exit(1);
	}
	pid = fork(); //创建一个进程
	if (pid < 0)
	{
		printf("fork error!\n");
		exit(1);
	}
	if (pid == 0)
	{
		printf("child process! PID:%d\n", getpid()); //如果pid等于0,子进程,getpid()方法获取当前的进程ID
		close(fd[0]);
		const char *x = "pipe hello!\n";
		ssize_t result;
		if ((result = write(fd[1], x, 12) < 0))//写入一个字符串
		{
			printf("write error");
		}
	} else
	{
		printf("parent process! PID:%d\n", getpid()); //父进程
		close(fd[1]);
		int c;
		ssize_t result;
		while ((result = read(fd[0], &c, 1)) > 0)
		{ //等待读取pipe管道中的数据
			putchar(c);
		}
	}
}

/**
 * @brief 命名管道
 *
 * 头文件：
 *  #include <sys/types.h>
    #include <sys/stat.h>
    int mkfifo(const char *filename, mode_t mode);
    int mknod(const char *filename, mode_t mode | S_IFIFO, (dev_t)0);
	filename：是存放管道的名称
	mode：用于指定创建文件的权限。
	如果调用成功，返回0；否则返回-1

 打开文件的四种方式
	open(const char *path, O_RDONLY);//1
	open(const char *path, O_RDONLY | O_NONBLOCK);//2
	open(const char *path, O_WRONLY);//3
	open(const char *path, O_WRONLY | O_NONBLOCK);//4
 */
void start_test_haveName_pipe()
{
	printf("Test\n");
	pid_t pid; //定义一个进程ID
	pid = fork(); //创建一个进程
	if (pid < 0)
	{
		printf("fork error!\n");
		exit(1);
	}
	if (pid == 0)
	{
		printf("child process! PID:%d\n", getpid()); //如果pid等于0,子进程,getpid()方法获取当前的进程ID
		int res = mkfifo("hello1", 0666); //创建一个FIFO管道
		if (res != 0)
		{
			printf("mkfifo error!");
			exit(1);
		}
		int fd = -1;
		fd = open("hello", O_WRONLY); //打开文件，可写模式
		if (fd < 0)
		{
			printf("open file error!");
			exit(1);
		}
		ssize_t result;
		if ((result = write(fd, "fifo\n", 5)< 0))//写入文件
		{
			printf("write error\n");
		}
	} else
	{
		sleep(5); //等待5秒
		printf("parent process! PID:%d\n", getpid()); //父进程
		//读取fifo管道数据
		char x[1024];
		int len;
		int fd = open("hello", O_RDONLY); //读取fifo管道
		if (fd < 0)
		{
			printf("open file error!");
			exit(1);
		}
		while ((len = read(fd, x, 5) > 0))
		{
			printf("%s", x);
		}
	}
}

#endif //FAST_SOCKET_TEST_PROCESS_COMMUNICATION_H
#endif // __linux__