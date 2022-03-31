/*******************************************************************************
    @file      ipc.cpp
    @brief     unix 进程
    @details

	 头文件：
	 #include <unistd.h>

    @date      26.01.2022
    @copyright © Yu DaiChen , 2022. All right reserved.
*******************************************************************************/
#ifdef __linux__
#ifndef FAST_SOCKET_TEST_PROCESS_H
#define FAST_SOCKET_TEST_PROCESS_H

#include <unistd.h>
#include <wait.h>

/**
 * @note 创建进程的两种方式
 * pid_t fork(void); 通常将原有的进程称为父进程，而通过fork生成的继承称为子进程。
 * 返回值： 若成功调用一次则返回两个值，子进程返回0，父进程返回子进程ID； error: if return -1
 * 使用fork之前的代码都在父进程中执行，而fork之后的代码会在父进程和子进程之间执行
 * 子进程是父进程的副本、拷贝了 进程数据空间、堆、栈等
 *
 * pid_t vfork(void);
 * vfork方法 不完全复制  父进程的数据段，与父进程 共享数据段
 * （调用vfork时，父进程会被挂起，子进程运行完exec函数或者exit的时候才会接触父进程的挂起状态）
 * 父进程停止运行、等子进程退出后或者运行完函数后、继续执行
 * 挂起：挂起进程在操作系统中可以定义为暂时被淘汰出内存的进程
 *
 */
void test_fork()
{
	printf("Test\n");
	pid_t pid; //定义一个进程ID
	pid = fork(); //fork.在fork之前是一个进程运行，而fork之后是两个进程在运行了。
	if (pid < 0)
	{
		printf("fork error!\n");
		exit(1);
	}
	if (pid == 0)
	{
		printf("child process! PID:%d\n", getpid()); //如果pid等于0,子进程,getpid()方法获取当前的进程ID
	} else
	{
		printf("parent process! PID:%d\n", getpid()); //父进程
	}
}

void test_vfork()
{
	printf("Test\n");
	pid_t pid; //定义一个进程ID
	pid = vfork(); //vfork 父进程会被挂起，而子进程结束后才会继续执行父进程
	if (pid < 0)
	{
		printf("fork error!\n");
		exit(1);
	}
	if (pid == 0)
	{
		printf("child process! PID:%d\n", getpid()); //如果pid等于0,子进程,getpid()方法获取当前的进程ID
		exit(1); //父进程会等待子进程结束，子进程调用exit或者exec函数的时候，父进程的挂起状态会解除
	} else
	{
		printf("parent process! PID:%d\n", getpid()); //父进程
	}
}


/**
 * @brief 进程等待
 * #include <sys/types.h>
 * #inculde <sys/wait.h>
 * pid_t wait(int *status);
 *
 * 成功：return 当前等待进程的 PID，失败：返回-1
 *
 * 当参数status不为NULL的时候，可以用下面的宏来解析状态：
 *
 * 	WIFEXITED(status) 如果子进程正常结束则为非 0 值。
 * 	WEXITSTATUS(status) 取得子进程 exit()返回的结束代码,一般会先用 WIFEXITED 来判断是否正常结束才能使用此宏。
 * 	WIFSIGNALED(status) 如果子进程是因为信号而结束则此宏值为真
 * 	WTERMSIG(status) 取得子进程因信号而中止的信号代码,一般会先用 WIFSIGNALED 来判断后才使用此宏。
 * 	WIFSTOPPED(status) 如果子进程处于暂停执行情况则此宏值为真。一般只有使用 WUNTRACED 时才会有此情况。
 * 	WSTOPSIG(status) 取得引发子进程暂停的信号代码,一般会先用 WIFSTOPPED 来判断后才使用此宏。
 */
void check_exit(int status)
{
	if (WIFEXITED(status))
	{
		printf("Wait Success eixt\n");
	} else if (WIFSIGNALED(status))
	{
		printf("killed by signal\n");
	} else if (WIFSTOPPED(status))
	{
		printf("stopped by signal\n");
	} else if (WIFCONTINUED(status))
	{
		printf("continued");
	}
}

void test_wait()
{
	printf("Test\n");
	pid_t pid; //定义一个进程ID
	int status;
	pid = vfork(); //vfork 父进程会被挂起，而子进程结束后才会继续执行父进程
	if (pid < 0)
	{
		printf("fork error!\n");
		exit(1);
	}
	if (pid == 0)
	{
		printf("child process! PID:%d\n", getpid()); //如果pid等于0,子进程,getpid()方法获取当前的进程ID
		exit(1); //父进程会等待子进程结束，子进程调用exit或者exec函数的时候，父进程的挂起状态会解除
	} else
	{
		if (wait(&status) != pid)
		{//等待操作
			printf("wait Error!\n");
			exit(0);
		}
		printf("parent process! PID:%d\n", getpid()); //父进程
		check_exit(status); //检测返回的状态
	}
}


/**
 * @brief 等待进程结束
 * pid_t waitpid(pid_t pid, int *status, int option);
 *
 * 参数说明：pid：
 * pid<-1   等待进程组识别码为 pid 绝对值的任何子进程。
 * pid=-1   等待任何子进程,相当于 wait()。
 * pid=0     等待进程组识别码与目前进程相同的任何子进程。
 * pid>0     等待任何子进程识别码为 pid 的子进程。
 * status：状态
 * option：0 进程挂起，等待其结束
 *
 * WNOHANG 如果没有任何已经结束的子进程则马上返回, 不予以等待。
 * WUNTRACED 如果子进程进入暂停执行情况则马上返回,但结束状态不予以理会。
 * waitpid能指定具体的线程ID，以及可以选择不同的等待方式，所以比wait更加灵活一些
 */
void test_waitpid()
{
	printf("Test\n");
	pid_t pid; //定义一个进程ID
	int status;
	pid = vfork(); //vfork 父进程会被挂起，而子进程结束后才会继续执行父进程
	if (pid < 0)
	{
		printf("fork error!\n");
		exit(1);
	}
	if (pid == 0)
	{
		printf("child process! PID:%d\n", getpid()); //如果pid等于0,子进程,getpid()方法获取当前的进程ID
		exit(1); //父进程会等待子进程结束，子进程调用exit或者exec函数的时候，父进程的挂起状态会解除
	} else
	{
		if (waitpid(-1, &status, 0) != pid)
		{//等待所有子进程，然后主进程挂起状态等待返回
			printf("wait Error!\n");
			exit(0);
		}
		printf("parent process! PID:%d\n", getpid()); //父进程
		check_exit(status); //检测返回的状态
	}
}

/**
 * @brief 进程终止四种方式
 * 1. 常用的c标准进程终止函数
void exit(int status);

2. abort函数退出
发送一个SIGABRT信号使当前的进程终止。
void abort(void)

3. atexit函数退出
用于注册一个不带参数也没有返回值的函数以供程序正常退出时被调用
int atexit(void (* function)(void))

4. on_exit函数退出
和atexit类似，但是不同的是它注册的函数具有参数，退出状态。调用成功返回0，失败返回0-1
int on_exit(void (* function)(int, void*), void *arg)

 */
void test_exit()
{
}

#endif //FAST_SOCKET_TEST_PROCESS_H
#endif //__linux__
