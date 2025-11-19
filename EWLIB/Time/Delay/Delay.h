/**
 * @file Delay.h
 * @author Jinhee.Lee (tjrgl@naver.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-07
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __EWLIB_TIME_DELAY_DELAY_H__
#define __EWLIB_TIME_DELAY_DELAY_H__

#include "EWLIB/stdEWLIB.h"

namespace jlib
{
    /**
     * @brief 
     * 
     * @param ns 
     */
    void delay_ns(std::uint64_t ns) noexcept;

    /**
     * @brief 
     * 
     * @param ms 
     */
    void delay_ms(std::uint32_t ms) noexcept;

    /**
     * @brief 
     * 
     * @param us 
     */
    void delay_us(std::uint32_t us) noexcept;
} /* namespace EWLIB */
#endif /* __EWLIB_TIME_DELAY_DELAY_H__ */