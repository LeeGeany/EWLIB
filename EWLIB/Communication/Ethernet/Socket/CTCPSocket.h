/**
 * @file CTCPSocket.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-29
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __EWLIB_COMMUNICATION_ETHERNET_CTCPSOCKET_H__
#define __EWLIB_COMMUNICATION_ETHERNET_CTCPSOCKET_H__

#include "EWLIB/stdEWLIB.h"
#include "ISocket.h"

namespace jlib
{
    class CTCPSocket : public ISocket 
    {
    public:
        CTCPSocket() noexcept;
        explicit CTCPSocket(int fd) noexcept;
        ~CTCPSocket();

        int  GetFd() const override;
        bool SetNonBlocking(bool enable) override;
        bool Close() override;

        virtual ssize_t Send(const void* buf, size_t len) override;
        virtual ssize_t Recv(void* buf, size_t len) override;

    private:
        int m_fd;
    };
} /* namespace jlib */
#endif /* __EWLIB_COMMUNICATION_ETHERNET_CTCPSOCKET_H__ */