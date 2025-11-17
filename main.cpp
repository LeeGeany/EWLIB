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

#include "EWLIB/Task/Process/CProcess.h"

int main() {
    
    // CProcess Example
    jlib::CProcess Process1("../../a.out");
    jlib::CProcess Process2("../../a.out", jlib::J_PRINT_IN_TERMINAL);
    jlib::CProcess process3("../../a.out", jlib::J_PRINT_IN_STRING);
    std::cout << process3.Result();

    jlib::CProcess Process4(" if ping -c 1 192.168.0.1 > /dev/null 2>&1; then echo \"connected\"; else echo \"Disconnect\"; fi", jlib::J_PRINT_IN_TERMINAL);
    jlib::CProcess Process5(" if ping -c 1 192.168.0.1 > /dev/null 2>&1; then echo \"connected\"; else echo \"Disconnect\"; fi", jlib::J_PRINT_IN_STRING);
    std::cout << Process5.Result();

    return 0;
}
