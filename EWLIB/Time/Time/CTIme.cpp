/**
 * @file CTIme.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "CTime.h"

namespace EWLIB
{

    CTime::CTime()
    : m_tm({0,0})
    {
    }

    CTime::~CTime()
    {
    }

    [[nodiscard]] ST_SYSTEM_TIME_T CTime::get_system_time() noexcept
    {
        struct timespec ts;
        ST_SYSTEM_TIME_T time{};
        if (std::timespec_get(&ts, TIME_UTC) == 0)
        {
            time =  ST_SYSTEM_TIME_T{0, 0};
        } else {
            time =  ST_SYSTEM_TIME_T{static_cast<std::int64_t>(ts.tv_sec), static_cast<std::int64_t>(ts.tv_nsec)};
        }
        return time;
    }

    [[nodiscard]] bool CTime::set_system_time(const ST_SYSTEM_TIME_T& new_time) noexcept
    {
        struct timespec ts;
        ts.tv_sec = static_cast<time_t>(new_time.seconds);
        ts.tv_nsec = static_cast<long>(new_time.nanoseconds);

        return (::clock_settime(CLOCK_REALTIME, &ts) == 0);
    }

    [[nodiscard]] std::string CTime::to_string(const ST_SYSTEM_TIME_T& time) noexcept
    {
        // 총 초를 분해
        std::int64_t total_seconds = time.seconds + 9 * 3600;
        constexpr std::int64_t sec_per_day = 86400;
        constexpr std::int64_t sec_per_hour = 3600;
        constexpr std::int64_t sec_per_min  = 60;

        std::int64_t days = total_seconds / sec_per_day;
        std::int64_t sec_of_day = total_seconds % sec_per_day;

        std::int64_t hours = (sec_of_day ) / sec_per_hour;
        std::int64_t minutes = (sec_of_day % sec_per_hour) / sec_per_min;
        std::int64_t seconds = sec_of_day % sec_per_min;

        // 1970년 1월 1일 기준으로 연도 계산
        int year = 1970;
        while (true)
        {
            int days_in_year = is_leap_year(year) ? 366 : 365;
            if (days >= days_in_year)
            {
                days -= days_in_year;
                ++year;
            }
            else
            {
                break;
            }
        }

        // 월 계산
        constexpr int days_in_month_normal[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        constexpr int days_in_month_leap[12]   = { 31,29,31,30,31,30,31,31,30,31,30,31 };

        const int* dim = is_leap_year(year) ? days_in_month_leap : days_in_month_normal;

        int month = 0;
        while (days >= dim[month])
        {
            days -= dim[month];
            ++month;
        }


        std::string buf; buf.resize(32);
        std::snprintf(buf.data(), buf.size(),
                    "%04d-%02d-%02ld %02lld:%02lld:%02lld",
                    year, month + 1, days + 1,
                    static_cast<long long>(hours),
                    static_cast<long long>(minutes),
                    static_cast<long long>(seconds));
        return buf;
    }

    [[nodiscard]] constexpr bool CTime::is_leap_year(int year) noexcept
    {
        return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
    }

} /* namespace EWLIB */