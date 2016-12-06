
// MFCTestDlg.cpp : ʵ���ļ�
//
//#define _CRT_SECURE_NO_WARNINGS
//#define /D_CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "MFCTest.h"
#include "MFCTestDlg.h"
#include "afxdialogex.h"
#include <string.h>
#include "AES.h"
#include <stdio.h>
#include <stdlib.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


int m_nTextX;//x text begin point
int m_nTextY;//y
CFont m_newFont;
CFont *m_pOldFont;
unsigned char *OutEncrytionInChar = { 0 }, *OutEncrytionInHex = {0};


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCTestDlg �Ի���



CMFCTestDlg::CMFCTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCTEST_DIALOG, pParent)
	, m_IptString(_T(""))
	, m_IptEncry(_T(""))
	, m_OptEncry(_T(""))
	, m_OptString(_T(""))
	, m_Key(_T(""))
	, m_Key2(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	// my add
	m_nTextX = 400;
	m_nTextY = 10;
	m_pOldFont = NULL;
}

void CMFCTestDlg::DoDataExchange(CDataExchange* pDX)//Do data exchange here
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_IptString);
	DDV_MaxChars(pDX, m_IptString, 16);
	DDX_Text(pDX, IDC_EDIT2, m_IptEncry);
	DDV_MaxChars(pDX, m_IptEncry, 32);
	DDX_Text(pDX, IDC_EDIT3, m_OptEncry);
	DDX_Text(pDX, IDC_EDIT4, m_OptString);
	DDX_Text(pDX, IDC_EDIT5, m_Key);
	DDV_MaxChars(pDX, m_Key, 16);
	DDX_Text(pDX, IDC_EDIT6, m_Key2);
	DDV_MaxChars(pDX, m_Key2, 16);
}

BEGIN_MESSAGE_MAP(CMFCTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &CMFCTestDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCTestDlg::OnBnClickedButton1)
	ON_COMMAND(AFX_IDS_SCMOVE, &CMFCTestDlg::OnAfxIdsScmove)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCTestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCTestDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCTestDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCTestDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CMFCTestDlg ��Ϣ�������

BOOL CMFCTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	// A new Font
	m_newFont.CreatePointFont(100, _T("΢���ź�"));
	//SetTimer(1, 200, NULL);//200 ms


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMFCTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//text here
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCTestDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCTestDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	unsigned char *s1 , *s2, *s3, *temp, *temp2;
	int i, j = 0, flag = 0;
	UpdateData(true);
	s1 = (unsigned char*)malloc(16 * sizeof(unsigned char));
	s2 = (unsigned char*)malloc(16 * sizeof(unsigned char));
	s3 = (unsigned char*)malloc(16 * sizeof(unsigned char));
	temp2 = (unsigned char*)malloc(33 * sizeof(unsigned char));
	temp = (unsigned char*)m_IptString.GetBuffer();
	for (j = 0, i = 0; i < 32; i++)
	{
		if (temp[i] != '\0') { s1[j] = temp[i]; j++; }
		if (i < 31 && temp[i + 1] == '\0' && temp[i] == '\0') break;
	}
	s1[j] = '\0';
	flag = ZeroPadding(s1, 16);
	temp = (unsigned char*)m_Key.GetBuffer();
	for (j = 0, i = 0; i < 32; i++)
	{
		if (temp[i] != '\0') { s2[j] = temp[i]; j++; }
		if (i < 31 && temp[i + 1] == '\0' && temp[i] == '\0') break;
	}
	s2[j] = '\0';
	flag |= ZeroPadding(s2, 16);

	//unsigned char plantext[16] = { 0x6b, 0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96,0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a };
	//unsigned char fixkey[16] = { 0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c };
	//Encryption(plantext, s3, fixkey);
	//result: 3ad77bb40d7a3660a89ecaf32466ef97
	
	Encryption(s1, s3, s2);
	OutEncrytionInChar = s3;//Ϊ�ַ���ʽ�����׼��
	for (i = 0, j = 0; j < 16; j++)//tranfer string to discret numbers
	{
		temp2[i] = s3[j] >> 4;
		if (temp2[i] >= 0x00 && temp2[i] <= 0x09) temp2[i] += '0';
		else temp2[i] = temp2[i] - 10 + 'a';
		temp2[i+1] = s3[j] & 0x0f;
		if (temp2[i+1] >= 0x00 && temp2[i+1] <= 0x09) temp2[i+1] += '0';
		else temp2[i + 1] = temp2[i + 1] - 10 + 'a';
		i += 2;
	}
	temp2[32] = '\0';//33th should be the end
	OutEncrytionInHex = temp2;
	m_OptEncry = temp2;
	


	UpdateData(false);

	//=========================Text out==========================
	if (flag == 1)
	{
		CRect rect;
		GetClientRect(&rect);
		CClientDC dc(this);
		m_pOldFont = (CFont*)dc.SelectObject(&m_newFont);
		dc.SetBkMode(TRANSPARENT); //���ñ���Ϊ͸��    
		//dc.SetTextColor(RGB(0, 0, 0));
		//dc.TextOut(m_nTextX, 10, m_OptEncry);
		dc.SetTextColor(RGB(255, 0, 1));
		dc.TextOut(20, m_nTextY, _T("Text or key less than 128 bits. '0' Padding appplied!"));
		dc.SelectObject(m_pOldFont);// �ָ���ǰ������   
	}

	m_IptString.ReleaseBuffer();
	m_OptEncry.ReleaseBuffer();
	m_Key.ReleaseBuffer();
}

void CMFCTestDlg::OnBnClickedButton2()
{
	
	unsigned char *s4, *s5, *s6, *temp3, *temp4;
	unsigned char num1, num2;
	int i, j = 0, flag = 0;
	UpdateData(true);
	s4 = (unsigned char*)malloc(16 * sizeof(unsigned char));//m_IptEncry
	s5 = (unsigned char*)malloc(16 * sizeof(unsigned char));//Key2
	s6 = (unsigned char*)malloc(16 * sizeof(unsigned char));//m_OptString
	temp4 = (unsigned char*)malloc(33 * sizeof(unsigned char));
	temp3 = (unsigned char*)m_IptEncry.GetBuffer();
	for (j = 0, i = 0; i < 64; i++)
	{
		if (temp3[i] != '\0') { temp4[j] = temp3[i]; j++; }//�Ȱ�����32����temp4�У���ת��Ϊ�ַ�����s4
		if (i < 63 && temp3[i + 1] == '\0' && temp3[i] == '\0') break;
	}
	temp4[j] = '\0';
	flag = ZeroPadding(temp4, 32);
	for (i = 0,j = 0; j < 32; j += 2)//'2','\0','5' -> 0x02,0x05 -> 0x25
	{
		if (temp4[j] >= '0' && temp4[j] <= '9') num1 = (temp4[j] - '0' + 0x00) << 4;
		else num1 = (temp4[j] - 'a' + 0x0a) << 4;
		if (temp4[j+1] >= '0' && temp4[j+1] <= '9') num2 = temp4[j+1] - '0' + 0x00;
		else num2 = temp4[j+1] - 'a' + 0x0a;
		s4[i] = num1 + num2;
		i++;
	}
	s4[i] = '\0';

	temp3 = (unsigned char*)m_Key2.GetBuffer();
	for (j = 0, i = 0; i < 32; i++)
	{
		if (temp3[i] != '\0') { s5[j] = temp3[i]; j++; }
		if (i < 31 && temp3[i + 1] == '\0' && temp3[i] == '\0') break;
	}
	s5[j] = '\0';
	flag |= ZeroPadding(s5, 16);//padding error
	
	Decryption(s4, s6, s5);
	m_OptString = s6;
	UpdateData(false);
}


void CMFCTestDlg::OnAfxIdsScmove()// click x on right corner
{
	// TODO: �˳�
	CloseFile();
	OnClose();
}

void CMFCTestDlg::OnBnClickedButton3()
{
	UpdateData(true);
	m_IptEncry = m_OptEncry;
	m_Key2 = m_Key;
	UpdateData(false);
}


void CMFCTestDlg::OnBnClickedButton4()
{
	unsigned char * temp;
	int len = 0;
	temp = (unsigned char*)malloc(65 * sizeof(unsigned char));
	temp = (unsigned char*)m_OptEncry.GetBuffer();
	
	while (temp[len] != '\0' || temp[len + 1] != '\0')
	{
		len++;
	}

	UpdateData(true);
	if (len >= 31)
		m_OptEncry = OutEncrytionInChar;
	else if (len < 31 && len >= 15)
		m_OptEncry = OutEncrytionInHex;
	UpdateData(false);

}


void CMFCTestDlg::OnBnClickedButton5()
{
	
	UpdateData(true);
	m_IptString = { '\0' };
	m_Key = { '\0' };
	m_Key2 = { '\0' };
	m_OptEncry = { '\0' };
	m_IptEncry = { '\0' };
	m_OptString = { '\0' };
	UpdateData(false);
}
