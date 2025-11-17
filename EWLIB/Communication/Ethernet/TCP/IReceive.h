/**
 * @file IReceive.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-07-29
 * 
 * @copyright Copyright (c) 2025
 * 
 */

namespace EWLIB
{
    class IReceive
    {
    public:
        IReceive() = default;
        virtual ~IReceive() = default;

    protected:
        virtual uint32_t OnReceive(char * Buffer, const size_t BufferSize) = 0;
    };
} /* namespace EWLIB */