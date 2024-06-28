#pragma once
#include <afxsock.h>
#include "MainFrm.h"

class CMsgSock :
    public CAsyncSocket
{
public:
    CMsgSock();
    virtual void OnReceive(int nErrorCode);
    BOOL turn;
    CString m_strMSG;
};

