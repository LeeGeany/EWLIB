/**
 * @file CTimer.cpp
 * @author Jinhee.Lee (tjrgl@naver.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "CTimer.h"

namespace jlib
{
    CTimer::CTimer(const J_NANOSECOND_T interval,
                J_CALLBACK_T<void(void)> _callback,
                bool periodic,
                J_NANOSECOND_T spin_threshold) noexcept
    : m_interval(interval)
    , m_callback(_callback)
    , m_periodic(periodic)
    , m_spin_threshold(spin_threshold)
    , m_running(true)
    {
        m_next_expire = J_CLOCK_T::now() + m_interval;
        m_thread = std::thread(&CTimer::run, this);
    }

    CTimer::~CTimer()
    {
        stop();
    }

    void CTimer::stop()
    {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_running = false;
        }
        m_cv.notify_all();
        if (m_thread.joinable())
            m_thread.join();
    }

    void CTimer::restart()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_next_expire = J_CLOCK_T::now() + m_interval;
        m_running = true;
        m_cv.notify_all();
    }

    void CTimer::set_interval(J_NANOSECOND_T interval)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_interval = interval;
    }

    J_STATE CTimer::setCPUCore()
    {
        J_STATE Ret = true;
    #ifdef LINUX
        pthread_t native_handle = m_worker.native_handle();
        
        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        CPU_SET(2, &cpuset); // CPU 0 고정

        pthread_setaffinity_np(native_handle, sizeof(cpu_set_t), &cpuset) != 0 ? Ret = false : Ret = true;
    #endif
        return Ret;
    }

    void CTimer::run()
    {
        std::unique_lock<std::mutex> lock(m_mutex);

        while (m_running)
        {
            J_TIMEPOINT_T now = J_CLOCK_T::now();

            if (m_next_expire > now)
            {
                m_cv.wait_until(lock, m_next_expire, [this]{ return !m_running; });
                if (!m_running) break;
                now = J_CLOCK_T::now();
            }

            // Spin threshold
            J_NANOSECOND_T remaining = m_next_expire - now;
            if (remaining.count() > 0 && remaining <= m_spin_threshold)
            {
                while (J_CLOCK_T::now() < m_next_expire) {
                    // busy spin
                }
            }

            // Execute callback
            lock.unlock();
            try { m_callback(); } catch (...) {}
            lock.lock();

            if (m_periodic)
            {
                m_next_expire += m_interval;
            }
            else
            {
                m_running = false;
            }
        }
    }
} /* namespace jlib */