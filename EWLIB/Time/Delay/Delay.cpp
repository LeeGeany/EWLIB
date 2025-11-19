/**
 * @file Delay.cpp
 * @author Jinhee.Lee (tjrgl@naver.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-07
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "Delay.h"

namespace jlib
{
    void delay_ns(std::uint64_t ns) noexcept
    {
        struct timespec req;
        req.tv_sec  = static_cast<time_t>(ns / 1000000000ULL);
        req.tv_nsec = static_cast<long>(ns % 1000000000ULL);

        // 신호에 의해 중단될 수도 있으므로 EINTR 처리
        while (::nanosleep(&req, &req) == -1 && errno == EINTR)
        {
            // 재시도
        }
    }

    void delay_ms(std::uint32_t ms) noexcept
    {
        delay_ns(static_cast<std::uint64_t>(ms) * 1000000ULL);
    }

    void delay_us(std::uint32_t us) noexcept
    {
        delay_ns(static_cast<std::uint64_t>(us) * 1000ULL);
    }

} // namespace EWLIB
