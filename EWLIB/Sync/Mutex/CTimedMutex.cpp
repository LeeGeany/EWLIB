/**
 * @file CTimedMutex.cpp
 * @author Jinhee.Lee (tjrgl@naver.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "CTimedMutex.h"

namespace jlib
{
    CTimedMutex::CTimedMutex() noexcept
    {

    }

    CTimedMutex::~CTimedMutex() noexcept
    {

    }

    void CTimedMutex::try_lock_for(J_MILLISECOND_T _timeOut)
    {
        m_tm_mtx.try_lock_for(_timeOut);
    }

    std::timed_mutex & CTimedMutex::native_handle()
    {
        return m_tm_mtx;
    }
} /* namespace jlib */