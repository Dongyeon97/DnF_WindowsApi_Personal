#include "stdafx.h"
#include "Expeller.h"

#include "TimeMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

#include "AI.h"
#include "State.h"

CExpeller::CExpeller()
{
}


CExpeller::~CExpeller()
{
	Release();
}

void CExpeller::Initialize()
{
	m_tInfo = { 200.f, 200.f, 350.f, 350.f };
	SetMonInfo({ 200.f, 100.f });	// 인식 범위, 공격 범위

	// 스테이터스
	m_strName = L" Lv. 83  익스펠러 ";

	m_eMonType = NORMAL;

	m_fSpeed = 3.f;

	m_tInfo.fMaxHp = 50'000'000;
	m_tInfo.fHp = 50'000'000;

	m_tInfo.fMaxMp = 10000;
	m_tInfo.fMp = 10000;

	m_tInfo.fAtk = 59.f;

	// 피격 Rect 크기
	m_fCollisionSizeX = 80.f;
	m_fCollisionSizeY = 120.f;

	// 타일충돌 Rect 크기
	m_fTileCollisionSizeX = 64.f;
	m_fTileCollisionSizeY = 64.f;

	m_eRender = GAMEOBJECT;
	m_eCurState = MON_IDLE;
	m_eMonType = NORMAL;

	m_pPortrait = L"Expeller_Portrait";
	m_pFrameKey = L"Expeller_L";

	// 표시하고 싶은 Hp줄 수
	m_iMaxDrawLineCount = 362;
	m_iDrawLineCount = 362;

	m_fPortraitX = 24.f;
	m_fPortraitY = 24.f;

	// 스프라이트 초기값
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 0.2;
	m_tFrame.dwTime = 0;
}

int CExpeller::Update()
{
	m_dwTime += CTimeMgr::Get_Instance()->GetfDT();
	m_tFrame.dwTime += CTimeMgr::Get_Instance()->GetfDT();

	if (m_bDead)
		return OBJ_DEAD;

	if ((m_tInfo.fHp <= 0)
		&& m_eCurState != MON_NORMAL_ATTACKED && m_eCurState != MON_THRUST_ATTACKED && m_eCurState != MON_LEVITATE_ATTACKED)
	{
		m_pAI->GetCurState()->Exit();
		Set_IsImmune(true);
		Set_State(MON_DEAD);
		m_pAI->SetCurState(MON_DEAD);
		m_pAI->GetCurState()->Enter();
	}

	m_pAI->Update();
	Motion_Change();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CExpeller::Update_Rect()
{
	// 오브젝트 실제 크기 업데이트
	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));

	// 오브젝트 충돌체 업데이트
	m_tRectCollision.left = LONG(m_tInfo.fX - (m_fCollisionSizeX * 0.5f));
	m_tRectCollision.top = LONG(m_tInfo.fY - (m_fCollisionSizeY * 0.5f) + 34.f);
	m_tRectCollision.right = LONG(m_tInfo.fX + (m_fCollisionSizeX * 0.5f));
	m_tRectCollision.bottom = LONG(m_tInfo.fY + (m_fCollisionSizeY * 0.5f) + 34.f);

	m_lRectCollisionCenter = { m_tRectCollision.left + LONG(m_fCollisionSizeX * 0.5f),
							m_tRectCollision.top + LONG(m_fCollisionSizeY * 0.5f) };

	// 플레이어 - 타일 충돌용 업데이트
	if (m_eCurState != MON_NORMAL_ATTACKED && m_eCurState != MON_THRUST_ATTACKED && m_eCurState != MON_LEVITATE_ATTACKED)
	{
		m_tTileCollision.left = LONG(m_tInfo.fX - (m_fTileCollisionSizeX * 0.5f));
		m_tTileCollision.top = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f) - m_fTileCollisionSizeY) - 80.f;
		m_tTileCollision.right = LONG(m_tInfo.fX + (m_fTileCollisionSizeX * 0.5f));
		m_tTileCollision.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f) - 80.f);

		m_lTileCollisionCenter = { m_tTileCollision.left + LONG(m_fTileCollisionSizeX * 0.5f),
								m_tTileCollision.top + LONG(m_fTileCollisionSizeY * 0.5f) };
	}
}

void CExpeller::Late_Update()
{
	if (MON_THRUST_ATTACKED == m_eCurState || MON_NORMAL_ATTACKED == m_eCurState || MON_LEVITATE_ATTACKED == m_eCurState)
	{
		OnKnockback(m_tHitInfo, m_tTileCollision.bottom);
	}
	if (!m_bStopMotion)
	{
		__super::Move_Frame();
	}
}

void CExpeller::Render(HDC hDC)
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
}

void CExpeller::Release()
{
	if (m_pAI)
		delete(m_pAI);
}

void CExpeller::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case MON_IDLE:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iMotion = 12;
			m_tFrame.dwSpeed = 50000;
			break;
			
		case MON_APPEAR:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iMotion = 12;
			m_tFrame.dwSpeed = 0.2;
			break;

		case MON_TRACE:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 0.15;
			break;

		case MON_ATTACK1:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 0.3;
			break;

		case MON_ATTACK2:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 0.3;
			break;

		case MON_NORMAL_ATTACKED:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 0.3;
			break;

		case MON_THRUST_ATTACKED:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 0.3;
			break;

		case MON_LEVITATE_ATTACKED:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 5;
			m_tFrame.dwSpeed = 0.3;
			break;

		case MON_DEAD:

			m_tFrame.iFrameStart = 2;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 5;
			m_tFrame.dwSpeed = 5;
			break;
		}

		// 새롭게 변경된 상태를 m_ePreState에 저장한다.
		m_ePreState = m_eCurState;
	}
}