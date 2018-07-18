#pragma once
#include "afxwin.h"


// CTestStopPLDlg �Ի���

class CTestStopPLDlg : public CDialog
{
	DECLARE_DYNAMIC(CTestStopPLDlg)

public:
	CTestStopPLDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTestStopPLDlg();

// �Ի�������
	enum { IDD = IDD_DLG_TEST_STOPPL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
public:
	afx_msg void OnBnClickedButton2();
public:
	virtual BOOL OnInitDialog();
public:
	CComboBox m_cmbLongShort;
public:
	CString m_csHand;
public:
	CString m_csPrice;
public:
	CString m_csProdCode;
public:
	UINT m_uiLast;
public:
	UINT m_uiBuy1;
public:
	UINT m_uiSell1;
	CComboBox m_cmbInst;
public:
	afx_msg void OnCbnSelchangeComboProdcode();
public:
	afx_msg void OnBnClickedButton3();
public:
	CString m_csOrderNum;
public:
	CString m_csExchID;
public:
	CString m_csMatchNo;
};
