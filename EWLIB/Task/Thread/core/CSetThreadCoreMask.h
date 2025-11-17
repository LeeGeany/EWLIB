// /**
//  * @file CSetThreadCoreMask.h
//  * @author your name (you@domain.com)
//  * @brief 
//  * @version 0.1
//  * @date 2025-10-11
//  * 
//  * @copyright Copyright (c) 2025
//  * 
//  */

// #ifndef __EWLIB_TASK_CSETTHREADCOREMASK_H__
// #define __EWLIB_TASK_CSETTHREADCOREMASK_H__

// #include "EWLIB/stdEWLIB.h"

// namespace EWLIB
// {
//     template <typename T>
//     class CSetThreadCoreMask
//     {
//     public:
//         CSetThreadCoreMask(T * _thread, unsigned int _mask)
//         {
//             if constexpr(std::is_same_v<_thread, std::thread> || std::is_base_of_v<_thread, std::thread>) {
//                 m_pthread  = _thread->getThread().native_handle();
//                 CPU_ZERO(&m_CPUSet);  
//             }

//         }

//         virtual ~CSetThreadCoreMask() = default;

//     public:
//         void operator()(thread::CThread * _thread, unsigned int _mask)
//         {
//             CPU_SET(_mask, &m_CPUSet);
//             pthread_setaffinity_np(_thread->getThread().native_handle(), sizeof(cpu_set_t), &m_CPUSet);
//         }

//     private:
//         /**
//          * @brief 
//          * 
//          */
//         pthread_t m_pthread;

//         /**
//          * @brief 
//          * 
//          */
//         cpu_set_t m_CPUSet;

//     }; /* class CSetThreadCoreMask */
// } /* namespace EWLIB */
// #endif  /* __EWLIB_TASK_CSETTHREADCOREMASK_H__ */
