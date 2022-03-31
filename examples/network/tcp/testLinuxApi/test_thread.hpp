/*******************************************************************************
    @file      ipc.cpp
    @brief     unix 多线程与锁
    @details

    1、创建线程
	    int pthread_create(pthread_t  *  thread, pthread_attr_t * attr, void * (*start_routine)(void *),void * arg)

		参数：
			thread：返回创建的线程的ID
			attr：线程属性，调度策略、优先级等都在这里设置，如果为NULL则表示用默认属性
			start_routine：线程入口函数，可以返回一个void*类型的返回值，该返回值可由pthread_join()捕获
			arg：传给start_routine的参数，可以为NULL
			返回值：创建线程成功为0


 	2、线程调度模式设置API

	    线程调度策略三种：
			SCHED_OTHER：非实时、正常
			SCHED_RR：实时、轮询法
			SCHED_FIFO：实时、先入先出，与vxworks的调度机制一致
	    pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setschedpolicy(&attr, SCHED_FIFO);

	3、 线程等待API
		pthread_join(pthread_t id, void **ret)

		参数：
		id : 线程ID
		ret：可以设置为NULL
		说明：使用了pthread_join后，会线程等待，直到等待的线程执行完毕之后 当前线程才会执行

	4、 线程终止API
 		pthread_exit(void *ret);
			线程终止有三种方法：
			当前线程的函数中有return进行返回，则结束，一般用的最多
			调用了pthread_exit(void *ret) 线程终止方法，则终止
			被同一进程中的其他线程取消

	5、mutex互斥锁API
	    #定义一个锁
		pthread_mutex_t lock;
		#初始化一个锁
		pthread_mutex_init(&lock,NULL);
		#销毁一个锁
		pthread_mutex_destroy(&lock)
		# 加锁
		pthread_mutex_lock(&lock)
		#解锁
		pthread_mutex_unlock(&lock)


 	6、cond条件变量API
	    #定义一个条件
		pthread_cond_t cond;
		#初始化一个条件
		pthread_cond_init(&cond, NULL)
		#等待一个条件
		pthread_cond_wait(&cond,&mutex); //解锁并等待
		#唤醒一个条件
		pthread_cond_signal(&cond); //唤醒一个条件


    @date      26.01.2022
    @copyright © Yu DaiChen , 2022. All right reserved.
*******************************************************************************/
#ifdef __linux__


#include <cstdio>
#include <pthread.h>
#include <unistd.h>

volatile int static_i = 0;

pthread_mutex_t mut;

void *thread1(void *args)
{
	pthread_mutex_lock(&mut); //上锁
	static_i++;
	pthread_mutex_unlock(&mut); //解锁
	printf("tprocess1:%d\n", static_i);
	sleep(10);
	printf("Hello World\n");
	return NULL;
}

void *thread2(void *args)
{
	pthread_mutex_lock(&mut); //锁定
	static_i++;
	pthread_mutex_unlock(&mut); //解锁
	printf("tprocess2: %d\n", static_i);
	sleep(5); //线程sleep
	printf("Helloo===========\n");
	return NULL;
}

void start_test_thread()
{
	pthread_t t1;
	pthread_t t2;
	pthread_mutex_init(&mut, NULL); //初始化锁
	pthread_create(&t1, NULL, thread1, NULL); //创建线程1
	pthread_create(&t2, NULL, thread2, NULL); //创建线程2
	pthread_join(t1, NULL); //等待线程1结束
	pthread_mutex_destroy(&mut); //销毁
	printf("%lu", t1);
}

//1.管道


#endif //__LINUX__
