/**
 * @file stdLinux.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-08-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __STD__LINUX_H__
#define __STD__LINUX_H__

// STANDARD
#include <unistd.h>

// TYPE
#include <sys/types.h>

// IPC
#include <sys/msg.h>
#include <sys/ipc.h>

// ETHERNET
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

// FILE CONTROL
#include <fcntl.h>

#endif /* __STD__LINUX_H__ */