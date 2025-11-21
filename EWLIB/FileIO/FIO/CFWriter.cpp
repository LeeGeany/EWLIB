/**
 * @file CFile.cpp
 * @author Jinhee.Lee (tjrgl@naver.com)
 * @brief File Read/Write class source
 * @version 0.1
 * @date 2025-09-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "CFWriter.h"

namespace jlib
{
    CFWriter::CFWriter(const std::string _filePath)
    : m_strFilePath(_filePath)
    , m_ecFileType(EC_WFILE_TYPE_T::WFILE_TYPE_ASCII)
    , m_ofsFile(_filePath, std::ios::app)
    {
    }

    CFWriter::CFWriter(const std::string _filePath, j_binary_wfile_t )
    : m_strFilePath(_filePath)
    , m_ecFileType(EC_WFILE_TYPE_T::WFILE_TYPE_BINARY)
    , m_ofsFile(_filePath, std::ios::binary | std::ios::app)
    {
    }

    CFWriter::CFWriter(const std::string _filePath, j_ascii_wfile_t)
    : m_strFilePath(_filePath)
    , m_ecFileType(EC_WFILE_TYPE_T::WFILE_TYPE_ASCII)
    , m_ofsFile(_filePath, std::ios::app)
    {
    }

    CFWriter::~CFWriter()
    {
    }

    std::ofstream & CFWriter::native_handle()
    {
        return m_ofsFile;
    }

    void CFWriter::fwrite(std::string & _buffer, size_t _size)
    {
        if(EC_WFILE_TYPE_T::WFILE_TYPE_ASCII == m_ecFileType) {
            m_ofsFile << _buffer;
        } else if (EC_WFILE_TYPE_T::WFILE_TYPE_BINARY == m_ecFileType) {
            m_ofsFile.write(_buffer.c_str(), _size);
        } else {
            /* Nothing to do */
        }
    }

    void CFWriter::fwrite(const char * _buffer, size_t _size)
    {
        if(EC_WFILE_TYPE_T::WFILE_TYPE_ASCII == m_ecFileType) {
            m_ofsFile << &(_buffer[0]);
        } else if (EC_WFILE_TYPE_T::WFILE_TYPE_BINARY == m_ecFileType) {
            m_ofsFile.write(&(_buffer[0]), _size);
        } else {
            /* Nothing to do */
        }
    }

    void CFWriter::toString(std::string & str, std::vector<std::string> & tokens)
    {

    }
} /* namespace EWLIB */
