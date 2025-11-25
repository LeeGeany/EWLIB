/**
 * @file CRingBuffer.h
 * @author Jinhee.Lee (tjrgl@naver.com)
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

namespace jlib
{
    inline constexpr size_t RINGBUFFER_DEFAULT_BUFFER_SIZE = 1024;

    template<typename T>
    class CRingBuffer 
    {
    public:
        CRingBuffer() noexcept
        : m_Buffer(RINGBUFFER_DEFAULT_BUFFER_SIZE)
        , m_Capacity(RINGBUFFER_DEFAULT_BUFFER_SIZE)
        , m_RDFD(0)
        , m_WRFD(0)
        , m_Size(0)
        {
            m_Buffer.reserve(RINGBUFFER_DEFAULT_BUFFER_SIZE);
        }

        explicit CRingBuffer(size_t _capacity) noexcept
        : m_Buffer(_capacity)
        , m_Capacity(_capacity)
        , m_RDFD(0)
        , m_WRFD(0)
        , m_Size(0)
        {
            m_Buffer.reserve(_capacity);
        }

        virtual ~CRingBuffer() = default;

        // 소켓에서 읽은 데이터 저장
        J_STATE write(T * _pData, size_t _Size)
        {

            J_STATE ret = true;
            if (_Size > freeSpace()) {
                ret = false; // 공간 부족
            } else {
                uint32_t tail = m_Capacity - m_WRFD;
                if (_Size <= tail) {
                    // wrap-around 없음 → memcpy 1번
                    std::memcpy(&(m_Buffer[m_WRFD]), &(_pData[0]), _Size* sizeof(T));
                } else {
                    // wrap-around 발생 → memcpy 2번
                    std::memcpy(&(m_Buffer[m_WRFD]), &(_pData[0]), tail* sizeof(T));
                    std::memcpy(&(m_Buffer[0]), &(_pData[tail]), (_Size - tail)* sizeof(T));
                }
                m_WRFD = (m_WRFD + _Size) % m_Capacity;
                m_Size += _Size;
            }
            return ret;
        }

        // 메시지 단위 읽기 (길이 + 데이터)
        J_STATE read(T * _pData, size_t _Size)
        {
            J_STATE ret = true;
            if (_Size > m_Size) 
            {
                return false; // 읽을 데이터 부족
            } else {
                
                // Read FD to End of Insert Data size
                // |-------------------------------------------|            Capacity
                // |--------------------|                                   Ok
                // |----------------------------------------------------|   Not Ok
                //                                             |  space | 
                uint32_t tail = m_Capacity - m_RDFD;
                if(_Size <= tail){
                    memcpy(&(_pData[0]), &(m_Buffer[m_RDFD]), _Size * sizeof(T));
                } else {
                    memcpy(&(_pData[0]), &(m_Buffer[m_RDFD]), tail * sizeof(T));
                    memcpy(&(_pData[tail]), &(m_Buffer[0]), (_Size - tail) * sizeof(T));
                }
                m_RDFD = (m_RDFD + _Size) % m_Capacity;
                m_Size -= _Size;
            }
            return ret;
        }

    private:
        inline J_STATE isEmpty() const
        {
            J_STATE Ret = true;
            if(m_Size > 0) {
                Ret = false;
            } 
            return Ret;
        }

        inline J_STATE isFull() const
        {
            J_STATE Ret = true;
            if(m_Size != m_Capacity) {
                Ret = false;
            } 
            return Ret;
        }

        inline size_t available() const
        {
            return m_Size;
        }

        inline size_t freeSpace() const
        {
            return m_Capacity - m_Size;
        }

    private:
        std::vector<T> m_Buffer;
        size_t m_Capacity;
        size_t m_RDFD; // 읽기 위치
        size_t m_WRFD; // 쓰기 위치
        size_t m_Size; // 현재 데이터 크기
    };
} /* namespace EWLIB */

#endif /* __EWLIB_CONTAINER_CRINGBUFFER_H__ */

