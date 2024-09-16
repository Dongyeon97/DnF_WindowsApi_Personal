#include "stdafx.h"
#include "Mouse.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"


CMouse::CMouse()
{
}


CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize()
{
	m_eRender = MOUSEPOINTER;

	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;

	m_pFrameKey = L"Mouse";
}

int CMouse::Update()
{
	POINT	ptMouse{};					// ���콺 ������ ��ġ�� ������ POINT����
	GetCursorPos(&ptMouse);				// ���콺 ������ ��ġ�� �����ͼ� ������ ����
	ScreenToClient(g_hWnd, &ptMouse);	// ���� ������ â�� �´� ��ǥ�� �缳��

	m_tInfo.fX = (float)ptMouse.x;		// ���콺 ��ü ��ġ�� ������ ������ ��ǥ�� ����
	m_tInfo.fY = (float)ptMouse.y;
	
	__super::Update_Rect();
	ShowCursor(false);					// ���콺 Ŀ���� ���̰� �ϴ� ����

	return OBJ_NOEVENT;
}

void CMouse::Late_Update()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
	{
		m_tFrame.iFrameStart = 1;
	}
	if (CKeyMgr::Get_Instance()->Key_Up(VK_LBUTTON))
	{
		m_tFrame.iFrameStart = 0;
	}
}

void CMouse::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	/*HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Rectangle(hDC, m_tRect.left , m_tRect.top ,
		m_tRect.right , m_tRect.bottom );

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);*/

	GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));
}

void CMouse::Release()
{
}
