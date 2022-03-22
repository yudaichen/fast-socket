/*******************************************************************************
    @file      main.cpp
    @brief    过滤器模式 ---- shiro and spring Security 都使用了权限认证过滤器

        1、过滤器（Filter） - 过滤器在请求处理程序执行请求之前或之后，执行某些任务。

        2、过滤器链（Filter Chain） - 过滤器链带有多个过滤器，并在 Target 上按照定义的顺序执行这些过滤器。

        3、Target - Target 对象是请求处理程序。

        4、过滤管理器（Filter Manager） - 过滤管理器管理过滤器和过滤器链。

        5、客户端（Client） - Client 是向 Target 对象发送请求的对象

    @details   ~
    @date      22.03.2022
    @copyright © Yu Dai Cheng Technologies Co Ltd, 2022. All right reserved.
*******************************************************************************/
#include<iostream>
#include<string>
#include<list>

using namespace std;

//创建过滤器抽象接口类Filter
class Filter {
public:
	Filter() = default;

	virtual ~Filter() = default;

	// 放行请求
	bool passThrough = true;

	// 拦截请求
	bool intercept = false;

	// 执行器
	virtual bool execute(string request) = 0;
};

//创建过滤器实体类AuthenticationFilter
class AuthenticationFilter : public Filter {
public:
	AuthenticationFilter() = default;

	~AuthenticationFilter() override
	{

	}

	bool execute(string request) override
	{
		cout << "AuthenticationFilter request: " << request << endl;
		// 空请求就拦截
		if (!request.empty())
		{
			return passThrough;
		} else
		{
			return intercept;
		}
	}
};

//创建过滤器实体类DebugFilter
class DebugFilter : public Filter {
public:
	DebugFilter() = default;

	~DebugFilter() override
	{

	}

	bool execute(string request) override
	{
		cout << "DebugFilter request: " << request << endl;
		// 空请求就拦截
		if (!request.empty())
		{
			return passThrough;
		} else
		{
			return intercept;
		}
	}
};


//创建请求处理程序Target类
class Target {
public:
	Target()
	{};

	~Target()
	{};

	void execute(const string &request)
	{
		cout << "Target request: " << request << endl;
	}
};


//创建过滤器链，将多个过滤器实体对象连接起来，实现更强大的过滤功能
class FilterChain {
public:
	FilterChain()
	{ target = nullptr; }

	~FilterChain()
	{
		list<Filter *>::iterator it;
		for (it = this->filterList.begin(); it != this->filterList.end(); ++it)
		{
			// 过滤链执行失败就不继续执行了
			delete (*it);
			(*it) = nullptr;
		}
		delete this->target;
		this->target = nullptr;
	}

	void addFilter(Filter *filter)
	{
		this->filterList.push_back(filter);
	}

	bool execute(const string &request)
	{
		list<Filter *>::iterator it;
		for (it = this->filterList.begin(); it != this->filterList.end(); ++it)
		{
			// 过滤链执行失败就不继续执行了
			if (!(*it)->execute(request))
			{
				return (*it)->intercept;
			}
		}
		//类似于spring boot 开发中 通过了过滤链，才能执行“业务逻辑”
		this->target->execute(request);
		return true;
	}

	void setTarget(Target *cTarget)
	{
		this->target = cTarget;
	}

private:
	// 过滤链
	list<Filter *> filterList;

	// 请求处理目标
	Target *target;
};


//创建过滤器管理类FilterManager，主要是管理过滤器链，负责增删改查过滤器链
class FilterManager {
public:
	explicit FilterManager(Target *target)
	{
		this->filterChain = new FilterChain();
		this->filterChain->setTarget(target);
	}

	~FilterManager()
	{
		delete this->filterChain;
		this->filterChain = nullptr;
	}

	void setFilter(Filter *filter)
	{
		this->filterChain->addFilter(filter);
	}


	bool filterRequest(const string &request)
	{
		if (this->filterChain->execute(request))
		{
			cout << "code [200] : success request pass through" << endl;
		} else
		{
			cout << "code [500] :error request intercept" << endl;
		}
		return true;
	}

private:
	FilterChain *filterChain;
};


//创建客户端Client
class Server {
public:
	Server() = default;

	~Server() = default;

	void setFilterManager(FilterManager *cFilterManager)
	{
		this->filterManager = cFilterManager;
	}

	void getRequestInfo(const string &request)
	{
		this->filterManager->filterRequest(request);
	}

private:
	FilterManager *filterManager;
};


int main()
{
	// 切面执行目标方法
	Target *target = new Target();

	//过滤链设置
	FilterManager *filterManager = new FilterManager(target);
	filterManager->setFilter(new AuthenticationFilter());
	filterManager->setFilter(new DebugFilter());

	//拦截请求
	Server *server = new Server();
	server->setFilterManager(filterManager);
	std::string requestInfo;
	server->getRequestInfo(requestInfo);

	delete filterManager;
	filterManager = nullptr;

	delete server;
	server = nullptr;

	system("pause");
	return 0;
}