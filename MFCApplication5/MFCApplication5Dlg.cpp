
// MFCApplication5Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MFCApplication5.h"
#include "MFCApplication5Dlg.h"
#include "afxdialogex.h"

#include "DlgEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication5Dlg ��ȭ ����



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


// CMFCApplication5Dlg �޽��� ó����

BOOL CMFCApplication5Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.	
	m_FrameWidth = GetSystemMetrics(SM_CXSCREEN);
	m_FrameHeight = GetSystemMetrics(SM_CYSCREEN);
	this->SetWindowPos(NULL, 0, 0, m_FrameWidth, m_FrameHeight, SWP_NOREPOSITION);


	GetDlgItem(IDC_BUTTON1)->MoveWindow(0, m_FrameHeight-200, m_FrameWidth-15, 95);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}


void CMFCApplication5Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	if(m_image)
		m_image.Destroy();
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMFCApplication5Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{

		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CMFCApplication5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// �׵θ� ��
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

// �� ä�� ��
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

// ���� �߽� ã��
void CMFCApplication5Dlg::OnBnClickedButton1()
{
	CDlgEdit dlg;
	dlg.m_size = m_nSize;
	dlg.m_radio = m_nRadio;
	if (dlg.DoModal()!=IDOK)
	{
		return;
	}
	m_nSize = dlg.m_size;	// ����
	m_nRadio = dlg.m_radio;	// ���÷��� ����

	/////////////////////////////////////// CImage ���� ///////////////////////////////////
	int nWidth = m_FrameWidth;
	int nHeight = m_FrameHeight;
	int nBpp = m_FrameBpps;

	// ���� �̹��� �ʱ�ȭ
	m_image.Destroy();

	// ���ο� �̹��� ����
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

	///////////////////////////////// ���� �׸���(data) /////////////////////////////////////////
	int radius = m_nSize;
	int color = 255;
	int nCenterX = rand()%(m_FrameWidth-240)+1;
	int nCenterY = rand()%(m_FrameHeight-240)+1;
	if (nCenterX < 240)	nCenterX = 240;
	if (nCenterY < 240)	nCenterY = 240;
	drawCircle(fm, m_FrameWidth, m_FrameHeight, nCenterX, nCenterY, m_nSize, 255);

	/////////////////////////////// �� ã�� ///////////////////////////////////////////
	cv::Mat image = cv::Mat(m_FrameHeight, m_FrameWidth, CV_8UC1, fm);

	// �̹��� ��ó�� (����þ� �� ����)
	cv::GaussianBlur(image, image, cv::Size(5, 5), 0);

	// Hough �� ����
	std::vector<cv::Vec3f> circles;
	cv::HoughCircles(image, circles, cv::HOUGH_GRADIENT, 1, image.rows / 8, 100, 30);

	//////////////////////////////// ã�� �� �׸���(dc) //////////////////////////////////////////
	CClientDC dc(this);

	CRect clientRect;
	GetClientRect(&clientRect);
	dc.FillSolidRect(&clientRect, RGB(0, 0, 0));  // ��� ��
	
	if(m_nRadio == 1)
	{
		for (const auto& circle : circles) {
			cv::Point center(cvRound(circle[0]), cvRound(circle[1]));
			int radius = cvRound(circle[2]);

			//////////////////////////////////////////////////////////////////////////
			// �� �׸���
			CPen pen(PS_SOLID, 1, RGB(255, 255, 0));  // ����� �� ����
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
			// ���� �߽ɿ� ���ڰ� �׸���
			CPen redPen(PS_SOLID, 1, RGB(255, 0, 0));		// ������ �� ����
			CPen* pOldRedPen = dc.SelectObject(&redPen);	// ���� �� ����
			int nRedPen = 3;

			// ���� �׸���
			dc.MoveTo(center.x - nRedPen, center.y);
			dc.LineTo(center.x + nRedPen, center.y);

			// ������ �׸���
			dc.MoveTo(center.x, center.y - nRedPen);
			dc.LineTo(center.x, center.y + nRedPen);

			// ������ �� ����
			dc.SelectObject(pOldRedPen);
		}
	}
	else
	{
		m_image.Draw(dc, 0, 0);
	}	
}
