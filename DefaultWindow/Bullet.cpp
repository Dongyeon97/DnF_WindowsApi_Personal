#include "stdafx.h"
#include "Bullet.h"

#include "ScrollMgr.h"
#include "TimeMgr.h"
#include "BmpMgr.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize()
{
	m_eRender = GAMEOBJECT;

	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 20.f;

	m_dwTime = 0.f;
}

int CBullet::Update()
{
	m_eRender = GAMEOBJECT;
	m_dwTime += CTimeMgr::Get_Instance()->GetfDT();

	LifeTimeOver();
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));
	
	__super::Update_Rect();	

	return OBJ_NOEVENT;
}
void CBullet::Late_Update()
{
}

void CBullet::Render(HDC hDC)
{
	float fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	GdiTransparentBlt(hDC,
		m_tRect.left + (long)fScrollX,
		m_tRect.top + (long)fScrollY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));
}

void CBullet::Release()
{
}
