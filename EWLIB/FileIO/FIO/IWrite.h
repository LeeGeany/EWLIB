/**
 * @file IWrite.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __EWLIB_FILEIO_FILE_IWRITE_H__
#define __EWLIB_FILEIO_FILE_IWRITE_H__

#include "EWLIB/stdEWLIB.h"

namespace EWLIB
{
    struct ew_binary_wfile_t{};
    struct ew_ascii_wfile_t{};

    inline constexpr ew_binary_wfile_t   EW_BINARY_WFILE_T{};
    inline constexpr ew_ascii_wfile_t    EW_ASCII_WFILE_T{};
    const constexpr std::size_t DEFAULT_BINARY_WBUFFER_SIZE = 1024;

    enum class EC_WFILE_TYPE_T { 
          WFILE_TYPE_ASCII
        , WFILE_TYPE_BINARY
    };
    
    class IWrite
    {
    public:
        IWrite() = default;
        virtual ~IWrite() = default;

    protected:
        virtual void FWrite(const std::string & _wBuffer)=0;
        virtual void FWrite(const char * const _wBuffer)=0;
        virtual void FWrite(const EW_BYTE_VECTOR_T & _wBuffer)=0;
        virtual void FWrite(const EW_BYTE_ARRAY_T<DEFAULT_BINARY_WBUFFER_SIZE> & _wBuffer)=0;
    }; /* class IFileRW */
} /* namespace EWLIB */
#endif /* __EWLIB_FILEIO_FILE_IWRITE_H__ */