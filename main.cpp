/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-09-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "EWLIB/stdEWLIB.h"

#define TIMER

#include "EWLIB/Task/Process/CProcess.h"
#include "EWLIB/Task/Thread/CThread.h"
#include "EWLIB/Time/Delay/Delay.h"
#include "EWLIB/Time/Time/CTime.h"
#include "EWLIB/Time/Timer/CTimer.h"

int main() 
{    
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

    return 0;
}
