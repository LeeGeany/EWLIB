/**
 * @file CThread.h
 * @author Jinhee.Lee (jinhee.lee@lignex1.com)
 * @brief 
 * @version 0.1
 * @date 2025-07-13
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __EWLIB_TASK_CTHREAD_H__
#define __EWLIB_TASK_CTHREAD_H__

#include "EWLIB/stdEWLIB.h"

#include "IOperator.h"

namespace jlib 
{
    using J_THREAD_T           = std::thread;
    using J_THREAD_ID_T        = uint32_t;
    using J_THREAD_NAME_T      = std::string;

    enum class EC_THREAD_RUN_TYPE {
          THREAD_ONCE_T
        , THREAD_LOOP_T
    };

    enum class EC_THREAD_STATUS_TYPE {
          THREAD_STATUS_NEW_T
        , THREAD_STATUS_WAIT_T
        , THREAD_STATUS_RUN_T
        , THREAD_STATUS_TERMINATE_T
    };

    struct ST_THREAD_CONTROL_BLOCK_T{
        J_THREAD_NAME_T         strThreadName   ;
        J_THREAD_ID_T              uiThreadID      ;
        EC_THREAD_RUN_TYPE      ecThreadRun     ;
        EC_THREAD_STATUS_TYPE   ecThreadStatus  ;
    };

    class CThread : public IOperator
    {
    public:
        /**
         * @brief Construct a new CThread object
         * 
         * @param _strThreadName 
         * @param _uiThreadID 
         * @param _ecThreadRunType 
         * @param _function 
         */
        explicit CThread( J_THREAD_NAME_T      _strThreadName
                        , J_THREAD_ID_T        _uiThreadID
                        , EC_THREAD_RUN_TYPE   _ecThreadRunType
                        , J_FUNCTION_T<void()> _function) noexcept;

        /**
         * @brief Construct a new CThread object
         * 
         * @param _strThreadName 
         * @param _uiThreadID 
         * @param _ecThreadRunType 
         */
        explicit CThread( J_THREAD_NAME_T      _strThreadName
                        , J_THREAD_ID_T        _uiThreadID
                        , EC_THREAD_RUN_TYPE    _ecThreadRunType) noexcept;

        /**
         * @brief Destroy the CThread object
         * 
         */
        virtual ~CThread() noexcept;

    public:
        /**
         * @brief 
         * 
         * @return state_t 
         */
        state_t Run();

        /**
         * @brief 
         * 
         * @return state_t 
         */
        state_t Wait();

        /**
         * @brief 
         * 
         * @return state_t 
         */
        state_t Terminate();

        /**
         * @brief 
         * 
         * @return state_t 
         */
        state_t Join();

        /**
         * @brief 
         * 
         * @return state_t 
         */
        state_t Detach();

    public:
        /**
         * @brief 
         * 
         * @return ST_THREAD_CONTROL_BLOCK_T 
         */
        ST_THREAD_CONTROL_BLOCK_T getTCBInfo();

        /**
         * @brief 
         * 
         * @return J_THREAD_T& 
         */
        J_THREAD_T & native_handle();

    protected:
        virtual void PreOperate() override;
        virtual void Operate() override;
        virtual void PostOperate() override;

    private:
        void Runnable();

    protected:
        J_FUNCTION_T<void()> m_Function;

        J_THREAD_T m_Thread;

        J_MUTEX_T m_ThreadStateMutex;

        ST_THREAD_CONTROL_BLOCK_T m_TCB;
    }; /* class CThread */
} /* namespace jlib */
#endif /* __EWLIB_TASK_CTHREAD_H__ */