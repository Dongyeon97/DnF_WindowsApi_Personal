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
	SetMonInfo({ 200.f, 100.f });	// �ν� ����, ���� ����

	// �������ͽ�
	m_strName = L" Lv.120  ���� - ������-�̽ý� ";

	m_eMonType = BOSS;

	m_fSpeed = 3.f;

	m_tInfo.fMaxHp = 300'000'000;
	m_tInfo.fHp = 300'000'000;

	m_tInfo.fMaxMp = 10000;
	m_tInfo.fMp = 10000;

	m_tInfo.fAtk = 30.f;

	// �ǰ� Rect ũ��
	m_fCollisionSizeX = 120.f;
	m_fCollisionSizeY = 250.f;

	// Ÿ���浹 Rect ũ��
	m_fTileCollisionSizeX = 64.f;
	m_fTileCollisionSizeY = 64.f;

	m_eRender = GAMEOBJECT;
	m_eCurState = BOSS_IDLE;
	m_eMonType = BOSS;

	m_pPortrait = L"Isys_Portrait";
	m_pFrameKey = L"Isys_FlyingReady2";

	// ǥ���ϰ� ���� Hp�� ��
	m_iMaxDrawLineCount = 6398;
	m_iDrawLineCount = 6398;

	m_fPortraitX = 25.f;
	m_fPortraitY = 25.f;

	// ��������Ʈ �ʱⰪ
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

	//// ü�� 90�� ����3 �ӽ�
	//if (m_tInfo.fHp < (m_tInfo.fMaxHp * 0.9f) && false == Get_Pattern3())
	//{
	//	m_pAI->GetCurState()->Exit();

	//	// �̽ý��� ������ ������� bool������ üũ(�������� �� ��� ���ϰ�)
	//	Set_Pattern3(true);
	//	Set_State(BOSS_PATTERN3);
	//	m_pAI->SetCurState(BOSS_PATTERN3);
	//	m_pAI->GetCurState()->Enter();
	//}

	// ü���� 0 ���Ϸ� ���������� ���
	if (m_tInfo.fHp <= 0 && false ==  m_IsDead)
	{
		m_pAI->GetCurState()->Exit();

		m_IsDead = true;
		Set_IsImmune(true);
		Set_State(BOSS_DEAD);
		m_pAI->SetCurState(BOSS_DEAD);
		m_pAI->GetCurState()->Enter();
	}

	// ü���� 80�� ���Ϸ� ���������� 1�� ����ȭ �ߵ�
	if (m_tInfo.fHp < (m_tInfo.fMaxHp * 0.8f) && false == Get_Pattern1())
	{
		m_pAI->GetCurState()->Exit();

		// �̽ý��� ������ ������� bool������ üũ(�������� �� ��� ���ϰ�)
		Set_Pattern1(true);
		Set_State(BOSS_PREPATTERN);
		m_pAI->SetCurState(BOSS_PREPATTERN);
		m_pAI->GetCurState()->Enter();
	}

	// ü���� 60�� ���Ϸ� ���������� 2�� ����ȭ �ߵ�
	if (m_tInfo.fHp < (m_tInfo.fMaxHp * 0.6f) && true == Get_Pattern1() && false == Get_Pattern2())
	{
		m_pAI->GetCurState()->Exit();

		// �̽ý��� ������ ������� bool������ üũ(�������� �� ��� ���ϰ�)
		Set_Pattern2(true);
		Set_State(BOSS_PATTERN2);
		m_pAI->SetCurState(BOSS_PATTERN2);
		m_pAI->GetCurState()->Enter();
	}

	// ü���� 40�� ���Ϸ� ���������� 3�� ����ȭ �ߵ�
	if (m_tInfo.fHp < (m_tInfo.fMaxHp * 0.4f) && true == Get_Pattern1() && true == Get_Pattern2() && false == Get_Pattern3())
	{
		m_pAI->GetCurState()->Exit();

		// �̽ý��� ������ ������� bool������ üũ(�������� �� ��� ���ϰ�)
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
	// ������Ʈ ���� ũ�� ������Ʈ
	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));

	// ������Ʈ �浹ü ������Ʈ
	m_tRectCollision.left = LONG(m_tInfo.fX - (m_fCollisionSizeX * 0.5f));
	m_tRectCollision.top = LONG(m_tInfo.fY - m_fCollisionSizeY * 0.5f + 64.f);
	m_tRectCollision.right = LONG(m_tInfo.fX + (m_fCollisionSizeX * 0.5f));
	m_tRectCollision.bottom = LONG(m_tInfo.fY + (m_fCollisionSizeY * 0.5f + 64.f));

	m_lRectCollisionCenter = { m_tRectCollision.left + LONG(m_fCollisionSizeX * 0.5f),
							m_tRectCollision.top + LONG(m_fCollisionSizeY * 0.5f) };

	// �÷��̾� - Ÿ�� �浹�� ������Ʈ
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

	// ��Ʈ
	HFONT font = CreateFont(18, 0, 0, 0, 850, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
		VARIABLE_PITCH | FF_ROMAN, L"���� ���");
	HFONT oldfont = (HFONT)SelectObject(hDC, font);

	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkMode(hDC, TRANSPARENT); // �Ű����� DC�� ���ڹ���� �����ϰ� �Ѵ�. 
	SetTextAlign(hDC, TA_CENTER);
	TextOut(hDC, m_tRectCollision.left + (Get_RectCollisionSizeX() * 0.5f) + fScrollX + 3, m_tRectCollision.top + fScrollY + 3,
		L"���� - ������ �̽ý�", 13);
	SetBkMode(hDC, OPAQUE);

	SetTextColor(hDC, RGB(255, 0, 255));
	SetBkMode(hDC, TRANSPARENT); // �Ű����� DC�� ���ڹ���� �����ϰ� �Ѵ�. 
	SetTextAlign(hDC, TA_CENTER);
	TextOut(hDC, m_tRectCollision.left + (Get_RectCollisionSizeX() * 0.5f) + fScrollX + 2, m_tRectCollision.top + fScrollY + 2,
		L"���� - ������ �̽ý�", 13);
	SetBkMode(hDC, OPAQUE);

	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkMode(hDC, TRANSPARENT); // �Ű����� DC�� ���ڹ���� �����ϰ� �Ѵ�. 
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

		// �ǰ� ������ ��� ����
		float fTotal_Damage = (_tHitInfo.fAttPoint * _tHitInfo.fAttRatio) + float(rand() % 15000);
		Take_Damage(fTotal_Damage);
		
		// �̽ý��� �˹� �ȴ���
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

			// 2�� ����ȭ ���� ���
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

		// ���Ӱ� ����� ���¸� m_ePreState�� �����Ѵ�.
		m_ePreState = m_eCurState;
	}
}