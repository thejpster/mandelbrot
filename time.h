/*
 Cross platform time handling routines.
*/

#ifdef _WIN32

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

#else

#error Platform not supported

#endif