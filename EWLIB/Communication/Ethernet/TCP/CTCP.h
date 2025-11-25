/**
 * @file CTCP.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __EWLIB_COMMUNICATION_ETHERNET_TCP_CTCP_H__
#define __EWLIB_COMMUNICATION_ETHERNET_TCP_CTCP_H__

#include "EWLIB/stdEWLIB.h"

namespace EWLIB
{
    inline constexpr const size_t EW_CLIENT_CONN_MAX_SIZE  = 16;
    inline constexpr const size_t EW_PACKET_SIZE           = 1400;
    inline constexpr const size_t EW_RECV_BUFFER_SIZE      = 1400 ;      
    inline constexpr const size_t EW_SEND_BUFFER_SIZE      = 1400 ;

    using EW_SOCKET_T           =   int32_t                ;
    using EW_SOCKET_ADDR_T      =   struct sockaddr        ;
    using EW_SOCKET_ADDR_IN_T   =   struct sockaddr_in     ;
    using EW_SOCKET_LENGTH_T    =   socklen_t              ;
    using EW_SOCK_OPTION_T      =   int32_t                ;

    using EW_PORT_T             =   const uint16_t         ;
    using EW_IP_T               =   std::string            ;
    using EW_SERVER_NAME_T      =   std::string            ;

    struct ST_CONNECTION_INFO
    {
        EW_SOCKET_T ClientSocket;
        EW_SOCKET_ADDR_IN_T ClientAddress;
    };

    enum class EC_SOCKET_OPT {
        EW_REUSEADDR,
        EW_REUSEPORT,
        EW_KEEPALIVE,
        EW_RECVBUFSIZE,
        EW_SENDBUFSIZE,
        EW_TCP_NODELAY,
        EW_LINGER
    };

    class CTCP : public IReceive, public ISend
    {
    public:
        explicit CTCP(EW_IP_T _ip, EW_PORT_T _port) noexcept;
        virtual ~CTCP() noexcept;


        STATUS Bind();
        STATUS Listen();
        ST_CONNECTION_INFO Accept();
        ST_CONNECTION_INFO Connect();
        STATUS Close();

        EW_SOCKET_T native_handle();
        
        STATUS SetSockOption(EW_SOCKET_T _Socket, EC_SOCKET_OPT _Option, EW_SOCK_OPTION_T * _pOption);
    
        public:
        virtual uint32_t OnReceive(char * Buffer, const size_t BufferSize) override;
        virtual uint32_t OnSend(char * Buffer, const size_t BufferSize) override;

    protected:
        EW_IP_T                 m_IP;
        EW_PORT_T               m_Port;
        EW_SOCKET_T             m_Sock;
        EW_SOCK_OPTION_T        m_Option;
    }; /* class CTCP */
} /* namespace jhlib */


#endif /* __EWLIB_COMMUNICATION_ETHERNET_TCP_CTCP_H__ */