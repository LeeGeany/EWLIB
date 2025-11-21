/**
 * @file CMutex.h
 * @author Jinhee.Lee (tjrgl@naver.com)
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

namespace jlib
{
    class CMutex : std::mutex
    {
    public:
        CMutex() noexcept;
        virtual ~CMutex() noexcept;

    public:
        void lock();
        void try_lock();
        void unlock();
    }; /* class CMutex */
} /* namespace jlib */
#endif /* __EWLIB_SYNC_MUTEX_CMUTEX_H__ */