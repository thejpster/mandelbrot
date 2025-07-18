/*
 Cross platform time handling routines.
*/

#if defined(_WIN32)

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

typedef struct my_time_t
{
    DWORD milliseconds;
} my_time_t;

static my_time_t time_get(void)
{
    my_time_t t;
    t.milliseconds = GetTickCount();
    return t;
}

static float time_diff(my_time_t start, my_time_t end, unsigned long num_pixels)
{
    DWORD delta = end.milliseconds - start.milliseconds;
    float result = ((float)num_pixels / (float)delta);
    return result;
}

#elif defined(__linux__) || defined(__APPLE__) || defined(__unix) || defined(unix)

#include <sys/time.h>

#if defined(__sgi)||defined(__sun)||defined(__hpux)
// nothing required
#elif defined(NeXT)
// stdint.h not available - but unsigned long long is 64 bits
typedef unsigned long long uint64_t;
#else
#include <stdint.h>
#endif

#include <stdlib.h>

typedef struct my_time_t
{
    struct timeval timeval;
} my_time_t;

static my_time_t time_get(void)
{
    my_time_t t;
    int result = gettimeofday(&t.timeval, NULL);
    if (result != 0)
    {
        perror("gettimeofday");
        exit(1);
    }
    return t;
}

static float time_diff(my_time_t start, my_time_t end, unsigned long num_pixels)
{
    uint64_t start_us = (uint64_t)start.timeval.tv_usec + ((uint64_t)start.timeval.tv_sec * 1000000);
    uint64_t end_us = (uint64_t)end.timeval.tv_usec + ((uint64_t)end.timeval.tv_sec * 1000000);
    uint64_t delta = end_us - start_us;
    float result = (((float)num_pixels / (float)delta) * 1000.0);
    return result;
}

#else

#error Platform not supported

#endif
