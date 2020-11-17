#pragma once


// CMyDialog dialog

class CMFCApplicationDoc;

class CMyDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDialog)

	CMFCApplicationDoc* m_pDoc;

public:
	CMyDialog(CMFCApplicationDoc*, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CMyDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bShowTitles;
	CListBox m_List;
	CComboBox m_Combo;
	CString m_Text;
	int m_ShowType;
	afx_msg void OnBnClickedRadio();
	virtual BOOL OnInitDialog();
	afx_msg void OnLbnSelchangeList();
	afx_msg void OnCbnSelchangeCombo();
	void DoChange(int n);
	void DoEdit(int n);
	int m_X;
	int m_Y;
	afx_msg void OnEnChangeEdit();
	afx_msg void OnBnClickedShowTitlesCheck();
	CEdit m_Edit;
	CSpinButtonCtrl m_Spin;
	CSliderCtrl m_Slider;
	CProgressCtrl m_Progress;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnCancel();
	afx_msg void OnBnClickedButton();
};
