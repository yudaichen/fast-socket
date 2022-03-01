/*******************************************************************************
    @file      ipc.cpp
    @brief     unix 守护进程以及守护线程
    @details
    @date      26.01.2022
    @copyright © Yu DaiChen , 2022. All right reserved.
*******************************************************************************/

#ifndef FAST_SOCKET_TEST_DAEMON_H
#define FAST_SOCKET_TEST_DAEMON_H

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
#endif //FAST_SOCKET_TEST_DAEMON_H
