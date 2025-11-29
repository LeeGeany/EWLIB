/**
 * @file CUDPServer.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-29
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __EWLIB_COMMUNICATION_ETHERNET_SERVER_CUDPSERVER_H__
#define __EWLIB_COMMUNICATION_ETHERNET_SERVER_CUDPSERVER_H__

#include "EWLIB/stdEWLIB.h"
#include "EWLIB/Communication/Ethernet/Socket/CUDPSocket.h"
#include "IServer.h"

namespace jlib
{
    class CUDPServer : public IServer 
    {
    public:
        CUDPServer() noexcept;
        virtual ~CUDPServer() noexcept;

        bool Bind(const std::string& ip, int port) override;
        bool Listen(int backlog = 0) override { return true; }
        std::shared_ptr<ISocket> Accept() override { return nullptr; }

    private:
        int m_fd;
    };

} /* namespace jlib */
#endif /* __EWLIB_COMMUNICATION_ETHERNET_SERVER_CUDPSERVER_H__ */