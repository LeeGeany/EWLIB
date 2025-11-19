/**
 * @file CProcess.h
 * @author Jinhee.Lee (tjrgl@naver.com)
 * @brief Create a new process
 * @version 0.1
 * @date 2025-10-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __EWLIB_TASK_CPROCESS_H__
#define __EWLIB_TASK_CPROCESS_H__

#include "EWLIB/stdEWLIB.h"

// "/bin/sh" 
// {/bin/sh -c command}
// EWLIB::CShellCmd CMD1(" if ping -c 1 192.168.0.1 > /dev/null 2>&1; then echo \"connected\"; else echo \"Disconnect\"; fi", EWLIB::EW_CMD_IN_SHELL_T);

namespace jlib
{
    struct st_print_in_terminal_t   {};
    struct st_print_in_string_t     {};

    inline constexpr st_print_in_terminal_t  J_PRINT_IN_TERMINAL = st_print_in_terminal_t{};
    inline constexpr st_print_in_string_t    J_PRINT_IN_STRING   = st_print_in_string_t{};
    inline const std::string                 SHELL_PATH          = "/bin/sh";

    class CProcess
    {
    public:
        /**
         * @brief Construct a new CProcess object
         * 
         * @param _cmd 
         */
        explicit CProcess(const std::string _cmd) noexcept;

        /**
         * @brief Construct a new CProcess object
         * 
         * @param _cmd 
         * @param _type 
         */
        explicit CProcess(const std::string _cmd, st_print_in_terminal_t _type) noexcept;

        /**
         * @brief Construct a new CProcess object
         * 
         * @param _cmd 
         * @param _type 
         */
        explicit CProcess(const std::string _cmd, st_print_in_string_t _type) noexcept;
        
        /**
         * @brief Destroy the CProcess object
         * 
         */
        virtual ~CProcess() noexcept;
        
        /**
         * @brief Return the result in string
         * 
         * @return std::string &
         */
        std::string & Result();

    private:
        /**
         * @brief Fork another process and print result in shell
         * 
         * @param _cmd 
         * @param _args 
         * @return state_t 
         */
        J_STATE RunShell(const std::string _cmd, std::vector<std::string> _args) noexcept;

        /**
         * @brief Fork another process and print result in string
         * 
         * @param _cmd 
         * @param _args 
         * @return state_t 
         */
        J_STATE RunString(const std::string _cmd, std::vector<std::string> _args) noexcept;

    private:
        std::string m_strResult;
    }; /* class CProcess*/
} /* namespace EWLIB */
#endif /* __EWLIB_TASK_CPROCESS_H__ */