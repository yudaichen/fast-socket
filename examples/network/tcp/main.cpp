#include "loadDll.hpp"
#include <boost/array.hpp>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#include "network/testLinuxApi/test_process.hpp"
#include "network/testLinuxApi/test_thread.hpp"
#include "network/testLinuxApi/test_process_communication.hpp"
#include "network/testLinuxApi/test_socket.hpp"
#include "network/testLinuxApi/test_daemon.hpp"

void testBoost()
{
	typedef boost::array<std::string, 3> array;
	array a;

	a[0] = "Boris";
	a.at(1) = "Anton";
	*a.rbegin() = "Caesar";

	std::sort(a.begin(), a.end());

	for (const auto &it: a)
	{
		std::cout << it << std::endl;
	}

	std::cout << a.size() << std::endl;
	std::cout << a.max_size() << std::endl;
}

void print(const std::string &n)
{
	std::cout << n << std::endl;
}

void print2(const std::string &n)
{
	std::cout << "1/" << n << std::endl;
}


void testHaiKang()
{

	double initNum = 1;
	std::vector<std::string> numUpper;
	std::vector<std::string> numUnder;
	numUpper.emplace_back(std::to_string(static_cast<int>(initNum)));
	for (int i = 0; i < 15; i++)
	{
		initNum = initNum * 1.3;
		char middleNum[30];
		sprintf(middleNum, "%.1f", initNum);
		numUpper.emplace_back(middleNum);
	}

	initNum = 1;
	for (int j = 0; j < 15; j++)
	{
		if (initNum >= 0.01)
		{
			initNum = initNum * 0.8;
		} else if (initNum >= 0.001)
		{
			initNum = initNum * 0.8 * 10;
		} else if (initNum >= 0.00001)
		{
			initNum = initNum * 0.8 * 100;
		} else if (initNum >= 0.000001)
		{
			numUnder.emplace_back((std::string &) ("8000"));
			break;
		}
		int temp = (int) initNum * 100;
		int clearDecimal = temp * 100;
		numUnder.emplace_back(std::to_string(clearDecimal));
	}
	std::for_each(numUpper.rbegin(), numUpper.rend(), print);
	std::for_each(numUnder.rbegin(), numUnder.rend(), print2);
}

int main(int argc, char **argv)
{
	//thread_create_start();
	//test_daemon_start();
	//use_file_fd_get_fileName_start();
	//child_process_exit_signal_by_linux_gc_start();
	//child_process_exit_signal_start();
	//signal_handle_start();
	//register_signal_handler_start();
	//signal_process_mask();
	//signal_set_start();
	//time_linux_start();
	//testBoost();
	//start_test_socket();
	//start_test_haveName_pipe();
	//start_test_pipe();
	//test_waitpid();
	//test_fork();
	//test_vfork();
	//start_test_thread();
	//testBoost();
	//testHaiKang();
	return 0;
}
