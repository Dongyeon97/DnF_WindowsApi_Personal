#include "stdafx.h"
#include "UI_BossBar.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"

CUI_BossBar::CUI_BossBar()
{
}

CUI_BossBar::~CUI_BossBar()
{
	Release();
}

void CUI_BossBar::Initialize()
{
	m_eRender = UI;

	m_tInfo.fCX = 634.f;
	m_tInfo.fCY = 36.f;

	m_dwTime = 0.f;

	m_fLifeTime = 7.5f;

	m_pFrameKey = L"BossBar";
}

int CUI_BossBar::Update()
{
	m_dwTime += CTimeMgr::Get_Instance()->GetfDT();

	LifeTimeOver();
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return 0;
}

void CUI_BossBar::Late_Update()
{
}

void CUI_BossBar::Render(HDC hDC)
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

void CUI_BossBar::Release()
{
}
