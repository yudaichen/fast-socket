#pragma once
#ifndef __ZZ_STRING__HPP__
#define __ZZ_STRING__HPP__

#include <string>
#include <algorithm>
#include <cstring>

/**
 * @brief string 工具类
 * @Item lexicalCast 类型转换
 * @Item StringUtil 子传承处理工具
 */
namespace fast
{
class lexicalCast
{

public:
	// 简化调用
	template<typename To, typename From>
	static To cast(const From &from)
	{
		return converter<To, From>::convert(from);
	}

private:
	// 模板特化定义
	template<typename To, typename From>
	struct converter
	{
	};

	// 转换到int类型
	template<typename From>
	struct converter<int, From>
	{
		static int convert(const std::string &from)
		{ return std::atoi(from.c_str()); }
		static int convert(const char *from)
		{ return std::atoi(from); }
	};

	// 转换到long类型
	template<typename From>
	struct converter<long, From>
	{
		static long convert(const std::string &from)
		{ return std::atol(from.c_str()); }
		static long convert(const char *from)
		{ return std::atol(from); }
	};

	// 转换到long long类型
	template<typename From>
	struct converter<long long, From>
	{
		static long long convert(const std::string &from)
		{ return std::atoll(from.c_str()); }
		static long long convert(const char *from)
		{ return std::atoll(from); }
	};

	// 转换到double类型
	template<typename From>
	struct converter<double, From>
	{
		static double convert(const std::string &from)
		{ return std::atof(from.c_str()); }
		static double convert(const char *from)
		{ return std::atof(from); }
	};

	// 转换到float类型
	template<typename From>
	struct converter<float, From>
	{
		static float convert(const std::string &from)
		{ return static_cast<float>(std::atof(from.c_str())); }
		static float convert(const char *from)
		{ return static_cast<float>(std::atof(from)); }
	};

	// 转换到bool类型
	template<typename From>
	struct converter<bool, From>
	{
		static bool convert(int from)
		{ return from > 0; }
		static bool convert(const std::string from)
		{ return std::atoi(from.c_str()) > 0; }
	};

	// 转换到string类型
	template<typename From>
	struct converter<std::string, From>
	{
		static std::string convert(int from)
		{ return std::to_string(from); }
		static std::string convert(double from)
		{ return std::to_string(from); }
		static std::string convert(float from)
		{ return std::to_string(from); }
		static std::string convert(const std::string &from)
		{ return from; }
		static std::string convert(const char *from)
		{ return from; }
		static std::string convert(char from)
		{ return std::string(&from); }
	};
};

class StringUtil
{
public:
	/**
	 * @brief 向左修剪
	 * @param str 源字符串
	 * @param token 条件字符串
	 * @return 裁剪后的字符串
	 */
	static std::string trimLeft(const std::string &str, const std::string &token = " ")
	{
		std::string t = str;
		t.erase(0, t.find_first_not_of(token));
		return t;
	}

	/**
	 * @brief 向右修剪
	 * @param str 源字符串
	 * @param token 条件字符串
	 * @return 裁剪后的字符串
	 */
	static std::string trimRight(const std::string &str, const std::string &token = " ")
	{
		std::string t = str;
		t.erase(t.find_last_not_of(token) + 1);
		return t;
	}

	/**
	 * @brief 根据字符同时 左右修剪，默认整理空格
	 * @param str 源字符串
	 * @param token 条件字符串
	 * @return 裁剪后的字符串
	 */
	static std::string trim(const std::string &str, const std::string &token = " ")
	{
		std::string t = str;
		t.erase(0, t.find_first_not_of(token));
		t.erase(t.find_last_not_of(token) + 1);
		return t;
	}

	/**
	 * @brief 转大写
	 * @param str 源字符串
	 * @return 转换后的字符串
	 */
	static std::string toLower(const std::string &str)
	{
		std::string t = str;
		std::transform(t.begin(), t.end(), t.begin(), ::tolower);
		return t;
	}

	/**
	 * @brief 转小写
	 * @param str 源字符串
	 * @return 转换后的字符串
	 */
	static std::string toUpper(const std::string &str)
	{
		std::string t = str;
		std::transform(t.begin(), t.end(), t.begin(), ::toupper);
		return t;
	}

	/**
	 * @brief 当前的字符是否以字串开头
	 * @param str 源字符串
	 * @param subStr 子串
	 * @return bool
	 */
	static bool startsWith(const std::string &str, const std::string &subStr)
	{
		return str.find(subStr) == 0;
	}

	/**
	 * @brief 当前的字符是以字串结尾
	 * @param str 源字符串
	 * @param subStr 字串
	 * @return bool
	 */
	static bool endsWith(const std::string &str, const std::string &substr)
	{
		return str.rfind(substr) == (str.length() - substr.length());
	}

	/**
	 * @brief 忽略大小写匹配是否相等
	 * @param str1 比较1
	 * @param str2 比较2
	 * @return bool
	 */
	static bool equalsIgnoreCase(const std::string &str1, const std::string &str2)
	{
		return toLower(str1) == toLower(str2);
	}

	/**
	 * @brief 分割字符串
	 * @param str 源字串
	 * @param delimiter 分隔符
	 * @return std::vector
	 */
	static std::vector<std::string> split(const std::string &str, const std::string &delimiter)
	{
		char *save = nullptr;
#ifdef _WIN32
		char *token = strtok_s(const_cast<char *>(str.c_str()), delimiter.c_str(), &save);
#else
		char *token = strtok_r(const_cast<char *>(str.c_str()), delimiter.c_str(), &save);
#endif
		std::vector<std::string> result;
		while (token != nullptr)
		{
			result.emplace_back(token);
#ifdef _WIN32
			token = strtok_s(nullptr, delimiter.c_str(), &save);
#else
			token = strtok_r(nullptr, delimiter.c_str(), &save);
#endif
		}
		return result;
	}

	/**
	 * @brief 字串是否包含在源串中
	 * @param str 源串
	 * @param token 查找串
	 * @return bool
	 */
	static bool contains(const std::string &str, const std::string &token)
	{
		return str.find(token) != std::string::npos;
	}
};

}

#endif //__ZZ_STRING__HPP__
