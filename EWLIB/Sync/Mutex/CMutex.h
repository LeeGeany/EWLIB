/**
 * @file CMutex.h
 * @author Jinhee.Lee (jinhee.lee@lignex1.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __EWLIB_SYNC_MUTEX_CMUTEX_H__
#define __EWLIB_SYNC_MUTEX_CMUTEX_H__

#include "EWLIB/stdEWLIB.h"

namespace EWLIB
{
    struct normal_mutex
    {
    };

    struct time_mutex
    {
    };

    inline constexpr normal_mutex normal_mutex_t;
    inline constexpr time_mutex time_mutex_t;

    enum class EC_MUTEX_TYPE
    {
          NORMAL_MUTEX
        , TIME_MUTEX
    };

    class CMutex
    {
    private:
        std::mutex m_mtx;
        std::timed_mutex m_tm_mtx;
        EC_MUTEX_TYPE m_type;

    public:
        CMutex() noexcept;
        CMutex(normal_mutex _type) noexcept;
        CMutex(time_mutex _type) noexcept;
        virtual ~CMutex() noexcept;

    public:
        void lock();
        void try_lock();
        void unlock();
        
    public:
        void try_lock_for(EW_MILLISECOND_T _timeOut);
        void try_lock_until(EW_TIMEPOINT_T _timePoint);


    }; /* class CMutex */
} /* namespace EWLIB */
#endif /* __EWLIB_SYNC_MUTEX_CMUTEX_H__ */