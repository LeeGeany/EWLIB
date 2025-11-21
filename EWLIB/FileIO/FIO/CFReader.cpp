/**
 * @file FReader.cpp
 * @author Jinhee.Lee (tjrgl@naver.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "CFReader.h"

namespace jlib
{
    CFReader::CFReader(const std::string _filePath) noexcept
    : m_strFilePath(_filePath)
    , m_ecFileType(EC_RFILE_TYPE_T::RFILE_TYPE_ASCII)
    , m_ifsFile(_filePath, std::ios::app)
    {
    }

    CFReader::CFReader(const std::string _filePath, j_binary_rfile_t) noexcept
    : m_strFilePath(_filePath)
    , m_ecFileType(EC_RFILE_TYPE_T::RFILE_TYPE_BINARY)
    , m_ifsFile(_filePath, std::ios::binary | std::ios::app)
    {
    }

    CFReader::CFReader(const std::string _filePath, j_ascii_rfile_t) noexcept
    : m_strFilePath(_filePath)
    , m_ecFileType(EC_RFILE_TYPE_T::RFILE_TYPE_ASCII)
    , m_ifsFile(_filePath, std::ios::app)
    {
    }

    std::ifstream & CFReader::native_handle()
    {
        return m_ifsFile;
    }

    void CFReader::fread(std::string & _buffer, size_t _size)
    {
        if(EC_RFILE_TYPE_T::RFILE_TYPE_ASCII == m_ecFileType) {
            std::getline(m_ifsFile, _buffer);
        } else if (EC_RFILE_TYPE_T::RFILE_TYPE_BINARY == m_ecFileType) {
            m_ifsFile.read(&(_buffer[0]), _size);
        } else {
            /* Nothing to do */
        }
    }

    void CFReader::fread(char * const _buffer, size_t _size)
    {
        if(EC_RFILE_TYPE_T::RFILE_TYPE_ASCII == m_ecFileType) {
            std::string temp;
            std::getline(m_ifsFile, temp);
            memcpy(&(_buffer[0]), temp.c_str(), _size);
        } else if (EC_RFILE_TYPE_T::RFILE_TYPE_BINARY == m_ecFileType) {
            m_ifsFile.read(&(_buffer[0]), _size);
            std::cout << _size;
        } else {
            /* Nothing to do */
        }
    }

    void CFReader::toToken(std::string & _str, std::vector<std::string> _tokens)
    {

    }
} /* namespace EWLIB */