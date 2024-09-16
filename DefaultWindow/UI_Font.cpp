#include "stdafx.h"
#include "UI_Font.h"

#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

CUI_Font::CUI_Font()
{
}

CUI_Font::~CUI_Font()
{
	Release();
}

void CUI_Font::Initialize()
{
	m_eRender = EFFECT;

	m_tInfo.fCX = 18.f;
	m_tInfo.fCY = 16.f;

	m_dwTime = 0.f;

	m_pFrameKey = L"DamageFont1";
}

int CUI_Font::Update()
{
	m_dwTime += CTimeMgr::Get_Instance()->GetfDT();

	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));

	LifeTimeOver();
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return 0;
}

void CUI_Font::Late_Update()
{
}

void CUI_Font::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	__super::Update_Rect();

	GdiTransparentBlt(hDC,			// 복사 받을(최종적으로 그림을 그릴) DC를 전달
		m_tRect.left + (long)fScrollX, // 복사 받을 위치의 좌표를 전달 (x,y 좌표)
		m_tRect.top + (long)fScrollY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,				// 비트맵을 가지고 있는 DC 전달
		m_iSpriteIndex * (int)m_tInfo.fCX,					// 비트맵을 출력할 시작 X,Y 좌표
		0,
		(int)m_tInfo.fCX,	// 복사할 비트맵의 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));
	
}

void CUI_Font::Release()
{
}
