/**
 * @file CSharedMutex.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-07
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "CSharedMutex.h"

namespace EWLIB
{

    CSharedMutex::CSharedMutex()
    {

    }

    CSharedMutex::~CSharedMutex()
    {

    }

    void CSharedMutex::lock()
    {
        shared_mutex::lock();

    }

    void CSharedMutex::try_lock()
    {
        shared_mutex::try_lock();
    }

    void CSharedMutex::unlock()
    {
        shared_mutex::unlock();
    }
    
    void CSharedMutex::lock_shared()
    {
        shared_mutex::lock_shared();
    }

    void CSharedMutex::try_lock_shared()
    {
        shared_mutex::try_lock_shared();
    }

    void CSharedMutex::unlock_shared()
    {
        shared_mutex::unlock_shared();
    }

} /* namespace EWLIB */