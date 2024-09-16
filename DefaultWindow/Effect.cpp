#include "stdafx.h"
#include "Effect.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "TimeMgr.h"

CEffect::CEffect()
{
}

CEffect::~CEffect()
{
	Release();
}

void CEffect::Initialize()
{
	m_eRender = EFFECT;
}

int CEffect::Update()
{
	m_eRender = EFFECT;
	m_dwTime += CTimeMgr::Get_Instance()->GetfDT();
	m_tFrame.dwTime += CTimeMgr::Get_Instance()->GetfDT();

	LifeTimeOver();
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CEffect::Late_Update()
{
	__super::Move_Frame();
}

void CEffect::Render(HDC hDC)
{
	float fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	GdiTransparentBlt(hDC,
		m_tRect.left + fScrollX,
		m_tRect.top + fScrollY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(m_tRGB.R, m_tRGB.G, m_tRGB.B));
}

void CEffect::Release()
{
}