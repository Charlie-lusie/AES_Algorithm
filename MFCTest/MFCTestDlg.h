
// MFCTestDlg.h : ͷ�ļ�
//

#pragma once




// CMFCTestDlg �Ի���
class CMFCTestDlg : public CDialogEx
{
// ����
public:
	CMFCTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	CString m_IptString;
	CString m_IptEncry;
	CString m_OptEncry;
	CString m_OptString;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnAfxIdsScmove();
	// Key
	CString m_Key;
	// Decryption Kay
	CString m_Key2;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
};
