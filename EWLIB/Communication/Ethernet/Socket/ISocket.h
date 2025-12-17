/**
 * @file ISocket.h
 * @author Jinhee.Lee (tjrgl@naver.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-29
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __EWLIB_COMMUNICATION_ETHERNET_ISOCKET_H__
#define __EWLIB_COMMUNICATION_ETHERNET_ISOCKET_H__

#include "EWLIB/stdEWLIB.h"

namespace jlib
{
    //inline constexpr const size_t EW_PACKET_SIZE           = 1400;
    //inline constexpr const size_t EW_RECV_BUFFER_SIZE      = 1400 ;      
    //inline constexpr const size_t EW_SEND_BUFFER_SIZE      = 1400 ;

    class ISocket 
    {
    public:
        ISocket();
        virtual ~ISocket() {}

    public:
        virtual int  GetFd() const = 0;
        virtual bool SetNonBlocking(bool enable) = 0;
        virtual bool Close() = 0;

    public:
        virtual ssize_t Send(const void* buf, size_t len) = 0;
        virtual ssize_t Recv(void* buf, size_t len) = 0;
    }; /* class ISocket */
} /* namespace jlib */
#endif /* __EWLIB_COMMUNICATION_ETHERNET_ISOCKET_H__ */