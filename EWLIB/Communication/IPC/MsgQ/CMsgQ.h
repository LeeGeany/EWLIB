/**
 * @file CMsgQ.h
 * @author Jinhee.Lee (tjrgl@naver.com)
 * @brief 
 * @version 0.1
 * @date 2025-07-13
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __SRCS_COMMUNICATION_IPC_CMSGQ_H__
#define __SRCS_COMMUNICATION_IPC_CMSGQ_H__
 
#include "EWLIB/stdEWLIB.h"

namespace jlib 
{
    inline constexpr size_t MAX_BUFFER_SIZE = 128;
    
    struct ST_MSG_Q_T {
        long mtype;
        char mtext[MAX_BUFFER_SIZE];
    };

    class CMsgQ 
    {
    public:
        CMsgQ() noexcept;
        explicit CMsgQ(EW_MSGQ_KEY_T _MsgKey) noexcept;
        virtual ~CMsgQ() noexcept;

    public:
        EW_MSGQ_ID_T SubscribeMsgQ(EW_MSGQ_KEY_T _MsgKey);

        // TODO
        // Make same function as another type parameter
        // ex) EW_BYTE_ARRAY_T, EW_BYTE_VECTOR_T
        int SendMsg(char * _pBuffer, size_t _size);
        int RecvMsg(char * _pBuffer, size_t _size);
        
        int FlushMsg();
        int InfoMsg(EW_MSGQ_ID_T _MsgID, struct msqid_ds * _pINfo);
        J_STATE DeleteMsg();

    public:
        EW_MSGQ_ID_T native_handle();

    private:
        EW_MSGQ_ID_T m_MsgID;

        ST_MSG_Q_T m_SendBuffer;
        ST_MSG_Q_T m_RecvBuffer;
    }; /* class CMsgQ */

} /* namespace EWLIB */
#endif /* __SRCS_COMMUNICATION_IPC_CMSGQ_H__ */