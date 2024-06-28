
// OmokServerView.h: COmokServerView 클래스의 인터페이스
//

#pragma once
#include "ConnectSock.h"
#include "CMsgSock.h"

class COmokServerView : public CView
{
protected: // serialization에서만 만들어집니다.
	COmokServerView() noexcept;
	DECLARE_DYNCREATE(COmokServerView)

// 특성입니다.
public:
	COmokServerDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~COmokServerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	ConnectSock m_Master;
	CMsgSock m_Servant;
	CPoint StPoint[15][15];
	int stone[15][15];
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // OmokServerView.cpp의 디버그 버전
inline COmokServerDoc* COmokServerView::GetDocument() const
   { return reinterpret_cast<COmokServerDoc*>(m_pDocument); }
#endif

