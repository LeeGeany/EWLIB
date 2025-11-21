/**
 * @file Dir.cpp
 * @author Jinhee.Lee (tjrgl@naver.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "Dir.h"

namespace jlib
{
    J_STATE isExist(std::string _path) noexcept
    {
        J_STATE Ret = true;
        std::error_code ec;
        Ret = std::filesystem::exists(_path, ec) && std::filesystem::is_directory(_path, ec);
        return Ret;
    }

    J_STATE isDirectory(std::string _path) noexcept
    {
        std::error_code ec;
        return std::filesystem::is_directory(_path, ec);
    }

    J_STATE CreateDirectory(std::string _path, bool recursive) noexcept
    {
        std::error_code ec;
        if (recursive)
        {
            std::filesystem::create_directories(_path, ec);
        }
        else
        {
            std::filesystem::create_directory(_path, ec);
        }
        return !ec;
    }

    J_STATE RemoveAll(std::string _path) noexcept
    {
        std::error_code ec;
        std::filesystem::remove_all(_path, ec);
        return !ec;
    }

    void ShowDirectory(std::string _path,  bool recursive) noexcept
    {
        std::error_code ec;
        if (!std::filesystem::exists(_path, ec)) { return; }

        if (recursive)
        {
            for (const auto& entry : std::filesystem::recursive_directory_iterator(_path, ec))
            {
                std::cout << entry.path() << '\n';
            }
        }
        else
        {
            for (const auto& entry : std::filesystem::directory_iterator(_path, ec))
            {
                std::cout << entry.path() << '\n';
            }
        }
    }
    
    std::filesystem::space_info Space(std::string _path)
    {
        std::error_code ec;
        std::filesystem::space_info tInfo =std::filesystem::space(_path, ec);
        return tInfo;
    }
} /* namespace EWLIB */