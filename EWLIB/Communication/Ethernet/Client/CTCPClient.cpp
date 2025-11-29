/**
 * @file CTCPClient.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-29
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "CTCPClient.h"

namespace jlib
{
    CTCPClient::CTCPClient()
    : m_socket(std::make_unique<CTCPSocket>())
    {
    }

    CTCPClient::~CTCPClient()
    {
        // m_socket은 자동 close 됨
    }

    bool CTCPClient::Connect(const std::string& ip, int port)
    {
        int fd = m_socket->GetFd();
        if (fd < 0) return false;

        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port   = htons(port);
        addr.sin_addr.s_addr = inet_addr(ip.c_str());

        return ::connect(fd, (sockaddr*)&addr, sizeof(addr)) == 0;
    }

    ISocket * CTCPClient::GetSocket()
    {
        // accept처럼 새로운 fd를 만드는 게 아니라
        // 클라이언트는 소켓 하나만 사용하므로 unique_ptr로 감싸서 반환
        return m_socket.get();
    }
}