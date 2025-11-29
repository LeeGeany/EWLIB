/**
 * @file CUDPClient.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-29
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "CUDPClient.h"

namespace jlib
{
        CUDPClient::CUDPClient() noexcept
        {

        }

        CUDPClient::~CUDPClient() noexcept
        {

        }

        bool CUDPClient::Connect(const std::string& ip, int port)
        {
            if (!m_socket.open(AF_INET, SOCK_DGRAM, 0))
                return false;

            sockaddr_in addr{};
            addr.sin_family = AF_INET;
            addr.sin_addr.s_addr = inet_addr(ip);
            addr.sin_port = htons(port);

            // UDP connect()는 목적지 기본 설정만 해주는 것
            if (::connect(m_socket.get(), (sockaddr*)&addr, sizeof(addr)) < 0)
                return false;

            return true;
        }

        ISocket *  CUDPClient::GetSocket()
        {
            return m_socket.get();
        }
} /* namespace jlib */