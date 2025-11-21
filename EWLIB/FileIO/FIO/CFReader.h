/**
 * @file FReader.h
 * @author Jinhee.Lee (tjrgl@naver.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __EWLIB_FILEIO_FIO_FREADER_H__
#define __EWLIB_FILEIO_FIO_FREADER_H__

#include "EWLIB/stdEWLIB.h"
#include "IRead.h"

namespace jlib
{
    class CFReader : public IRead
    {
    public:
        explicit CFReader(const std::string _filePath) noexcept;
        explicit CFReader(const std::string _filePath, j_binary_rfile_t) noexcept;
        explicit CFReader(const std::string _filePath, j_ascii_rfile_t) noexcept;
        virtual ~CFReader() noexcept = default;

    public:
        // TODO.
        // 1) MAKE THIS WITH ANY, VARIANT
        CFReader & operator>>(std::string & _buffer)
        {   
            fread(_buffer, _buffer.size());
            return *this;
        }

        CFReader & operator>>(char * const _buffer)
        {
            std::cout << sizeof(_buffer);
            fread(_buffer, sizeof(_buffer));
            return *this;
        }

    public:
        std::ifstream & native_handle();
        
    protected:
        virtual void fread(std::string & _buffer, size_t _size) override;
        virtual void fread(char * _buffer, size_t _size) override;

    protected:
        virtual void toToken(std::string & _str, std::vector<std::string> _tokens) override;

    private:
        const std::string   m_strFilePath;
        EC_RFILE_TYPE_T      m_ecFileType;

    private:
        std::ifstream m_ifsFile;
    }; /* class FReader */
} /* namespace EWLIB */
#endif /* __EWLIB_FILEIO_FIO_FREADER_H__ */