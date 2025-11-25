/**
 * @file    CSignal.h
 * @author  jinhee.lee
 * @date    2024.07.09
 * @brief   Class of Signal Header
 * 
 * @copyright jinhee.lee
 */

#ifndef __EWLIB_EVENT_SIGNAL_SIGNAL_H__
#define __EWLIB_EVENT_SIGNAL_SIGNAL_H__

#include "EWLIB/stdEWLIB.h"

namespace jlib
{
    class CSignal
    {
    public:
        /**
         * @brief Construct a new CSignal object
         */
        CSignal() noexcept;

        /**
         * @brief Destroy the CSignal object
         */
        virtual ~CSignal() noexcept;


    public:
        /**
         * @brief 
         * @param Signal
         * @param
         * @return
         */
        //void Insert(int SigType, void(*Handler)(int));
        void Insert(int SigType, J_CALLBACK_T<void(int)>  _callback);

        /**
         * @brief 
         */
        void Delete(int SigType);

        /**
         * @brief
         * @param SigType
         * @return 
         */
        int Block(int SigType);

        /**
         * @brief
         * @return 
         */
        int BlockAll();

        /**
         * @brief 
         * @param SigType
         * @return
         */
        int Release(int SigType);

        /**
         * @brief 
         * @return
         */
        int ReleaseAll();

    private:
        static void Callback(int sig);

    private:
        /**
         * @brief 
         */
        sigset_t m_Set;

        /**
         * @brief 
         * 
         */
        static J_CALLBACK_T<void(int)> m_callback;
    };
} /* namespace jlib */
#endif /* __EWLIB_EVENT_SIGNAL_SIGNAL_H__ */