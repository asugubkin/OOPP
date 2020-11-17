
// MFCApplicationView.cpp : implementation of the CMFCApplicationView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCApplication.h"
#endif

#include "MFCApplicationDoc.h"
#include "MFCApplicationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplicationView

IMPLEMENT_DYNCREATE(CMFCApplicationView, CScrollView)

BEGIN_MESSAGE_MAP(CMFCApplicationView, CScrollView)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CMFCApplicationView construction/destruction

CMFCApplicationView::CMFCApplicationView() noexcept
{
	// TODO: add construction code here

}

CMFCApplicationView::~CMFCApplicationView()
{
}

BOOL CMFCApplicationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

// CMFCApplicationView drawing

void CMFCApplicationView::OnDraw(CDC* pDC)
{
	CMFCApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CPen pen(PS_SOLID, 3, RGB(0, 0, 192));
	CPen* pOldPen = pDC->SelectObject(&pen);

	bool bFirst = true;
	for (auto& p : pDoc->m_Points)
	{
		if (pDoc->m_bShowTitles)
		{
			CString s;
			s.Format("[%d, %d]", p.x, p.y);
			pDC->SetTextColor(RGB(255, 0, 0));
			pDC->SetBkColor(RGB(0, 255, 0));
			pDC->SetBkMode(TRANSPARENT);
			pDC->TextOut(p.x, p.y, s);
		}
		if (bFirst)
		{
			pDC->MoveTo(p);
			bFirst = false;
		}
		else
			pDC->LineTo(p);
	}
	pDC->SelectObject(pOldPen);
}

void CMFCApplicationView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = 1920;
	sizeTotal.cy = 1080;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CMFCApplicationView diagnostics

#ifdef _DEBUG
void CMFCApplicationView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMFCApplicationView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMFCApplicationDoc* CMFCApplicationView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplicationDoc)));
	return (CMFCApplicationDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplicationView message handlers


void CMFCApplicationView::OnLButtonDown(UINT nFlags, CPoint point)
{
	GetDocument()->m_Points.push_back(point);
	GetDocument()->SetModifiedFlag();
	Invalidate();
}
