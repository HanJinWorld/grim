#pragma once


// CDlgEdit ��ȭ �����Դϴ�.

class CDlgEdit : public CDialog
{
	DECLARE_DYNAMIC(CDlgEdit)

public:
	CDlgEdit(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgEdit();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	// ���� ����
	long m_size;
	int m_radio;
};
