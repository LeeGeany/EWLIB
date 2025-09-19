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

#include "stdEWLIB.h"
#include "stdC++17.h"

namespace EWLIB
{
    class CFile
    {
    public:
        explicit CFile(std::string _pathName);
        virtual ~CFile();

    public: 
        CFile & operator+(const std::string & _rBuffer)
        {   

            return *this;
        }

        CFile & operator+=(const std::string & _rBuffer)
        {
            return *this;
        }

    public:
        STATUS FileCreate();
        STATUS FileRemove();

    private:
        std::string m_strFilePath;
        std::ofstream m_ofsFile;  
    };
} /* namespace EWLIB */
#endif /* _EWLIB_FILEIO_FILE_CFILE_H__ */