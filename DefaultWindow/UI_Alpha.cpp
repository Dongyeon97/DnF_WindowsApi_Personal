#include "stdafx.h"
#include "UI_Alpha.h"

#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

CUI_Alpha::CUI_Alpha()
{
}

CUI_Alpha::~CUI_Alpha()
{
}

void CUI_Alpha::Initialize()
{
	m_eRender = EFFECT;

	m_iAlpha = 255;
}

int CUI_Alpha::Update()
{
	m_eRender = EFFECT;

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

void CUI_Alpha::Late_Update()
{
	__super::Move_Frame();
}

void CUI_Alpha::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	float fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	// Rectangle(hDC, m_tRectCollision.left + fScrollX, m_tRectCollision.top + fScrollY,
		// m_tRectCollision.right + fScrollX, m_tRectCollision.bottom + fScrollY);

	// ¾ËÆÄ ºí·»µù
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = m_iAlpha;

	GdiAlphaBlend(hDC,
		m_tRect.left + (long)fScrollX,
		m_tRect.top + (long)fScrollY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		bf);
}

void CUI_Alpha::Release()
{
}