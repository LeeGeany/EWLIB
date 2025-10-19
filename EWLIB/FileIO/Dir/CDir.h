/**
 * @file CDir.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __EWLIB_FILEIO_DIR_CDIR_H__
#define __EWLIB_FILEIO_DIR_CDIR_H__

#include "EWLIB/stdEWLIB.h"

namespace EWLIB
{
    using EW_PATH = std::filesystem::path;

    class CDir
    {
    public:
        explicit CDir() noexcept = default;
        virtual ~CDir() noexcept = default;

    public:
        [[nodiscard]] static STATUS isExist(std::string _path) noexcept
        {
            STATUS Ret = true;
            std::error_code ec;
            Ret = std::filesystem::exists(_path, ec) && std::filesystem::is_directory(_path, ec);
            return Ret;
        }

        [[nodiscard]] static STATUS isDirectory(std::string _path) noexcept
        {
            std::error_code ec;
            return std::filesystem::is_directory(_path, ec);
        }

        [[nodiscard]] static STATUS CreateDirectory(std::string _path, bool recursive = false) noexcept
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

        [[nodiscard]] static STATUS RemoveAll(std::string _path) noexcept
        {
            std::error_code ec;
            std::filesystem::remove_all(_path, ec);
            return !ec;
        }

        void ShowDirectory(std::string _path,  bool recursive = false) noexcept
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
        
        [[nodiscard]] static std::filesystem::space_info Space(std::string _path)
        {
            std::error_code ec;
            std::filesystem::space_info tInfo =std::filesystem::space(_path, ec);
            return tInfo;
        }

    }; /* CDir */
} /* namespace EWLIB */
#endif /* __EWLIB_FILEIO_DIR_CDIR_H__ */