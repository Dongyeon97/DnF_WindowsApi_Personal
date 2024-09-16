#include "stdafx.h"
#include "UI_AlphaObject.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

CUI_AlphaObject::CUI_AlphaObject()
{
}

CUI_AlphaObject::~CUI_AlphaObject()
{
}

void CUI_AlphaObject::Initialize()
{
	m_eRender = GAMEOBJECT;

	m_tInfo.fCX = 94.f;
	m_tInfo.fCY = 83.f;

	// 타일충돌 Rect 크기
	m_fTileCollisionSizeX = 64.f;
	m_fTileCollisionSizeY = 64.f;

	// 피격 Rect 크기
	m_fCollisionSizeX = 94.f;
	m_fCollisionSizeY = 83.f;

	m_pFrameKey = L"PostBox";

	m_dwTime = 0;
}

int CUI_AlphaObject::Update()
{
	m_dwTime += CTimeMgr::Get_Instance()->GetfDT();
	m_tFrame.dwTime += CTimeMgr::Get_Instance()->GetfDT();

	m_tRect.left = m_tInfo.fX - (m_tInfo.fCX * 0.5f);
	m_tRect.top = m_tInfo.fY - (m_tInfo.fCY * 0.5f);
	m_tRect.right = m_tInfo.fX + (m_tInfo.fCX * 0.5f);
	m_tRect.bottom = m_tInfo.fY + (m_tInfo.fCY * 0.5f);

	LifeTimeOver();

	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return 0;
}

void CUI_AlphaObject::Late_Update()
{
}

void CUI_AlphaObject::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	float fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	Rectangle(hDC, m_tRectCollision.left + fScrollX, m_tRectCollision.top + fScrollY,
		m_tRectCollision.right + fScrollX, m_tRectCollision.bottom + fScrollY);

	Rectangle(hDC, m_tRect.left + fScrollX, m_tRect.top + fScrollY,
		m_tRect.right + fScrollX, m_tRect.bottom + fScrollY);

	GdiTransparentBlt(hDC,
		m_tRect.left + (long)fScrollX,
		m_tRect.top + (long)fScrollY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		0,
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(0, 0, 0));
}

void CUI_AlphaObject::Release()
{
}