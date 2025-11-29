/**
 * @file CTCPServer.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-29
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __EWLIB_COMMUNICATION_ETHERNET_SERVER_CTCPSERVER_H__
#define __EWLIB_COMMUNICATION_ETHERNET_SERVER_CTCPSERVER_H__

#include "EWLIB/stdEWLIB.h"
#include "EWLIB/Communication/Ethernet/Socket/CTCPSocket.h"
#include "IServer.h"

namespace jlib
{
    class CTCPServer : public IServer 
    {
    public:
        CTCPServer();
        ~CTCPServer();

    public:
        J_STATE Bind(const std::string& ip, int port) override;
        J_STATE Listen(int backlog = 128) override;
        std::shared_ptr<ISocket> Accept() override;

    private:
        int m_fd;
    };
} /* namespace jlib */
#endif /* __EWLIB_COMMUNICATION_ETHERNET_SERVER_CTCPSERVER_H__ */