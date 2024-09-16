#include "stdafx.h"
#include "MonsterAttack2.h"

#include "TimeMgr.h"
#include "ScrollMgr.h"
#include "CollsionMgr.h"
#include "BmpMgr.h"

CMonsterAttack2::CMonsterAttack2()
{
}

CMonsterAttack2::~CMonsterAttack2()
{
	Release();
}

void CMonsterAttack2::Initialize()
{
	m_eRender = GAMEOBJECT;

	// 타일충돌 Rect 크기
	m_fTileCollisionSizeX = 64.f;
	m_fTileCollisionSizeY = 64.f;
}

int CMonsterAttack2::Update()
{
	m_dwTime += CTimeMgr::Get_Instance()->GetfDT();
	m_tFrame.dwTime += CTimeMgr::Get_Instance()->GetfDT();

	LifeTimeOver();
	if (m_bDead)
		return OBJ_DEAD;

	// 발사 종료 좌표가 ( 0.f, 0.f )인 투사체는 종료 조건없이 그냥 발사되는 오브젝트임
	if (0.f == m_fEndPosX && 0.f == m_fEndPosY)
	{
		m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
		m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));
	}
	// 둘중 하나라도 종료 좌표가 있으면 그 지점에 도달하면 정지
	else
	{
		// 발사체가 종료지점 + 20.f보다 오른쪽에 있을때 혹은 -20.f보다 왼쪽에 있으면
		// 발사를 지속한다
		if (m_fEndPosX + 20.f < m_tInfo.fX || m_fEndPosX - 20.f > m_tInfo.fX)
		{
			m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
		}
		// y도 같은 조건
		if (m_fEndPosY + 20.f < m_tInfo.fY || m_fEndPosY - 20.f > m_tInfo.fY)
		{
			m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));
		}
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMonsterAttack2::Late_Update()
{
	Move_Frame();
}

void CMonsterAttack2::Move_Frame()
{
	// 시간에 흐름에 따라 프레임 변화
	if (m_tFrame.dwSpeed < m_tFrame.dwTime)
	{
		// if문에 한번 들어올 때마다 프레임 변화를 줌
		++m_tFrame.iFrameStart;

		// 계속해서 델타 타임 갱신
		m_tFrame.dwTime = 0;

		// 스프라이트 끝에 도달하면 첫 스프라이트로 돌아감
		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
	}
}

void CMonsterAttack2::Render(HDC hDC)
{
	float fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	// 피격 충돌 테스트용 렉트
	/*HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Rectangle(hDC, m_tRectCollision.left + (int)fScrollX, m_tRectCollision.top + (int)fScrollY,
		m_tRectCollision.right + (int)fScrollX, m_tRectCollision.bottom + (int)fScrollY);

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);*/

	GdiTransparentBlt(hDC,
		m_tRect.left + (long)fScrollX,
		m_tRect.top + (long)fScrollY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		0,
		(m_tFrame.iFrameStart) * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(m_tRGB.R, m_tRGB.G, m_tRGB.B));
}

void CMonsterAttack2::Release()
{
}