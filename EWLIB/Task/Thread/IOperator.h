/**
 * @file IOperator.h
 * @author Jinhee.Lee (tjrgl@naver.com)
 * @brief 
 * @version 0.1
 * @date 2025-07-13
 * 
 * @copyright Copyright (c) 2025
 * 
 */

namespace jlib 
{
    class IOperator
    {
    public:
        IOperator(){};
        virtual ~IOperator(){};

    protected:
        virtual void PreOperate() =0;
        virtual void Operate() = 0;
        virtual void PostOperate() = 0;

    }; /* IOperator */
} /* namespace EWLIB */
