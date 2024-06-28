#pragma once
#include <afxsock.h>
#include "MainFrm.h"
#include "CMsgSock.h"

class ConnectSock :
    public CAsyncSocket
{
public:
    void SetServant(CMsgSock* ptrSock);
    void OnAccept(int nErrorCode);
    CMsgSock* m_ptServant;
};

