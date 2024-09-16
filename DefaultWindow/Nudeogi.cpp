#include "stdafx.h"
#include "Nudeogi.h"

#include "TimeMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

#include "AI.h"
#include "State.h"

CNudeogi::CNudeogi()
{
}


CNudeogi::~CNudeogi()
{
	Release();
}

void CNudeogi::Initialize()
{
	m_tInfo = { 200.f, 200.f, 500.f, 500.f };
	SetMonInfo({ 200.f, 100.f });	// �ν� ����, ���� ����

	// �������ͽ�
	m_strName = L" Lv. 75  ������ ";

	m_eMonType = NORMAL;

	m_fSpeed = 2.f;

	m_tInfo.fMaxHp = 20'000'000;
	m_tInfo.fHp = 20'000'000;

	m_tInfo.fMaxMp = 10000;
	m_tInfo.fMp = 10000;

	m_tInfo.fAtk = 30.f;

	// �ǰ� Rect ũ��
	m_fCollisionSizeX = 200.f;
	m_fCollisionSizeY = 240.f;

	// Ÿ���浹 Rect ũ��
	m_fTileCollisionSizeX = 64.f;
	m_fTileCollisionSizeY = 64.f;

	m_eRender = GAMEOBJECT;
	m_eCurState = MON_IDLE;
	m_eMonType = NORMAL;

	m_pPortrait = L"Nudeogi_Portrait";
	m_pFrameKey = L"LNudeogi";

	// ǥ���ϰ� ���� Hp�� ��
	m_iMaxDrawLineCount = 5000;
	m_iDrawLineCount = 5000;

	m_fPortraitX = 24.f;
	m_fPortraitY = 24.f;

	// ��������Ʈ �ʱⰪ
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 6;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 0.2;
	m_tFrame.dwTime = 0;
}

int CNudeogi::Update()
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

void CNudeogi::Update_Rect()
{
	// ������Ʈ ���� ũ�� ������Ʈ
	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));

	// ������Ʈ �浹ü ������Ʈ
	m_tRectCollision.left = LONG(m_tInfo.fX - (m_fCollisionSizeX * 0.5f));
	m_tRectCollision.top = LONG(m_tInfo.fY - (m_fCollisionSizeY * 0.5f));
	m_tRectCollision.right = LONG(m_tInfo.fX + (m_fCollisionSizeX * 0.5f));
	m_tRectCollision.bottom = LONG(m_tInfo.fY + (m_fCollisionSizeY * 0.5f));

	m_lRectCollisionCenter = { m_tRectCollision.left + LONG(m_fCollisionSizeX * 0.5f),
							m_tRectCollision.top + LONG(m_fCollisionSizeY * 0.5f) };

	// �÷��̾� - Ÿ�� �浹�� ������Ʈ
	if (m_eCurState != MON_NORMAL_ATTACKED && m_eCurState != MON_THRUST_ATTACKED && m_eCurState != MON_LEVITATE_ATTACKED)
	{
		m_tTileCollision.left = LONG(m_tInfo.fX - (m_fTileCollisionSizeX * 0.5f));
		m_tTileCollision.top = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f) - m_fTileCollisionSizeY - 130.f);
		m_tTileCollision.right = LONG(m_tInfo.fX + (m_fTileCollisionSizeX * 0.5f));
		m_tTileCollision.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f) - 130.f);

		m_lTileCollisionCenter = { m_tTileCollision.left + LONG(m_fTileCollisionSizeX * 0.5f),
								m_tTileCollision.top + LONG(m_fTileCollisionSizeY * 0.5f) };
	}
}

void CNudeogi::Late_Update()
{
	if (MON_THRUST_ATTACKED == m_eCurState || MON_NORMAL_ATTACKED == m_eCurState || MON_LEVITATE_ATTACKED == m_eCurState)
	{
		OnKnockback(m_tHitInfo, m_tTileCollision.bottom);
	}
	if (!m_bStopMotion)
		__super::Move_Frame();
}

void CNudeogi::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	// �浹 �׽�Ʈ�� ��Ʈ
	/*HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Rectangle(hDC, m_tRectCollision.left + fScrollX, m_tRectCollision.top + fScrollY,
		m_tRectCollision.right + fScrollX, m_tRectCollision.bottom + fScrollY);

	Rectangle(hDC, m_tRect.left + fScrollX, m_tRect.top + fScrollY,
		m_tRect.right + fScrollX, m_tRect.bottom + fScrollY);

	Rectangle(hDC, m_tTileCollision.left + fScrollX, m_tTileCollision.top + fScrollY,
		m_tTileCollision.right + fScrollX, m_tTileCollision.bottom + fScrollY);

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);*/
	// �浹 �׽�Ʈ�� ��Ʈ

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

void CNudeogi::Release()
{
	if (m_pAI)
		delete(m_pAI);
}

void CNudeogi::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case MON_IDLE:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 50000;
			break;

		case MON_TRACE:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 0.2;
			break;

		case MON_ATTACK1:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 0.2;
			break;

		case MON_ATTACK2:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 0.2;
			break;

		case MON_NORMAL_ATTACKED:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 4;
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
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 5;
			m_tFrame.dwSpeed = 0.2;
			break;

		case MON_DEAD:

			m_tFrame.iFrameStart = 4;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 5;
			m_tFrame.dwSpeed = 5;
			break;
		}

		// ���Ӱ� ����� ���¸� m_ePreState�� �����Ѵ�.
		m_ePreState = m_eCurState;
	}
}