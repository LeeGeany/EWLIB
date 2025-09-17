/**
 * @file CTCPClient.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-07-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "CTCPServer.h"

namespace EWLIB 
{
    CTCPServer::CTCPServer(EW_PORT_T _usLocalPort)
    : m_serverPort(_usLocalPort)
    , m_sockServer{0}
    , m_stServerAddr{}
    , m_Option(1)
    {

    }

    EW_SOCKET_T CTCPServer::Socket()
    {
        m_sockServer = socket(AF_INET, SOCK_STREAM, 0);
        if(m_sockServer < 0) {
            std::cout << "[ERROR] : Errno | " << errno << "\n";
        } 
        
        return m_sockServer;
    }

    void CTCPServer::setServerInfo()
    {
        m_stServerAddr.sin_family       = AF_INET;
        m_stServerAddr.sin_addr.s_addr  = INADDR_ANY;
        m_stServerAddr.sin_port         = htons(m_serverPort);
    }

    EW_SOCKET_ADDR_IN_T CTCPServer::setServerInfo(EW_PORT_T _port)
    {
        EW_SOCKET_ADDR_IN_T ret{0,};
        ret.sin_family       = AF_INET;
        ret.sin_addr.s_addr  = INADDR_ANY;
        ret.sin_port         = htons(_port);
        return ret;
    }

    STATUS CTCPServer::Bind()
    {
        STATUS ret = true;
        int ret = bind(m_sockServer, reinterpret_cast<sockaddr*>(&(m_stServerAddr)), sizeof(m_stServerAddr));

        if(ret < 0) {
            std::cout << "[ERROR] : Errno | " << errno << "\n";
            ret = false;
        } 
        return ret;
    }

    STATUS CTCPServer::Bind(EW_SOCKET_T _sockServer, EW_SOCKET_ADDR_IN_T _sockAddrInfo)
    {
        STATUS ret = true;
        int ret = bind(_sockServer, reinterpret_cast<sockaddr*>(&(_sockAddrInfo)), sizeof(m_stServerAddr));

        if(ret < 0) {
            std::cout << "[ERROR] : Errno | " << errno << "\n";
            ret = false;
        } 
        return ret;
    }

    STATUS CTCPServer::Listen()
    {
        STATUS ret = true;
        int ret = listen(m_sockServer, EW_CLIENT_CONN_MAX_SIZE);
        
        if(ret < 0) {
            std::cout << "[ERROR] : Errno | " << errno << "\n";
            ret = false;
        } 
        return ret;
    }

    STATUS CTCPServer::Listen(EW_SOCKET_T _sockServer)
    {
        STATUS ret = true;
        int ret = listen(_sockServer, EW_CLIENT_CONN_MAX_SIZE);
        
        if(ret < 0) {
            std::cout << "[ERROR] : Errno | " << errno << "\n";
            ret = false;
        } 
        return ret;
    }

    STATUS CTCPServer::Accept()
    {
        STATUS ret = true;
        EW_SOCKET_ADDR_IN_T stClientAddr{};
        EW_SOCKET_LENGTH_T stClientAddrSize = sizeof(stClientAddr);

        EW_SOCKET_T m_sockClient = accept(m_sockServer, reinterpret_cast<sockaddr*>(&stClientAddr), &stClientAddrSize);
        
        if(m_sockClient < 0) {
            std::cout << "[ERROR] : Errno | " << errno << "\n";
            ret = false;
        } else {
            std::string ip = std::string(inet_ntoa(stClientAddr.sin_addr));
            ip += ":";
            ip += std::to_string(ntohs(stClientAddr.sin_port));
            
            size_t tSize = m_umSockClient.size();
            if(tSize < EWLIB::EW_CLIENT_CONN_MAX_SIZE) {
                m_umSockClient[ip] = m_sockClient;
            } else {
                std::cout << "[ERROR] | Too Many Client\n";
            }

        }

        return ret;
    }

    EW_SOCKET_T CTCPServer::Accept(EW_SOCKET_T _sockServer, sockaddr * _pSockAddrInfo, EW_SOCKET_LENGTH_T * pSockAddrSize)
    {

        EW_SOCKET_T m_sockClient = accept(_sockServer, _pSockAddrInfo, pSockAddrSize);
        
        if(m_sockClient < 0) {
            std::cout << "[ERROR] : Errno | " << errno << "\n";
        }
        return m_sockClient;
    }

    EW_SOCKET_T CTCPServer::TCPSend(std::string _strWhereIp, const char* _strBuffer, const size_t _iBufferSize)
    {
        EW_SOCKET_T ret;
        auto item = m_umSockClient.find(_strWhereIp);
        
        if(item == m_umSockClient.end())
        {
            ret = -1;
        } else {
            ret = item->second;
            ret = send(ret, _strBuffer, _iBufferSize, MSG_DONTWAIT);
            if(ret < 0) {
                std::cout << "[ERROR] : Errno | " << errno << "\n";
            }
        }
        return ret;
    }

    STATUS CTCPServer::SetSockOption(EC_SOCKET_OPT _Option)
    {
        STATUS ret = true;
        switch (_Option)
        {
            case EC_SOCKET_OPT::EW_REUSEADDR :
            {
                int ret = setsockopt(m_sockServer, SOL_SOCKET, SO_REUSEADDR, &m_Option, sizeof(m_Option));
                if(ret < 0) {
                    ret = false;
                }
            }
            case EC_SOCKET_OPT::EW_REUSEPORT :
            {
                int ret = setsockopt(m_sockServer, SOL_SOCKET, SO_REUSEADDR, &m_Option, sizeof(m_Option));
                if(ret < 0) {
                    ret = false;
                }
            }
            case EC_SOCKET_OPT::EW_KEEPALIVE :
            {
                int ret = setsockopt(m_sockServer, SOL_SOCKET, SO_KEEPALIVE, &m_Option, sizeof(m_Option));
                if(ret < 0) {
                    ret = false;
                }
            }
            case EC_SOCKET_OPT::EW_TCP_NODELAY :
            {
                int ret = setsockopt(m_sockServer, IPPROTO_TCP, TCP_NODELAY, &m_Option, sizeof(m_Option));
                if(ret < 0) {
                    ret = false;
                }
            }
            case EC_SOCKET_OPT::EW_LINGER :
            {
                int ret = setsockopt(m_sockServer, SOL_SOCKET, SO_LINGER, &m_Option, sizeof(m_Option));
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

    STATUS CTCPServer::SetSockOption(EW_SOCKET_T _Socket, EC_SOCKET_OPT _Option, EW_SOCK_OPTION_T * _pOption)
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

    STATUS CTCPServer::SetRecvBufferSize(EW_BUFFER_SIZE _BufferSize)
    {
        STATUS ret = true;
        int ret = setsockopt(m_sockServer, SOL_SOCKET, SO_RCVBUF, &_BufferSize, sizeof(m_Option));
        if(ret < 0) {
            ret = false;
        }
        return ret;
    }

    STATUS CTCPServer::SetRecvBufferSize(EW_BUFFER_SIZE _BufferSize)
    {
        STATUS ret = true;
        int ret = setsockopt(m_sockServer, SOL_SOCKET, SO_SNDBUF, &_BufferSize, sizeof(m_Option));
        if(ret < 0) {
            ret = false;
        }
        return ret;
    }

    STATUS CTCPServer::Close()
    {
        STATUS ret = true;
        int n = close(m_sockServer);
        if(n < 0) {
            ret = false;
        }
        return ret;
    }

    STATUS CTCPServer::Close(EW_SOCKET_T _Socket)
    {
        STATUS ret = true;
        int n = close(_Socket);
        if(n < 0) {
            ret = false;
        }
        return ret;
    }

} /* namespace EWLIB */