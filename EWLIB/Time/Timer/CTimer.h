/**
 * @file CTimer.h
 * @author Jinhee.Lee (tjrgl@naver.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __EWLIB_TIME_TIMER_CTIMER_H__
#define __EWLIB_TIME_TIMER_CTIMER_H__

#include "EWLIB/stdEWLIB.h"

namespace jlib
{
    class CTimer
    {
    public:
        explicit CTimer(const J_NANOSECOND_T interval,
                        J_CALLBACK_T<void(void)> _callback,
                        bool periodic = false,
                        J_NANOSECOND_T spin_threshold = J_NANOSECOND_T(5000)) noexcept;


        ~CTimer();

        void stop();
        void restart();
        void set_interval(J_NANOSECOND_T interval);

        J_STATE setCPUCore();

    private:
        void run();

    private:
        std::thread m_thread;
        std::mutex m_mutex;
        std::condition_variable m_cv;

        J_NANOSECOND_T m_interval;
        J_NANOSECOND_T m_spin_threshold;
        J_TIMEPOINT_T m_next_expire;
        J_CALLBACK_T<void(void)> m_callback;

        bool m_periodic;
        bool m_running;
    };
}
#endif