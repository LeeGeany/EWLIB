/**
 * @file CTCPSocket.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-29
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "CTCPSocket.h"

namespace jlib
{
    CTCPSocket::CTCPSocket() noexcept
    {
        m_fd = ::socket(AF_INET, SOCK_STREAM, 0);
    }

    CTCPSocket::CTCPSocket(int fd) noexcept
    : m_fd(fd)
    {
    }

    CTCPSocket::~CTCPSocket()
    {
        Close();
    }

    int CTCPSocket::GetFd() const
    {
        return m_fd;
    }

    bool CTCPSocket::SetNonBlocking(bool enable)
    {
        int flags = fcntl(m_fd, F_GETFL, 0);
        if (flags < 0) return false;

        if (enable)
            return fcntl(m_fd, F_SETFL, flags | O_NONBLOCK) == 0;
        else
            return fcntl(m_fd, F_SETFL, flags & ~O_NONBLOCK) == 0;
    }

    bool CTCPSocket::Close()
    {
        if (m_fd > 0) {
            ::close(m_fd);
            m_fd = -1;
        }
        return true;
    }


    ssize_t CTCPSocket::Send(const void* buf, size_t len)
    {
        return ::send(m_fd, buf, len, 0);
    }

    ssize_t CTCPSocket::Recv(void* buf, size_t len)
    {
        return ::recv(m_fd, buf, len, 0);
    }

}