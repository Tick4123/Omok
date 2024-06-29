#include "pch.h"
#include "CMsgSock.h"

CMsgSock::CMsgSock()
{
	turn = FALSE;
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
	if (!wcsncmp(m_strMSG, L"win", 5))
	{
		turn = FALSE;
		pFrame->MessageBox(_T("우승"));
	}
	else if (!wcsncmp(m_strMSG, L"lose", 5))
	{
		turn = FALSE;
		pFrame->MessageBox(_T("패배"));
	}
	CAsyncSocket::OnReceive(nErrorCode);
}
