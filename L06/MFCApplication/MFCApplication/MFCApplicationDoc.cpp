
// MFCApplicationDoc.cpp : implementation of the CMFCApplicationDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCApplication.h"
#endif

#include "MFCApplicationDoc.h"
#include "CMyDialog.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCApplicationDoc

IMPLEMENT_DYNCREATE(CMFCApplicationDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCApplicationDoc, CDocument)
	ON_COMMAND(IDC_SHOW_TITLES, &CMFCApplicationDoc::OnShowTitles)
	ON_UPDATE_COMMAND_UI(IDC_SHOW_TITLES, &CMFCApplicationDoc::OnUpdateShowTitles)
	ON_COMMAND(IDC_EDIT_DIALOG, &CMFCApplicationDoc::OnEditDialog)
END_MESSAGE_MAP()


// CMFCApplicationDoc construction/destruction

CMFCApplicationDoc::CMFCApplicationDoc() noexcept
{
	// TODO: add one-time construction code here

}

CMFCApplicationDoc::~CMFCApplicationDoc()
{
}

BOOL CMFCApplicationDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_Points.clear();
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMFCApplicationDoc serialization

void CMFCApplicationDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_Points.size();
		for (auto& p : m_Points)
		{
			ar << p;
		}
	}
	else
	{
		m_Points.clear();
		CPoint p;
		int n;
		ar >> n;
		for (int i = 0; i < n; ++i)
		{
			ar >> p;
			m_Points.push_back(p);
		}
		AfxGetMainWnd()->Invalidate();
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMFCApplicationDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CMFCApplicationDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCApplicationDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCApplicationDoc diagnostics

#ifdef _DEBUG
void CMFCApplicationDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCApplicationDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCApplicationDoc commands


void CMFCApplicationDoc::OnShowTitles()
{
	m_bShowTitles = !m_bShowTitles;
	UpdateAllViews(NULL);
}


void CMFCApplicationDoc::OnUpdateShowTitles(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bShowTitles);
}


void CMFCApplicationDoc::OnEditDialog()
{
	CMyDialog dlg(this);
	dlg.m_bShowTitles = m_bShowTitles;
	dlg.m_ShowType = 2;
	if (dlg.DoModal() == IDOK)
	{
		m_bShowTitles = dlg.m_bShowTitles;
		UpdateAllViews(NULL);
	}
}