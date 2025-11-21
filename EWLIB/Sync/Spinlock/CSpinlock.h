/**
 * @file CSpinlock.h
 * @author Jinhee.Lee (tjrgl@naver.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __EWLIB_SYNC_CSPINLOCK_H__
#define __EWLIB_SYNC_CSPINLOCK_H__

#include "EWLIB/stdEWLIB.h"

namespace jlib
{
    class CSpinlock
    {
    public:
        CSpinlock() noexcept;
        virtual ~CSpinlock() noexcept;

    public:
        void lock() noexcept;
        void unlock() noexcept;
        bool try_lock() noexcept;

    private:
        void CPU_PAUSE();
    
    private:
        std::atomic_flag m_flag;

    };

} /* EWLIB */
#endif /* __EWLIB_SYNC_CSPINLOCK_H__ */