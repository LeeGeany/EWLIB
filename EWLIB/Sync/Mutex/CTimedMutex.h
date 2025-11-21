/**
 * @file CTimedMutex.h
 * @author Jinhee.Lee (tjrgl@naver.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "EWLIB/stdEWLIB.h"

namespace jlib
{
    class CTimedMutex
    {
    public:
        CTimedMutex() noexcept;
        virtual ~CTimedMutex() noexcept;

    public:
        void try_lock_for(J_MILLISECOND_T _timeOut);

    public:
        std::timed_mutex & native_handle();

    private:
        std::timed_mutex m_tm_mtx;
    }; /* class CMutex */
} /* namespace jlib */