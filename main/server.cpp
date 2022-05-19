#include <vector>
#include "utils/collection/string/string.hpp"
#include "utils/collection/string/format.hpp"
#include "utils/magic/crossPlatformDll/dllParser.hpp"
#include "meta.hpp"
#include "yaml.hpp"
using namespace Yaml;
using namespace fast;
#include "gLog.h"
#include "tcp_server.h"
#include "buffer/buf_pool.h"
#include "event_base.h"
#include "stringSwitch.hpp"

#include "tcp_server.h"
#include <string>
#include <string.h>
#include "config_file.h"


#include <iostream>
#include <string>
#include <chrono>
#include "thread_pool.hpp"

void test_task(const std::string& str)
{
	std::cout << "Current thread id: " << std::this_thread::get_id() << ", str: " << str << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

class Test
{
public:
	void print(const std::string& str, int i)
	{
		std::cout << "Test: " << str << ", i: " << i << std::endl;
	}
};

class Test2
{
public:
	void operator()(const std::string& str, int i)
	{
		std::cout << "Test2: " << str << ", i: " << i << std::endl;
	}
};

int main()
{
	Test t;
	Test2 t2;
	simple_switch("thirfthirfthirfthirfthirfthirfthirf");
	try
	{
		fast::thread_pool pool;
		pool.init_thread_num(10);

		std::string str = "Hello world";

		for (int i = 0; i < 1000; ++i)
		{
			pool.add_task([]{ std::cout << "Hello ThreadPool" << std::endl; });
			pool.add_task(test_task, str);
			pool.add_task(t2, str, i);
			pool.add_task(&Test::print, &t, str, i);
		}

		std::cin.get();
		std::cout << "##############END###################" << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}


#if 0
tcp_server *server;

//回显业务的回调函数
void callback_busi(const char *data, uint32_t len, int msgid, net_connection
*conn, void *user_data)
{
	printf("callback_busi ...\n");
	//直接回显
	conn->send_message(data, len, msgid);
	printf("conn param = %s\n", (const char *)conn->param);
}

//打印信息回调函数
void print_busi(const char *data, uint32_t len, int msgid, net_connection *conn, void *user_data)
{
	printf("recv client: [%s]\n", data);
	printf("msgid: [%d]\n", msgid);
	printf("len: [%d]\n", len);
}

//新客户端创建的回调
void on_client_build(net_connection *conn, void *args)
{
	int msgid = 101;
	const char *msg = "welcome! you online..";
	conn->send_message(msg, strlen(msg), msgid);
	//将当前的net_connection 绑定⼀个⾃定义参数，供我们开发者使⽤
	const char *conn_param_test = "I am the conn for you!";
	conn->param = (void *)conn_param_test;
}

//客户端销毁的回调
void on_client_lost(net_connection *conn, void *args)
{
	printf("connection is lost !\n");
}

int main()
{

	Yaml::Node root;
	try
	{
		Parse(root, "zzConfig.yaml");
	}
	catch (const Yaml::Exception &e)
	{
		std::cout << "Exception " << e.Type() << ": " << e.what() << std::endl;
	}

	event_loop loop;
	//加载配置⽂件
	config_file::setPath("./serv.conf");
	std::string ip = config_file::instance()->GetString("reactor", "ip","0.0.0.0");
	short port = config_file::instance()->GetNumber("reactor", "port", 7777);
	printf("ip = %s, port = %d\n", ip.c_str(), port);
	server = new tcp_server(&loop, ip.c_str(), port);

	//注册消息业务路由
	server->add_msg_router(1, callback_busi);
	server->add_msg_router(2, print_busi);

	//注册链接hook回调
	server->set_conn_start(on_client_build);
	server->set_conn_close(on_client_lost);
	loop.event_process();
	return 0;
}

#endif //0

#if 0
int main(int argc, char *argv[])
{

	//全局日志初始化
	Log::instance(argv[0]);

	LOG_INFO << "init log";

	int a = 5, b = 5;
	std::cout << (a & b) << std::endl;

	a = 0, b = 7;
	std::cout << (a & b) << std::endl;


	std::cout << (a | b) << std::endl;

	a = 3, b = 3;
	//std::cout<<std::to_string(a~b) <<std::endl;
	std::cout << (a ^ b) << std::endl;
	return 0;
}

#endif

#if 0
struct Person
{
	std::string name;
	int age;

	META(name, age)
};

template<typename T>
void func(T& t)
{
	auto ret = t.meta();
	std::cout << typeid(ret).name() << std::endl;
}

// 获取成员变量类型
int main()
{
	Person p {"Jack", 10};
	std::cout << typeid(Person).name() << std::endl;
	func(p);
	return 0;
}
#endif

#if 0
int main(int argc, char *argv[])
{

	std::string dllFilePath = "./cygtestDll.dll";

	DllParser parser;
	bool ret = parser.load(dllFilePath);
	if (!ret)
	{
		return 1;
	}

	int a = 20;
	int b = 10;

	try
	{
		auto addRet = parser.executeFunction<int(int, int)>("add", a, b);
		std::cout << "a + b = " << addRet << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::string str = "Hello world";
	std::cout << StringUtil::trimLeft(str, "Hello") << std::endl;
	std::cout << StringUtil::trimRight(str, "world") << std::endl;
	str = "  nihao ";
	std::cout << StringUtil::trim(str) << std::endl;
	std::cout << StringUtil::toUpper(str) << std::endl;
	std::cout << StringUtil::toLower(StringUtil::toUpper(str)) << std::endl;
	str = "Hello world";
	std::cout << StringUtil::startsWith(str, "Hello") << std::endl;
	std::cout << StringUtil::endsWith(str, "a") << std::endl;
	std::vector<std::string> result = StringUtil::split(str, " ");

	for (auto &iter: result)
	{
		std::cout << iter << std::endl;
	}

	try
	{
		std::string str = "a = {0}, b = {1}";
		std::cout << format(const_cast<char *>(str.c_str()), 10.23, 200) << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	str = "1000";
	int n = 200;
	std::cout << typeid(lexicalCast::cast<int>(str)).name() << std::endl;
	std::cout << lexicalCast::cast<std::string>(n) << std::endl;
	std::cout << lexicalCast::cast<bool>(n) << std::endl;
	std::cout << lexicalCast::cast<bool>(-1) << std::endl;
	std::cout << typeid(lexicalCast::cast<bool>(-1)).name() << std::endl;

	std::cout << lexicalCast::cast<std::string>(str) << std::endl;
	std::cout << lexicalCast::cast<std::string>("hello") << std::endl;

	return 0;
}
#endif