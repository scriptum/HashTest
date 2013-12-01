/* http://stackoverflow.com/questions/17432502/how-can-i-measure-cpu-time-and-wall-clock-time-on-both-linux-windows */

/* Windows */
#ifdef _WIN32

#include <Windows.h>
static inline double get_wall_time()
{
    LARGE_INTEGER time, freq;
    if(!QueryPerformanceFrequency(&freq))
        return 0;
    if(!QueryPerformanceCounter(&time))
        return 0;
    return (double)time.QuadPart / freq.QuadPart;
}

static inline double get_cpu_time()
{
    FILETIME a, b, c, d;
    if(GetProcessTimes(GetCurrentProcess(),&a,&b,&c,&d) != 0)
    {
        return
            (double)(d.dwLowDateTime |
            ((unsigned long long)d.dwHighDateTime << 32)) * 0.0000001;
    }
    else
    {
        return 0;
    }
}

/* Posix/Linux */
#else

#include <time.h>
#include <sys/time.h>
static inline double get_wall_time()
{
    struct timeval time;
    if (gettimeofday(&time,NULL))
    {
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

static inline double get_cpu_time()
{
    return (double)clock() / CLOCKS_PER_SEC;
}
#endif

static double perf_start_time;
static double perf_end_time;

static inline void perf_timer_start()
{
	perf_start_time = get_cpu_time();
}

static inline void perf_timer_end()
{
	perf_end_time = get_cpu_time();
}

static inline double perf_timer_get()
{
	return perf_end_time - perf_start_time;
}

static inline void perf_timer_print()
{
	printf("%.3g\n", perf_timer_get());
}
