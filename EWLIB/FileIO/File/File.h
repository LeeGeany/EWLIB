/**
 * @file File.h
 * @author Jinhee.Lee (tjrgl@naver.com)
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

namespace jlib
{
    /**
     * @brief 
     * 
     */
    J_STATE Exists(const std::filesystem::path& _path) noexcept;

    /**
     * @brief 
     * 
     * @param _path 
     * @return std::uintmax_t 
     */
    std::uintmax_t Size(const std::filesystem::path& _path) noexcept;

    /**
     * @brief 
     * 
     */
    J_STATE Copy(const std::filesystem::path& _src, const std::filesystem::path& _dst, bool _overwrite = false) noexcept;

    /**
     * @brief 
     * 
     * @param src 
     * @param dst 
     * @return J_STATE 
     */
    J_STATE Rename(const std::filesystem::path& src, const std::filesystem::path& dst) noexcept;

    /**
     * @brief 
     * 
     * @param filePath 
     * @return J_STATE 
     */
    J_STATE Remove(const std::filesystem::path& filePath) noexcept;

    /**
     * @brief 
     * 
     * @param filePath 
     * @return std::filesystem::file_time_type 
     */
    std::filesystem::file_time_type LastWriteTime(const std::filesystem::path& filePath) noexcept;

    /**
     * @brief Get the Permissions object
     * 
     * @param filePath 
     * @return std::filesystem::perms 
     */
    std::filesystem::perms GetPermissions(const std::filesystem::path& filePath) noexcept;

    /**
     * @brief Set the Permissions object
     * 
     * @param filePath 
     * @param perms 
     */
    void SetPermissions(const std::filesystem::path& filePath, std::filesystem::perms perms) noexcept;
} // namespace EWLIB
#endif // __EWLIB_FILEIO_FILE_CFILE_H__
