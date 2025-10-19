/**
 * @file CTimer.h
 * @author Jinhee.Lee (jinhee.lee@lignex1.com)
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

namespace EWLIB
{
    using EW_PRECISION_TIMER_ID_T = std::size_t;

    struct ST_TIMER_TASK_T
    {
        EW_PRECISION_TIMER_ID_T id;
        EW_TIMEPOINT_T          next_expire;
        EW_NANOSECOND_T         interval;
        EW_CALLBACK_T           callback;
        bool                    periodic;
        bool                    active;
    };

    class CTimer
    {
    public:
        explicit CTimer(const EW_NANOSECOND_T spin_threshold = EW_NANOSECOND_T(100000));
        virtual ~CTimer();

    public:
        STATUS initTimer();

        EW_PRECISION_TIMER_ID_T addTimer(const EW_NANOSECOND_T _interval, EW_CALLBACK_T _callback, const bool _periodic);
        EW_PRECISION_TIMER_ID_T addTimer(const EW_MICROSECOND_T _interval, EW_CALLBACK_T _callback, const bool _periodic);
        EW_PRECISION_TIMER_ID_T addTimer(const EW_MILLISECOND_T _interval, EW_CALLBACK_T _callback, const bool _periodic);

        STATUS cancelTimer(const EW_PRECISION_TIMER_ID_T id);

        void stop() noexcept;

        void set_spin_threshold(const EW_NANOSECOND_T _threshold) noexcept;
        
    private:
        void run();

    private:
        std::atomic<bool>                       m_running;
        std::atomic<EW_PRECISION_TIMER_ID_T>    m_next_id;
        std::thread                             m_worker;
        std::mutex                              m_mutex;
        std::condition_variable                 m_cv;
        std::vector<ST_TIMER_TASK_T>            m_tasks;
        std::atomic<long long>                  m_spin_threshold;

    }; /* class CTimer */
} /* namespace EWLIB */
#endif /* __EWLIB_TIME_TIMER_CTIMER_H__ */