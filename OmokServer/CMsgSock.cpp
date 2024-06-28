#include "pch.h"
#include "CMsgSock.h"

CMsgSock::CMsgSock()
{
	turn = TRUE;
}

void CMsgSock::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	char msg[100];
	int len;
	len = CAsyncSocket::Receive(msg, 100);
	msg[len] = NULL;
	m_strMSG = CString(msg);
	turn = TRUE;
	pFrame->GetActiveView()->Invalidate();
	CAsyncSocket::OnReceive(nErrorCode);
}
