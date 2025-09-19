/**
 * @file CThread.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-07-13
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "CThread.h"

namespace EWLIB 
{

    CThread::CThread( EW_THREAD_NAME_T      _strThreadName
                    , EW_THREAD_ID_T        _uiThreadID
                    , EC_THREAD_RUN_TYPE    _ecThreadRunType
                    , EW_FUNCTION_T<void()> _function) noexcept
    : m_Function{std::bind(_function)}
    , m_Thread{m_Function}
    , m_ThreadStateMutex{}
    , m_TCB{  static_cast<std::string>(_strThreadName)
            , _uiThreadID
            , _ecThreadRunType
            , EC_THREAD_STATUS_TYPE::THREAD_STATUS_NEW_T}
    {

    }

    CThread::CThread( EW_THREAD_NAME_T      _strThreadName
                    , EW_THREAD_ID_T        _uiThreadID            
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

    STATUS CThread::Run()
    {
        std::unique_lock<std::mutex> lock(m_ThreadStateMutex);
        m_TCB.ecThreadStatus = EC_THREAD_STATUS_TYPE::THREAD_STATUS_RUN_T;

        return 0;
    }

    STATUS CThread::Wait()
    {
        std::unique_lock<std::mutex> lock(m_ThreadStateMutex);
        m_TCB.ecThreadStatus = EC_THREAD_STATUS_TYPE::THREAD_STATUS_WAIT_T;

        return 0;
    }

    STATUS CThread::Terminate()
    {
        std::unique_lock<std::mutex> lock(m_ThreadStateMutex);
        m_TCB.ecThreadStatus = EC_THREAD_STATUS_TYPE::THREAD_STATUS_TERMINATE_T;

        return 0;
    }

    STATUS CThread::Join()
    {
        STATUS ret = 0;
        m_Thread.join();
        return ret;
    }

    STATUS CThread::Detach()
    {
        STATUS ret = 0;
        m_Thread.detach();
        return ret;
    }

    ST_THREAD_CONTROL_BLOCK_T CThread::getTCBInfo()
    {
        return m_TCB;
    }

    void CThread::PreOperate()
    {
        //std::cout << "PreOperate\n";
    }

    void CThread::Operate()
    {
        std::cout << m_TCB.strThreadName << " is Running!!\n";
    }

    void CThread::PostOperate()
    {
        //std::cout << "PostOperate\n";
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
            }

            if(m_TCB.ecThreadStatus == EC_THREAD_STATUS_TYPE::THREAD_STATUS_TERMINATE_T)
            {
                break;
            }
        }
        while(m_TCB.ecThreadRun == EC_THREAD_RUN_TYPE::THREAD_LOOP_T);

        try
        {
            PostOperate();
        }
        catch(const std::exception& e)
        {
            std::cout << e.what() << '\n';
        }
    }

} /* namespace EWLIB */