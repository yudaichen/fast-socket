#ifndef FAST_SOCKET_LOAD_DLL_HPP
#define FAST_SOCKET_LOAD_DLL_HPP

#include <string>
#include <functional>
#include <iostream>

#ifdef _WIN32
#include "windows.h"
typedef HINSTANCE DllHandle;
#elif __linux__
#include <dlfcn.h>
typedef void* DllHandle;
#else
typedef void* DllHandle;
#endif //_WIN32

/**
 * @brief C ++动态地将任意函数从DLL加载到std :: function
 * @Link https://www.thinbug.com/q/15249465
 */
class loadDll {

	template<typename T>
	struct TypeParser {
	};

#ifdef _WIN32

	template<typename ReturnType, typename... Args>
	struct TypeParser<ReturnType(Args...)> {
		static std::function<ReturnType(Args...)> createFunction(const FARPROC lpfnGetProcessID)
		{
			return std::function<ReturnType(Args...)>(reinterpret_cast<ReturnType (__stdcall *)(Args...)>(lpfnGetProcessID));
		}
	};

#elif __linux__


#endif //_WIN32

	/**
	 * @brief 加载dll
	 * @tparam T 返回泛型std::function
	 * @param dllName  dll名称
	 * @param funcName 待执行函数的名称
	 * @return 返回泛型std::function
	 */
	template<typename T>
	std::function<T> load(const std::string &dllName, const std::string &funcName)
	{
#ifdef _WIN32
		// Load DLL.
		dllHandle = LoadLibrary(dllName.c_str());

		// Check if DLL is loaded.
		if (dllHandle == NULL)
		{
			std::cerr << "Could not load DLL \"" << dllName << "\"" << std::endl;
			return nullptr;
		}

		// Locate function in DLL.
		FARPROC lpfnGetProcessID = GetProcAddress(dllHandle, funcName.c_str());

		// Check if function was located.
		if (!lpfnGetProcessID)
		{
			std::cerr << "Could not locate the function \"" << funcName << "\" in DLL\"" << dllName << "\""
			          << std::endl;
			return nullptr;
		}

		// Create function object from function pointer.
		return TypeParser<T>::createFunction(lpfnGetProcessID);

#elif __linux__
		return nullptr;
#endif //_WIN32
		return nullptr;
	}

	/**
	 * @brief free dll
	 */
	void free()
	{

		if (dllHandle != NULL)
		{
#ifdef _WIN32
			FreeLibrary(dllHandle);
#endif //_WIN32
		}

	}

private:
	DllHandle dllHandle;

};

#endif //FAST_SOCKET_LOAD_DLL_HPP


