/**
 * @file CFile.cpp
 * @author Jinhee.Lee (jinhee.lee@lignex1.com)
 * @brief File Read/Write class source
 * @version 0.1
 * @date 2025-09-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "CFWriter.h"

namespace EWLIB
{
    CFWriter::CFWriter(const std::string _filePath)
    : m_strFilePath(_filePath)
    , m_ecFileType(EC_WFILE_TYPE_T::WFILE_TYPE_ASCII)
    , m_ofsFile(_filePath, std::ios::app)
    {
    }

    CFWriter::CFWriter(const std::string _filePath, ew_binary_wfile_t _fileType)
    : m_strFilePath(_filePath)
    , m_ecFileType(EC_WFILE_TYPE_T::WFILE_TYPE_BINARY)
    , m_ofsFile(_filePath, std::ios::binary | std::ios::app)
    {
    }

    CFWriter::CFWriter(const std::string _filePath, ew_ascii_wfile_t _fileType)
    : m_strFilePath(_filePath)
    , m_ecFileType(EC_WFILE_TYPE_T::WFILE_TYPE_ASCII)
    , m_ofsFile(_filePath, std::ios::app)
    {
    }

    CFWriter::~CFWriter()
    {
    }

    void CFWriter::FWrite(const std::string & _wBuffer)
    {
        if(EC_WFILE_TYPE_T::WFILE_TYPE_ASCII == m_ecFileType) {

            m_ofsFile << _wBuffer;

        } else if (EC_WFILE_TYPE_T::WFILE_TYPE_BINARY == m_ecFileType) {

            EWLIB::EW_BYTE_ARRAY_T<DEFAULT_BINARY_WBUFFER_SIZE> byteTemp;
            std::size_t tSize = _wBuffer.size();

            std::size_t offset = 0;
            while (offset < tSize) {
                // 이번 chunk에서 복사할 크기
                std::size_t copySize = std::min(_wBuffer.size() - offset, byteTemp.size());

                // 문자열 → byteArray 변환
                std::transform(_wBuffer.begin() + offset, _wBuffer.begin() + offset + copySize, byteTemp.begin(),
                            [](char c) { return static_cast<EW_BYTE>(c); });

                offset += copySize; // 다음 chunk로 이동
            }

        } else {

            /* Nothing to do */

        }
    }

    void CFWriter::FWrite(const char * const _wBuffer)
    {

    }

    void CFWriter::FWrite(const EW_BYTE_VECTOR_T & _wBuffer)
    {

    }

    void CFWriter::FWrite(const EW_BYTE_ARRAY_T<DEFAULT_BINARY_WBUFFER_SIZE> & _wBuffer)
    {

    }
    


} /* namespace EWLIB */
