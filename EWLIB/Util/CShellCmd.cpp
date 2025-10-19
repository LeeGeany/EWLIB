/**
 * @file CShellCmd.cpp
 * @author Jinhee.Lee (jinhee.lee@lignex1.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "CShellCmd.h"

namespace EWLIB
{
    CShellCmd::CShellCmd(const std::string _cmd)
    {
        const std::vector<std::string> args = {SHELL_PATH, "-c", _cmd};
        Run_Shell(SHELL_PATH, args);
    }

    CShellCmd::CShellCmd(const std::string _cmd, PRINT_IN_STRING _type)
    {
        std::vector<std::string> args = {SHELL_PATH, "-c", _cmd};
        Run_String(SHELL_PATH, args);
    }

    CShellCmd::CShellCmd(const std::string _cmd, PRINT_IN_SHELL _type)
    {
        std::vector<std::string> args = {SHELL_PATH, "-c", _cmd};
        Run_Shell(SHELL_PATH, args);
    }

    std::string CShellCmd::Result()
    {
        return m_strResult;
    }

    STATUS CShellCmd::Run_Shell(const std::string _path, const std::vector<std::string> _args) noexcept
    {
        STATUS Ret = true;

        pid_t pid = fork();
        if(pid < 0) {
            Ret = false;
        } else {
            if(pid == 0)
            {
                std::vector<char*> argv;
                for(const auto & str : _args) {
                    argv.push_back(const_cast<char*>(str.c_str()));
                }
                argv.push_back(nullptr);
            
                execv(_path.c_str(), argv.data());
                _exit(1);
            }
        }

        int state = 0;
        waitpid(pid, &state, 0);
        
        return Ret;
    }


    STATUS CShellCmd::Run_String(const std::string _path, const std::vector<std::string> _args) noexcept
    {
        STATUS Ret = true;

        int pipefd[2] = {0,0};
        if(pipe(pipefd) == -1)
        {
            Ret = false;
        } else {
            pid_t pid = fork();
            if(pid < 0) {
                Ret = false;
            } else {
                if(pid == 0)
                {
                    close(pipefd[0]);
                    dup2(pipefd[1], STDOUT_FILENO);
                    dup2(pipefd[1], STDERR_FILENO);
                    close(pipefd[1]);

                    std::vector<char*> argv;
                    for(const auto & str : _args) {
                        argv.push_back(const_cast<char*>(str.c_str()));
                    }
                    argv.push_back(nullptr);
                
                    execv(_path.c_str(), argv.data());
                    _exit(1);
                }

                close(pipefd[1]);
                
                std::stringstream ss;
                char buffer[128] = "";

                while(true)
                {
                    ssize_t n = read(pipefd[0], buffer, sizeof(buffer));
                    ss.write(buffer, n);

                    if(n <= 0) {break;}
                }
                close(pipefd[0]);

                int state = 0;
                waitpid(pid, &state, 0);

                m_strResult = ss.str();
            }
        }
        return Ret;
    }
}