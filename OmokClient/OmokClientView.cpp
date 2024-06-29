
// OmokClientView.cpp: COmokClientView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "OmokClient.h"
#endif

#include "OmokClientDoc.h"
#include "OmokClientView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define START_POINT 150
#define END_POINT 850
#define DISTANCE 50
#define LINE 15
#define NONE_STONE 0
#define BLACK_STONE 1
#define WHITE_STONE 2
#define STONE_SIZE 25
#define BORAD_COLOR RGB(242, 175, 96)
#define LINE_COLOR RGB(136,85,51)
#define WHITE_COLOR RGB(255, 255, 255)
#define BLACK_COLOR RGB(30,30,30)

#define IP _T("192.168.0.6")

// COmokClientView

IMPLEMENT_DYNCREATE(COmokClientView, CView)

BEGIN_MESSAGE_MAP(COmokClientView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// COmokClientView 생성/소멸

COmokClientView::COmokClientView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

	for (int i = 0; i < LINE; i++)
	{
		for (int j = 0; j < LINE; j++)
		{
			StPoint[i][j].x = START_POINT + j * DISTANCE;
			StPoint[i][j].y = START_POINT + i * DISTANCE;
			stone[i][j] = NONE_STONE;
		}
	}

	m_Client.Create();
	m_Client.Connect(IP, 100);
	if (m_Client.m_hSocket != INVALID_SOCKET)
		m_Client.Send("start", 5);
}

COmokClientView::~COmokClientView()
{
}

BOOL COmokClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// COmokClientView 그리기

void COmokClientView::OnDraw(CDC* pDC)
{
	COmokClientDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	if (m_Client.turn && !m_Client.m_strMSG.IsEmpty())
	{
		CString num1;
		CString num2;
		AfxExtractSubString(num1, m_Client.m_strMSG, 0, L' ');
		AfxExtractSubString(num2, m_Client.m_strMSG, 1, L' ');
		stone[_ttoi(num1)][_ttoi(num2)] = BLACK_STONE;
	}

	CRect rect;
	GetClientRect(&rect);

	CBrush brush, * oldBrush;
	brush.CreateSolidBrush(BORAD_COLOR);
	oldBrush = pDC->SelectObject(&brush);
	pDC->Rectangle(rect);
	pDC->SelectObject(oldBrush);
	brush.DeleteObject();

	CPen pen, * oldPen;
	pen.CreatePen(PS_SOLID, 2, LINE_COLOR);
	oldPen = pDC->SelectObject(&pen);
	for (int i = 0; i < LINE; i++)
	{
		CPoint p;
		p.x = START_POINT;
		p.y = START_POINT + i * DISTANCE;
		pDC->MoveTo(p);
		p.x = END_POINT;
		p.y = START_POINT + i * DISTANCE;
		pDC->LineTo(p);

		p.x = START_POINT + i * DISTANCE;
		p.y = START_POINT;
		pDC->MoveTo(p);
		p.x = START_POINT + i * DISTANCE;
		p.y = END_POINT;
		pDC->LineTo(p);
	}
	pDC->SelectObject(oldPen);
	pen.DeleteObject();

	CBrush blackBrush, whiteBrush;
	blackBrush.CreateSolidBrush(BLACK_COLOR);
	whiteBrush.CreateSolidBrush(WHITE_COLOR);
	pDC->SelectObject(&blackBrush);

	for (int i = 0; i < LINE; i++)
	{
		for (int j = 0; j < LINE; j++)
		{
			if (stone[i][j] == BLACK_STONE)
			{
				pDC->SelectObject(&blackBrush);
				pDC->Ellipse(StPoint[i][j].x - STONE_SIZE, StPoint[i][j].y - STONE_SIZE,
					StPoint[i][j].x + STONE_SIZE, StPoint[i][j].y + STONE_SIZE);
			}
			else if (stone[i][j] == WHITE_STONE)
			{
				pDC->SelectObject(&whiteBrush);
				pDC->Ellipse(StPoint[i][j].x - STONE_SIZE, StPoint[i][j].y - STONE_SIZE,
					StPoint[i][j].x + STONE_SIZE, StPoint[i][j].y + STONE_SIZE);
			}
		}
	}

	pDC->SelectObject(oldBrush);
	brush.DeleteObject();
}


// COmokClientView 인쇄

BOOL COmokClientView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void COmokClientView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void COmokClientView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// COmokClientView 진단

#ifdef _DEBUG
void COmokClientView::AssertValid() const
{
	CView::AssertValid();
}

void COmokClientView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COmokClientDoc* COmokClientView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COmokClientDoc)));
	return (COmokClientDoc*)m_pDocument;
}
#endif //_DEBUG


// COmokClientView 메시지 처리기

//마우스 왼쪽 클릭
void COmokClientView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	for (int i = 0; i < LINE; i++)
	{
		for (int j = 0; j < LINE; j++)
		{
			//오목돌 채워지면 제외 처리문 추가해야함
			if ((StPoint[i][j].x - DISTANCE / 2 < point.x && StPoint[i][j].y - DISTANCE / 2 < point.y) &&
				(StPoint[i][j].x + DISTANCE / 2 > point.x && StPoint[i][j].y + DISTANCE / 2 > point.y) && stone[i][j] == NONE_STONE)
			{
				if (m_Client.m_hSocket != INVALID_SOCKET && m_Client.turn)
				{
					CString str;
					str.Format(_T("%d %d"), i, j);

					int msgLen;
					msgLen = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
					char buffer[100];
					WideCharToMultiByte(CP_ACP, 0, str, -1, buffer, msgLen, NULL, NULL);

					m_Client.Send(buffer, strlen(buffer));
					stone[i][j] = WHITE_STONE;
					m_Client.turn = FALSE;
					Invalidate();
				}

			}
		}
	}


	CView::OnLButtonDown(nFlags, point);
}


//마우스 오른쪽 클릭
void COmokClientView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//for (int i = 0; i < LINE; i++)
	//{
	//	for (int j = 0; j < LINE; j++)
	//	{
	//		//오목돌 채워지면 제외 처리문 추가해야함
	//		if ((StPoint[i][j].x - 25 < point.x && StPoint[i][j].y - 25 < point.y) &&
	//			(StPoint[i][j].x + 25 > point.x && StPoint[i][j].y + 25 > point.y) && stone[i][j] == NONE_STONE)
	//		{
	//			stone[i][j] = WHITE_STONE;
	//		}
	//	}
	//}
	//Invalidate();

	CView::OnRButtonDown(nFlags, point);
}



