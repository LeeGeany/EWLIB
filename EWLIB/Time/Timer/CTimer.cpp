/**
 * @file CTimer.cpp
 * @author Jinhee.Lee (jinhee.lee@lignex1.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "CTimer.h"

namespace EWLIB
{

    CTimer::CTimer(const EW_NANOSECOND_T _spin_threshold)
    : m_running(true)
    , m_next_id(0U)
    , m_spin_threshold(_spin_threshold.count())
    {
        m_worker = std::thread(&CTimer::run, this);
    }

    CTimer::~CTimer()
    {
        stop();
    }

    STATUS CTimer::initTimer()
    {
        STATUS Ret = true;
        pthread_t native_handle = m_worker.native_handle();
        
        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        CPU_SET(2, &cpuset); // CPU 0 고정

        pthread_setaffinity_np(native_handle, sizeof(cpu_set_t), &cpuset) != 0 ? Ret = false : Ret = true;
        
        return Ret;
    }

    EW_PRECISION_TIMER_ID_T CTimer::addTimer(const EW_NANOSECOND_T _interval, EW_CALLBACK_T _callback, const bool _periodic)
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        ST_TIMER_TASK_T task = {
            .id             = m_next_id++                       ,
            .next_expire    = EW_CLOCK_T::now() + _interval     ,
            .interval       = _interval                         ,
            .callback       = _callback                         ,
            .periodic       = _periodic                         ,
            .active         = true
        };

        m_tasks.push_back(task);
        m_cv.notify_all();
        return task.id;
    }

    EW_PRECISION_TIMER_ID_T CTimer::addTimer(const EW_MICROSECOND_T _interval_us, EW_CALLBACK_T _callback, const bool _periodic)
    {
        return addTimer(std::chrono::duration_cast<EW_NANOSECOND_T>(_interval_us), _callback, _periodic);
    }

    EW_PRECISION_TIMER_ID_T CTimer::addTimer(const EW_MILLISECOND_T _interval_ms, EW_CALLBACK_T _callback, const bool _periodic)
    {
        return addTimer(std::chrono::duration_cast<EW_NANOSECOND_T>(_interval_ms), _callback, _periodic);
    }

    STATUS CTimer::cancelTimer(const EW_PRECISION_TIMER_ID_T id)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        STATUS Ret = false;

        for(auto & t : m_tasks)
        {
            if(t.id == id && t.active) {
                t.active = false;
                Ret = true;
            }
        }

        if(Ret)
        {
            m_cv.notify_all();
        }

        return Ret;
    }

    void CTimer::stop() noexcept
    {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_running = false;
        }

        m_cv.notify_all();
        if(m_worker.joinable())
        {
            m_worker.join();
        }
    }

    void CTimer::set_spin_threshold(const EW_NANOSECOND_T _threshold) noexcept
    {
        m_spin_threshold.store(_threshold.count(), std::memory_order_relaxed);
    }

    // void CTimer::run()
    // {
    //     std::unique_lock<std::mutex> lock(m_mutex);

    //     while (m_running)
    //     {
    //         if (m_tasks.empty())
    //         {
    //             // 타이머가 없으면 대기
    //             m_cv.wait(lock, [this]{ return !m_running || !m_tasks.empty(); });
    //         }
    //         else
    //         {
    //             // 다음 만료 시각 찾기
    //             auto next_it = std::min_element(m_tasks.begin(), m_tasks.end(),
    //                 [](const ST_TIMER_TASK_T& a, const ST_TIMER_TASK_T& b)
    //                 {
    //                     return a.next_expire < b.next_expire;
    //                 });

    //             if (next_it != m_tasks.end())
    //             {
    //                 EW_TIMEPOINT_T now = EW_CLOCK_T::now();
    //                 EW_TIMEPOINT_T target = next_it->next_expire;

    //                 if (target > now)
    //                 {
    //                     // wait_until로 대기
    //                     m_cv.wait_until(lock, target, [this]{ return !m_running; });
    //                     now = EW_CLOCK_T::now();
    //                 }

    //                 // spin_threshold 적용
    //                 const auto spin_thr = EW_NANOSECOND_T(m_spin_threshold.load(std::memory_order_relaxed));

    //                 for (auto & t : m_tasks)
    //                 {
    //                     if (t.active && t.next_expire <= now)
    //                     {
    //                         const EW_TIMEPOINT_T scheduled_time = t.next_expire;
    //                         const EW_NANOSECOND_T interval = t.interval;
    //                         const bool periodic = t.periodic;
    //                         EW_CALLBACK_T cb = t.callback;

    //                         // spin 보정
    //                         EW_TIMEPOINT_T before_spin = EW_CLOCK_T::now();
    //                         if (scheduled_time > before_spin)
    //                         {
    //                             const auto rem = scheduled_time - before_spin;
    //                             if (rem <= spin_thr)
    //                             {
    //                                 while (EW_CLOCK_T::now() < scheduled_time)
    //                                 {
    //                                     // busy-spin
    //                                 }
    //                             }
    //                         }

    //                         // 콜백 실행
    //                         lock.unlock();
    //                         EW_TIMEPOINT_T cb_start = EW_CLOCK_T::now();
    //                         try
    //                         {
    //                             cb();
    //                         }
    //                         catch (...)
    //                         {
    //                             // MISRA: 예외 전파 금지
    //                         }
    //                         EW_TIMEPOINT_T cb_end = EW_CLOCK_T::now();
    //                         lock.lock();

    //                         // 정밀 보정
    //                         if (periodic && t.active)
    //                         {
    //                             t.next_expire = scheduled_time + interval;
    //                             if (cb_end >= t.next_expire)
    //                             {
    //                                 auto diff = cb_end - t.next_expire;
    //                                 std::uint64_t missed = 0U;
    //                                 if (interval.count() > 0)
    //                                 {
    //                                     missed = static_cast<std::uint64_t>(diff.count() / interval.count()) + 1U;
    //                                 }
    //                                 t.next_expire += EW_NANOSECOND_T(static_cast<std::int64_t>(missed) * interval.count());
    //                             }
    //                         }
    //                         else
    //                         {
    //                             t.active = false;
    //                         }
    //                     }
    //                 }

    //                 // 비활성 타이머 제거
    //                 m_tasks.erase(std::remove_if(m_tasks.begin(), m_tasks.end(),
    //                     [](const ST_TIMER_TASK_T& t){ return !t.active; }),
    //                     m_tasks.end());
    //             }
    //             else
    //             {
    //                 // next_it가 없으면 그냥 대기
    //                 m_cv.wait(lock);
    //             }
    //         } // else tasks_.empty()
    //     } // while
    // }

    void CTimer::run()
    {
        std::unique_lock<std::mutex> lock(m_mutex);

        while (m_running)
        {
            if (m_tasks.empty())
            {
                // 타이머 없으면 대기
                m_cv.wait(lock, [this]{ return !m_running || !m_tasks.empty(); });
            }
            else
            {
                auto next_it = std::min_element(m_tasks.begin(), m_tasks.end(),
                    [](const ST_TIMER_TASK_T& a, const ST_TIMER_TASK_T& b)
                    {
                        return a.next_expire < b.next_expire;
                    });

                if (next_it != m_tasks.end())
                {
                    EW_TIMEPOINT_T now = EW_CLOCK_T::now();
                    EW_TIMEPOINT_T target = next_it->next_expire;

                    if (target > now)
                    {
                        // 목표 시각까지 condition_variable로 대기
                        m_cv.wait_until(lock, target, [this]{ return !m_running; });
                        now = EW_CLOCK_T::now();
                    }

                    const EW_NANOSECOND_T spin_thr = EW_NANOSECOND_T(m_spin_threshold.load(std::memory_order_relaxed));

                    for (auto & t : m_tasks)
                    {
                        if (t.active && t.next_expire <= now)
                        {
                            EW_TIMEPOINT_T scheduled_time = t.next_expire;
                            EW_NANOSECOND_T interval = t.interval;
                            bool periodic = t.periodic;
                            EW_CALLBACK_T cb = t.callback;

                            // spin_threshold 기반 busy-spin
                            EW_TIMEPOINT_T before_spin = EW_CLOCK_T::now();
                            if ((scheduled_time > before_spin) && ((scheduled_time - before_spin) <= spin_thr))
                            {
                                while (EW_CLOCK_T::now() < scheduled_time)
                                {
                                    // busy-spin
                                }
                            }

                            // 콜백 실행
                            lock.unlock();
                            try
                            {
                                cb();
                            }
                            catch (...)
                            {
                                // MISRA: 예외 전파 금지
                            }
                            lock.lock();

                            // 주기적 타이머 보정
                            if (periodic && t.active)
                            {
                                t.next_expire = scheduled_time + interval;
                                if (EW_CLOCK_T::now() >= t.next_expire)
                                {
                                    auto diff = EW_CLOCK_T::now() - t.next_expire;
                                    std::uint64_t missed = 0U;
                                    if (interval.count() > 0)
                                    {
                                        missed = static_cast<std::uint64_t>(diff.count() / interval.count()) + 1U;
                                    }
                                    t.next_expire += EW_NANOSECOND_T(static_cast<std::int64_t>(missed) * interval.count());
                                }
                            }
                            else
                            {
                                t.active = false;
                            }
                        }
                    }

                    // 비활성 타이머 제거
                    m_tasks.erase(std::remove_if(m_tasks.begin(), m_tasks.end(),
                        [](const ST_TIMER_TASK_T& t){ return !t.active; }),
                        m_tasks.end());
                }
                else
                {
                    // next_it가 없으면 그냥 대기
                    m_cv.wait(lock);
                }
            }
        }
    }

} /* namespace EWLIB */