/**
 * @file CMutex.cpp
 * @author Jinhee.Lee (jinhee.lee@lignex1.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "CMutex.h"

namespace EWLIB
{

    CMutex::CMutex() noexcept
    : m_type(EC_MUTEX_TYPE::NORMAL_MUTEX)
    {
    }

    CMutex::CMutex(normal_mutex _type) noexcept
    : m_type(EC_MUTEX_TYPE::NORMAL_MUTEX)
    {

    }

    CMutex::CMutex(time_mutex _type) noexcept
    : m_type(EC_MUTEX_TYPE::TIME_MUTEX)
    {

    }

    CMutex::~CMutex() noexcept
    {
    }

    void CMutex::lock()
    {
        m_mtx.lock();
    }

    void CMutex::try_lock()
    {
        m_mtx.try_lock();
    }

    void CMutex::try_lock_for(EW_MILLISECOND_T _timeOut)
    {
        m_tm_mtx.try_lock_for(_timeOut);
    }

    void CMutex::try_lock_until(EW_TIMEPOINT_T _timePoint)
    {
        m_tm_mtx.try_lock_until(_timePoint);
    }

    void CMutex::unlock()
    {
        m_mtx.unlock();
    }
} /* namespace EWLIB */