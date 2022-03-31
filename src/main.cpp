#include <vector>
#include "utils/collection/string/string.hpp"
#include "utils/collection/string/format.hpp"
#include "utils/magic/crossPlatformDll/dllParser.hpp"

using namespace fast;
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