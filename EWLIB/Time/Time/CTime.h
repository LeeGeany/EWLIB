/**
 * @file CTime.h
 * @author Jinhee.Lee (tjrgl@naver.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef _EWLIB_TIME_TIME_CTIME_H__
#define _EWLIB_TIME_TIME_CTIME_H__

#include "EWLIB/stdEWLIB.h"

namespace jlib
{
    struct ST_SYSTEM_TIME_T
    {
        std::int64_t seconds;
        std::int64_t nanoseconds;
    };

    class CTime
    {
    public:
        CTime();
        virtual ~CTime();

    public:
        ST_SYSTEM_TIME_T getSystemTime() noexcept;
        std::string getSystemTimeString() noexcept;
        bool set_system_time(const ST_SYSTEM_TIME_T& new_time) noexcept;


    private:
        std::string to_string(const ST_SYSTEM_TIME_T& time) noexcept;
        inline constexpr bool is_leap_year(int year) noexcept;
        
    private:
        ST_SYSTEM_TIME_T m_tm;
    }; /* class CTime */

    


} /* namespace EWLIB */
#endif /* _EWLIB_TIME_TIME_CTIME_H__ */