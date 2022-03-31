/*******************************************************************************
    @file      ipc.cpp
    @brief     unix 守护进程以及守护线程
    @details
    @date      26.01.2022
    @copyright © Yu DaiChen , 2022. All right reserved.
*******************************************************************************/

#ifndef FAST_SOCKET_TEST_DAEMON_H
#define FAST_SOCKET_TEST_DAEMON_H

#include <cstring>
#define SIZE 0x100000
/**
 * @brief
 * char *ttyname(int fd);
功能：由文件描述符查出对应的文件名
参数：
    fd：文件描述符
返回值：
    成功：终端名
    失败：NULL
 */
int use_file_fd_get_fileName_start()
{
	/**
	 * @note
	 * 1、 tty
	 tty(终端设备的统称)：tty一词源于teletypes，或者teletypewriters，原来指的是电传打字机，
	 是通过串行线用打印机键盘阅读和发送信息的东西，后来这东西被键盘与显示器取代，
	 所以现在叫终端比较合适。终端是一种字符型设备，它有多种类型，通常使用tty来简称各种类型的终端设备。

	   2、 pty
	   pty（伪终端，虚拟终端)：但是如果我们远程telnet到主机或使用xterm时不也需要一个终端交互么？
	   是的，这就是虚拟终端pty(pseudo-tty)

	   3、 pts/ptmx
	   pts/ptmx(pts/ptmx结合使用，进而实现pty)：pts(pseudo-terminal slave)是pty的实现方法，
	   与ptmx(pseudo-terminal master)配合使用实现pty。
	 */
	printf("fd 0: %s\n", ttyname(0));
	printf("fd 1: %s\n", ttyname(1));
	printf("fd 2: %s\n", ttyname(2));

	return 0;
}

/*
* time_t rawtime;
* time ( &rawtime  ); --- 获取时间，以秒计，从1970年1月一日起算，存于rawtime
* localtime ( &rawtime  ); //转为当地时间，tm 时间结构
* asctime() // 转为标准ASCII时间格式：
*/
void write_time(int num)
{
	time_t rawtime;
	struct tm *timeinfo;
	// 获取时间
	time(&rawtime);
#if 0
	// 转为本地时间
	timeinfo = localtime(&rawtime);
	// 转为标准ASCII时间格式
	char *cur = asctime(timeinfo);
#else
	char *cur = ctime(&rawtime);
#endif

	// 将得到的时间写入文件中
	int fd = open("/home/25007/timelog.txt", O_RDWR | O_CREAT | O_APPEND, 0664);
	if (fd == -1)
	{
		perror("open error");
		exit(1);
	}
	// 写文件
	int ret = write(fd, cur, strlen(cur) + 1);
	if (ret == -1)
	{
		perror("write error");
		exit(1);
	}
	// 关闭文件
	close(fd);
}

void test_daemon_start()
{
	pid_t pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		exit(1);
	}

	if (pid > 0)
	{
		// 父进程退出
		exit(1);
	} else if (pid == 0)
	{
		// 子进程
		// 提升为会长，同时也是新进程组的组长
		setsid();

		// 更改进程的执行目录
		chdir("/home/25007");

		// 更改掩码
		umask(0022);

		// 关闭文件描述符
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);

		// 注册信号捕捉函数
		//先注册，再定时
		struct sigaction sigact = {0};
		sigact.sa_flags = 0;
		sigemptyset(&sigact.sa_mask);
		sigact.sa_handler = write_time;
		sigaction(SIGALRM, &sigact, NULL);

		// 设置定时器
		struct itimerval act = {0};
		// 定时周期
		act.it_interval.tv_sec = 2;
		act.it_interval.tv_usec = 0;
		// 设置第一次触发定时器时间
		act.it_value.tv_sec = 2;
		act.it_value.tv_usec = 0;
		// 开始计时
		setitimer(ITIMER_REAL, &act, NULL);

		// 防止子进程退出
		while (true);
	}
}

/**
 * @brief 获取线程号 、待判断的线程号
 * 、#include <pthread.h>

pthread_t pthread_self(void);
功能：获取线程号
    。
参数：
    无
返回值：
    调用线程的线程 ID 。

 int pthread_equal(pthread_t t1, pthread_t t2);
功能：
    判断线程号 t1 和 t2 是否相等。为了方便移植，尽量使用函数来比较线程 ID。
参数：
    t1，t2：待判断的线程号。
返回值：
    相等：  非 0
    不相等：0

 */
void  get_threadId_and_equal_start(){
	pthread_t thread_id;

	thread_id = pthread_self(); // 返回调用线程的线程ID
	printf("Thread ID = %lu \n", thread_id);

	if (0 != pthread_equal(thread_id, pthread_self()))
	{
		printf("Equal!\n");
	}
	else
	{
		printf("Not equal!\n");
	}
}

[[noreturn]] void *th_fun(void *arg)
{
	while (true)
	{
		sleep(1);
	}
}

/**
 * @brief 线程创建 、线程资源回收、线程与当前进程分离、退出线程、杀死(取消)线程
 *
 * #include <pthread.h>

	int pthread_create(pthread_t *thread,
            const pthread_attr_t *attr,
            void *(*start_routine)(void *),
            void *arg );
功能：
    创建一个线程。
参数：
    thread：线程标识符地址。
    attr：线程属性结构体地址，通常设置为 NULL。
    start_routine：线程函数的入口地址。
    arg：传给线程函数的参数。
返回值：
    成功：0
    失败：非 0



    int pthread_join(pthread_t thread, void **retval);
功能：
    等待线程结束（此函数会阻塞），并回收线程资源，类似进程的 wait() 函数。如果线程已经结束，那么该函数会立即返回。
参数：
    thread：被等待的线程号。
    retval：用来存储线程退出状态的指针的地址。
返回值：
    成功：0
    失败：非 0


    int pthread_detach(pthread_t thread);
功能：
    使调用线程与当前进程分离，分离后不代表此线程不依赖与当前进程，线程分离的目的是将线程资源的回收工作交由系统自动来完成，也就是说当被分离的线程结束之后，系统会自动回收它的资源。所以，此函数不会阻塞。
参数：
    thread：线程号。
返回值：
    成功：0
    失败：非0


    void pthread_exit(void *retval);
功能：
    退出调用线程。一个进程中的多个线程是共享该进程的数据段，因此，通常线程退出后所占用的资源并不会释放。
参数：
    retval：存储线程退出状态的指针。
返回值：无


 #include <pthread.h>

int pthread_cancel(pthread_t thread);
功能：
    杀死(取消)线程
参数：
    thread : 目标线程ID。
返回值：
    成功：0
    失败：出错编号
 */

void thread_create_start(){
	pthread_t tid;
	int err, detachstate, i = 1;

	pthread_attr_t attr;
	size_t stacksize;
	void *stackaddr;

	pthread_attr_init(&attr);  //线程属性初始化
	pthread_attr_getstack(&attr, &stackaddr, &stacksize); //获取线程的栈地址
	pthread_attr_getdetachstate(&attr, &detachstate);           //获取线程分离状态

	if (detachstate == PTHREAD_CREATE_DETACHED)
	{
		printf("thread detached\n");
	}
	else if (detachstate == PTHREAD_CREATE_JOINABLE)
	{
		printf("thread join\n");
	}
	else
	{
		printf("thread unknown\n");
	}

	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); //设置分离状态

	while (true)
	{
		stackaddr = malloc(SIZE);
		if (stackaddr == NULL)
		{
			perror("malloc");
			exit(1);
		}

		stacksize = SIZE;
		pthread_attr_setstack(&attr, stackaddr, stacksize); //设置线程的栈地址
		err = pthread_create(&tid, &attr, th_fun, NULL); //创建线程
		if (err != 0)
		{
			printf("%s\n", strerror(err));
			exit(1);
		}
		printf("%d\n", i++);
	}

	pthread_attr_destroy(&attr); //销毁线程属性所占用的资源函数

	return;
}
#endif //FAST_SOCKET_TEST_DAEMON_H
