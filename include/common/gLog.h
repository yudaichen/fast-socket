#pragma once

#include "glog/logging.h"
#include <ctime>
#include <iostream>
#include <clocale>

using namespace google;
using namespace std;

#define LOG_DEBUG\
           LOG(INFO)
#define LOG_INFO\
           LOG(INFO)
#define LOG_WARNING\
           LOG(WARNING)
#define LOG_ERROR\
           LOG(ERROR)

class Log
{

public:

	static void instance(const char *slogName = nullptr)
	{
		static int g_instance = 0;
		char gLogFileName[256], gLogName[256];
		if (g_instance == 1) return;

		if (slogName == nullptr)
		{
			strcpy(gLogName, "unknown");
		}
		else
		{
			strncpy(gLogName, slogName, sizeof(gLogName));
		}
		google::InitGoogleLogging(gLogName);
		//snprintf(gLogFileName, sizeof(gLogFileName) - 1, "./log_[%s]", slogName);
		g_instance = 1;
		const char *slash = strrchr(gLogName, '/');

#ifdef _WIN32
		if (!slash)  slash = strrchr(gLogName, '\\');
#endif


		time_t timestamp = time(NULL);
		tm *tm_time = localtime(&timestamp);

		//日志文件名定
		sprintf(gLogFileName,
		        "./log_[%s]_%d%02d%02d",
		        slash ? slash + 1 : gLogName,
		        1900 + tm_time->tm_year,
		        1 + tm_time->tm_mon,
		        tm_time->tm_mday);

		//文件输出日志最小级别。
		google::SetLogDestination(google::GLOG_INFO, gLogFileName);
		//控制台输出日志最小级别。
		google::SetStderrLogging(google::GLOG_INFO);
		//google::SetLogDestination(google::GLOG_INFO, "./log_error");
		/*google::SetLogDestination(google::GLOG_WARNING, "./log_warning");*/
		/*google::SetLogDestination(google::GLOG_FATAL, "./log_");*/

		google::SetLogFilenameExtension(".log");
		//FLAGS_logbuflevel = 5;
		//控制台输出颜色
		FLAGS_colorlogtostderr = true;

		//输出文件名包含时间戳。（多文件）
		//FLAGS_timestamp_in_logfile_name = false;
		//所有日志到一个文件，
		//FLAGS_servitysinglelog = true;

		//磁盘满停止输出日志
		FLAGS_stop_logging_if_full_disk = true;
		//实时输出日志
		FLAGS_logbufsecs = 0;  // Set log output speed(s)
		//文件最大输出
		FLAGS_max_log_size = 1024;  // Set max log file size

#ifdef _WIN32
		std::setlocale(LC_ALL, "zh_CN.UTF-8");
		std::setlocale(LC_NUMERIC, "C");
		std::setlocale(LC_TIME, "zh_CN.UTF-8");
#endif

	}
	~Log()
	{
		google::ShutdownGoogleLogging();
	}
	//void StopLog() { google::ShutdownGoogleLogging(); }


};
