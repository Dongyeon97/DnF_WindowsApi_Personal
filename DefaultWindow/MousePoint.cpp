#include "stdafx.h"
#include "MousePoint.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"


CMousePoint::CMousePoint()
{
}


CMousePoint::~CMousePoint()
{
	Release();
}

void CMousePoint::Initialize()
{
	m_eRender = MOUSEPOINTER;

	m_tInfo.fCX = 2.f;
	m_tInfo.fCY = 2.f;

	m_pFrameKey = L"MousePoint";
}

int CMousePoint::Update()
{
	POINT	ptMouse{};					// ���콺 ������ ��ġ�� ������ POINT����
	GetCursorPos(&ptMouse);				// ���콺 ������ ��ġ�� �����ͼ� ������ ����
	ScreenToClient(g_hWnd, &ptMouse);	// ���� ������ â�� �´� ��ǥ�� �缳��

	m_tInfo.fX = (float)ptMouse.x - 16.f;		// ���콺 ��ü ��ġ�� ������ ������ ��ǥ�� ����
	m_tInfo.fY = (float)ptMouse.y - 16.f;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMousePoint::Late_Update()
{

}

void CMousePoint::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Rectangle(hDC, m_tRect.left, m_tRect.top,
		m_tRect.right, m_tRect.bottom);

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
}

void CMousePoint::Release()
{
}
