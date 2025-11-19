/**
 * @file CThread.cpp
 * @author Jinhee.Lee (tjrgl@naver.com)
 * @brief 
 * @version 0.1
 * @date 2025-07-13
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "CThread.h"

namespace jlib 
{

    CThread::CThread( J_THREAD_NAME_T      _strThreadName
                    , J_THREAD_ID_T        _uiThreadID
                    , EC_THREAD_RUN_TYPE   _ecThreadRunType
                    , J_FUNCTION_T<void()> _function) noexcept
    : m_Function{_function}
    , m_Thread{m_Function}
    , m_ThreadStateMutex{}
    , m_TCB{  static_cast<std::string>(_strThreadName)
            , _uiThreadID
            , _ecThreadRunType
            , EC_THREAD_STATUS_TYPE::THREAD_STATUS_NEW_T}
    {

    }

    CThread::CThread( J_THREAD_NAME_T      _strThreadName
                    , J_THREAD_ID_T        _uiThreadID            
                    , EC_THREAD_RUN_TYPE    _ecThreadRunType) noexcept
    : m_Thread{&CThread::Runnable, this}
    , m_ThreadStateMutex{}
    , m_TCB{  static_cast<std::string>(_strThreadName)
            , _uiThreadID
            , _ecThreadRunType
            , EC_THREAD_STATUS_TYPE::THREAD_STATUS_NEW_T}
    {
        
    }

    CThread::~CThread() noexcept
    {

    }

    J_STATE CThread::Run()
    {
        std::unique_lock<std::mutex> lock(m_ThreadStateMutex);
        m_TCB.ecThreadStatus = EC_THREAD_STATUS_TYPE::THREAD_STATUS_RUN_T;

        return 0;
    }

    J_STATE CThread::Wait()
    {
        std::unique_lock<std::mutex> lock(m_ThreadStateMutex);
        m_TCB.ecThreadStatus = EC_THREAD_STATUS_TYPE::THREAD_STATUS_WAIT_T;

        return 0;
    }

    J_STATE CThread::Terminate()
    {
        std::unique_lock<std::mutex> lock(m_ThreadStateMutex);
        m_TCB.ecThreadStatus = EC_THREAD_STATUS_TYPE::THREAD_STATUS_TERMINATE_T;

        return 0;
    }

    J_STATE CThread::Join()
    {
        J_STATE ret = 0;
        m_Thread.join();
        return ret;
    }

    J_STATE CThread::Detach()
    {
        J_STATE ret = 0;
        m_Thread.detach();
        return ret;
    }

    ST_THREAD_CONTROL_BLOCK_T CThread::getTCBInfo()
    {
        return m_TCB;
    }

    J_THREAD_T & CThread::native_handle()
    {
        return m_Thread;
    }

    void CThread::PreOperate()
    {
        std::cout << "PreOperate\n";
    }

    void CThread::Operate()
    {
        std::cout << m_TCB.strThreadName << " is Running!!\n";
    }

    void CThread::PostOperate()
    {
        std::cout << "PostOperate\n";
    }

    void CThread::Runnable()
    {
        try
        {
            PreOperate();
        }
        catch(const std::exception& e)
        {
            std::cout << e.what() << '\n';
        }

        do
        {
            if(m_TCB.ecThreadStatus == EC_THREAD_STATUS_TYPE::THREAD_STATUS_RUN_T)
            {
                try
                {
                    Operate();
                }
                catch(const std::exception& e)
                {
                    std::cout << e.what() << '\n';
                }

                if(m_TCB.ecThreadRun == EC_THREAD_RUN_TYPE::THREAD_ONCE_T)
                {
                    m_TCB.ecThreadStatus = EC_THREAD_STATUS_TYPE::THREAD_STATUS_TERMINATE_T;
                }
            }

            if(m_TCB.ecThreadStatus == EC_THREAD_STATUS_TYPE::THREAD_STATUS_TERMINATE_T)
            {
                break;
            }
        }
        while(m_TCB.ecThreadRun == EC_THREAD_RUN_TYPE::THREAD_LOOP_T || m_TCB.ecThreadRun == EC_THREAD_RUN_TYPE::THREAD_ONCE_T);

        try
        {
            PostOperate();
        }
        catch(const std::exception& e)
        {
            std::cout << e.what() << '\n';
        }
    }
} /* namespace jlib */