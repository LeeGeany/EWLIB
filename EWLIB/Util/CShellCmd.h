/**
 * @file CShellCmd.h
 * @author Jinhee.Lee (jinhee.lee@lignex1.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __EWLIB_UTIL_CSHELLCMD_H__
#define __EWLIB_UTIL_CSHELLCMD_H__

#include "EWLIB/stdEWLIB.h"

// "/bin/sh" 
// {/bin/sh -c command}
// EWLIB::CShellCmd CMD1(" if ping -c 1 192.168.0.1 > /dev/null 2>&1; then echo \"connected\"; else echo \"Disconnect\"; fi", EWLIB::EW_CMD_IN_SHELL_T);

namespace EWLIB
{
    struct PRINT_IN_SHELL
    {
    };

    struct PRINT_IN_STRING
    {
    };

    inline constexpr PRINT_IN_SHELL     EW_CMD_IN_SHELL_T    = PRINT_IN_SHELL{};
    inline constexpr PRINT_IN_STRING    EW_CMD_IN_STRING_T   = PRINT_IN_STRING{};
    
    const std::string SHELL_PATH          = "/bin/sh";  

    class CShellCmd
    {
    private:
        std::string m_strResult;

    public:
        explicit CShellCmd(const std::string _cmd);
        explicit CShellCmd(const std::string _cmd, PRINT_IN_SHELL _type);
        explicit CShellCmd(const std::string _cmd, PRINT_IN_STRING _type);

    public:
        std::string Result();

    private:
        STATUS Run_Shell(const std::string _path, std::vector<std::string> _args) noexcept;
        STATUS Run_String(const std::string _path, std::vector<std::string> _args) noexcept;
    }; /* CShellCmd*/

} /* EWLIB */
#endif /* __EWLIB_UTIL_CSHELLCMD_H__ */