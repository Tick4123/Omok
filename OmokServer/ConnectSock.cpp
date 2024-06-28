#include "pch.h"
#include "ConnectSock.h"

void ConnectSock::SetServant(CMsgSock* ptrSock)
{
	m_ptServant = ptrSock;
}

void ConnectSock::OnAccept(int nErrorCode)
{	
	CAsyncSocket::Accept(*m_ptServant);
	CAsyncSocket::OnAccept(nErrorCode);
}