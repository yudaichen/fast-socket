/*******************************************************************************
    @file      ipc.cpp
    @brief     unix 进程通讯六种方式
    @details


    @date      26.01.2022
    @copyright © Yu DaiChen , 2022. All right reserved.
*******************************************************************************/

//#ifdef __linux__
#ifndef FAST_SOCKET_TEST_PROCESS_COMMUNICATION_H
#define FAST_SOCKET_TEST_PROCESS_COMMUNICATION_H

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <ctime>
#include <sys/time.h>
#include <sys/wait.h>

/**
 * @brief 无名管道
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
		if ((result = write(fd, "fifo\n", 5) < 0))//写入文件
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

/**
 * @brief 功能：
    设置定时器(闹钟)。 可代替alarm函数。精度微秒us，可以实现周期定时。
参数：
    which：指定定时方式
        a) 自然定时：ITIMER_REAL → 14）SIGALRM计算自然时间
        b) 虚拟空间计时(用户空间)：ITIMER_VIRTUAL → 26）SIGVTALRM  只计算进程占用cpu的时间
        c) 运行时计时(用户 + 内核)：ITIMER_PROF → 27）SIGPROF计算占用cpu及执行系统调用的时间
    new_value：struct itimerval, 负责设定timeout时间
        struct itimerval {
            struct timerval it_interval; // 闹钟触发周期
            struct timerval it_value;    // 闹钟触发时间
        };
        struct timeval {
            long tv_sec;            // 秒
            long tv_usec;           // 微秒
        }
        itimerval.it_value： 设定第一次执行function所延迟的秒数
        itimerval.it_interval：  设定以后每几秒执行function

    old_value： 存放旧的timeout值，一般指定为NULL
返回值：
    成功：0
    失败：-1
 */

void time_linux_start()
{
	struct itimerval new_value = {0};

	//定时周期
	new_value.it_interval.tv_sec = 1;
	new_value.it_interval.tv_usec = 0;

	//第一次触发的时间
	new_value.it_value.tv_sec = 2;
	new_value.it_value.tv_usec = 0;

	signal(SIGALRM, reinterpret_cast<_sig_func_ptr>(start_test_pipe)); //信号处理
	setitimer(ITIMER_REAL, &new_value, NULL); //定时器设置
	sleep(500);
}

// 信号集
/**
 * @note #include <signal.h>

int sigemptyset(sigset_t *set);       //将set集合置空
int sigfillset(sigset_t *set)；          //将所有信号加入set集合
int sigaddset(sigset_t *set, int signo);  //将signo信号加入到set集合
int sigdelset(sigset_t *set, int signo);   //从set集合中移除signo信号
int sigismember(const sigset_t *set, int signo); //判断信号是否存在
 */

void signal_set_start()
{
	sigset_t set;   // 定义一个信号集变量
	int ret = 0; // 返回值

	sigemptyset(&set); // 清空信号集的内容

	// 判断 SIGINT 是否在信号集 set 里
	// 在返回 1， 不在返回 0
	ret = sigismember(&set, SIGINT);
	if (ret == 0)
	{
		printf("SIGINT is not a member of set \nret = %d\n", ret);
	}

	sigaddset(&set, SIGINT); // 把 SIGINT 添加到信号集 set
	sigaddset(&set, SIGQUIT);// 把 SIGQUIT 添加到信号集 set

	// 判断 SIGINT 是否在信号集 set 里
	// 在返回 1， 不在返回 0
	ret = sigismember(&set, SIGINT);
	if (ret == 1)
	{
		printf("SIGINT is a member of set \nret = %d\n", ret);
	}

	sigdelset(&set, SIGQUIT); // 把 SIGQUIT 从信号集 set 移除

	// 判断 SIGQUIT 是否在信号集 set 里
	// 在返回 1， 不在返回 0
	ret = sigismember(&set, SIGQUIT);
	if (ret == 0)
	{
		printf("SIGQUIT is not a member of set \nret = %d\n", ret);
	}
}

// 信号阻塞集也称信号屏蔽集、信号掩码
/**
 * @brief #include <signal.h>

int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
功能：
	 用于改变进程的当前阻塞信号集,也可以用来检测当前进程的信号掩码
    检查或修改信号阻塞集，根据 how 指定的方法对进程的阻塞集合进行修改，新的信号阻塞集由 set 指定，而原先的信号阻塞集合由 oldset 保存。

参数：
    how : 信号阻塞集合的修改方法，有 3 种情况：
        SIG_BLOCK：向信号阻塞集合中添加 set 信号集，新的信号掩码是set和旧信号掩码的并集。相当于 mask = mask|set。
        SIG_UNBLOCK：从信号阻塞集合中删除 set 信号集，从当前信号掩码中去除 set 中的信号。相当于 mask = mask & ~ set。
        SIG_SETMASK：将信号阻塞集合设为 set 信号集，相当于原来信号阻塞集的内容清空，然后按照 set 中的信号重新设置信号阻塞集。相当于mask = set。
    set : 要操作的信号集地址。
        若 set 为 NULL，则不改变信号阻塞集合，函数只把当前信号阻塞集合保存到 oldset 中。
    oldset : 保存原先信号阻塞集地址

返回值：
    成功：0，
    失败：-1，失败时错误代码只可能是 EINVAL，表示参数 how 不合法。
 */

/**
 * @brief
 *
#include <signal.h>

int sigpending(sigset_t *set);
功能：读取当前进程的未决信号集
参数：
    set：未决信号集
返回值：
    成功：0
    失败：-1
 */

[[noreturn]] void signal_process_mask()
{

	// 自定义信号集
	sigset_t myset, old;
	sigemptyset(&myset);// 清空　－》　０

	// 添加要阻塞的信号
	sigaddset(&myset, SIGINT);
	sigaddset(&myset, SIGQUIT);
	sigaddset(&myset, SIGKILL);

	// 自定义信号集设置到内核中的阻塞信号集
	sigprocmask(SIG_BLOCK, &myset, &old);

	sigset_t pend;
	int i = 0;
	while (true)
	{
		// 读内核中的未决信号集的状态
		sigpending(&pend);
		for (int j = 1; j < 32; ++j)
		{
			if (sigismember(&pend, j))
			{
				printf("1");
			} else if (sigismember(&pend, j) == 0)
			{
				printf("0");
			}
		}
		printf("\n");
		sleep(1);
		i++;

		// 10s之后解除阻塞
		if (i > 10)
		{
			// sigprocmask(SIG_UNBLOCK, &myset, NULL);
			sigprocmask(SIG_SETMASK, &old, NULL);
		}
	}
}


void register_signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("recv SIGINT\n");
	} else if (signo == SIGQUIT)
	{
		printf("recv SIGQUIT\n");
	}
}

[[noreturn]] void register_signal_handler_start()
{
	printf("wait for SIGINT OR SIGQUIT\n");

	/* SIGINT: Ctrl+c ; SIGQUIT: Ctrl+\ */
	// 信号注册函数
	signal(SIGINT, register_signal_handler);
	signal(SIGQUIT, register_signal_handler);

	while (true)
	{} //不让程序结束

}

/**
 * @brief 修改信号
 *
 * int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
功能：
    检查或修改指定信号的设置（或同时执行这两种操作）。

参数：
    signum：要操作的信号。
    act：   要设置的对信号的新处理方式（传入参数）。
    oldact：原来对信号的处理方式（传出参数）。

    如果 act 指针非空，则要改变指定信号的处理方式（设置），如果 oldact 指针非空，则系统将此前指定信号的处理方式存入 oldact。

返回值：
    成功：0
    失败：-1


    struct sigaction {
    void(*sa_handler)(int); //旧的信号处理函数指针
    void(*sa_sigaction)(int, siginfo_t *, void *); //新的信号处理函数指针
    sigset_t   sa_mask;      //信号阻塞集
    int        sa_flags;     //信号处理的方式
    void(*sa_restorer)(void); //已弃用
};
 */

/**
 * @brief 信号处理
 */

[[noreturn]] void signal_handle_start()
{
	// 注册信号捕捉函数
	struct sigaction act = {0};
	act.sa_flags = 0;
	act.sa_handler = register_signal_handler;
	// 设置临时屏蔽的信号
	sigemptyset(&act.sa_mask);  // 清空
	// ctrl + 反斜杠
	sigaddset(&act.sa_mask, SIGQUIT);

	sigaction(SIGINT, &act, NULL); //注册信号

	while (true)
	{}
}

/**
 * @brief 给指定进程发信号
 * int sigqueue(pid_t pid, int sig, const union sigval value);
功能：
    给指定进程发送信号。
参数：
    pid : 进程号。
    sig : 信号的编号。
    value : 通过信号传递的参数。
        union sigval 类型如下：
            union sigval
            {
                int   sival_int;
                void *sival_ptr;
            };
返回值：
    成功：0
    失败：-1

 */

void child_process_exit_signal_handler(int signo)
{
	pid_t pid;

	//处理僵尸进程, -1 代表等待任意一个子进程, WNOHANG代表不阻塞
	while ((pid = waitpid(-1, NULL, WNOHANG)) > 0)
	{
		printf("child %d terminated.\n", pid);
	}
}

/**
 * @brief 通过信号回收子进程
 */
void child_process_exit_signal_start()
{
	pid_t pid;

	// 创建捕捉子进程退出信号
	// 只要子进程退出，触发SIGCHLD，自动调用sig_child()
	signal(SIGCHLD, child_process_exit_signal_handler);

	pid = fork();   // 创建进程
	if (pid < 0)
	{ // 出错
		perror("fork error:");
		exit(1);
	} else if (pid == 0)
	{ // 子进程
		printf("I am child process,pid id %d.I am exiting.\n", getpid());
		exit(0);
	} else if (pid > 0)
	{ // 父进程
		sleep(2);   // 保证子进程先运行
		printf("I am father, i am exited\n\n");
		system("ps -ef | grep defunct"); // 查看有没有僵尸进程
	}
}
/**
 * @brief 如果父进程不关心子进程什么时候结束，那么可以用signal（SIGCHLD, SIG_IGN）通知内核，
 * 自己对子进程的结束不感兴趣，父进程忽略此信号，
 * 子进程结束后，内核会回收，并不再给父进程发送信号
 */
void child_process_exit_signal_by_linux_gc_start(){
	pid_t pid;

	// 忽略子进程退出信号的信号
	// 那么子进程结束后，内核会回收， 并不再给父进程发送信号
	signal(SIGCHLD, SIG_IGN);

	pid = fork();   // 创建进程

	if (pid < 0)
	{ // 出错
		perror("fork error:");
		exit(1);
	}
	else if (pid == 0)
	{ // 子进程
		printf("I am child process,pid id %d.I am exiting.\n", getpid());
		exit(0);

	}
	else if (pid > 0)
	{ // 父进程
		sleep(2);   // 保证子进程先运行
		printf("I am father, i am exited\n\n");
		system("ps -ef | grep defunct"); // 查看有没有僵尸进程
	}
}
#endif //FAST_SOCKET_TEST_PROCESS_COMMUNICATION_H
//#endif // __linux__