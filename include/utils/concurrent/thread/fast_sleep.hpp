
namespace fast
{
//msc毫秒
int sleep(int millisecond)
{
#ifdef _WIN32
	Sleep(msc);
#else
	struct timespec ts = {millisecond / 1000, (millisecond % 1000) * 1000 * 1000};
	nanosleep(&ts, NULL);
#endif
}
}
