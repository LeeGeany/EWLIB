/**
 * @file CUDP.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "CUDP.h"

namespace EWLIB
{
    CUDP::CUDP(EW_IP_T _ip, EW_PORT_T _port) noexcept
    : m_ip(_ip)
    , m_port(_port)
    {

    }

    CUDP::~CUDP()
    {

    }

    STATUS CUDP::Socket()
    {
        STATUS Ret = true;
        m_sock = socket(AF_INET, SOCK_DGRAM, 0);
        if(m_sock < 0)
        {
            Ret = false;
        }
        return Ret;
    }

    STATUS CUDP::Bind()
    {
        STATUS Ret = true;
        int iRet = bind(m_sock, reinterpret_cast<sockaddr*>(&m_sockMyInfo), sizeof(m_sockMyInfo));
        if(iRet < 0 )
        {
            Ret = false;
        }
        return Ret;
    }

    ssize_t CUDP::Send(std::string _toIP, EW_CHAR_VECTOR_T _datagram, size_t _size)
    {

    }

    ssize_t CUDP::Recv(EW_CHAR_VECTOR_T & _datagram)
    {
        ssize_t ssRet = 0;
        EW_SOCKET_ADDR_IN_T tSockOtherInfo;
        EW_SOCKET_LENGTH_T tSockInfoSize = sizeof(tSockOtherInfo);

        ssRet = recvfrom(m_sock, _datagram.data(), _datagram.size(), 0, reinterpret_cast<sockaddr*>(&m_sockOtherInfo), &tSockInfoSize);
        if(ssRet < 0)
        {
            EW_SOCKET_ADDR_IN_T GetSockInfo(std::string _key);
        }

        return ssRet;
    }

    void InsertSockInfo(EW_SOCKET_ADDR_IN_T _otherSock)
    {

    }
    
    EW_SOCKET_ADDR_IN_T GetSockInfo(std::string _key)
    {

    }

    std::string ew_tostring(EW_SOCKET_ADDR_IN_T _otherSock)
    {
    
    }
} /* namespace EWLIB */