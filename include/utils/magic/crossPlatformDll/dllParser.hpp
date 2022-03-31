#ifndef _DLLPARSER_H
#define _DLLPARSER_H

#ifdef _WIN32
#include "windows.h"

typedef HINSTANCE DllHandle;
typedef FARPROC FunctionAddress;
#else

#include <dlfcn.h>
typedef void* DllHandle;
typedef void* FunctionAddress;

#endif //_WIN32


#include <iostream>
#include <exception>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <functional>
#include <memory>


/**
 * @brief 跨平台dll加载器
 */
class DllParser
{
public:
	~DllParser()
	{
		unload();
	}

	bool load(const std::string &dllFilePath)
	{
#ifdef _WIN32
		m_handle = LoadLibrary(dllFilePath.c_str());

#else
		m_handle = dlopen(dllFilePath.c_str(), RTLD_NOW);
#endif //_WIN32
		if (m_handle == nullptr)
		{
#ifdef _WIN32
			std::cerr << "Open dll failed, error: " << dllFilePath << std::endl;
#else
			std::cout << "Open dll failed, error: " << dlerror() << std::endl;
#endif //_WIN32
			return false;
		}

		return true;
	}

	bool unload()
	{
		if (m_handle == nullptr)
		{
			return true;
		}

#ifdef _WIN32
		int ret = FreeLibrary(m_handle);
#else
		int ret = dlclose(m_handle);
#endif //_WIN32

		m_handle = nullptr;
#ifdef _WIN32
		if (ret < 1)
		{
			std::cout << "Close dll failed, error: " << std::endl;
			return false;
		}
#else
		if (ret != 0)
		{
			std::cout << "Close dll failed, error: " << dlerror() << std::endl;
			return false;
		}

#endif //_WIN32
		return true;
	}

	template<typename T>
	std::function<T> getFunction(const std::string &funcName)
	{
		auto iteration = m_funcMap.find(funcName);
		if (iteration == m_funcMap.end())
		{
#ifdef _WIN32
			FunctionAddress address = GetProcAddress(m_handle, funcName.c_str());
#else
			FunctionAddress address = dlsym(m_handle, funcName.c_str());
#endif //_WIN32

			if (address == nullptr)
			{
#ifdef _WIN32
				std::cout << "func is nullptr, error " << std::endl;
#else
				std::cout << "func is nullptr, error: " << dlerror() << std::endl;
#endif //_WIN32

				return nullptr;
			}

			m_funcMap.emplace(funcName, address);
			return std::function<T>(reinterpret_cast<T *>(address));
		}

		return std::function<T>(reinterpret_cast<T *>(iteration->second));
	}

	template<typename T, typename... Args>
	typename std::result_of<std::function<T>(Args...)>::type executeFunction(const std::string &funcName,
	                                                                         Args &&... args)
	{
		auto func = getFunction<T>(funcName);
		if (func == nullptr)
		{
			std::string str = "Can not find this function: " + funcName;
			throw std::runtime_error(str);
		}

		return func(std::forward<Args>(args)...);
	}

private:
	DllHandle m_handle = nullptr;
	std::unordered_map<std::string, FunctionAddress> m_funcMap;
};

#endif
