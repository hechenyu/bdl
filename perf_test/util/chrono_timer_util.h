#ifndef __chrono_timer_util_h
#define __chrono_timer_util_h

#include "chrono_timer.h"

inline
ChronoTimer::duration sum(const std::vector<ChronoTimer> &timer_list)
{
    ChronoTimer::duration res = ChronoTimer::duration::zero();
    for (auto &timer: timer_list) {
        res += timer.elapsed();
    }
    return res;
}

inline
ChronoTimer::duration avg(const std::vector<ChronoTimer> &timer_list)
{
    return sum(timer_list)/timer_list.size();
}

#endif
