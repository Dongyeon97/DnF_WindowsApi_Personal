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

	// Ÿ���浹 Rect ũ��
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

	// �߻� ���� ��ǥ�� ( 0.f, 0.f )�� ����ü�� ���� ���Ǿ��� �׳� �߻�Ǵ� ������Ʈ��
	if (0.f == m_fEndPosX && 0.f == m_fEndPosY)
	{
		m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
		m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));
	}
	// ���� �ϳ��� ���� ��ǥ�� ������ �� ������ �����ϸ� ����
	else
	{
		// �߻�ü�� �������� + 20.f���� �����ʿ� ������ Ȥ�� -20.f���� ���ʿ� ������
		// �߻縦 �����Ѵ�
		if (m_fEndPosX + 20.f < m_tInfo.fX || m_fEndPosX - 20.f > m_tInfo.fX)
		{
			m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
		}
		// y�� ���� ����
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
	// �ð��� �帧�� ���� ������ ��ȭ
	if (m_tFrame.dwSpeed < m_tFrame.dwTime)
	{
		// if���� �ѹ� ���� ������ ������ ��ȭ�� ��
		++m_tFrame.iFrameStart;

		// ����ؼ� ��Ÿ Ÿ�� ����
		m_tFrame.dwTime = 0;

		// ��������Ʈ ���� �����ϸ� ù ��������Ʈ�� ���ư�
		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
	}
}

void CMonsterAttack2::Render(HDC hDC)
{
	float fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	// �ǰ� �浹 �׽�Ʈ�� ��Ʈ
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