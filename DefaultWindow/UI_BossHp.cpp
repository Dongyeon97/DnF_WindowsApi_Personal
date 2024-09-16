#include "stdafx.h"
#include "UI_BossHp.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "UI_MonsterType.h"

CUI_BossHp::CUI_BossHp()
	: m_DrawRatio(0)
{
}

CUI_BossHp::~CUI_BossHp()
{
	Release();
}

void CUI_BossHp::Initialize()
{
	m_eRender = OVERDUI;

	m_tInfo.fCX = 600.f;
	m_tInfo.fCY = 26.f;

	m_dwTime = 0.f;

	m_iAlpha = 255;
	m_iOption = 0;

	m_fLifeTime = 7.5f;

	m_pFrameKey = L"BossHp";
}

int CUI_BossHp::Update()
{
	m_dwTime += CTimeMgr::Get_Instance()->GetfDT();
	if(1 > m_DrawRatio)
		m_DrawRatio += 0.025;

	if(7 < m_iAlpha)
		m_iAlpha -= 7;

	LifeTimeOver();
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return 0;
}

void CUI_BossHp::Late_Update()
{
}

void CUI_BossHp::Render(HDC hDC)
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

	HFONT font = CreateFont(13, 0, 0, 0, 750, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
		VARIABLE_PITCH | FF_ROMAN, L"굴림");
	HFONT oldfont = (HFONT)SelectObject(hDC, font);

	// 이시스 텍스트
	if (L" Lv.120  보스 - 프레이-이시스 " == m_strName)
	{
		SetTextColor(hDC, RGB(0, 0, 0));
		SetBkMode(hDC, TRANSPARENT); // 매개변수 DC의 글자배경을 투명하게 한다. 
		SetTextAlign(hDC, TA_LEFT);
		TextOut(hDC, m_tRect.left + 102, m_tRect.top + 8, m_strName.c_str(), m_strName.size());
		SetBkMode(hDC, OPAQUE);

		SetTextColor(hDC, RGB(255, 255, 255));
		SetBkMode(hDC, TRANSPARENT); // 매개변수 DC의 글자배경을 투명하게 한다. 
		SetTextAlign(hDC, TA_LEFT);
		TextOut(hDC, m_tRect.left + 100, m_tRect.top + 6, m_strName.c_str(), m_strName.size());
		SetTextColor(hDC, RGB(0, 0, 0));
		SetBkMode(hDC, OPAQUE);
	}
	// 이시스 몬스터타입
	if (L" Lv.120  보스 - 프레이-이시스 " == m_strName && 0 == m_iOption)
	{
		++m_iOption;

		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTERTYPE, CAbstractFactory<CUI_MonsterType>::Create_Obj(m_tRect.left + 20, m_tRect.top + 14, L"Devil_Type"));
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTERTYPE, CAbstractFactory<CUI_MonsterType>::Create_Obj(m_tRect.left + 52, m_tRect.top + 14, L"Beast_Type"));
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTERTYPE, CAbstractFactory<CUI_MonsterType>::Create_Obj(m_tRect.left + 84, m_tRect.top + 14, L"Human_Type"));
	}
	// 스카사 텍스트
	if (L" Lv. 105  냉룡 스카사 " == m_strName)
	{
		SetTextColor(hDC, RGB(0, 0, 0));
		SetBkMode(hDC, TRANSPARENT); // 매개변수 DC의 글자배경을 투명하게 한다. 
		SetTextAlign(hDC, TA_LEFT);
		TextOut(hDC, m_tRect.left + 38, m_tRect.top + 8, m_strName.c_str(), m_strName.size());
		SetBkMode(hDC, OPAQUE);

		SetTextColor(hDC, RGB(255, 255, 255));
		SetBkMode(hDC, TRANSPARENT); // 매개변수 DC의 글자배경을 투명하게 한다. 
		SetTextAlign(hDC, TA_LEFT);
		TextOut(hDC, m_tRect.left + 36, m_tRect.top + 6, m_strName.c_str(), m_strName.size());
		SetTextColor(hDC, RGB(0, 0, 0));
		SetBkMode(hDC, OPAQUE);
	}
	// 스카사
	if(L" Lv. 105  냉룡 스카사 " == m_strName && 0 == m_iOption)
	{
		++m_iOption;

		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTERTYPE, CAbstractFactory<CUI_MonsterType>::Create_Obj(m_tRect.left + 20, m_tRect.top + 14, L"Dragon_Type"));
	}

	SelectObject(hDC, oldfont);
	DeleteObject(font);
}

void CUI_BossHp::Release()
{
}
