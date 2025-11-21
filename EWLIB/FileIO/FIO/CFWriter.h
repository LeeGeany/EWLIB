/**
 * @file CFile.h
 * @author Jinhee.Lee (tjrgl@naver.com)
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

namespace jlib
{
    class CFWriter : public IWrite
    {
    public:
        explicit CFWriter(const std::string _filePath);
        explicit CFWriter(const std::string _filePath, j_binary_wfile_t);
        explicit CFWriter(const std::string _filePath, j_ascii_wfile_t);
        virtual ~CFWriter();

    public: 
        // std::string 
        CFWriter & operator<<(std::string _buffer)
        {   
            fwrite(_buffer, _buffer.size());
            return *this;
        }

        CFWriter & operator<<(const char * _buffer)
        {
            fwrite(_buffer, strlen(_buffer));
            return *this;
        }
        
        std::ofstream & native_handle();

    protected:
        virtual void fwrite(std::string & _buffer, size_t _size) override;
        virtual void fwrite(const char * _buffer, size_t _size) override;

    protected:
        virtual void toString(std::string & str, std::vector<std::string> & tokens) override;

    private:
        const std::string   m_strFilePath;
        EC_WFILE_TYPE_T     m_ecFileType;

    protected:
        std::ofstream m_ofsFile;
    };
} /* namespace EWLIB */
#endif /* _EWLIB_FILEIO_FILE_CFILE_H__ */