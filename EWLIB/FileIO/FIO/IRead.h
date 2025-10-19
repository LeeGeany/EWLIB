/**
 * @file IRead.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __EWLIB_FILEIO_FILE_IREAD_H__
#define __EWLIB_FILEIO_FILE_IREAD_H__

#include "EWLIB/stdEWLIB.h"

namespace EWLIB
{
    struct ew_binary_rfile_t{};
    struct ew_ascii_rfile_t{};

    inline constexpr ew_binary_rfile_t   EW_BINARY_RFILE_T{};
    inline constexpr ew_ascii_rfile_t    EW_ASCII_RFILE_T{};
    const constexpr std::size_t DEFAULT_BINARY_RBUFFER_SIZE = 1024;

    enum class EC_RFILE_TYPE_T { 
          RFILE_TYPE_ASCII
        , RFILE_TYPE_BINARY
    };
    
    class IRead
    {
    public:
        IRead() = default;
        virtual ~IRead() = default;

    protected:
        virtual void FRead(std::vector<std::string> & _rToken)=0;
        virtual void FRead(char * (&_wBuffer)[DEFAULT_BINARY_RBUFFER_SIZE])=0;
        virtual void FRead(std::vector<EW_BYTE_VECTOR_T> & _rToken)=0;
        virtual void FRead(std::vector<EW_BYTE_ARRAY_T<DEFAULT_BINARY_RBUFFER_SIZE>> & _rToken)=0;
    }; /* class IRead */
} /* namespace EWLIB */
#endif /* __EWLIB_FILEIO_FILE_IREAD_H__ */