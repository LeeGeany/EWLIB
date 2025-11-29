/**
 * @file IClient.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-29
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __EWLIB_COMMUNICATION_ETHERNET_CLIENT_ICLIENT_H__
#define __EWLIB_COMMUNICATION_ETHERNET_CLIENT_ICLIENT_H__

#include "EWLIB/stdEWLIB.h"

class CTCPSocket;

namespace jlib
{
    class IClient 
    {
    public:
        virtual ~IClient() {}

    protected:
        virtual bool Connect(const std::string& ip, int port) = 0;
        virtual ISocket * GetSocket() = 0;
    };
} /* namespace jlib */
#endif /* __EWLIB_COMMUNICATION_ETHERNET_CLIENT_ICLIENT_H__ */