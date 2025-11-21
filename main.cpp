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
#include "EWLIB/Container/RingBuffer/CRingBuffer.h"

#define FILE
#pragma pack()

int main() 
{
#ifdef DIR

#endif

#ifdef FILE

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
