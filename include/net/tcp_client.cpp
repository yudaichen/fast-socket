#include "tcp_client.h"

int selectCheckConnect(int iSocket)
{
	fd_set rset;
	FD_ZERO(&rset);
	FD_SET(iSocket, &rset);
	timeval tm;
	tm.tv_sec = 0;
	tm.tv_usec = 0;
	if (select(iSocket + 1, NULL, &rset, NULL, &tval) <= 0)
	{
		close(iSocket);
		return -1;
	}
	if (FD_ISSET(iSocket, &rset))
	{
		int err = -1;
		socklen_t len = sizeof(int);
		if (getsockopt(iSocket, SOL_SOCKET, SO_ERROR, &err, &len) < 0)
		{
			close(iSocket);
			printf("errno:%d %s\n", errno, strerror(errno));
			return -2;
		}
		if (err)
		{
			errno = err;
			close(iSocket);
			return -3;
		}
	}
	return 0;
}

int pollCheckConnect(int iSocket)
{
	struct pollfd fd;
	int ret = 0;
	socklen_t len = 0;
	fd.fd = iSocket;
	fd.events = POLLOUT;
	while (poll(&fd, 1, -1) == -1)
	{
		if (errno != EINTR)
		{
			perror("poll");
			return -1;
		}
	}
	len = sizeof(ret);
	if (getsockopt(iSocket, SOL_SOCKET, SO_ERROR, &ret, &len) == -1)
	{
		perror("getsockopt");
		return -1;
	}
	if (ret != 0)
	{
		fprintf(stderr, "socket %d connect failed: %s\n",
		        iSocket, strerror(ret));
		return -1;
	}
	return 0;
}

static void write_callback(event_loop *loop, int fd, void *args)
{
	tcp_client *cli = (tcp_client *)args;
	cli->do_write();
}

static void read_callback(event_loop *loop, int fd, void *args)
{
	tcp_client *cli = (tcp_client *)args;
	cli->do_read();
}

//判断链接是否是创建链接，主要是针对⾮阻塞socket 返回EINPROGRESS错误
static void connection_delay(event_loop *loop, int fd, void *args)
{
	tcp_client *cli = (tcp_client *)args;
	loop->del_io_event(fd);
	int result = 0;
	socklen_t result_len = sizeof(result);
	getsockopt(fd, SOL_SOCKET, SO_ERROR, &result, &result_len);
	if (result == 0)
	{
		//链接是建⽴成功的
		cli->connected = true;
		printf("connect %s:%d succ!\n", inet_ntoa(cli->_server_addr.sin_addr),
		       ntohs(cli->_server_addr.sin_port));

		//建⽴连接成功之后，主动发送send_message
		const char *msg = "hello lars!";
		int msgid = 1;
		cli->send_message(msg, strlen(msg), msgid);
		loop->add_io_event(fd, read_callback, EPOLLIN, cli);
		if (cli->_obuf.length != 0)
		{
			//输出缓冲有数据可写
			loop->add_io_event(fd, write_callback, EPOLLOUT, cli);
		}
	}
	else
	{
		//链接创建失败
		fprintf(stderr,
		        "connection %s:%d error\n",
		        inet_ntoa(cli - > _server_addr.sin_addr),
		        ntohs(cli->_server_addr.sin_port));
	}
}

tcp_client::tcp_client(event_loop *loop, const char *ip, unsigned short port,
                       const char *name)
	:
	_ibuf(4194304),
	_obuf(4194304)
{
	_sockfd = -1;
	_msg_callback = NULL;
	_name = name;
	_loop = loop;

	bzero(&_server_addr, sizeof(_server_addr));

	_server_addr.sin_family = AF_INET;
	inet_aton(ip, &_server_addr.sin_addr);
	_server_addr.sin_port = htons(port);
	_addrlen = sizeof(_server_addr);
	this->do_connect();
}

//创建链接
void tcp_client::do_connect()
{
	if (_sockfd != -1)
	{
		close(_sockfd);
	}

	//创建套接字
	_sockfd = socket(AF_INET, SOCK_STREAM | SOCK_CLOEXEC | SOCK_NONBLOCK,
	                 IPPROTO_TCP);
	if (_sockfd == -1)
	{
		fprintf(stderr, "create tcp client socket error\n");
		exit(1);
	}
	int ret = connect(_sockfd, (const struct sockaddr *)&_server_addr, _addrlen);
	if (ret == 0)
	{
		//链接创建成功
		connected = true;

		//注册读回调
		_loop->add_io_event(_sockfd, read_callback, EPOLLIN, this);

		//如果写缓冲去有数据，那么也需要触发写回调
		if (this->_obuf.length != 0)
		{
			_loop->add_io_event(_sockfd, write_callback, EPOLLOUT, this);
		}

		printf("connect %s:%d succ!\n", inet_ntoa(_server_addr.sin_addr),
		       ntohs(_server_addr.sin_port));
	}
	else
	{
		if (errno == EINPROGRESS)
		{
			//fd是⾮阻塞的，可能会出现这个错误,但是并不表示链接创建失败
			//如果fd是可写状态，则为链接是创建成功的.
			fprintf(stderr, "do_connect EINPROGRESS\n");

			//让event_loop去触发⼀个创建判断链接业务 ⽤EPOLLOUT事件⽴刻触发
			_loop->add_io_event(_sockfd, connection_delay, EPOLLOUT, this);
		}
		else
		{
			fprintf(stderr, "connection error\n");
			exit(1);
		}
	}
}

//处理读业务
int tcp_client::do_read()
{
	//确定已经成功建⽴连接
	assert(connected == true);
	// 1. ⼀次性全部读取出来

	//得到缓冲区⾥有多少字节要被读取，然后将字节数放⼊b⾥⾯。
	int need_read = 0;
	if (ioctl(_sockfd, FIONREAD, &need_read) == -1)
	{
		fprintf(stderr, "ioctl FIONREAD error");
		return -1;
	}
	//确保_buf可以容纳可读数据
	assert(need_read <= _ibuf.capacity - _ibuf.length);
	int ret;
	do
	{
		ret = read(_sockfd, _ibuf.data + _ibuf.length, need_read);
	}
	while (ret == -1 && errno == EINTR);
	if (ret == 0)
	{
		//对端关闭
		if (_name != NULL)
		{
			printf("%s client: connection close by peer!\n", _name);
		}
		else
		{
			printf("client: connection close by peer!\n");
		}
		clean_conn();
		return -1;
	}
	else if (ret == -1)
	{
		fprintf(stderr, "client: do_read() , error\n");
		clean_conn();
		return -1;
	}

	assert(ret == need_read);
	_ibuf.length += ret;
	//2. 解包
	msg_head head;
	int msgid, length;
	while (_ibuf.length >= MESSAGE_HEAD_LEN)
	{
		memcpy(&head, _ibuf.data + _ibuf.head, MESSAGE_HEAD_LEN);
		msgid = head.msgid;
		length = head.msglen;
		/*
		if (length + MESSAGE_HEAD_LEN < _ibuf.length) {
		break;
		}
		*/
		//头部读取完毕
		_ibuf.pop(MESSAGE_HEAD_LEN);
		//3. 交给业务函数处理
		if (_msg_callback != NULL)
		{
			this->_msg_callback(_ibuf.data + _ibuf.head, length, msgid, this,
			                    NULL);
		}

		//数据区域处理完毕
		_ibuf.pop(length);
	}

	//重置head指针
	_ibuf.adjust();
	return 0;
}

//处理写业务
int tcp_client::do_write()
{
	//数据有⻓度，切头部索引是起始位置
	assert(_obuf.head == 0 && _obuf.length);
	int ret;
	while (_obuf.length)
	{
		//写数据
		do
		{
			ret = write(_sockfd, _obuf.data, _obuf.length);
		}
		while (ret == -1 && errno == EINTR);//⾮阻塞异常继续重写
		if (ret > 0)
		{
			_obuf.pop(ret);
			_obuf.adjust();
		}
		else if (ret == -1 && errno != EAGAIN)
		{
			fprintf(stderr, "tcp client write \n");
			this->clean_conn();
		}
		else
		{
			//出错,不能再继续写
			break;
		}
	}
	if (_obuf.length == 0)
	{
		//已经写完，删除写事件
		printf("do write over, del EPOLLOUT\n");
		this->_loop->del_io_event(_sockfd, EPOLLOUT);
	}
	return 0;
}

//释放链接资源,重置连接
void tcp_client::clean_conn()
{
	if (_sockfd != -1)
	{
		printf("clean conn, del socket!\n");
		_loop->del_io_event(_sockfd);
		close(_sockfd);
	}
	connected = false;
	//重新连接
	this->do_connect();
}

tcp_client::~tcp_client()
{
	close(_sockfd);
}