/**
 * @file CUDP.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-13
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __EWLIB_COMMUNICATION_ETHERNET_UDP_CUDP_H__
#define __EWLIB_COMMUNICATION_ETHERNET_UDP_CUDP_H__

#include "EWLIB/stdEWLIB.h"

namespace EWLIB
{
    class CUDP
    {
    public: 
        explicit CUDP(EW_IP_T _ip, EW_PORT_T _port) noexcept;
        virtual ~CUDP();

    public:
        STATUS Socket();
        STATUS Bind();
        ssize_t Send(std::string _toIP, EW_CHAR_VECTOR_T _datagram, size_t _size);
        ssize_t Recv(EW_CHAR_VECTOR_T & _datagram);

    public:
        void InsertSockInfo(EW_SOCKET_ADDR_IN_T _otherSock);
        EW_SOCKET_ADDR_IN_T GetSockInfo(std::string _key);

    private:
        std::string ew_tostring(EW_SOCKET_ADDR_IN_T _otherSock);

    private:
        EW_SOCKET_T m_sock;
        EW_PORT_T m_port;
        EW_IP_T m_ip;

        EW_SOCKET_ADDR_IN_T m_sockMyInfo;
        std::unordered_map<std::string, EW_SOCKET_ADDR_IN_T> m_sockOtherInfo;
        
    }; /* class CUDP */
} /* namespace EWLIB */
#endif /* __EWLIB_COMMUNICATION_ETHERNET_UDP_CUDP_H__ */