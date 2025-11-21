/**
 * @file CMutex.cpp
 * @author Jinhee.Lee (tjrgl@naver.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "CMutex.h"

namespace jlib
{

    CMutex::CMutex() noexcept
    {

    }

    CMutex::~CMutex() noexcept
    {

    }

    void CMutex::lock()
    {
        std::mutex::lock();
    }

    void CMutex::try_lock()
    {
        std::mutex::try_lock();
    }

    void CMutex::unlock()
    {
        std::mutex::unlock();
    }
} /* namespace jlib */