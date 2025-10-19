/**
 * @file CFile.h
 * @author Jinhee.Lee (jinhee.lee@lignex1.com)
 * @brief File Read/Write class header
 * @version 0.1
 * @date 2025-09-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef _EWLIB_FILEIO_FILE_CFILE_H__
#define _EWLIB_FILEIO_FILE_CFILE_H__

#include "EWLIB/stdEWLIB.h"
#include "IWrite.h"

namespace EWLIB
{
    class CFWriter : public IWrite
    {
    public:
        explicit CFWriter(const std::string _filePath);
        explicit CFWriter(const std::string _filePath, ew_binary_wfile_t _fileType);
        explicit CFWriter(const std::string _filePath, ew_ascii_wfile_t _fileType);
        virtual ~CFWriter();


    public: 
        // std::string 
        CFWriter & operator<<(const std::string _wBuffer)
        {   
            FWrite(_wBuffer);
            return *this;
        }

        CFWriter & operator<=(const std::string _wBuffer)
        {
            FWrite(_wBuffer);
            return *this;
        }

        // char buffer

        // byte vector

        // btye array
        
    protected:
        virtual void FWrite(const std::string & _wBuffer) override;
        virtual void FWrite(const char * const _wBuffer) override;
        virtual void FWrite(const EW_BYTE_VECTOR_T & _wBuffer) override;
        virtual void FWrite(const EW_BYTE_ARRAY_T<DEFAULT_BINARY_WBUFFER_SIZE> & _wBuffer) override;

    private:
        const std::string   m_strFilePath;
        EC_WFILE_TYPE_T      m_ecFileType;

    protected:
        std::ofstream m_ofsFile;
    };
} /* namespace EWLIB */
#endif /* _EWLIB_FILEIO_FILE_CFILE_H__ */