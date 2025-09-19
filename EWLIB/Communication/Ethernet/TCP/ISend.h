/**
 * @file ISend.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-09-13
 * 
 * @copyright Copyright (c) 2025
 * 
 */

 namespace EWLIB
{
    class ISend
    {
    public:
        ISend() = default;
        virtual ~ISend() = default;

    protected:
        virtual void OnSend(char * Buffer, const size_t BufferSize) = 0;
    };
} /* namespace EWLIB */