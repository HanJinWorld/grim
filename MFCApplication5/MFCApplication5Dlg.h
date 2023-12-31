
// MFCApplication5Dlg.h : 헤더 파일
//

#pragma once


// CMFCApplication5Dlg 대화 상자
class CMFCApplication5Dlg : public CDialogEx
{
private:
	CImage m_image;

// 생성입니다.
public:	
	int		m_FrameChannel;
	int		m_FrameWidth;
	int		m_FrameHeight;
	int		m_FrameBpps;
	CMFCApplication5Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION5_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
