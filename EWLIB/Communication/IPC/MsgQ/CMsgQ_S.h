/**
 * @file CMsgQ_S.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-25
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "EWLIB/stdEWLIB.h"

namespace jlib
{
    inline constexpr size_t MSG_DEFAULT_BUFFER_SIZE = 1024;

    template<typename T>
    class CMsgQ_S
    {
    public:
        CMsgQ_S() noexcept
        {
        
        }

        explicit CMsgQ_S(size_t _bufferSize) noexcept

        {

        }

        virtual ~CMsgQ_S() noexcept
        {

        }

    public:
        void SendMsg(T * _pBuffer, size_t _size)
        {
            std::unique_lock<std::mutex> lock(mtx);
            q.push(*_pBuffer);
            cond.notify_one();
        }

        void RecvMsg(T * _pBuffer, size_t _size)
        {
            std::unique_lock<std::mutex> lock(mtx);
            cond.wait(lock, [&] {
                return !q.empty();
            });
            *_pBuffer = q.front();
            q.pop();
        }

    private:
        std::mutex mtx;
        std::condition_variable cond;
        std::queue<T> q;
    };
}