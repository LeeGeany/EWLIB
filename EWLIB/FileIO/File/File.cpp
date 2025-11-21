/**
 * @file CFile.cpp
 * @author Jinhee.Lee (tjrgl@naver.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "File.h"

namespace jlib
{
    J_STATE Exists(const std::filesystem::path& _path) noexcept
    {
        J_STATE Ret = true;
        std::error_code ec;
        Ret = std::filesystem::exists(_path, ec) && std::filesystem::is_regular_file(_path, ec);
        return Ret;
    }

    std::uintmax_t Size(const std::filesystem::path& _path) noexcept
    {
        std::error_code ec;
        std::uintmax_t tSize = std::filesystem::file_size(_path, ec);
        return tSize;
    }

    J_STATE Copy(const std::filesystem::path& _src, const std::filesystem::path& _dst, bool _overwrite) noexcept
    {
        std::error_code ec;
        std::filesystem::copy_options opt = _overwrite ? std::filesystem::copy_options::overwrite_existing : std::filesystem::copy_options::none;
        std::filesystem::copy_file(_src, _dst, opt, ec);
        return !ec;
    }

    J_STATE Rename(const std::filesystem::path& src, const std::filesystem::path& dst) noexcept
    {
        std::error_code ec;
        std::filesystem::rename(src, dst, ec);
        return !ec;
    }

    J_STATE Remove(const std::filesystem::path& filePath) noexcept
    {
        std::error_code ec;
        std::filesystem::remove(filePath, ec);
        return !ec;
    }

    std::filesystem::file_time_type LastWriteTime(const std::filesystem::path& filePath) noexcept
    {
        std::error_code ec;
        std::filesystem::file_time_type tInfo = std::filesystem::last_write_time(filePath, ec);
        return tInfo;
    }

    std::filesystem::perms GetPermissions(const std::filesystem::path& filePath) noexcept
    {
        std::error_code ec;
        auto status = std::filesystem::status(filePath, ec);
        return status.permissions();
    }

    void SetPermissions(const std::filesystem::path& filePath, std::filesystem::perms perms) noexcept
    {
        std::error_code ec;
        std::filesystem::permissions(filePath, perms, std::filesystem::perm_options::replace, ec);
    }

} /* namespace EWLIB */