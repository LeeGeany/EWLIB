/**
 * @file CTCPClient.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-29
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __EWLIB_COMMUNICATION_ETHERNET_CLIENT_CTCPCLIENT_H__
#define __EWLIB_COMMUNICATION_ETHERNET_CLIENT_CTCPCLIENT_H__

#include "EWLIB/stdEWLIB.h"
#include "EWLIB/Communication/Ethernet/Socket/CTCPSocket.h"
#include "IClient.h"

namespace jlib
{
    class CTCPClient : public IClient 
    {
    public:
        CTCPClient();
        virtual ~CTCPClient();

        virtual bool Connect(const std::string& ip, int port) override;
        virtual ISocket * GetSocket() override;

    private:
        std::unique_ptr<CTCPSocket> m_socket;
    };
} /* namespace jlib */
#endif /* __EWLIB_COMMUNICATION_ETHERNET_CLIENT_CTCPCLIENT_H__ */