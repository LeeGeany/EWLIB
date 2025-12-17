/**
 * @file main.cpp
 * @author Jinhee.Lee (tjrgl@naver.com)
 * @brief 
 * @version 0.1
 * @date 2025-09-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "EWLIB/Task/Process/CProcess.h"
#include "EWLIB/Task/Thread/CThread.h"
#include "EWLIB/Time/Delay/Delay.h"
#include "EWLIB/Time/Time/CTime.h"
#include "EWLIB/Time/Timer/CTimer.h"
#include "EWLIB/Sync/Waiter/CWaiter.h"
#include "EWLIB/Sync/Spinlock/CSpinlock.h"
#include "EWLIB/Sync/Mutex/CMutex.h"
#include "EWLIB/Sync/Mutex/CSharedMutex.h"
#include "EWLIB/Sync/Mutex/CTimedMutex.h"
#include "EWLIB/Sync/Lock/CAutoLock.h"
#include "EWLIB/FileIO/FIO/CFWriter.h"
#include "EWLIB/FileIO/FIO/CFReader.h"
#include "EWLIB/FileIO/File/File.h"
#include "EWLIB/FileIO/Dir/Dir.h"
#include "EWLIB/Container/CRingBuffer.h"
#include "EWLIB/Communication/IPC/MsgQ/CMsgQ.h"
#include "EWLIB/Communication/IPC/MsgQ/CMsgQ_S.h"
#include "EWLIB/Communication/Event/Signal/CSignal.h"
#include "EWLIB/Communication/Event/Epoll/CEpoll.h"
#include "EWLIB/Communication/Ethernet/Server/CTCPServer.h"
#include "EWLIB/Communication/Ethernet/Client/CTCPClient.h"
#include "EWLIB/Communication/Ethernet/Socket/CTCPSocket.h"
#include "EWLIB/Communication/Ethernet/Server/CUDPServer.h"
#include "EWLIB/Communication/Ethernet/Client/CUDPClient.h"
#include "EWLIB/Communication/Ethernet/Socket/CUDPSocket.h"


#define RINGBUFFER
#pragma pack()

int main() 
{
#ifdef UDP
    std::string str_;
    std::cin >> str_;

    jlib::J_FUNCTION_T<void()> clientFunction_ = [](){
        jlib::CUDPClient client_;
        client_.Connect("127.0.0.1", 9000); 
        auto SOCK = reinterpret_cast<jlib::CTCPSocket*>(client_.GetSocket());
        SOCK->Send("HELLO", 5);

        char buf[1024];
        ssize_t n = SOCK->Recv(buf, sizeof(buf));
        if (n > 0) {
            printf("recv: %.*s\n", (int)n, buf);
        }
    };

    jlib::J_FUNCTION_T<void()> serverFunction_ = [](){
        jlib::CUDPServer server_;
        server_.Bind("0.0.0.0", 9000);

        while (true)
        {
            //auto client_ = server_.Accept();
            //if(!client_) continue;

            auto server = server_.

            char buf[1024];
            ssize_t n = server_->Recv(buf, sizeof(buf));
            if (n > 0) {
                server_->Send(buf, n); // echo
            }
        }
    };

    if(str_ == "client")
    {
        jlib::CThread thread1("client", 0x1000, jlib::EC_THREAD_RUN_TYPE::THREAD_LOOP_T, clientFunction_);
        thread1.Run();
        thread1.Join();
    }
    else if(str_ == "server")
    {
        jlib::CThread thread2("server", 0x2000, jlib::EC_THREAD_RUN_TYPE::THREAD_ONCE_T, serverFunction_);
        thread2.Run();
        thread2.Join();
    }
    else
    {
        std::cout << "NO COmmand\n";
    }
#endif 

#ifdef TCP

    std::string str_;
    std::cin >> str_;

    jlib::J_FUNCTION_T<void()> clientFunction_ = [](){
        jlib::CTCPClient client_;
        client_.Connect("127.0.0.1", 9000); 
        auto SOCK = reinterpret_cast<jlib::CTCPSocket*>(client_.GetSocket());
        SOCK->Send("HELLO", 5);

        char buf[1024];
        ssize_t n = SOCK->Recv(buf, sizeof(buf));
        if (n > 0) {
            printf("recv: %.*s\n", (int)n, buf);
        }
    };

    jlib::J_FUNCTION_T<void()> serverFunction_ = [](){
        jlib::CTCPServer server_;
        server_.Bind("0.0.0.0", 9000);
        server_.Listen(128);

        while (true)
        {
            auto client_ = server_.Accept();
            if(!client_) continue;

            char buf[1024];
            ssize_t n = client_->Recv(buf, sizeof(buf));
            if (n > 0) {
                client_->Send(buf, n); // echo
            }
        }
    };

    if(str_ == "client")
    {
        jlib::CThread thread1("client", 0x1000, jlib::EC_THREAD_RUN_TYPE::THREAD_LOOP_T, clientFunction_);
        thread1.Run();
        thread1.Join();
    }
    else if(str_ == "server")
    {
        jlib::CThread thread2("server", 0x2000, jlib::EC_THREAD_RUN_TYPE::THREAD_ONCE_T, serverFunction_);
        thread2.Run();
        thread2.Join();
    }
    else
    {
        std::cout << "NO COmmand\n";
    }

#endif

#ifdef RINGBUFFER
    jlib::CRingBuffer<int> rb;
    std::array<int, 7> arr1 = {1,2,3,4,5,6,7};
    rb.write(arr1.data(), arr1.size());

    std::array<int, 7> arr2 = {};
    rb.read(arr2.data(), arr2.size());

    for(auto e : arr2)
    {
        std::cout << e;
    }

#endif

#ifdef EPOLL
        jlib::CEpoll epoll(10);

        int pipefd[2];
        if (pipe(pipefd) == -1) {
            perror("pipe");
            return 1;
        }

        int readFd = pipefd[0];
        int writeFd = pipefd[1];

        const char* msg = "Hello epoll";

        // addFd 테스트
        epoll.addFd(readFd, EPOLLIN, (void*)"read_pipe");

        std::cout << "Epoll FD: " << epoll.fd() << std::endl;

        // writeFd로 데이터 쓰기
        write(writeFd, msg, strlen(msg));

        // wait 테스트
        int n = epoll.wait(1000); // 1초 대기
        std::cout << "epoll_wait returned: " << n << std::endl;

        for (int i = 0; i < n; ++i) {
            const struct epoll_event& ev = epoll.getEvent(i);
            std::cout << "Event " << i << ": ";
            if (ev.events & EPOLLIN) std::cout << "EPOLLIN ";
            if (ev.events & EPOLLOUT) std::cout << "EPOLLOUT ";
            std::cout << ", userData: " << static_cast<const char*>(ev.data.ptr) << std::endl;

            // 실제 읽기
            if (ev.events & EPOLLIN) {
                char buf[128] = {0};
                int r = read(readFd, buf, sizeof(buf));
                std::cout << "Read from pipe: " << buf << std::endl;

                // modifyFd 테스트 (예: 이제 EPOLLOUT 감지)
                epoll.modifyFd(readFd, EPOLLOUT, (void*)"read_pipe_mod");
            }
        }

        // removeFd 테스트
        epoll.removeFd(readFd);
        close(readFd);
        close(writeFd);

        std::cout << "CEpoll test finished." << std::endl;
#endif

#ifdef SIGNAL
    jlib::CSignal sig;

    // 일반 함수형 람다로 등록
    sig.Insert(SIGINT, [](int s){
        std::cout << "SIGINT received! signal=" << s << std::endl;
    });

    sig.Insert(SIGTERM, [](int s){
        std::cout << "SIGTERM received! signal=" << s << std::endl;
    });

    std::cout << "Press Ctrl+C to test SIGINT..." << std::endl;

    // 프로그램 종료 전까지 무한 대기
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
#endif

#ifdef MSGQ_S
    jlib::CMsgQ_S<int> msg;
    jlib::J_FUNCTION_T<void()> func1 = [&](){
                    int msg_s = 0;
        while(1)
        {
            msg_s++;
            msg.SendMsg(&msg_s, sizeof(int));
            jlib::delay_ms(1000);
        }
    };

    jlib::J_FUNCTION_T<void()> func2 = [&](){
        while(1)
        {            
            int rec;
            msg.RecvMsg(&rec, 12);
            std::cout << rec << "\n";
        }
    };

    jlib::CThread thread2("recv", 0x2000, jlib::EC_THREAD_RUN_TYPE::THREAD_ONCE_T, func2);
    jlib::CThread thread1("send", 0x1000, jlib::EC_THREAD_RUN_TYPE::THREAD_ONCE_T, func1);
    thread1.Join();
    thread2.Join();

#endif

#ifdef MSGQ

    jlib::CMsgQ msg1_(0x1000);
    jlib::J_FUNCTION_T<void()> func1 = [&](){
        jlib::delay_ms(3000);
        while(1)
        {
            char buffer[12] = "helloworld\n";
            msg1_.SendMsg(&(buffer[0]), strlen(buffer) + 1);
            jlib::delay_ms(3000);
        }
    };

    jlib::J_FUNCTION_T<void()> func2 = [&](){
        jlib::delay_ms(3000);
        while(1)
        {
            char buffer[64] = "";
            msg1_.RecvMsg(buffer, 12);
            printf("recv : %s\n", buffer);
        }
    };

    jlib::CThread thread2("recv", 0x2000, jlib::EC_THREAD_RUN_TYPE::THREAD_ONCE_T, func2);
    jlib::CThread thread1("send", 0x1000, jlib::EC_THREAD_RUN_TYPE::THREAD_ONCE_T, func1);

    thread1.Join();
    thread2.Join();
#endif

#ifdef FILEREAD

    struct header_t{
        uint32_t Source;
        uint32_t Dest;
        uint16_t Command;
        uint16_t Class;
    };

    header_t header_{};
    std::string str; str.reserve(64);
    char buffer[12] = "";

    jlib::CFReader reader_txt("./test.txt", jlib::J_ASCII_RFILE_T);
    reader_txt >> str;
    std::cout << str << '\n';

    // error do not use
    jlib::CFReader reader_bin("./test.bin", jlib::J_BINARY_RFILE_T);
    reader_bin >> buffer;
    memcpy(&header_, buffer, sizeof(header_));
    std::cout << std::hex;
    std::cout << header_.Source << header_.Dest << header_.Command << header_.Class;

#endif

#ifdef FILEWRITE
    struct header_t{
        uint32_t Source;
        uint32_t Dest;
        uint16_t Command;
        uint16_t Class;
    };

    std::string str_ = "This is Sample string\n";
    header_t header_ = {0x12345678, 0xABCDEFA, 0xFFFF, 0xAAAA};
    char buffer[12] = "";
    //std::cout << sizeof(header_);
    memcpy(&buffer[0], &header_, sizeof(header_));

    jlib::CFWriter _writer_aci("./test.txt", jlib::J_ASCII_WFILE_T);
    _writer_aci << str_;
    _writer_aci << str_.c_str();

    jlib::CFWriter _writer_bin("./test.bin", jlib::J_BINARY_WFILE_T);
    _writer_bin << std::string(buffer);
    _writer_bin << buffer;
#endif

#ifdef PROCESS
    jlib::CProcess Process1("../../a.out");
    jlib::CProcess Process2("../../a.out", jlib::J_PRINT_IN_TERMINAL);
    jlib::CProcess process3("../../a.out", jlib::J_PRINT_IN_STRING);
    std::cout << process3.Result();

    jlib::CProcess Process4(" if ping -c 1 192.168.0.1 > /dev/null 2>&1; then echo \"connected\"; else echo \"Disconnect\"; fi", jlib::J_PRINT_IN_TERMINAL);
    jlib::CProcess Process5(" if ping -c 1 192.168.0.1 > /dev/null 2>&1; then echo \"connected\"; else echo \"Disconnect\"; fi", jlib::J_PRINT_IN_STRING);
    std::cout << Process5.Result();
#endif

#ifdef THREAD
    jlib::CThread thread1("myThread", 0x1000, jlib::EC_THREAD_RUN_TYPE::THREAD_ONCE_T);
    thread1.Run();
    thread1.Join();

    jlib::CThread thread2("myThread", 0x1000, jlib::EC_THREAD_RUN_TYPE::THREAD_LOOP_T);
    thread2.Run();
    jlib::delay_ms(3);
    thread2.Terminate();
    thread2.Join();

    jlib::J_FUNCTION_T<void()> Function = [](){std::cout << "hello world\n";};
    jlib::CThread thread3("myThread", 0x1000, jlib::EC_THREAD_RUN_TYPE::THREAD_ONCE_T, Function);
    thread3.Run();
    thread3.Join();
#endif

#ifdef DELAY
    constexpr uint32_t MS = 7;
    jlib::J_FUNCTION_T<void()> Function = [](){
            for(int i = 0; i < MS; ++i)
            {
                std::cout << "hello world\n";
                jlib::delay_ms(1);
            }
        };
    jlib::CThread thread("myThread", 0x1000, jlib::EC_THREAD_RUN_TYPE::THREAD_ONCE_T, Function);
    jlib::delay_ms(MS);
    thread.Join();
#endif 

#ifdef TIME
    jlib::CTime tm;
    jlib::ST_SYSTEM_TIME_T tm_ = tm.getSystemTime();
    std::cout << tm_.seconds << " " << tm_.nanoseconds << "\n";
    std::string strTM = tm.getSystemTimeString();
    std::cout << strTM << "\n";
#endif

#ifdef TIMER
    std::chrono::nanoseconds nInveral = std::chrono::nanoseconds(500000000);
    jlib::CTimer timer(nInveral, [](){std::cout << "hello world\n";}, true, jlib::nanosec_t(5000));
    while(1)
    {

    }
#endif

#ifdef WAITER
    std::cout << "Begin\n";
    jlib::CWaiter waiter;
    
    jlib::CThread thread("myThread", 0x1000, jlib::EC_THREAD_RUN_TYPE::THREAD_ONCE_T, [&](){
        std::cout << "Thread Start\n";
        jlib::delay_ms(3000);
        waiter.release();
        jlib::delay_ms(3000);
        std::cout << "Thread End\n";
    });
    waiter.wait();
    std::cout << "End\n";
    thread.Join();

    std::cout << "Begin\n";
    waiter.wait_for(jlib::J_MILLISECOND_T(3000));
    std::cout << "End\n";
#endif

#ifdef SPINLOCK
    std::cout << "Begin\n";
    jlib::CSpinlock spinlock;
    
    spinlock.lock();
    jlib::CThread thread("myThread", 0x1000, jlib::EC_THREAD_RUN_TYPE::THREAD_ONCE_T, [&](){
        std::cout << "Thread Start\n";
        jlib::delay_ms(3000);
        spinlock.unlock();
        jlib::delay_ms(3000);
        std::cout << "Thread End\n";
    });
    std::cout << "End\n";
    thread.Join();
#endif

#ifdef MUTEX
    std::cout << "Mutex Begin\n";
    jlib::CMutex mutex;
    
    bool flag1 = true;

    jlib::CThread thread1("Mutex myThread", 0x1000, jlib::EC_THREAD_RUN_TYPE::THREAD_ONCE_T, [&](){
        std::cout << "Thread Start\n";
        mutex.lock();
        jlib::delay_ms(2000);
        flag1 = false;
        mutex.unlock();
        jlib::delay_ms(2000);
        std::cout << "Mutex  Thread End\n";
    });

    while(flag1)
    {

    }
    std::cout << "Mutex End\n";
    thread1.Join();


    std::cout << "Shared Mutex Begin\n";
    jlib::CSharedMutex smutex;
    
    bool flag2 = true;

    jlib::CThread thread2("Shared Mutex myThread", 0x1000, jlib::EC_THREAD_RUN_TYPE::THREAD_ONCE_T, [&](){
        std::cout << "Shared Thread Start\n";
        smutex.lock();
        jlib::delay_ms(2000);
        flag2 = false;
        smutex.unlock();
        jlib::delay_ms(2000);
        std::cout << "Shared Mutex  Thread End\n";
    });

    while(flag2)
    {

    }
    std::cout << "Shared Mutex End\n";
    thread2.Join();
#endif

#ifdef LOCK_GAURD
    {
        jlib::CMutex mtx;
        jlib::CAutoLock<jlib::CMutex> mlg(mtx, jlib::LOCK_GUARD_T);
    }

        jlib::CSharedMutex smtx;
    {
        jlib::CAutoLock<jlib::CSharedMutex> smlg1(smtx, jlib::SHARED_LOCK_T);
    }
    {
        jlib::CAutoLock<jlib::CSharedMutex> smlg2(smtx, jlib::UNIQUE_LOCK_T);
    }
#endif
    return 0;
}
