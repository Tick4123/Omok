#include "pch.h"
#include "CMsgSock.h"

CMsgSock::CMsgSock()
{
	turn = FALSE;
}

void CMsgSock::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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
		pFrame->MessageBox(_T("���"));
	}
	else if (!wcsncmp(m_strMSG, L"lose", 5))
	{
		turn = FALSE;
		pFrame->MessageBox(_T("�й�"));
	}
	CAsyncSocket::OnReceive(nErrorCode);
}
