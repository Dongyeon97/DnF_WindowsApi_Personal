#include "stdafx.h"
#include "UI_SkillIcon_2.h"

#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

CUI_SkillIcon_2::CUI_SkillIcon_2()
{
}

CUI_SkillIcon_2::~CUI_SkillIcon_2()
{
}

void CUI_SkillIcon_2::Initialize()
{
	m_eRender = OVERDUI;

	m_tInfo.fCX = 28.f;
	m_tInfo.fCY = 28.f;

	m_tRect.left = m_tInfo.fX - (m_tInfo.fCX * 0.5f);
	m_tRect.top = m_tInfo.fY - (m_tInfo.fCY * 0.5f);
	m_tRect.right = m_tInfo.fX + (m_tInfo.fCX * 0.5f);
	m_tRect.bottom = m_tInfo.fY + (m_tInfo.fCY * 0.5f);

	m_dwTime = 0;
}

int CUI_SkillIcon_2::Update()
{
	m_dwTime += CTimeMgr::Get_Instance()->GetfDT();

	m_tRect.left = m_tInfo.fX - (m_tInfo.fCX * 0.5f);
	m_tRect.top = m_tInfo.fY - (m_tInfo.fCY * 0.5f);
	m_tRect.right = m_tInfo.fX + (m_tInfo.fCX * 0.5f);
	m_tRect.bottom = m_tInfo.fY + (m_tInfo.fCY * 0.5f);

	LifeTimeOver();

	if (m_bDead)
		return OBJ_DEAD;

	return 0;
}

void CUI_SkillIcon_2::Late_Update()
{
}

void CUI_SkillIcon_2::Render(HDC hDC)
{
	float PlayerX = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).back()->Get_Info().fX;
	float PlayerY = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).back()->Get_Info().fY;

	float fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	// ¾ËÆÄ ºí·»µù
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 255;

	GdiAlphaBlend(hDC,
		PlayerX - 15 + fScrollX,
		PlayerY - 100 + fScrollY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		0,
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		bf);
}

void CUI_SkillIcon_2::Release()
{
}
