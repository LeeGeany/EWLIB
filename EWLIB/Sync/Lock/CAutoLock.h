/**
 * @file CAutoLock.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-10
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __EWLIB_SYNC_LOCK_CAUTOLOCK_H__
#define __EWLIB_SYNC_LOCK_CAUTOLOCK_H__

#include "EWLIB/stdEWLIB.h"

namespace EWLIB 
{
    struct lock_gaurd_t {};
    struct shared_lock_t{};
    struct unique_lock_t{};

    inline constexpr lock_gaurd_t     LOCK_GUARD_T {};
    inline constexpr shared_lock_t    SHARED_LOCK_T{};
    inline constexpr unique_lock_t    UNIQUE_LOCK_T{};

    enum class EC_LOCK_TYPE
    {
        LOCK_GRUARD,
        LOCK_SHARED,
        LOCK_UNIQUE
    };

    template<typename T>
    class CAutoLock
    {
    public:         
        explicit CAutoLock(T _mutex, lock_gaurd_t) noexcept
        : m_mutex(_mutex)
        , m_type(EC_LOCK_TYPE::LOCK_GRUARD)
        {
            if constexpr (std::is_base_of_v<std::mutex, T>) {
                m_mutex.lock();
            } else {
                static_assert(std::is_base_of_v<std::mutex, T>, "T must derive from Mutex\n");
            }
        }

        explicit CAutoLock(T _mutex, shared_lock_t) noexcept
        : m_mutex(_mutex)
        , m_type(EC_LOCK_TYPE::LOCK_SHARED)
        {
            if constexpr (std::is_base_of_v<std::shared_mutex, T>) {
                m_mutex.lock_shared();
            } else {
                static_assert(std::is_base_of_v<std::shared_mutex, T>, "T must derive from Mutex\n");
            }
        }

        explicit CAutoLock(T _mutex, unique_lock_t) noexcept
        : m_mutex(_mutex)
        , m_type(EC_LOCK_TYPE::LOCK_UNIQUE)
        {
            if constexpr (std::is_base_of_v<std::shared_mutex, T>) {
                m_mutex.lock();
            } else {
                static_assert(std::is_base_of_v<std::shared_mutex, T>, "T must derive from Mutex\n");
            }
        }

        virtual ~CAutoLock() noexcept
        {
            if(m_type == EC_LOCK_TYPE::LOCK_GRUARD) {

                m_mutex.unlock();

            } else if (m_type == EC_LOCK_TYPE::LOCK_SHARED) {

                m_mutex.unlock_shared();

            } else if(m_type == EC_LOCK_TYPE::LOCK_UNIQUE) {

                m_mutex.unlock();

            } else {
                /* Nothing to do */
            }
        }
    
    public:
        CAutoLock(const CAutoLock&) = delete;
        CAutoLock& operator=(const CAutoLock&) = delete;
        CAutoLock(CAutoLock&&) = delete;
        CAutoLock& operator=(CAutoLock&&) = delete;
    
    private:
        EC_LOCK_TYPE m_type;
        
        T &  m_mutex;
    }; /* class CAutoLock */
} /* namespace EWLIB */
#endif /* __EWLIB_SYNC_LOCK_CAUTOLOCK_H__ */