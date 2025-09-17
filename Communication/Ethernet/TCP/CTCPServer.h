/**
 * @file CTCPServer.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-07-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __EWLIB_COMMUNICATION_ETHERNET_TCP_CTCPSERVER_H__
#define __EWLIB_COMMUNICATION_ETHERNET_TCP_CTCPSERVER_H__

#include "EWLIB/stdEWLIB.h"
#include "EWLIB/stdLinux.h"

#include "EWLIB/Communication/Ethernet/TCP/IReceive.h"
#include "EWLIB/Communication/Ethernet/TCP/ISend.h"

namespace EWLIB 
{
    enum class EC_SOCKET_OPT {
        EW_REUSEADDR,
        EW_REUSEPORT,
        EW_KEEPALIVE,
        EW_RECVBUFSIZE,
        EW_SENDBUFSIZE,
        EW_TCP_NODELAY,
        EW_LINGER
    };

    class CTCPServer : public IReceive, public ISend
    {    
    public:
        explicit CTCPServer(EW_PORT_T _usLocalPort);
        virtual ~CTCPServer();

    public:
        EW_SOCKET_T Socket();

        void setServerInfo();
        EW_SOCKET_ADDR_IN_T setServerInfo(EW_PORT_T _port);

        STATUS Bind();
        STATUS Bind(EW_SOCKET_T _sockServer, EW_SOCKET_ADDR_IN_T _sockAddrInfo);

        STATUS Listen();
        STATUS Listen(EW_SOCKET_T _sockServer);

        STATUS Accept();
        EW_SOCKET_T Accept(EW_SOCKET_T _sockServer, sockaddr * _pSockAddrInfo, EW_SOCKET_LENGTH_T * pSockAddrSize);

        STATUS SetSockOption(EC_SOCKET_OPT _Option);
        STATUS SetSockOption(EW_SOCKET_T _Socket, EC_SOCKET_OPT _Option, EW_SOCK_OPTION_T * _pOption);

        STATUS SetRecvBufferSize(EW_BUFFER_SIZE _BufferSize);
        STATUS SetRecvBufferSize(EW_BUFFER_SIZE _BufferSize);

        STATUS Close();
        STATUS Close(EW_SOCKET_T _Socket);

    public:
        EW_SOCKET_T TCPSend(std::string _strWhereIp, const char* _strBuffer, const size_t _iBufferSize);

    protected:
        EW_PORT_T                   m_serverPort;
        EW_SOCKET_T                 m_sockServer;
        EW_SOCKET_ADDR_IN_T         m_stServerAddr;
        EW_SOCK_OPTION_T            m_Option;

        EW_BUFFER_SIZE              m_RecvBufferSize;
        EW_BUFFER_SIZE              m_SendBufferSize;

        EW_CLIENT_SOCKET_UMAP_T     m_umSockClient;
    }; /* class CTCPServer */

} /* namespace EWLIB */
#endif /* __EWLIB_COMMUNICATION_ETHERNET_TCP_CTCPSERVER_H__ */