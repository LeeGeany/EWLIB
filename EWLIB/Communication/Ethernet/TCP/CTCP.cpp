/**
 * @file CTCP.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "CTCP.h"

namespace EWLIB
{
    CTCP::CTCP(EW_IP_T _ip, EW_PORT_T _port) noexcept
    : m_IP(_ip)
    , m_Port(_port)
    , m_Option(1)
    {
        m_Sock = socket(AF_INET, SOCK_STREAM, 0);
        
        if(m_Sock < 0) {
            std::cout << "[ERROR] : Errno | " << errno << "\n";
        } 
    }

    CTCP::~CTCP() noexcept
    {
        Close();
    }

    STATUS CTCP::Bind()
    {
        STATUS ret = true;
        EW_SOCKET_ADDR_IN_T _SocketInfo;
        _SocketInfo.sin_family       = AF_INET;
        _SocketInfo.sin_addr.s_addr  = INADDR_ANY;
        _SocketInfo.sin_port         = htons(m_Port);

        int tRet = bind(m_Sock, reinterpret_cast<sockaddr*>(&(_SocketInfo)), sizeof(EW_SOCKET_ADDR_IN_T));

        if(tRet < 0) {
            std::cout << "[ERROR] : Errno | " << errno << "\n";
            ret = false;
        } 
        return ret;
    }

    STATUS CTCP::Listen()
    {
        STATUS ret = true;
        int tRet = listen(m_Sock, EW_CLIENT_CONN_MAX_SIZE);
        
        if(tRet < 0) {
            std::cout << "[ERROR] : Errno | " << errno << "\n";
            ret = false;
        } 
        return ret;
    }

    ST_CONNECTION_INFO CTCP::Accept()
    {
        ST_CONNECTION_INFO retClientInfo;
        EW_SOCKET_LENGTH_T stClientAddrSize = sizeof(EW_SOCKET_ADDR_IN_T);

        retClientInfo.ClientSocket = accept(m_Sock, reinterpret_cast<sockaddr*>(&(retClientInfo.ClientAddress)), &stClientAddrSize);
        
        if(retClientInfo.ClientSocket < 0) {
            std::cout << "[ERROR] : Errno | " << errno << "\n";
        } 

        return retClientInfo;
    }

    ST_CONNECTION_INFO CTCP::Connect()
    {
        ST_CONNECTION_INFO retClientInfo;
        EW_SOCKET_LENGTH_T stClientAddrSize = sizeof(EW_SOCKET_ADDR_IN_T);

        connect(m_Sock, reinterpret_cast<sockaddr*>(&retClientInfo.ClientAddress), stClientAddrSize);
        return retClientInfo;
    }

    STATUS CTCP::SetSockOption(EW_SOCKET_T _Socket, EC_SOCKET_OPT _Option, EW_SOCK_OPTION_T * _pOption)
    {
        STATUS ret = true;
        switch (_Option)
        {
            case EC_SOCKET_OPT::EW_REUSEADDR :
            {
                int ret = setsockopt(_Socket, SOL_SOCKET, SO_REUSEADDR, _pOption, sizeof(*_pOption));
                if(ret < 0) {
                    ret = false;
                }
            }
            case EC_SOCKET_OPT::EW_REUSEPORT :
            {
                int ret = setsockopt(_Socket, SOL_SOCKET, SO_REUSEADDR, _pOption, sizeof(*_pOption));
                if(ret < 0) {
                    ret = false;
                }
            }
            case EC_SOCKET_OPT::EW_KEEPALIVE :
            {
                int ret = setsockopt(_Socket, SOL_SOCKET, SO_KEEPALIVE, _pOption, sizeof(*_pOption));
                if(ret < 0) {
                    ret = false;
                }
            }
            case EC_SOCKET_OPT::EW_TCP_NODELAY :
            {
                int ret = setsockopt(_Socket, IPPROTO_TCP, TCP_NODELAY, _pOption, sizeof(*_pOption));
                if(ret < 0) {
                    ret = false;
                }
            }
            case EC_SOCKET_OPT::EW_LINGER :
            {
                int ret = setsockopt(_Socket, SOL_SOCKET, SO_LINGER, _pOption, sizeof(*_pOption));
                if(ret < 0) {
                    ret = false;
                }
            }
            default :
            {
                ret = false;
            }
        }
        return ret;
    }


    STATUS CTCP::Close()
    {
        close(m_Sock);
    }

    EW_SOCKET_T CTCP::native_handle()
    {
        return m_Sock;
    }
}