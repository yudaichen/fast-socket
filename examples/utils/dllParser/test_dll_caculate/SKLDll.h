#ifndef _SKL_DLL_H_
#define _SKL_DLL_H_

#ifndef DLL_API
#define DLL_API extern "C" __declspec(dllexport)
#else
#define DLL_API extern "C" __declspec(dllimport)
#endif

DLL_API int add(int a,int b);

#endif//_SKL_DLL_H_