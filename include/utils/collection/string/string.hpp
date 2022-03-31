#pragma once
#ifndef __ZZ_STRING__HPP__
#define __ZZ_STRING__HPP__

#include <string>
#include <algorithm>
#include <cstring>

/**
 * @brief string ������
 * @Item lexicalCast ����ת��
 * @Item StringUtil �Ӵ��д�����
 */
namespace fast
{
class lexicalCast
{

public:
	// �򻯵���
	template<typename To, typename From>
	static To cast(const From &from)
	{
		return converter<To, From>::convert(from);
	}

private:
	// ģ���ػ�����
	template<typename To, typename From>
	struct converter
	{
	};

	// ת����int����
	template<typename From>
	struct converter<int, From>
	{
		static int convert(const std::string &from)
		{ return std::atoi(from.c_str()); }
		static int convert(const char *from)
		{ return std::atoi(from); }
	};

	// ת����long����
	template<typename From>
	struct converter<long, From>
	{
		static long convert(const std::string &from)
		{ return std::atol(from.c_str()); }
		static long convert(const char *from)
		{ return std::atol(from); }
	};

	// ת����long long����
	template<typename From>
	struct converter<long long, From>
	{
		static long long convert(const std::string &from)
		{ return std::atoll(from.c_str()); }
		static long long convert(const char *from)
		{ return std::atoll(from); }
	};

	// ת����double����
	template<typename From>
	struct converter<double, From>
	{
		static double convert(const std::string &from)
		{ return std::atof(from.c_str()); }
		static double convert(const char *from)
		{ return std::atof(from); }
	};

	// ת����float����
	template<typename From>
	struct converter<float, From>
	{
		static float convert(const std::string &from)
		{ return static_cast<float>(std::atof(from.c_str())); }
		static float convert(const char *from)
		{ return static_cast<float>(std::atof(from)); }
	};

	// ת����bool����
	template<typename From>
	struct converter<bool, From>
	{
		static bool convert(int from)
		{ return from > 0; }
		static bool convert(const std::string from)
		{ return std::atoi(from.c_str()) > 0; }
	};

	// ת����string����
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
	 * @brief �����޼�
	 * @param str Դ�ַ���
	 * @param token �����ַ���
	 * @return �ü�����ַ���
	 */
	static std::string trimLeft(const std::string &str, const std::string &token = " ")
	{
		std::string t = str;
		t.erase(0, t.find_first_not_of(token));
		return t;
	}

	/**
	 * @brief �����޼�
	 * @param str Դ�ַ���
	 * @param token �����ַ���
	 * @return �ü�����ַ���
	 */
	static std::string trimRight(const std::string &str, const std::string &token = " ")
	{
		std::string t = str;
		t.erase(t.find_last_not_of(token) + 1);
		return t;
	}

	/**
	 * @brief �����ַ�ͬʱ �����޼���Ĭ������ո�
	 * @param str Դ�ַ���
	 * @param token �����ַ���
	 * @return �ü�����ַ���
	 */
	static std::string trim(const std::string &str, const std::string &token = " ")
	{
		std::string t = str;
		t.erase(0, t.find_first_not_of(token));
		t.erase(t.find_last_not_of(token) + 1);
		return t;
	}

	/**
	 * @brief ת��д
	 * @param str Դ�ַ���
	 * @return ת������ַ���
	 */
	static std::string toLower(const std::string &str)
	{
		std::string t = str;
		std::transform(t.begin(), t.end(), t.begin(), ::tolower);
		return t;
	}

	/**
	 * @brief תСд
	 * @param str Դ�ַ���
	 * @return ת������ַ���
	 */
	static std::string toUpper(const std::string &str)
	{
		std::string t = str;
		std::transform(t.begin(), t.end(), t.begin(), ::toupper);
		return t;
	}

	/**
	 * @brief ��ǰ���ַ��Ƿ����ִ���ͷ
	 * @param str Դ�ַ���
	 * @param subStr �Ӵ�
	 * @return bool
	 */
	static bool startsWith(const std::string &str, const std::string &subStr)
	{
		return str.find(subStr) == 0;
	}

	/**
	 * @brief ��ǰ���ַ������ִ���β
	 * @param str Դ�ַ���
	 * @param subStr �ִ�
	 * @return bool
	 */
	static bool endsWith(const std::string &str, const std::string &substr)
	{
		return str.rfind(substr) == (str.length() - substr.length());
	}

	/**
	 * @brief ���Դ�Сдƥ���Ƿ����
	 * @param str1 �Ƚ�1
	 * @param str2 �Ƚ�2
	 * @return bool
	 */
	static bool equalsIgnoreCase(const std::string &str1, const std::string &str2)
	{
		return toLower(str1) == toLower(str2);
	}

	/**
	 * @brief �ָ��ַ���
	 * @param str Դ�ִ�
	 * @param delimiter �ָ���
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
	 * @brief �ִ��Ƿ������Դ����
	 * @param str Դ��
	 * @param token ���Ҵ�
	 * @return bool
	 */
	static bool contains(const std::string &str, const std::string &token)
	{
		return str.find(token) != std::string::npos;
	}
};

}

#endif //__ZZ_STRING__HPP__
