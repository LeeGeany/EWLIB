/**
 * @file CEpoll.h@
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __EWLIB_EVENT_EPOLL_CEPOLL_H__
#define __EWLIB_EVENT_EPOLL_CEPOLL_H__

#include "EWLIB/stdEWLIB.h"

namespace EWLIB
{
    class CEpoll
    {
    public:
        explicit CEpoll(uint32_t _maxEvent) noexcept;
        virtual ~CEpoll() noexcept;

    public:
        void addFd(int fd, uint32_t events, void* userData = nullptr);
        void modifyFd(int fd, uint32_t events, void* userData = nullptr);
        void removeFd(int fd);
        int wait(int timeoutMs);
        const struct epoll_event& getEvent(int index) const;
        [[nodiscard]] int fd() const noexcept;
        
    private:
        int m_epollFd;
        int m_maxEvents;
        std::vector<struct epoll_event> m_events;
    }; /* class CEpoll */
}; /* namespace EWLIB */
#endif /* __EWLIB_EVENT_EPOLL_CEPOLL_H__ */