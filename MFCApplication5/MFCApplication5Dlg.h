
// MFCApplication5Dlg.h : ��� ����
//

#pragma once


// CMFCApplication5Dlg ��ȭ ����
class CMFCApplication5Dlg : public CDialogEx
{
private:
	CImage m_image;

// �����Դϴ�.
public:	
	int		m_FrameChannel;
	int		m_FrameWidth;
	int		m_FrameHeight;
	int		m_FrameBpps;
	CMFCApplication5Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION5_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnDestroy();
	int m_nSize;
	int m_nRadio;
};
