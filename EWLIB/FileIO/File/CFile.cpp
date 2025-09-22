/**
 * @file CFile.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-09-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "CFile.h"

namespace EWLIB
{
    CFile::CFile(const std::string _pathName)
    : m_strFilePath(_pathName)
    , m_ofsFile(_pathName)
    {

    }

    CFile::~CFile()
    {

    }

    // is File Exist
    STATUS CFile::isExist(EW_FILE_PATH_T _filePath)
    {
        STATUS ret = true;
        if (!std::filesystem::exists(_filePath)) 
        {
            ret = false;
        }
        return ret;
    }

    // File Remove
    STATUS CFile::Remove(EW_FILE_PATH_T _filePath)
    {
        STATUS ret = true;
        if(false == isExist(_filePath))
        {

            ret = false;

        } else {

            std::filesystem::remove_all(_filePath);

        }
    }

    EW_FILE_INFO_T CFile::GetFileStatus(EW_FILE_PATH_T _filePath)
    {
        return std::filesystem::status(_filePath);
    }

    STATUS CFile::Copy(EW_FILE_PATH_T _src, EW_FILE_PATH_T _dst)
    {
        STATUS ret = true;
        std::filesystem::copy()
    }

    STATUS CFile::Rename(EW_FILE_PATH_T _old, EW_FILE_PATH_T _new)
    {
        std::filesystem::rename(EW_FILE_PATH_T _old, EW_FILE_PATH_T _new);
    }

} /* namespace EWLIB */
