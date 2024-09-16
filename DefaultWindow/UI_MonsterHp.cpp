#include "stdafx.h"
#include "UI_MonsterHp.h"

#include "BmpMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "UI_MonsterType.h"

CUI_MonsterHp::CUI_MonsterHp()
	: m_DrawRatio(0)
{
}

CUI_MonsterHp::~CUI_MonsterHp()
{
	Release();
}

void CUI_MonsterHp::Initialize()
{
	m_eRender = OVERDUI;

	m_tInfo.fCX = 596.f;
	m_tInfo.fCY = 9.f;

	m_dwTime = 0.f;

	m_iAlpha = 255;

	m_fLifeTime = 7.5f;

	m_pFrameKey = L"MonsterHp";
}

int CUI_MonsterHp::Update()
{
	m_dwTime += CTimeMgr::Get_Instance()->GetfDT();
	if (1 > m_DrawRatio)
		m_DrawRatio += 0.025;

	if(7 < m_iAlpha)
		m_iAlpha -= 7;

	LifeTimeOver();
	if (m_bDead)
		return OBJ_DEAD;


	__super::Update_Rect();

	return 0;
}

void CUI_MonsterHp::Late_Update()
{
}

void CUI_MonsterHp::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	__super::Update_Rect();

	// 알파 블렌딩
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = m_iAlpha;

	if (4 == m_iSpriteIndex)
	{
		// 칸이 비면 안되기때문에 한줄 뒤의 색상을 표시해줌
		GdiTransparentBlt(hDC,
			m_tRect.left,
			m_tRect.top,
			int(m_tInfo.fCX),
			(int)m_tInfo.fCY,
			hMemDC,
			0,
			0,
			int(m_tInfo.fCX),
			(int)m_tInfo.fCY,
			RGB(255, 255, 255));
	}
	else
	{
		GdiTransparentBlt(hDC,
			m_tRect.left,
			m_tRect.top,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hMemDC,
			0,
			(m_iSpriteIndex + 1) * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 255, 255));
	}

	// 표시되는 가장 마지막줄
	GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		int(m_tInfo.fCX * m_fDrawRatio),
		(int)m_tInfo.fCY,
		hMemDC,
		0,
		m_iSpriteIndex * (int)m_tInfo.fCY,
		int(m_tInfo.fCX * m_fDrawRatio),
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));

	// 표시되는 가장 마지막줄 깎이는거 천천히하게
	GdiAlphaBlend(hDC,
		m_tRect.left + int(m_tInfo.fCX * m_fDrawRatio),
		m_tRect.top,
		(int(m_tInfo.fCX) - int(m_tInfo.fCX * m_fDrawRatio)) * (1 - m_DrawRatio),
		(int)m_tInfo.fCY,
		hMemDC,
		int(m_tInfo.fCX * m_fDrawRatio),
		m_iSpriteIndex * (int)m_tInfo.fCY,
		(int(m_tInfo.fCX) - int(m_tInfo.fCX * m_fDrawRatio)) * (1 - m_DrawRatio),
		(int)m_tInfo.fCY,
		bf);




	HFONT font = CreateFont(12, 0, 0, 0, 850, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
		VARIABLE_PITCH | FF_ROMAN, L"굴림");
	HFONT oldfont = (HFONT)SelectObject(hDC, font);

	// 익스펠러 텍스트
	if (L" Lv. 83  익스펠러 " == m_strName)
	{
		SetTextColor(hDC, RGB(255, 255, 255));
		SetBkMode(hDC, TRANSPARENT); // 매개변수 DC의 글자배경을 투명하게 한다. 
		SetTextAlign(hDC, TA_LEFT);
		TextOut(hDC, m_tRect.left + 2, m_tRect.top - 20, m_strName.c_str(), m_strName.size());
		SetTextColor(hDC, RGB(0, 0, 0));
		SetBkMode(hDC, OPAQUE);
	}
	// 익스펠러 몬스터 타입
	if (L" Lv. 83  익스펠러 " == m_strName && 0 == m_iOption)
	{
		++m_iOption;

		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTERTYPE, CAbstractFactory<CUI_MonsterType>::Create_Obj(m_tRect.left + 20, m_tRect.top + 5, L"Human_Type"));
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTERTYPE, CAbstractFactory<CUI_MonsterType>::Create_Obj(m_tRect.left + 52, m_tRect.top + 5, L"Complex_Type"));
	}
	// 누더기 텍스트
	if (L" Lv. 75  누더기 " == m_strName)
	{
		SetTextColor(hDC, RGB(255, 255, 255));
		SetBkMode(hDC, TRANSPARENT); // 매개변수 DC의 글자배경을 투명하게 한다. 
		SetTextAlign(hDC, TA_LEFT);
		TextOut(hDC, m_tRect.left + 2, m_tRect.top - 20, m_strName.c_str(), m_strName.size());
		SetTextColor(hDC, RGB(0, 0, 0));
		SetBkMode(hDC, OPAQUE);
	}
	// 누더기 몬스터 타입
	if (L" Lv. 75  누더기 " == m_strName && 0 == m_iOption)
	{
		++m_iOption;
		
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTERTYPE, CAbstractFactory<CUI_MonsterType>::Create_Obj(m_tRect.left + 20, m_tRect.top + 5, L"Undead_Type"));
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTERTYPE, CAbstractFactory<CUI_MonsterType>::Create_Obj(m_tRect.left + 52, m_tRect.top + 5, L"Complex_Type"));
	}
	// 장난감 병정 텍스트
	if (L" Lv. 75  난폭한 장난감 병정 " == m_strName)
	{
		SetTextColor(hDC, RGB(255, 255, 255));
		SetBkMode(hDC, TRANSPARENT); // 매개변수 DC의 글자배경을 투명하게 한다. 
		SetTextAlign(hDC, TA_LEFT);
		TextOut(hDC, m_tRect.left + 2, m_tRect.top - 20, m_strName.c_str(), m_strName.size());
		SetTextColor(hDC, RGB(0, 0, 0));
		SetBkMode(hDC, OPAQUE);
	}
	if (L" Lv. 75  난폭한 장난감 병정 " == m_strName && 0 == m_iOption)
	{
		++m_iOption;

		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTERTYPE, CAbstractFactory<CUI_MonsterType>::Create_Obj(m_tRect.left + 20, m_tRect.top + 5, L"Complex_Type"));
	}

	SelectObject(hDC, oldfont);
	DeleteObject(font);
}

void CUI_MonsterHp::Release()
{
}
