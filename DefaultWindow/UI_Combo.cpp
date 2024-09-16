#include "stdafx.h"
#include "UI_Combo.h"

#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

CUI_Combo::CUI_Combo()
{
}

CUI_Combo::~CUI_Combo()
{
	Release();
}

void CUI_Combo::Initialize()
{
	m_eRender = EFFECT;

	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 27.f;

	m_dwTime = 0.f;

	m_pFrameKey = L"ComboNumber";
}

int CUI_Combo::Update()
{
	m_dwTime += CTimeMgr::Get_Instance()->GetfDT();

	// m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));

	LifeTimeOver();
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return 0;
}

void CUI_Combo::Late_Update()
{
}

void CUI_Combo::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	__super::Update_Rect();

	if (L"Combo_Bonus" == Get_FrameKey())
	{
		GdiTransparentBlt(hDC,
			m_tRect.left,
			m_tRect.top,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hMemDC,
			0,
			m_iSpriteIndex * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(0, 0, 0));
	}
	if(L"ComboNumber" == Get_FrameKey())
	{
		GdiTransparentBlt(hDC,
			m_tRect.left,
			m_tRect.top,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hMemDC,
			m_iSpriteIndex * (int)m_tInfo.fCX,
			(int)m_tInfo.fCY + (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));
	}
}

void CUI_Combo::Release()
{
}
