// CMyDialog.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "CMyDialog.h"
#include "afxdialogex.h"
#include "MFCApplicationDoc.h"


// CMyDialog dialog

IMPLEMENT_DYNAMIC(CMyDialog, CDialogEx)

CMyDialog::CMyDialog(CMFCApplicationDoc* pDoc, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MY_DIALOG, pParent), m_pDoc(pDoc)
	, m_bShowTitles(FALSE)
	, m_Text(_T(""))
	, m_ShowType(0)
	, m_X(0)
	, m_Y(0)
{

}

CMyDialog::~CMyDialog()
{
}

void CMyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_SHOW_TITLES_CHECK, m_bShowTitles);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_COMBO, m_Combo);
	DDX_Text(pDX, IDC_EDIT, m_Text);
	DDX_Radio(pDX, IDC_RADIO1, m_ShowType);
	DDX_Text(pDX, IDC_X, m_X);
	DDX_Text(pDX, IDC_Y, m_Y);
	DDX_Control(pDX, IDC_EDIT, m_Edit);
	DDX_Control(pDX, IDC_SPIN, m_Spin);
	DDX_Control(pDX, IDC_SLIDER, m_Slider);
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
}


BEGIN_MESSAGE_MAP(CMyDialog, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO1, &CMyDialog::OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO2, &CMyDialog::OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO3, &CMyDialog::OnBnClickedRadio)
	ON_LBN_SELCHANGE(IDC_LIST, &CMyDialog::OnLbnSelchangeList)
	ON_CBN_SELCHANGE(IDC_COMBO, &CMyDialog::OnCbnSelchangeCombo)
	ON_EN_CHANGE(IDC_EDIT, &CMyDialog::OnEnChangeEdit)
	ON_BN_CLICKED(IDC_SHOW_TITLES_CHECK, &CMyDialog::OnBnClickedShowTitlesCheck)
	ON_WM_HSCROLL()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN, &CMyDialog::OnDeltaposSpin)
	ON_BN_CLICKED(IDC_BUTTON, &CMyDialog::OnBnClickedButton)
END_MESSAGE_MAP()


// CMyDialog message handlers


BOOL CMyDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_Spin.SetRange(0, 1920);
	m_Slider.SetRange(0, 1080);
	m_Progress.SetRange(0, 1080);

	if (!m_pDoc->m_Points.empty())
	{
		for (auto& p : m_pDoc->m_Points)
		{
			CString s;
			s.Format("%d x %d", p.x, p.y);
			m_List.AddString(s);
			m_Combo.AddString(s);
			m_List.SetCurSel(0);
			m_Combo.SetCurSel(0);
		}
		OnLbnSelchangeList();
	}
	OnBnClickedShowTitlesCheck();
	return TRUE;
}

void CMyDialog::OnBnClickedRadio()
{
	UpdateData();
	switch (m_ShowType)
	{
	case 0:
		m_List.ShowWindow(SW_HIDE);
		m_Combo.ShowWindow(SW_SHOW);
		break;
	case 1:
		m_List.ShowWindow(SW_SHOW);
		m_Combo.ShowWindow(SW_HIDE);
		break;
	case 2:
		m_List.ShowWindow(SW_SHOW);
		m_Combo.ShowWindow(SW_SHOW);
		break;
	}
}


void CMyDialog::OnLbnSelchangeList()
{
	int n = m_List.GetCurSel();
	if (n < 0)
		return;
	m_Combo.SetCurSel(n);
	DoChange(n);
}


void CMyDialog::OnCbnSelchangeCombo()
{
	int n = m_Combo.GetCurSel();
	if (n < 0)
		return;
	m_List.SetCurSel(n);
	DoChange(n);
}

void CMyDialog::DoChange(int n)
{
	m_X = m_pDoc->m_Points[n].x;
	m_Y = m_pDoc->m_Points[n].y;
	UpdateData(FALSE);

	m_Spin.SetPos(m_X);
	m_Slider.SetPos(m_Y);
	m_Progress.SetPos(m_Y);
}

void CMyDialog::OnEnChangeEdit()
{
	UpdateData();
	SetWindowText(m_Text);
}


void CMyDialog::OnBnClickedShowTitlesCheck()
{
	UpdateData();
	m_Edit.EnableWindow(m_bShowTitles);
}


void CMyDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int n = m_List.GetCurSel();
	if (n < 0)
		return;
	m_pDoc->m_Points[n].y = m_Slider.GetPos();
	m_Progress.SetPos(m_pDoc->m_Points[n].y);

	DoEdit(n);

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CMyDialog::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	int n = m_List.GetCurSel();
	if (n < 0)
		return;
	m_pDoc->m_Points[n].x = m_Spin.GetPos();

	DoEdit(n);

	*pResult = 0;
}

void CMyDialog::DoEdit(int n)
{
	m_X = m_pDoc->m_Points[n].x;
	m_Y = m_pDoc->m_Points[n].y;
	UpdateData(FALSE);

	CString s;
	s.Format("%d x %d", m_X, m_Y);

	m_List.DeleteString(n);
	m_List.InsertString(n, s);
	m_List.SetCurSel(n);

	m_Combo.DeleteString(n);
	m_Combo.InsertString(n, s);
	m_Combo.SetCurSel(n);

}

void CMyDialog::OnBnClickedButton()
{
	AfxMessageBox("Button pressed");
}

void CMyDialog::OnCancel()
{
	if (AfxMessageBox("Are you sure?", MB_YESNO) == IDYES)
	{
		CDialogEx::OnCancel();
	}
}

