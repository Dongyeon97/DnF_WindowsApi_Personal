#include "stdafx.h"
#include "Skasa.h"
#include "TimeMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

#include "AI.h"
#include "State.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "MonsterAttack.h"

CSkasa::CSkasa()
	: m_IsDead(false)
	, m_bPattern1(false)
{
}


CSkasa::~CSkasa()
{
	Release();
}

void CSkasa::Initialize()
{
	m_tInfo = { 200.f, 200.f, 512.f, 512.f };
	SetMonInfo({ 200.f, 100.f });	// 인식 범위, 공격 범위

	// 스테이터스
	m_strName = L" Lv. 105  냉룡 스카사 ";

	m_eMonType = BOSS;

	m_fSpeed = 3.f;

	m_tInfo.fMaxHp = 120'000'000;
	m_tInfo.fHp = 120'000'000;

	m_tInfo.fMaxMp = 10000;
	m_tInfo.fMp = 10000;

	m_tInfo.fAtk = 20.f;

	// 피격 Rect 크기
	m_fCollisionSizeX = 300.f;
	m_fCollisionSizeY = 300.f;

	// 타일충돌 Rect 크기
	m_fTileCollisionSizeX = 64.f;
	m_fTileCollisionSizeY = 64.f;

	m_eRender = GAMEOBJECT;
	m_eCurState = BOSS_IDLE;
	m_eMonType = BOSS;

	m_pPortrait = L"SkasaIcon";
	m_pFrameKey = L"LSkasa";

	// 표시하고 싶은 Hp줄 수
	m_iMaxDrawLineCount = 3000;
	m_iDrawLineCount = 3000;

	m_fPortraitX = 24.f;
	m_fPortraitY = 24.f;

	// 스프라이트 초기값
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 0.2;
	m_tFrame.dwTime = 0;
}

int CSkasa::Update()
{
	m_dwTime += CTimeMgr::Get_Instance()->GetfDT();
	m_tFrame.dwTime += CTimeMgr::Get_Instance()->GetfDT();

	if (m_bDead)
		return OBJ_DEAD;

	m_pAI->Update();

	if (m_tInfo.fHp <= 0 && false == m_IsDead)
	{
		m_pAI->GetCurState()->Exit();

		m_dwTime = 0;
		m_IsDead = true;
		Set_IsImmune(true);
		Set_State(BOSS_DEAD);
		m_pAI->SetCurState(BOSS_DEAD);
		m_pAI->GetCurState()->Enter();
	}

	Motion_Change();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CSkasa::Update_Rect()
{
	// 오브젝트 실제 크기 업데이트
	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));

	// 오브젝트 충돌체 업데이트
	m_tRectCollision.left = LONG(m_tInfo.fX - (m_fCollisionSizeX * 0.5f));
	m_tRectCollision.top = LONG(m_tInfo.fY - m_fCollisionSizeY * 0.5f + 64.f);
	m_tRectCollision.right = LONG(m_tInfo.fX + (m_fCollisionSizeX * 0.5f));
	m_tRectCollision.bottom = LONG(m_tInfo.fY + (m_fCollisionSizeY * 0.5f + 64.f));

	m_lRectCollisionCenter = { m_tRectCollision.left + LONG(m_fCollisionSizeX * 0.5f),
							m_tRectCollision.top + LONG(m_fCollisionSizeY * 0.5f) };

	// 플레이어 - 타일 충돌용 업데이트
	if (m_eCurState != BOSS_NORMAL_ATTACKED && m_eCurState != BOSS_THRUST_ATTACKED && m_eCurState != BOSS_LEVITATE_ATTACKED)
	{
		m_tTileCollision.left = LONG(m_tInfo.fX - (m_fTileCollisionSizeX * 0.5f));
		m_tTileCollision.top = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f) - m_fTileCollisionSizeY);
		m_tTileCollision.right = LONG(m_tInfo.fX + (m_fTileCollisionSizeX * 0.5f));
		m_tTileCollision.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));

		m_lTileCollisionCenter = { m_tTileCollision.left + LONG(m_fTileCollisionSizeX * 0.5f),
								m_tTileCollision.top + LONG(m_fTileCollisionSizeY * 0.5f) };
	}
}

void CSkasa::Late_Update()
{
	CObj::OnKnockback(m_tHitInfo, m_tTileCollision.bottom);

	if (!m_bStopMotion)
	{
		__super::Move_Frame();
	}
}

void CSkasa::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

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
		RGB(255, 255, 255));

	// 폰트
	HFONT font = CreateFont(18, 0, 0, 0, 850, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
		VARIABLE_PITCH | FF_ROMAN, L"맑은 고딕");
	HFONT oldfont = (HFONT)SelectObject(hDC, font);

	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkMode(hDC, TRANSPARENT); // 매개변수 DC의 글자배경을 투명하게 한다. 
	SetTextAlign(hDC, TA_CENTER);
	TextOut(hDC, m_tRectCollision.left + (Get_RectCollisionSizeX() * 0.5f) + fScrollX + 3, m_tRectCollision.top + fScrollY + 3,
		L"보스 - 냉룡 스카사", 12);
	SetBkMode(hDC, OPAQUE);

	SetTextColor(hDC, RGB(255, 0, 255));
	SetBkMode(hDC, TRANSPARENT); // 매개변수 DC의 글자배경을 투명하게 한다. 
	SetTextAlign(hDC, TA_CENTER);
	TextOut(hDC, m_tRectCollision.left + (Get_RectCollisionSizeX() * 0.5f) + fScrollX + 2, m_tRectCollision.top + fScrollY + 2,
		L"보스 - 냉룡 스카사", 12);
	SetBkMode(hDC, OPAQUE);

	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkMode(hDC, TRANSPARENT); // 매개변수 DC의 글자배경을 투명하게 한다. 
	SetTextAlign(hDC, TA_LEFT);

	SelectObject(hDC, oldfont);
	DeleteObject(font);
}

void CSkasa::Release()
{
	if (m_pAI)
		delete(m_pAI);
}

// 스카사 브레스패턴 제작용 함수
void CSkasa::Making_Breath(float _fX, float _fY)
{
	// 히트 박스
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_WIDEATTACK, CAbstractFactory<CMonsterAttack>::
		Create_Obj(ATT_THRUST, true, _fX, _fY, 200.f, 300.f, 0.f, 0.f, 0.f, 0.f, 0.3f, 200.f, 300.f, Get_Rect().bottom,
			Get_Info().fAtk, 10.f, 1.f, 1.f, 3.5f, 90.f, 180.f, 1.f, L"Isys6L", { 0, 0, 0 }));
	
	// 이펙트
	CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonsterAttack>::
		Create_Obj(ATT_JUSTEFFECT, true, _fX, _fY, 255.f, 305.f, 0.f, 180.f, 0.f, 0.f, 1.f, 700, 350.f, Get_Rect().bottom,
			Get_Info().fAtk, 10.f, 5.f, 1.f, 3.5f, 90.f, 180.f, 1.f, L"IceMagic", { 255, 255, 255 }));
	CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 4, 0, 0.2, 0. });
}

void CSkasa::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case BOSS_IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 50000;
			break;

		case BOSS_TRACE:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 0.2;
			break;

		case BOSS_ATTACK1:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 0.2;
			break;

			// 돌진
		case BOSS_ATTACK2:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 7;
			m_tFrame.dwSpeed = 0.8;
			break;

			// 브레스
		case BOSS_ATTACK3:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 0.5;
			break;

		case BOSS_DEAD:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 8;
			m_tFrame.dwSpeed = 5;
			break;
		}

		// 새롭게 변경된 상태를 m_ePreState에 저장한다.
		m_ePreState = m_eCurState;
	}
}