/**
 * @file CEpoll.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "CEpoll.h"

namespace jlib
{
    CEpoll::CEpoll(uint32_t _maxEvent) noexcept
    : m_epollFd(::epoll_create1(EPOLL_CLOEXEC)), m_maxEvents(_maxEvent)
    {
        m_events.resize(static_cast<std::size_t>(m_maxEvents));
    }

    CEpoll::~CEpoll() noexcept
    {
        if (m_epollFd != -1)
        {
            ::close(m_epollFd);
        }
    }

    void CEpoll::addFd(int fd, uint32_t events, void* userData)
    {
        struct epoll_event ev{};
        ev.events = events;
        ev.data.ptr = userData;
        if (::epoll_ctl(m_epollFd, EPOLL_CTL_ADD, fd, &ev) == -1)
        {
            throw std::runtime_error(std::string("epoll_ctl ADD failed: ") + std::strerror(errno));
        }
    }

    void CEpoll::modifyFd(int fd, uint32_t events, void* userData )
    {
        struct epoll_event ev{};
        ev.events = events;
        ev.data.ptr = userData;
        if (::epoll_ctl(m_epollFd, EPOLL_CTL_MOD, fd, &ev) == -1)
        {
            throw std::runtime_error(std::string("epoll_ctl MOD failed: ") + std::strerror(errno));
        }
    }

    void CEpoll::removeFd(int fd)
    {
        if (::epoll_ctl(m_epollFd, EPOLL_CTL_DEL, fd, nullptr) == -1)
        {
            throw std::runtime_error(std::string("epoll_ctl DEL failed: ") + std::strerror(errno));
        }
    }

    int CEpoll::wait(int timeoutMs)
    {
        const int n = ::epoll_wait(m_epollFd, m_events.data(), m_maxEvents, timeoutMs);
        if (n == -1)
        {
            if (errno == EINTR)
            {
                return 0; // interrupted, safe to continue
            }
            throw std::runtime_error(std::string("epoll_wait failed: ") + std::strerror(errno));
        }
        return n;
    }

    const struct epoll_event& CEpoll::getEvent(int index) const
    {
        return m_events.at(static_cast<std::size_t>(index));
    }

    [[nodiscard]] int CEpoll::fd() const noexcept 
    { 
        return m_epollFd; 
    }
};
