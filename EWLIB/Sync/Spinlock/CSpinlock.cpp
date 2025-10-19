/**
 * @file CSpinlock.cpp
 * @author Jinhee.Lee (jinhee.lee@lignex1.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "CSpinlock.h"

namespace EWLIB
{

    CSpinlock::CSpinlock() noexcept
    : m_flag(ATOMIC_FLAG_INIT)
    {
    }

    CSpinlock::~CSpinlock() noexcept
    {
    }

    void CSpinlock::lock() noexcept
    {
        while(m_flag.test_and_set(std::memory_order_acquire))
        {      
            CPU_PAUSE();
        }
    }

    void CSpinlock::unlock() noexcept
    {
        m_flag.clear(std::memory_order_release);
    }

    bool CSpinlock::try_lock() noexcept
    {
        return !m_flag.test_and_set(std::memory_order_acquire);
    }
    
    void CSpinlock::CPU_PAUSE()
    {
#if defined(__x86_64__) || defined(__i386__)
        __builtin_ia32_pause();
#elif defined(__arm__) || defined(__aarch64__)
        __asm__ volatile("yield");
#else
        /* Nothing to do */
#endif
    }

} /* EWLIB */