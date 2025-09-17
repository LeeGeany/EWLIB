/**
 * @file CMsgQ.cpp
 * @author jinhee.lee (jinhee.lee@lignex1.com)
 * @brief 
 * @version 0.1
 * @date 2025-07-13
 * 
 * @copyright Copyright (c) 2025
 * 
 */

 #include "CMsgQ.h"

 namespace EWLIB {

    CMsgQ::CMsgQ() noexcept
    {

    }

    CMsgQ::CMsgQ(EW_MSGQ_KEY_T _MsgKey) noexcept
    : m_MsgID{SubscribeMsgQ(_MsgKey)}
    , m_SendBuffer{0,}
    , m_RecvBuffer{0,}
    {
        std::cout << "MSGID : " << m_MsgID << "\n";
    }

    CMsgQ::~CMsgQ() noexcept
    {
        FlushMsg();
    }

    EW_MSGQ_ID_T CMsgQ::SubscribeMsgQ(EW_MSGQ_KEY_T _MsgKey)
    {
        EW_MSGQ_ID_T retID = msgget(_MsgKey, IPC_CREAT | 0x666);
        return retID;
    }

    int CMsgQ::SendMsg(EW_MSGQ_ID_T _DestID, BYTE * _pBuffer)
    {
        m_SendBuffer.mtype = 1;
        memcpy(&(m_SendBuffer.data[0]), _pBuffer, sizeof(m_SendBuffer.data));

        //printf("sizeof : %d , data : 0x%llx\n", sizeof(m_Buffer.data), (m_Buffer.data));
        //printf("sizeof : %d , data : 0x%llx\n", sizeof(_pBuffer), (long long)(_pBuffer));

        int ret = msgsnd(_DestID, &m_SendBuffer, sizeof(m_SendBuffer) - sizeof(long), IPC_NOWAIT);
        if(ret == -1) {
            printf("Send Errno = %d\n", errno);
        } else {
            printf("Send Success\n");
        }

        return ret;
    }

    int CMsgQ::RecvMsg(BYTE * _pBuffer)
    {
        int ret =  msgrcv(m_MsgID, &m_RecvBuffer, sizeof(m_RecvBuffer) - sizeof(long),0, 0);
        if(ret == -1) {
            printf("Receive Errno = %d\n", errno);
        } else {
            memcpy(_pBuffer, &(m_RecvBuffer.data[0]), sizeof(m_RecvBuffer.data));
        }

        return ret;
    }

    int CMsgQ::FlushMsg()
    {
        int ret = msgctl(m_MsgID, IPC_RMID, NULL);
        return ret;
    }

    int CMsgQ::InfoMsg(EW_MSGQ_ID_T _MsgID, struct msqid_ds * _pINfo)
    {
        int ret = msgctl(m_MsgID, IPC_STAT|IPC_SET, _pINfo);
        return ret;
    }


    STATUS CMsgQ::DeleteMsg()
    {
        STATUS ret = msgctl(m_MsgID, IPC_RMID, NULL);
        
        if(ret == -1)
        {
            std::cout << "errno = " << errno << " errno\n";
        }

        return ret;
    }

    EW_MSGQ_ID_T CMsgQ::getMsgID()
    {
        return m_MsgID;
    }

 } /* namespace EWLIB */