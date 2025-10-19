/**
 * @file CWaiter.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __EWLIB_SYNC_WAITER_CWAITER_H__
#define __EWLIB_SYNC_WAITER_CWAITER_H__

#include "EWLIB/stdEWLIB.h"

namespace EWLIB
{
    class CWaiter
    {
    public:
        CWaiter() noexcept;
        virtual ~CWaiter() noexcept;

    public:
        void wait();
        bool wait_for(const std::chrono::milliseconds timeout);
        void release() noexcept;

    private:
        std::mutex m_mtx;
        std::condition_variable m_cv;
        std::atomic<bool> m_is_released;
    };
} /* namespace EWLIB */
#endif /*  __EWLIB_SYNC_WAITER_CWAITER_H__ */