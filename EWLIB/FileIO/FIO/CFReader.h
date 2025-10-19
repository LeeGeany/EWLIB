/**
 * @file FReader.h
 * @author your name (you@domain.com)
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

namespace EWLIB
{
    class CFReader : public IRead
    {
    public:
        explicit CFReader(const std::string _filePath) noexcept;
        explicit CFReader(const std::string _filePath, ew_binary_rfile_t _fileType) noexcept;
        explicit CFReader(const std::string _filePath, ew_ascii_rfile_t _fileType) noexcept;
        virtual ~CFReader() noexcept = default;

    public:
        // TODO.
        // 1) MAKE THIS WITH ANY, VARIANT
        CFReader & operator>>(std::vector<std::string> & _rToken)
        {   
            FRead(_rToken);
            return *this;
        }

        CFReader & operator>=(std::vector<std::string> & _rToken)
        {
            FRead(_rToken);
            return *this;
        }
        
    protected:
        virtual void FRead(std::vector<std::string> & _rToken) override;
        virtual void FRead(char * (&_wBuffer)[DEFAULT_BINARY_RBUFFER_SIZE]) override;
        virtual void FRead(std::vector<EW_BYTE_VECTOR_T> & _rToken) override;
        virtual void FRead(std::vector<EW_BYTE_ARRAY_T<DEFAULT_BINARY_RBUFFER_SIZE>> & _rToken) override;
    
    protected:
        const std::string   m_strFilePath;
        EC_RFILE_TYPE_T      m_ecFileType;

    private:
        std::ifstream m_ifsFile;
    }; /* class FReader */
} /* namespace EWLIB */
#endif /* __EWLIB_FILEIO_FIO_FREADER_H__ */