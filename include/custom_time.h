#ifndef CUSTOM_TIME_H
#define CUSTOM_TIME_H

#include <sys/time.h>
#include <stdlib.h>
#include <stdint.h>

double get_time_s_double(void)
{
    double tm;
    struct timeval tim;

    gettimeofday(&tim, NULL);

    tm = (double)tim.tv_sec + tim.tv_usec / 1000000.0;

    return tm;
}

uint64_t get_time_now_us()
{
    timeval tim;
    gettimeofday(&tim, NULL);
    return 1.0e3 * tim.tv_sec + tim.tv_usec * 1.0e-3;
}

uint64_t get_time_now_ms()
{
    timeval tim;
    gettimeofday(&tim, NULL);
    return 1.0e6 * tim.tv_sec + tim.tv_usec;
}

uint64_t get_time_now_s()
{
    timeval tim;
    gettimeofday(&tim, NULL);
    return tim.tv_sec;
}

#endif