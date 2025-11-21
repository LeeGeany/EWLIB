/**
 * @file IRead.h
 * @author Jinhee.Lee (tjrgl@naver.com)
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

namespace jlib
{
    struct j_binary_rfile_t{};
    struct j_ascii_rfile_t{};

    inline constexpr j_binary_rfile_t   J_BINARY_RFILE_T = j_binary_rfile_t{};
    inline constexpr j_ascii_rfile_t    J_ASCII_RFILE_T = j_ascii_rfile_t{};
    inline constexpr std::size_t DEFAULT_BINARY_RBUFFER_SIZE = 1024;

    enum class EC_RFILE_TYPE_T { 
          RFILE_TYPE_ASCII
        , RFILE_TYPE_BINARY
    };
    
    class IRead
    {
    public:
        IRead();
        virtual ~IRead();

    protected:
        virtual void fread(std::string & _buffer, size_t _size)=0;
        virtual void fread(char * const _buffer, size_t _size)=0;
    
    protected:
        virtual void toToken(std::string & _str, std::vector<std::string> _tokens)=0;
    }; /* class IRead */
} /* namespace EWLIB */
#endif /* __EWLIB_FILEIO_FILE_IREAD_H__ */