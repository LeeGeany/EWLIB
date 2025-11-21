/**
 * @file CRingBuffer.cpp
 * @author Jinhee.Lee (tjrgl@naver.com)
 * @brief 
 * @version 0.1
 * @date 2025-09-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "CRingBuffer.h"


namespace jlib
{
    CRingBuffer::CRingBuffer(size_t capacity)
    : m_Buffer(capacity)
    , m_Capacity(capacity)
    , m_RDFD(0)
    , m_WRFD(0)
    , m_Size(0)
    {
        
    }

    CRingBuffer::~CRingBuffer()
    {
    
    }

    J_STATE CRingBuffer::write(const char* const _pData, size_t _Size) 
    {

        J_STATE ret = true;
        if (_Size > freeSpace()) {
            
            ret = false; // 공간 부족
        
        } else {

            uint32_t tail = m_Capacity - m_WRFD;
            if (_Size <= tail) {

                // wrap-around 없음 → memcpy 1번
                std::memcpy(&(m_Buffer[m_WRFD]), &(_pData[0]), _Size);

            } else {

                // wrap-around 발생 → memcpy 2번
                std::memcpy(&(m_Buffer[m_WRFD]), &(_pData[0]), tail);
                std::memcpy(&(m_Buffer[0]), &(_pData[tail]), _Size - tail);

            }

            m_WRFD = (m_WRFD + _Size) % m_Capacity;
            m_Size += _Size;

        }
        
        return ret;
    }

    J_STATE CRingBuffer::read(char* const _pData, size_t _Size)
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
            if(_Size <= tail) {

                memcpy(&(_pData[0]), &(m_Buffer[m_RDFD]), _Size);
            
            } else {
            
                memcpy(&(_pData[0]), &(m_Buffer[m_RDFD]), tail);
                memcpy(&(_pData[tail]), &(m_Buffer[0]), _Size - tail);
            
            }

            m_RDFD = (m_RDFD + _Size) % m_Capacity;
            m_Size -= _Size;
        }

        return ret;
    }
    
    inline J_STATE CRingBuffer::isEmpty() const
    {
        J_STATE Ret = true;
        if(m_Size > 0) {
            Ret = false;
        } 
        return Ret;
    }

    inline J_STATE CRingBuffer::isFull() const
    {
        J_STATE Ret = true;
        if(m_Size != m_Capacity) {
            Ret = false;
        } 
        return Ret;
    }

    inline size_t CRingBuffer::available() const
    {
        return m_Size;
    }

    inline size_t CRingBuffer::freeSpace() const
    {
        return m_Capacity - m_Size;
    }
}