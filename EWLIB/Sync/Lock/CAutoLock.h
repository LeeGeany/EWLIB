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

namespace jlib 
{
    struct lock_gaurd_t {};
    struct shared_lock_t{};
    struct unique_lock_t{};

    inline constexpr lock_gaurd_t LOCK_GUARD_T = lock_gaurd_t{};
    inline constexpr shared_lock_t SHARED_LOCK_T = shared_lock_t{};
    inline constexpr unique_lock_t UNIQUE_LOCK_T = unique_lock_t{};

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
        /**
         * @brief Construct a new CAutoLock object
         * 
         * @param _mutex 
         */
        template<typename U = T, 
         std::enable_if_t<std::is_base_of_v<std::mutex, U>, int> = 0>
        explicit CAutoLock(T & _mutex, lock_gaurd_t) noexcept
        : m_mutex(_mutex)
        , m_type(EC_LOCK_TYPE::LOCK_GRUARD)
        {
            m_mutex.lock();
        }

        /**
         * @brief Construct a new CAutoLock object. Can be read together
         * 
         * @param _mutex 
         */
        template<typename U = T, 
         std::enable_if_t<std::is_base_of_v<std::shared_mutex, U>, int> = 0>
        explicit CAutoLock(T & _mutex, shared_lock_t) noexcept
        : m_mutex(_mutex)
        , m_type(EC_LOCK_TYPE::LOCK_SHARED)
        {
                m_mutex.lock_shared();
        }

        /**
         * @brief Construct a new CAutoLock object. Can not be read together
         * 
         * @param _mutex 
         */
        template<typename U = T, 
         std::enable_if_t<std::is_base_of_v<std::shared_mutex, U>, int> = 0>
        explicit CAutoLock(T &_mutex, unique_lock_t) noexcept
        : m_mutex(_mutex)
        , m_type(EC_LOCK_TYPE::LOCK_UNIQUE)
        {
            m_mutex.lock();
        }

        /**
         * @brief Destroy the CAutoLock object
         * 
         */
        virtual ~CAutoLock() noexcept
        {
            if(m_type == EC_LOCK_TYPE::LOCK_GRUARD) {

                m_mutex.unlock();

            } else if (m_type == EC_LOCK_TYPE::LOCK_SHARED) {
                if constexpr (std::is_base_of_v<std::shared_mutex, T>) {
                    m_mutex.unlock_shared();
                }
            } else if(m_type == EC_LOCK_TYPE::LOCK_UNIQUE) {

                m_mutex.unlock();

            } else {
                /* Nothing to do */
            }
        }

    private:
        EC_LOCK_TYPE m_type;
        
        T &  m_mutex;
    }; /* class CAutoLock */
} /* namespace jlib */
#endif /* __EWLIB_SYNC_LOCK_CAUTOLOCK_H__ */