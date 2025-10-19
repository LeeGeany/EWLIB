/**
 * @file CTime.h
 * @author your name (you@domain.com)
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

namespace EWLIB
{
    class CTime
    {
    public:
        CTime();
        virtual ~CTime();

    public:
        [[nodiscard]] ST_SYSTEM_TIME_T get_system_time() noexcept;
        [[nodiscard]] bool set_system_time(const ST_SYSTEM_TIME_T& new_time) noexcept;
        [[nodiscard]] std::string to_string(const ST_SYSTEM_TIME_T& time) noexcept;

    private:
        [[nodiscard]] constexpr bool is_leap_year(int year) noexcept;
        
    private:
        ST_SYSTEM_TIME_T m_tm;
    }; /* class CTime */
} /* namespace EWLIB */
#endif /* _EWLIB_TIME_TIME_CTIME_H__ */