/**
 * @file CUDPServer.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-29
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "CUDPServer.h"

namespace jlib
{
    CUDPServer::CUDPServer() noexcept
    {
        m_fd = ::socket(AF_INET, SOCK_DGRAM, 0);
    }

    CUDPServer::~CUDPServer() noexcept
    {
        if (m_fd > 0) ::close(m_fd);
    }

    bool CUDPServer::Bind(const std::string& ip, int port)
    {
        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port   = htons(port);
        addr.sin_addr.s_addr = inet_addr(ip.c_str());

        int opt = 1;
        setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

        return ::bind(m_fd, (sockaddr*)&addr, sizeof(addr)) == 0;
    }
}