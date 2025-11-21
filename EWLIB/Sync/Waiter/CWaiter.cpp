/**
 * @file CWaiter.cpp
 * @author Jinhee.Lee (tjrgl@naver.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "CWaiter.h"

namespace jlib
{
    CWaiter::CWaiter() noexcept 
    : m_is_released(false)
    {
    }

    CWaiter::~CWaiter() noexcept
    {
    }

    void CWaiter::wait()
    {
        std::unique_lock<std::mutex> lock(m_mtx);
        m_cv.wait(lock, [this]() noexcept { return m_is_released.load(); });
        m_is_released.store(false); // 재사용 가능
    }

    // timeout 기능이 필요한 경우
    bool CWaiter::wait_for(J_MILLISECOND_T timeout)
    {
        std::unique_lock<std::mutex> lock(m_mtx);
        const bool signaled = m_cv.wait_for(
            lock,
            timeout,
            [this]() noexcept { return m_is_released.load(); });

        if (signaled)
        {
            m_is_released.store(false);
        }
        return signaled;
    }

    // 다른 스레드에서 깨움
    void CWaiter::release() noexcept
    {
        {
            std::lock_guard<std::mutex> lock(m_mtx);
            m_is_released.store(true);
        }
        m_cv.notify_one();
    }
} /* namespace EWLIB */