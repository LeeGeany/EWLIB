/**
 * @file Dir.h
 * @author Jinhee.Lee (tjrgl@naver.com)
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

namespace jlib
{
    /**
     * @brief 
     * 
     * @param _path 
     * @return J_STATE 
     */
    J_STATE isExist(std::string _path) noexcept;

    /**
     * @brief 
     * 
     * @param _path 
     * @return J_STATE 
     */
    J_STATE isDirectory(std::string _path) noexcept;

    /**
     * @brief Create a Directory object
     * 
     * @param _path 
     * @param recursive 
     * @return J_STATE 
     */
    J_STATE CreateDirectory(std::string _path, bool recursive = false) noexcept;

    /**
     * @brief 
     * 
     * @param _path 
     * @return J_STATE 
     */
    J_STATE RemoveAll(std::string _path) noexcept;

    /**
     * @brief 
     * 
     * @param _path 
     * @param recursive 
     */
    void ShowDirectory(std::string _path,  bool recursive = false) noexcept;
    
    /**
     * @brief 
     * 
     * @param _path 
     * @return std::filesystem::space_info 
     */
    std::filesystem::space_info Space(std::string _path);
} /* namespace EWLIB */
#endif /* __EWLIB_FILEIO_DIR_CDIR_H__ */