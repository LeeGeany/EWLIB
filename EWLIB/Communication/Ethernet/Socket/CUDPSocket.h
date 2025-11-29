/**
 * @file CUDPSocket.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-29
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __EWLIB_COMMUNICATION_ETHERNET_CUDPSOCKET_H__
#define __EWLIB_COMMUNICATION_ETHERNET_CUDPSOCKET_H__

#include "ISocket.h"

namespace jlib
{
    class CUDPSocket : public ISocket 
    {
    public:
        CUDPSocket();
        explicit CUDPSocket(int fd);
        ~CUDPSocket();

        int  GetFd() const override;
        bool SetNonBlocking(bool enable) override;
        bool Close() override;

        ssize_t Send(const void* buf, size_t len) override;
        ssize_t Recv(void* buf, size_t len) override;

        ssize_t SendTo(const void* buf, size_t len, const sockaddr_in& addr);
        ssize_t RecvFrom(void* buf, size_t len, sockaddr_in& addr);

    private:
        int m_fd;
    };
} /* namespace jlib */
#endif /* __EWLIB_COMMUNICATION_ETHERNET_CUDPSOCKET_H__ */