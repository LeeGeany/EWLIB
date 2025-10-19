/**
 * @file CFile.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __EWLIB_FILEIO_FILE_CFILE_H__
#define __EWLIB_FILEIO_FILE_CFILE_H__

#include "EWLIB/stdEWLIB.h"

namespace EWLIB
{
    class CFile 
    {
    public:
        CFile() noexcept = default;
        virtual ~CFile() = default;

    public:
        [[nodiscard]] static STATUS Exists(const std::filesystem::path& _path) noexcept
        {
            STATUS Ret = true;
            std::error_code ec;
            Ret = std::filesystem::exists(_path, ec) && std::filesystem::is_regular_file(_path, ec);
            return Ret;
        }

        [[nodiscard]] static std::uintmax_t Size(const std::filesystem::path& _path) noexcept
        {
            std::error_code ec;
            std::uintmax_t tSize = std::filesystem::file_size(_path, ec);
            return tSize;
        }

        [[nodiscard]] static STATUS Copy(const std::filesystem::path& _src, const std::filesystem::path& _dst, bool _overwrite = false) noexcept
        {
            std::error_code ec;
            std::filesystem::copy_options opt = _overwrite ? std::filesystem::copy_options::overwrite_existing : std::filesystem::copy_options::none;
            std::filesystem::copy_file(_src, _dst, opt, ec);
            return !ec;
        }

        [[nodiscard]] static STATUS Rename(const std::filesystem::path& src, const std::filesystem::path& dst) noexcept
        {
            std::error_code ec;
            std::filesystem::rename(src, dst, ec);
            return !ec;
        }

        [[nodiscard]] static STATUS Remove(const std::filesystem::path& filePath) noexcept
        {
            std::error_code ec;
            std::filesystem::remove(filePath, ec);
            return !ec;
        }

        [[nodiscard]] static std::filesystem::file_time_type LastWriteTime(const std::filesystem::path& filePath) noexcept
        {
            std::error_code ec;
            std::filesystem::file_time_type tInfo = std::filesystem::last_write_time(filePath, ec);
            return tInfo;
        }

        [[nodiscard]] static std::filesystem::perms GetPermissions(const std::filesystem::path& filePath) noexcept
        {
            std::error_code ec;
            auto status = std::filesystem::status(filePath, ec);
            return status.permissions();
        }

        static void SetPermissions(const std::filesystem::path& filePath, std::filesystem::perms perms) noexcept
        {
            std::error_code ec;
            std::filesystem::permissions(filePath, perms, std::filesystem::perm_options::replace, ec);
        }
    };

} // namespace EWLIB
#endif // __EWLIB_FILEIO_FILE_CFILE_H__
