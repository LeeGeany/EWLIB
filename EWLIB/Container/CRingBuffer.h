/**
 * @file CRingBuffer.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-09-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __EWLIB_CONTAINER_CRINGBUFFER_H__
#define __EWLIB_CONTAINER_CRINGBUFFER_H__

#include "EWLIB/stdEWLIB.h"
#include "EWLIB/stdC++17.h"

namespace EWLIB
{
    class CRingBuffer 
    {
    public:
        explicit CRingBuffer(size_t capacity);
        virtual ~CRingBuffer();

        // 소켓에서 읽은 데이터 저장
        STATUS write(const char* const _pData, size_t _Size);

        // 메시지 단위 읽기 (길이 + 데이터)
        STATUS read(char* const _pData, size_t _Size);

    private:
        inline STATUS isEmpty() const;
        inline STATUS isFull() const;
        inline size_t available() const;
        inline size_t freeSpace() const;

    public:
        std::vector<char> m_Buffer;
        size_t m_Capacity;
        size_t m_RDFD; // 읽기 위치
        size_t m_WRFD; // 쓰기 위치
        size_t m_Size; // 현재 데이터 크기
    };
} /* namespace EWLIB */

#endif /* __EWLIB_CONTAINER_CRINGBUFFER_H__ */

