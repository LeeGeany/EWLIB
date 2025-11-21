/**
 * @file IWrite.h
 * @author Jinhee.Lee (tjrgl@naver.com)
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

namespace jlib
{
    struct j_binary_wfile_t{};
    struct j_ascii_wfile_t{};

    inline constexpr j_binary_wfile_t   J_BINARY_WFILE_T = j_binary_wfile_t{};
    inline constexpr j_ascii_wfile_t    J_ASCII_WFILE_T = j_ascii_wfile_t{};

    inline constexpr std::size_t DEFAULT_BINARY_WBUFFER_SIZE = 1024;

    enum class EC_WFILE_TYPE_T { 
          WFILE_TYPE_ASCII
        , WFILE_TYPE_BINARY
    };
    
    class IWrite
    {
    public:
        IWrite();
        virtual ~IWrite();

    protected:
        virtual void fwrite(std::string & _Buffer, size_t _size)=0;
        virtual void fwrite(const char * _Buffer, size_t _size)=0;

    protected:
        virtual void toString(std::string & str, std::vector<std::string> & tokens)=0;
    }; /* class IFileRW */
} /* namespace EWLIB */
#endif /* __EWLIB_FILEIO_FILE_IWRITE_H__ */