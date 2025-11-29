/**
 * @file CUDPSocket.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-29
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "CUDPSocket.h"

namespace jlib
{
    CUDPSocket::CUDPSocket()
    {
        m_fd = ::socket(AF_INET, SOCK_DGRAM, 0);
    }

    CUDPSocket::CUDPSocket(int fd)
        : m_fd(fd)
    {}

    CUDPSocket::~CUDPSocket()
    {
        Close();
    }

    int CUDPSocket::GetFd() const
    {
        return m_fd;
    }

    bool CUDPSocket::SetNonBlocking(bool enable)
    {
        int flags = fcntl(m_fd, F_GETFL, 0);
        if (flags < 0) return false;

        if (enable)
            return fcntl(m_fd, F_SETFL, flags | O_NONBLOCK) == 0;
        else
            return fcntl(m_fd, F_SETFL, flags & ~O_NONBLOCK) == 0;
    }

    bool CUDPSocket::Close()
    {
        if (m_fd > 0) {
            ::close(m_fd);
            m_fd = -1;
        }
        return true;
    }

    ssize_t CUDPSocket::Send(const void* buf, size_t len)
    {
        return ::send(m_fd, buf, len, 0);
    }

    ssize_t CUDPSocket::Recv(void* buf, size_t len)
    {
        return ::recv(m_fd, buf, len, 0);
    }

    ssize_t CUDPSocket::SendTo(const void* buf, size_t len, const sockaddr_in& addr)
    {
        return ::sendto(m_fd, buf, len, 0, (sockaddr*)&addr, sizeof(addr));
    }

    ssize_t CUDPSocket::RecvFrom(void* buf, size_t len, sockaddr_in& addr)
    {
        socklen_t addrlen = sizeof(addr);
        return ::recvfrom(m_fd, buf, len, 0, (sockaddr*)&addr, &addrlen);
    }
} /* namespace jlib */