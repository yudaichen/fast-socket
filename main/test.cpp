#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <vector>
#include <numeric> //for std::accumulate

using namespace std;

std::mutex mtx;

class Widget
{
public:
	void foo(int x, const std::string& s)
	{
		std::lock_guard<std::mutex> lk(mtx);
		cout << "thread id = "<<std::this_thread::get_id()<<
		     " void Foo::foo(int, const std::string&): x = " <<  x << ", s = " << s<< endl;
	}

	void bar(const std::string& s)
	{
		std::lock_guard<std::mutex> lk(mtx);
		cout << "thread id = " << std::this_thread::get_id()
		     <<" void Widget::bar(const std::string&): s = " << s << endl;
	}

	void operator()(double val)
	{
		std::lock_guard<std::mutex> lk(mtx);
		cout << "thread id = " << std::this_thread::get_id()
		     << " void Widget::operator(): val = " << val << endl;
	}
};

class NonCopyable //只移动对象
{
public:
	NonCopyable() {};

	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator=(const NonCopyable&) = delete;

	NonCopyable(NonCopyable&&) = default;
	NonCopyable& operator=(NonCopyable&&) = default;

	double operator()(double d)
	{
		std::lock_guard<std::mutex> lk(mtx);
		cout << "thread id = " << std::this_thread::get_id()
		     << " void NonCopyable::operator(): d = " << d << endl;
		return d;
	}
};

//并行计算
template<typename RandomIt>
int parallel_sum(RandomIt beg, RandomIt end)
{
	auto len = end - beg;
	if (len < 1000)
	{
		std::lock_guard<std::mutex> lk(mtx);
		cout << "thread id = " << std::this_thread::get_id()
		     << " invoke parallel_sum()" << endl;
		return std::accumulate(beg, end, 0); //遍历[beg,end)区别的每个元素并累加。初始值为0
	}


	RandomIt mid = beg + len / 2;
	auto handle = std::async(std::launch::async,  //子线程将[mid,end)元素进行累加
	                         parallel_sum<RandomIt>, mid, end);

	int sum = parallel_sum(beg, mid);//本线程将[begin,mid)区间元素进行累加

	return sum + handle.get(); //返回两个区间结果的累加和
}

int main()
{

	unsigned int con_threads;

	// calculating number of concurrent threads
	// supported in the hardware implementation
	con_threads = thread::hardware_concurrency();

	cout << "Number of concurrent threads supported are:"
	     << con_threads << endl;

	Widget w;

	cout << "main thread id = " << std::this_thread::get_id() << endl;
	//1. 参数传递
	auto fut1 = std::async(&Widget::foo, &w, 42, "hello"); //传入this指针：&w
	auto fut2 = std::async(&Widget::bar, w, "goodbye"); //传入x的副本如tmp。 tmp.bar(...)

	auto fut3 = std::async(Widget(), 3.14159); //传入Widget临时对象，调用operator()
	auto fut4 = std::async(std::ref(w), 2.718);  //传入w的引用，调用operator();

	NonCopyable mo;    //只移动对象
	auto fut5 = std::async(std::move(mo),3.14159); //mo是只移动对象，必须被转为右值

	//2. 同步、异步
	auto fut6 = std::async(std::launch::async, Widget(), 1.2); //在新线程上运行,operator()
	auto fut7 = std::async(std::launch::deferred, &Widget::bar, &w, "deferred"); //线程延迟到调用get或wait才执行

	auto fut8 = std::async(std::launch::async | std::launch::deferred, //等价于默认启动策略
	                       &Widget::bar, &w, "async | deferred");

	fut7.get(); //主线程阻塞，等待fut7子线程。（子线程延迟到这时才执行）。

	//3. 并行计算
	std::vector<int> vec(10000, 1); //10000个1
	int res = parallel_sum(vec.begin(), vec.end());

	{
		std::lock_guard<std::mutex> lk(mtx);
		cout << "The sum is: " << res << endl;

		cout << "main thread  end." << endl;
	}

	return 0;
}
