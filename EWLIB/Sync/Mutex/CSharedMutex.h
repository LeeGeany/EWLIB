/**
 * @file CSharedMutex.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-07
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __EWLIB_SYNC_MUTEX_CSHAREDMUTEX_H__
#define __EWLIB_SYNC_MUTEX_CSHAREDMUTEX_H__

#include "EWLIB/stdEWLIB.h"

namespace EWLIB
{
    class CSharedMutex : public std::shared_mutex
    {
    public:
        CSharedMutex();
        virtual ~CSharedMutex();
    
    public:
        void lock();
        void try_lock();
        void unlock();
        
    public:
        void lock_shared();
        void try_lock_shared();
        void unlock_shared();

    }; /* class CShared_mutex */
} /* namespace EWLIB */
#endif /* __EWLIB_SYNC_MUTEX_CSHAREDMUTEX_H__ */