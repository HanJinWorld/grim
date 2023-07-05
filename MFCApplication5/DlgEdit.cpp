// DlgEdit.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCApplication5.h"
#include "DlgEdit.h"
#include "afxdialogex.h"


// CDlgEdit 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgEdit, CDialog)

CDlgEdit::CDlgEdit(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG1, pParent)
	, m_size(100)
	, m_radio(0)
{

}

CDlgEdit::~CDlgEdit()
{
}

void CDlgEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_size);
	DDV_MinMaxLong(pDX, m_size, 1, 512);
	DDX_Radio(pDX, IDC_RADIO1, m_radio);
}


BEGIN_MESSAGE_MAP(CDlgEdit, CDialog)
END_MESSAGE_MAP()


// CDlgEdit 메시지 처리기입니다.
