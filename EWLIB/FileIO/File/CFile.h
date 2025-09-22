/**
 * @file CFile.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-09-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef _EWLIB_FILEIO_FILE_CFILE_H__
#define _EWLIB_FILEIO_FILE_CFILE_H__

#include "EWLIB/stdEWLIB.h"
#include "EWLIB/stdC++17.h"

namespace EWLIB
{
    class CFile
    {
    public:
        explicit CFile(const std::string _pathName);
        virtual ~CFile();

    public: 
        CFile & operator+(const std::string & _rBuffer)
        {   
            m_ofsFile << _rBuffer;
            return *this;
        }

        CFile & operator+=(const std::string & _rBuffer)
        {
            m_ofsFile << _rBuffer;
            return *this;
        }

        CFile & operator+(const char * const _rBuffer)
        {   
            m_ofsFile << (std::string)_rBuffer;
            return *this;
        }

        CFile & operator+=(const char * const _rBuffer)
        {
            m_ofsFile << (std::string)_rBuffer;
            return *this;
        }

    public:
        // is File Exist
        STATUS isExist(EW_FILE_PATH_T _filePath);

        // File Remove
        STATUS Remove(EW_FILE_PATH_T _filePath);

        // File Read

        // File Write

        // File Permission
        EW_FILE_INFO_T GetFileStatus(EW_FILE_PATH_T _filePath);

        // File Copy
        STATUS Copy(EW_FILE_PATH_T _src, EW_FILE_PATH_T _dst);
    
        // File Rename
        STATUS Rename(EW_FILE_PATH_T _old, EW_FILE_PATH_T _new);

        // File Create exist findingn first
        STATUS CreateFile(EW_FILE_PATH_T _filePath);


    private:
        std::filesystem::path m_Path;
        const std::string m_strFilePath;
        std::ofstream m_ofsFile;  
    };
} /* namespace EWLIB */
#endif /* _EWLIB_FILEIO_FILE_CFILE_H__ */