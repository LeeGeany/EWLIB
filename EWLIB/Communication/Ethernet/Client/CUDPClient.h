/**
 * @file CUDPClient.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-29
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __EWLIB_COMMUNICATION_ETHERNET_CLIENT_CUDPCLIENT_H__
#define __EWLIB_COMMUNICATION_ETHERNET_CLIENT_CUDPCLIENT_H__

#include "EWLIB/stdEWLIB.h"
#include "EWLIB/Communication/Ethernet/Socket/CUDPSocket.h"
#include "IClient.h"

namespace jlib
{
    class CUDPClient : public IClient 
    {
    public:
        CUDPClient() noexcept;
        virtual ~CUDPClient() noexcept; 

        bool Connect(const std::string& ip, int port) override;
        virtual ISocket *  GetSocket();

    private:
        std::unique_ptr<CUDPSocket> m_socket;
    };
} /* namespace jlib */
#endif /* __EWLIB_COMMUNICATION_ETHERNET_CLIENT_CUDPCLIENT_H__ */