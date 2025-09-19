/**
 * @file CFile.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-09-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "CFile.h"

namespace EWLIB
{
    CFile::CFile(std::string _pathName)
    : m_strFilePath(_pathName)
    , m_ofsFile(_pathName)
    {

    }

    CFile::~CFile()
    {
        m_ofsFil.close();
    }

    STATUS FileCreate()
    {

    }


}

#include <iostream>
#include <fstream>      // for file creation
#include <cstdio>       // for std::remove (deletion)
#include <string>

int main() {
    std::string filename = "example.txt";

    // 1. 파일 생성
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "이 파일은 C++에서 생성되었습니다.\n";
        file.close();
        std::cout << "파일 생성 완료: " << filename << std::endl;
    } else {
        std::cerr << "파일 생성 실패: " << filename << std::endl;
        return 1;
    }

    // 2. 파일 삭제
    if (std::remove(filename.c_str()) == 0) {
        std::cout << "파일 삭제 성공: " << filename << std::endl;
    } else {
        std::perror("파일 삭제 실패");
        return 1;
    }

    return 0;
}
