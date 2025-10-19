/**
 * @file stdUsrType.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-07-30
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __EWLIB_STD_EWLIB_H__
#define __EWLIB_STD_EWLIB_H__

#include "EWLIB/stdC++.h"
#include "EWLIB/stdLinux.h"
#include "EWLIB/stdPosix.h"

namespace EWLIB
{
    // ========================= Primitive Type ========================= //
    using EW_BYTE                  = std::byte;
    using EW_BYTE_VECTOR_T         = std::vector<EW_BYTE>;
    template <std::size_t T>
    using EW_BYTE_ARRAY_T          = std::array<EW_BYTE, T>;

    using EW_CHAR_VECTOR_T         = std::vector<char>;
    template <std::size_t T>
    using EW_CHAR_ARRAY_T          = std::array<char, T>;

    using STATUS = bool;

    template <typename T>
    using EW_FUNCTION_T         = std::function<T>;
    using EW_CALLBACK_T         = std::function<void(void)>;

    // ========================= Time ========================= //
    using EW_MILLISECOND_T  = std::chrono::milliseconds;
    using EW_MICROSECOND_T  = std::chrono::microseconds;
    using EW_NANOSECOND_T   = std::chrono::nanoseconds;

    using EW_CLOCK_T        = std::chrono::steady_clock;
    using EW_TIMEPOINT_T    = std::chrono::steady_clock::time_point;
    using EW_DURATION_T     = std::chrono::steady_clock::duration;

    struct ST_SYSTEM_TIME_T
    {
        std::int64_t seconds;
        std::int64_t nanoseconds;
    };

    // ========================= Common/Mutex ========================= //
    using EW_MUTEX_T            = std::mutex;
    using EW_LOCK_GUARD_MUTEX_T = std::lock_guard<std::mutex>;


    // ========================= Task/Thread ========================= //
    using EW_THREAD_T           = std::thread;
    using EW_THREAD_ID_T        = uint32_t;
    using EW_THREAD_NAME_T      = std::string;
    
    enum class EC_THREAD_RUN_TYPE {
          THREAD_ONCE_T
        , THREAD_LOOP_T
        /*
        , THREAD_TIME_T
        */
    };

    enum class EC_THREAD_STATUS_TYPE {
          THREAD_STATUS_NEW_T
        , THREAD_STATUS_WAIT_T
        , THREAD_STATUS_RUN_T
        , THREAD_STATUS_TERMINATE_T
    };

    struct ST_THREAD_CONTROL_BLOCK_T{
        EW_THREAD_NAME_T        strThreadName   ;
        EW_THREAD_ID_T          uiThreadID      ;
        EC_THREAD_RUN_TYPE      ecThreadRun     ;
        EC_THREAD_STATUS_TYPE   ecThreadStatus  ;
    };


    // ========================= IPC/MSGQ ========================= //
    using EW_MSGQ_KEY_T            = int32_t;
    using EW_MSGQ_ID_T             = int32_t;

    struct ST_MSG_Q_T {
        long mtype;
        char data[8];
    } __attribute__((packed));


    // ========================= ETHERNET/TCP ========================= //
    // ETHERNET/BUFFER/SIZE
    inline constexpr const size_t EW_CLIENT_CONN_MAX_SIZE  = 16;
    inline constexpr const size_t EW_PACKET_SIZE           = 1400;
    inline constexpr const size_t EW_EPOLL_MAX_SIZE        = 32768;        // HOW MANY EVENT CAN BE STORED IN QUEUE? 32K
    inline constexpr const size_t EW_RECV_BUFFER_SIZE      = 1400 ;      
    inline constexpr const size_t EW_SEND_BUFFER_SIZE      = 1400 ;

    using EW_SOCKET_T           =   int32_t                ;
    using EW_SOCKET_ADDR_T      =   struct sockaddr        ;
    using EW_SOCKET_ADDR_IN_T   =   struct sockaddr_in     ;
    using EW_SOCKET_LENGTH_T    =   socklen_t              ;
    using EW_SOCK_OPTION_T      =   int32_t                ;

    // ETHENET/TYPE
    using EW_PORT_T             =   const uint16_t         ;
    using EW_IP_T               =   std::string            ;
    using EW_SERVER_NAME_T      =   std::string            ;

    // ETHERNET/BUFFER/SIZE
    using EW_BUFFER_SIZE            = size_t               ;
    using EW_SEND_DATA_BUFFER_T     = std::array<char, EW_SEND_BUFFER_SIZE> ;

    // ETHERNET/TCP/EPOLL
    using EW_EPOLL_EVENT_T      =   struct epoll_event     ;
    using EW_EPOLL_T            =   int32_t                ;

    // ETHERNET/BUFFER
    using EW_EPOLL_EVENT_BUFFER_T   = std::array<EW_EPOLL_EVENT_T, EW_EPOLL_MAX_SIZE>;


    // ETHERNET/HASHMAP
    using EW_CLIENT_SOCKET_UMAP_T = std::unordered_map<std::string, EW_SOCKET_T>;
    //using EW_CLIENT_BUFFER_UMAP_T = std::unordered_map<EW_SOCKET_T, std::deque<ST_TCP_PACKET_T>>;


    
} /* namespace EWLIB */
#endif /* __EWLIB_STD_EWLIB_H__ */