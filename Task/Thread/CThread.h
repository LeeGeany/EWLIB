/**
 * @file CThread.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-07-13
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __SRCS_TASK_THREAD_CTHREAD_H__
#define __SRCS_TASK_THREAD_CTHREAD_H__

#include "EWLIB/stdEWLIB.h"

#include "IOperator.h"

namespace EWLIB 
{

    class CThread : public IOperator
    {
    public:
        explicit CThread( EW_THREAD_NAME_T      _strThreadName
                        , EW_THREAD_ID_T        _uiThreadID
                        , EC_THREAD_RUN_TYPE    _ecThreadRunType
                        , EW_FUNCTION_T<void()> _function) noexcept;

        explicit CThread( EW_THREAD_NAME_T      _strThreadName
                        , EW_THREAD_ID_T        _uiThreadID
                        , EC_THREAD_RUN_TYPE    _ecThreadRunType) noexcept;

        virtual ~CThread() noexcept;

    public:
        STATUS Run(); 
        STATUS Wait();
        STATUS Terminate();
        STATUS Join();
        STATUS Detach();

    public:
        ST_THREAD_CONTROL_BLOCK_T getTCBInfo();

    protected:
        virtual void PreOperate() override;
        virtual void Operate() override;
        virtual void PostOperate() override;

    private:
        void Runnable();

    protected:
        EW_THREAD_T m_Thread;

        EW_MUTEX_T m_ThreadStateMutex;

        ST_THREAD_CONTROL_BLOCK_T m_TCB;

        EW_FUNCTION_T<void()> m_Function;
    }; /* class CThread */

} /* namespace EWLIB */
#endif /* __SRCS_TASK_THREAD_CTHREAD_H__ */