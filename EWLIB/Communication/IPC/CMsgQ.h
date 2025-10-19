/**
 * @file CMsgQ.h
 * @author jinhee.lee (jinhee.lee@lignex1.com)
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

namespace EWLIB 
{

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
        int SendMsg(EW_MSGQ_ID_T _DestID, EW_BYTE * _pBuffer);
        int RecvMsg(EW_BYTE * _pBuffer);
        
        int FlushMsg();
        int InfoMsg(EW_MSGQ_ID_T _MsgID, struct msqid_ds * _pINfo);

        STATUS DeleteMsg();

    public:
        EW_MSGQ_ID_T getMsgID();

    private:
        EW_MSGQ_ID_T m_MsgID;

        ST_MSG_Q_T m_SendBuffer;
        ST_MSG_Q_T m_RecvBuffer;
    }; /* class CMsgQ */

} /* namespace EWLIB */
#endif /* __SRCS_COMMUNICATION_IPC_CMSGQ_H__ */