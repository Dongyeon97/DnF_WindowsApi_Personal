#include "stdafx.h"
#include "Isys.h"

#include "TimeMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

#include "AI.h"
#include "State.h"

CIsys::CIsys()
	: m_IsDead(false)
	, m_bPattern1(false)
	, m_bPattern2(false)
	, m_bPattern3(false)
	, m_bPattern4(false)
{
}


CIsys::~CIsys()
{
	Release();
}

void CIsys::Initialize()
{
	

	m_tInfo = { 200.f, 200.f, 371.f, 373.f };
	SetMonInfo({ 200.f, 100.f });	// 인식 범위, 공격 범위

	// 스테이터스
	m_strName = L" Lv.120  보스 - 프레이-이시스 ";

	m_eMonType = BOSS;

	m_fSpeed = 3.f;

	m_tInfo.fMaxHp = 300'000'000;
	m_tInfo.fHp = 300'000'000;

	m_tInfo.fMaxMp = 10000;
	m_tInfo.fMp = 10000;

	m_tInfo.fAtk = 30.f;

	// 피격 Rect 크기
	m_fCollisionSizeX = 120.f;
	m_fCollisionSizeY = 250.f;

	// 타일충돌 Rect 크기
	m_fTileCollisionSizeX = 64.f;
	m_fTileCollisionSizeY = 64.f;

	m_eRender = GAMEOBJECT;
	m_eCurState = BOSS_IDLE;
	m_eMonType = BOSS;

	m_pPortrait = L"Isys_Portrait";
	m_pFrameKey = L"Isys_FlyingReady2";

	// 표시하고 싶은 Hp줄 수
	m_iMaxDrawLineCount = 6398;
	m_iDrawLineCount = 6398;

	m_fPortraitX = 25.f;
	m_fPortraitY = 25.f;

	// 스프라이트 초기값
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 0.2;
	m_tFrame.dwTime = 0;
}

int CIsys::Update()
{
	m_dwTime += CTimeMgr::Get_Instance()->GetfDT();
	m_tFrame.dwTime += CTimeMgr::Get_Instance()->GetfDT();

	if (m_bDead)
		return OBJ_DEAD;

	m_pAI->Update();

	//// 체력 90퍼 패턴3 임시
	//if (m_tInfo.fHp < (m_tInfo.fMaxHp * 0.9f) && false == Get_Pattern3())
	//{
	//	m_pAI->GetCurState()->Exit();

	//	// 이시스가 패턴을 사용함을 bool변수로 체크(다음번에 또 사용 안하게)
	//	Set_Pattern3(true);
	//	Set_State(BOSS_PATTERN3);
	//	m_pAI->SetCurState(BOSS_PATTERN3);
	//	m_pAI->GetCurState()->Enter();
	//}

	// 체력이 0 이하로 내려갔을시 사망
	if (m_tInfo.fHp <= 0 && false ==  m_IsDead)
	{
		m_pAI->GetCurState()->Exit();

		m_IsDead = true;
		Set_IsImmune(true);
		Set_State(BOSS_DEAD);
		m_pAI->SetCurState(BOSS_DEAD);
		m_pAI->GetCurState()->Enter();
	}

	// 체력이 80퍼 이하로 떨어졌을때 1차 광폭화 발동
	if (m_tInfo.fHp < (m_tInfo.fMaxHp * 0.8f) && false == Get_Pattern1())
	{
		m_pAI->GetCurState()->Exit();

		// 이시스가 패턴을 사용함을 bool변수로 체크(다음번에 또 사용 안하게)
		Set_Pattern1(true);
		Set_State(BOSS_PREPATTERN);
		m_pAI->SetCurState(BOSS_PREPATTERN);
		m_pAI->GetCurState()->Enter();
	}

	// 체력이 60퍼 이하로 떨어졌을때 2차 광폭화 발동
	if (m_tInfo.fHp < (m_tInfo.fMaxHp * 0.6f) && true == Get_Pattern1() && false == Get_Pattern2())
	{
		m_pAI->GetCurState()->Exit();

		// 이시스가 패턴을 사용함을 bool변수로 체크(다음번에 또 사용 안하게)
		Set_Pattern2(true);
		Set_State(BOSS_PATTERN2);
		m_pAI->SetCurState(BOSS_PATTERN2);
		m_pAI->GetCurState()->Enter();
	}

	// 체력이 40퍼 이하로 떨어졌을때 3차 광폭화 발동
	if (m_tInfo.fHp < (m_tInfo.fMaxHp * 0.4f) && true == Get_Pattern1() && true == Get_Pattern2() && false == Get_Pattern3())
	{
		m_pAI->GetCurState()->Exit();

		// 이시스가 패턴을 사용함을 bool변수로 체크(다음번에 또 사용 안하게)
		Set_Pattern3(true);
		Set_State(BOSS_PATTERN3);
		m_pAI->SetCurState(BOSS_PATTERN3);
		m_pAI->GetCurState()->Enter();
	}

	Motion_Change();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CIsys::Update_Rect()
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

void CIsys::Late_Update()
{
	/*if (BOSS_THRUST_ATTACKED == m_eCurState || BOSS_NORMAL_ATTACKED == m_eCurState || BOSS_LEVITATE_ATTACKED == m_eCurState)
	{
		CObj::OnKnockback(m_tHitInfo, m_tTileCollision.bottom);
	}*/

	CObj::OnKnockback(m_tHitInfo, m_tTileCollision.bottom);

	if (!m_bStopMotion)
	{
		__super::Move_Frame();
	}
}

void CIsys::Render(HDC hDC)
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
		L"보스 - 프레이 이시스", 13);
	SetBkMode(hDC, OPAQUE);

	SetTextColor(hDC, RGB(255, 0, 255));
	SetBkMode(hDC, TRANSPARENT); // 매개변수 DC의 글자배경을 투명하게 한다. 
	SetTextAlign(hDC, TA_CENTER);
	TextOut(hDC, m_tRectCollision.left + (Get_RectCollisionSizeX() * 0.5f) + fScrollX + 2, m_tRectCollision.top + fScrollY + 2,
		L"보스 - 프레이 이시스", 13);
	SetBkMode(hDC, OPAQUE);

	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkMode(hDC, TRANSPARENT); // 매개변수 DC의 글자배경을 투명하게 한다. 
	SetTextAlign(hDC, TA_LEFT);

	SelectObject(hDC, oldfont);
	DeleteObject(oldfont);
}

void CIsys::Release()
{
	if (m_pAI)
		delete(m_pAI);
}

void CIsys::OnKnockback(HIT_INFO _tHitInfo, float _fBottomPosY)
{
	if (m_bImmune)
		return;

	if (m_dwTime < _tHitInfo.fKnockbackTime)
	{
		Draw_HitEffect();

		// 피격 데미지 계산 공식
		float fTotal_Damage = (_tHitInfo.fAttPoint * _tHitInfo.fAttRatio) + float(rand() % 15000);
		Take_Damage(fTotal_Damage);
		
		// 이시스는 넉백 안당함
	}
}

void CIsys::Motion_Change()
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

		case BOSS_APPEAR:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 0.7;
			break;

		case BOSS_PREPATTERN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 0.3;
			break;

		case BOSS_TRACE:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 0.2;
			break;

		case BOSS_ATTACK1:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 0.15;
			break;

		case BOSS_ATTACK2:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 10;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 0.12;
			break;

		case BOSS_ATTACK3:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 0.20;
			break;

		case BOSS_ATTACK4:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 0.15;
			break;

		case BOSS_BACKSTEP:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 0.35;
			break;

		case BOSS_NORMAL_ATTACKED:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 0.2;
			break;

		case BOSS_THRUST_ATTACKED:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 0.2;
			break;

		case BOSS_LEVITATE_ATTACKED:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 0.2;
			break;

			// 2차 광폭화 시작 모션
		case BOSS_FLYINGREADY:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 0.15;
			break;

		case BOSS_FLYING:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 12;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 0.1;
			break;

		case BOSS_ONEHANDUP:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 16;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 0.1;
			break;

		case BOSS_TWOHANDUP:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 0.15;
			break;

		case BOSS_GROGY:

			m_tFrame.iFrameStart = 3;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 10;
			break;

		case BOSS_DEAD:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 1.25;
			break;
		}

		// 새롭게 변경된 상태를 m_ePreState에 저장한다.
		m_ePreState = m_eCurState;
	}
}