#include "stdafx.h"
#include "UI_MonsterBar.h"

#include "BmpMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"

CUI_MonsterBar::CUI_MonsterBar()
{
}

CUI_MonsterBar::~CUI_MonsterBar()
{
	Release();
}

void CUI_MonsterBar::Initialize()
{
	m_eRender = UI;

	m_tInfo.fCX = 629.f;
	m_tInfo.fCY = 32.f;

	m_dwTime = 0.f;

	m_fLifeTime = 7.5f;

	m_pFrameKey = L"MonsterBar";
}

int CUI_MonsterBar::Update()
{
	m_dwTime += CTimeMgr::Get_Instance()->GetfDT();

	LifeTimeOver();
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return 0;
}

void CUI_MonsterBar::Late_Update()
{
}

void CUI_MonsterBar::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	__super::Update_Rect();

	GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		0,
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));
}

void CUI_MonsterBar::Release()
{
}
