
// MFCApplication5.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMFCApplication5App:
// �� Ŭ������ ������ ���ؼ��� MFCApplication5.cpp�� �����Ͻʽÿ�.
//

class CMFCApplication5App : public CWinApp
{
public:
	CMFCApplication5App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication5App theApp;