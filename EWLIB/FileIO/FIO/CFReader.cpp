/**
 * @file FReader.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "CFReader.h"

namespace EWLIB
{

    CFReader::CFReader(const std::string _filePath) noexcept
    : m_strFilePath(_filePath)
    , m_ecFileType(EC_RFILE_TYPE_T::RFILE_TYPE_ASCII)
    , m_ifsFile(_filePath, std::ios::app)
    {
    }

    CFReader::CFReader(const std::string _filePath, ew_binary_rfile_t _fileType) noexcept
    : m_strFilePath(_filePath)
    , m_ecFileType(EC_RFILE_TYPE_T::RFILE_TYPE_BINARY)
    , m_ifsFile(_filePath, std::ios::binary | std::ios::app)
    {
    }

    CFReader::CFReader(const std::string _filePath, ew_ascii_rfile_t _fileType) noexcept
    : m_strFilePath(_filePath)
    , m_ecFileType(EC_RFILE_TYPE_T::RFILE_TYPE_ASCII)
    , m_ifsFile(_filePath, std::ios::app)
    {
    }

    void CFReader::FRead(std::vector<std::string> & _rToken)
    {
        if(EC_RFILE_TYPE_T::RFILE_TYPE_ASCII == m_ecFileType) {

            std::string strTemp;
            while(getline(m_ifsFile, strTemp))
            {
                _rToken.emplace_back(strTemp);
                strTemp.clear();
            }

        } else if (EC_RFILE_TYPE_T::RFILE_TYPE_BINARY == m_ecFileType) {

            while(m_ifsFile)
            {
                EWLIB::EW_BYTE_ARRAY_T<DEFAULT_BINARY_RBUFFER_SIZE> byteTemp;
                m_ifsFile.read((char*)&(byteTemp[0]), DEFAULT_BINARY_RBUFFER_SIZE);

                std::streamsize tBtyeread = m_ifsFile.gcount();
                if(tBtyeread > 0)
                {
                    std::string str;
                    str.resize(DEFAULT_BINARY_RBUFFER_SIZE + 1);
                    std::transform(byteTemp.begin(), byteTemp.end(), str.begin(),
                                    [](EW_BYTE b){return static_cast<char>(b);});
                    _rToken.emplace_back(str);
                }
            }

        } else {

            /* Nothing to do */

        }
    }

    void CFReader::FRead(char * (&_wBuffer)[DEFAULT_BINARY_RBUFFER_SIZE])
    {

    }

    void CFReader::FRead(std::vector<EW_BYTE_VECTOR_T> & _rToken)
    {

    }

    void CFReader::FRead(std::vector<EW_BYTE_ARRAY_T<DEFAULT_BINARY_RBUFFER_SIZE>> & _rToken)
    {

    }
} /* namespace EWLIB */