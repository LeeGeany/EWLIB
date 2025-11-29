/**
 * @file CTCPServer.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-29
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "CTCPServer.h"

namespace jlib
{
    CTCPServer::CTCPServer()
    {
        m_fd = ::socket(AF_INET, SOCK_STREAM, 0);
    }

    CTCPServer::~CTCPServer()
    {
        if (m_fd > 0)
        {
            ::close(m_fd);
        }
    }

    J_STATE CTCPServer::Bind(const std::string& ip, int port)
    {
        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port   = htons(port);
        addr.sin_addr.s_addr = inet_addr(ip.c_str());

        int opt = 1;
        setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

        return ::bind(m_fd, (sockaddr*)&addr, sizeof(addr)) == 0;
    }

    J_STATE CTCPServer::Listen(int backlog)
    {
        return ::listen(m_fd, backlog) == 0;
    }

    std::shared_ptr<ISocket> CTCPServer::Accept()
    {
        int client_fd = ::accept(m_fd, nullptr, nullptr);
        if (client_fd < 0) return nullptr;

        return std::make_unique<CTCPSocket>(client_fd);
    }
 
}