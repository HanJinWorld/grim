
// MFCApplication5Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MFCApplication5.h"
#include "MFCApplication5Dlg.h"
#include "afxdialogex.h"

#include "DlgEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication5Dlg 대화 상자



CMFCApplication5Dlg::CMFCApplication5Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION5_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_FrameWidth = 640;
	m_FrameHeight = 480;
	m_FrameBpps = 8;

	m_nSize = 100;
	m_nRadio = 0;
}

void CMFCApplication5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication5Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication5Dlg::OnBnClickedButton1)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFCApplication5Dlg 메시지 처리기

BOOL CMFCApplication5Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.	
	m_FrameWidth = GetSystemMetrics(SM_CXSCREEN);
	m_FrameHeight = GetSystemMetrics(SM_CYSCREEN);
	this->SetWindowPos(NULL, 0, 0, m_FrameWidth, m_FrameHeight, SWP_NOREPOSITION);


	GetDlgItem(IDC_BUTTON1)->MoveWindow(0, m_FrameHeight-200, m_FrameWidth-15, 95);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}


void CMFCApplication5Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(m_image)
		m_image.Destroy();
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication5Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{

		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 테두리 원
void drawCircle2(byte* image, int width, int height, int centerX, int centerY, int radius, byte color) 
{
	for (int y = 0; y < height; ++y) 
	{
		for (int x = 0; x < width; ++x) 
		{
			int dx = x - centerX;
			int dy = y - centerY;
			int distanceSquared = dx * dx + dy * dy;
			if (distanceSquared >= (radius - 1) * (radius - 1) && distanceSquared <= (radius + 1) * (radius + 1)) 
			{
				image[y * width + x] = color;
			}
		}
	}
}

// 꽉 채운 원
void drawCircle(byte* image, int width, int height, int centerX, int centerY, int radius, byte color) 
{
	int radiusSquared = radius * radius;
	for (int y = centerY - radius; y <= centerY + radius; ++y) 
	{
		for (int x = centerX - radius; x <= centerX + radius; ++x) 
		{
			int dx = x - centerX;
			int dy = y - centerY;
			int distanceSquared = dx * dx + dy * dy;
			if (distanceSquared <= radiusSquared) 
			{
				if (x >= 0 && x < width && y >= 0 && y < height) 
				{
					image[y * width + x] = color;
				}
			}
		}
	}
}

// 원의 중심 찾기
void CMFCApplication5Dlg::OnBnClickedButton1()
{
	CDlgEdit dlg;
	dlg.m_size = m_nSize;
	dlg.m_radio = m_nRadio;
	if (dlg.DoModal()!=IDOK)
	{
		return;
	}
	m_nSize = dlg.m_size;	// 지름
	m_nRadio = dlg.m_radio;	// 디스플레이 갱신

	/////////////////////////////////////// CImage 생성 ///////////////////////////////////
	int nWidth = m_FrameWidth;
	int nHeight = m_FrameHeight;
	int nBpp = m_FrameBpps;

	// 기존 이미지 초기화
	m_image.Destroy();

	// 새로운 이미지 생성
	m_image.Create(m_FrameWidth, -m_FrameHeight, m_FrameBpps);
	if (m_FrameBpps == 8)
	{
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
		{
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		}
		m_image.SetColorTable(0, 256, rgb);
	}


	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	///////////////////////////////// 원을 그리기(data) /////////////////////////////////////////
	int radius = m_nSize;
	int color = 255;
	int nCenterX = rand()%(m_FrameWidth-240)+1;
	int nCenterY = rand()%(m_FrameHeight-240)+1;
	if (nCenterX < 240)	nCenterX = 240;
	if (nCenterY < 240)	nCenterY = 240;
	drawCircle(fm, m_FrameWidth, m_FrameHeight, nCenterX, nCenterY, m_nSize, 255);

	/////////////////////////////// 원 찾기 ///////////////////////////////////////////
	cv::Mat image = cv::Mat(m_FrameHeight, m_FrameWidth, CV_8UC1, fm);

	// 이미지 전처리 (가우시안 블러 적용)
	cv::GaussianBlur(image, image, cv::Size(5, 5), 0);

	// Hough 원 검출
	std::vector<cv::Vec3f> circles;
	cv::HoughCircles(image, circles, cv::HOUGH_GRADIENT, 1, image.rows / 8, 100, 30);

	//////////////////////////////// 찾은 원 그리기(dc) //////////////////////////////////////////
	CClientDC dc(this);

	CRect clientRect;
	GetClientRect(&clientRect);
	dc.FillSolidRect(&clientRect, RGB(0, 0, 0));  // 배경 색
	
	if(m_nRadio == 1)
	{
		for (const auto& circle : circles) {
			cv::Point center(cvRound(circle[0]), cvRound(circle[1]));
			int radius = cvRound(circle[2]);

			//////////////////////////////////////////////////////////////////////////
			// 원 그리기
			CPen pen(PS_SOLID, 1, RGB(255, 255, 0));  // 노란색 펜 생성
			CPen* pOldPen = dc.SelectObject(&pen);
//			dc.Ellipse(center.x - radius, center.y - radius, center.x + radius, center.y + radius);

			CRect rectCircle;
			rectCircle.left = center.x - radius;
			rectCircle.top = center.y - radius;
			rectCircle.right = center.x + radius;
			rectCircle.bottom = center.y + radius;
			dc.Arc(rectCircle, CPoint(rectCircle.CenterPoint().x, rectCircle.CenterPoint().y),
								CPoint(rectCircle.CenterPoint().x, rectCircle.CenterPoint().y));

			dc.SelectObject(pOldPen);

			//////////////////////////////////////////////////////////////////////////
			// 원의 중심에 십자가 그리기
			CPen redPen(PS_SOLID, 1, RGB(255, 0, 0));		// 빨간색 펜 생성
			CPen* pOldRedPen = dc.SelectObject(&redPen);	// 기존 펜 저장
			int nRedPen = 3;

			// 수평선 그리기
			dc.MoveTo(center.x - nRedPen, center.y);
			dc.LineTo(center.x + nRedPen, center.y);

			// 수직선 그리기
			dc.MoveTo(center.x, center.y - nRedPen);
			dc.LineTo(center.x, center.y + nRedPen);

			// 빨간색 펜 복원
			dc.SelectObject(pOldRedPen);
		}
	}
	else
	{
		m_image.Draw(dc, 0, 0);
	}	
}
