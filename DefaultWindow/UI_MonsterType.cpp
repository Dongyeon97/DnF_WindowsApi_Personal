#include "stdafx.h"
#include "UI_MonsterType.h"
#include "BmpMgr.h"

CUI_MonsterType::CUI_MonsterType()
{
}

CUI_MonsterType::~CUI_MonsterType()
{
	Release();
}

void CUI_MonsterType::Initialize()
{
	m_eRender = TWOOVERDUI;

	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 15.f;

	m_dwTime = 0.f;

	m_fLifeTime = 7.5f;

	m_pFrameKey = L"";
}

int CUI_MonsterType::Update()
{
	m_dwTime += CTimeMgr::Get_Instance()->GetfDT();

	LifeTimeOver();
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return 0;
}

void CUI_MonsterType::Late_Update()
{
}

void CUI_MonsterType::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	__super::Update_Rect();

	// 표시되는 가장 마지막줄
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
		RGB(m_tRGB.R, m_tRGB.G, m_tRGB.B));
}

void CUI_MonsterType::Release()
{
}