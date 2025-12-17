/**
 * @file IServer.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-29
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __EWLIB_COMMUNICATION_ETHERNET_SERVER_H__
#define __EWLIB_COMMUNICATION_ETHERNET_SERVER_H__

#include "EWLIB/stdEWLIB.h"

class CTCPSocket;

namespace jlib
{
    class IServer 
    {
    public:
        virtual ~IServer() {}

    public:
        virtual bool Bind(const std::string& ip, int port) = 0;
        virtual bool Listen(int backlog = 128) = 0;

        // TCP는 Accept 사용
        virtual std::shared_ptr<ISocket> Accept() = 0;
    };
} /* namespace jlib */

#endif /*__EWLIB_COMMUNICATION_ETHERNET_SERVER_H__  */