#include "stdafx.h"
#include "Satelite.h"

#include "TimeMgr.h"
#include "ScrollMgr.h"
#include "CollsionMgr.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
#include "PlayerAttack.h"

CSatelite::CSatelite()
	: m_HitTerm(0)
{
}

CSatelite::~CSatelite()
{
	Release();
}

void CSatelite::Initialize()
{
	m_eRender = GAMEOBJECT;

	m_fSpeed = 5.f;

	// 타일충돌 Rect 크기
	m_fTileCollisionSizeX = 64.f;
	m_fTileCollisionSizeY = 64.f;
}

int CSatelite::Update()
{
	m_dwTime += CTimeMgr::Get_Instance()->GetfDT();
	m_tFrame.dwTime += CTimeMgr::Get_Instance()->GetfDT();
	m_HitTerm += CTimeMgr::Get_Instance()->GetfDT();

	if (0.2 < m_HitTerm)
	{
		m_HitTerm = 0;
		Making_Hitbox();
	}

	LifeTimeOver();

	if (m_bDead)
		return OBJ_DEAD;

	CObj* m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_MONSTER, this);

	if (m_pTarget)
	{
		float	fWidth = 0.f, fHeight = 0.f, fDiagonal = 0.f, fRadian = 0.f;

		fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
		fHeight = m_pTarget->Get_RectCollision().bottom - m_tRectCollision.bottom;

		fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		fRadian = acosf(fWidth / fDiagonal);

		if (m_pTarget->Get_TileCollision().bottom + 5.f > m_tRect.bottom)
			fRadian = (2 * PI) - fRadian;

		m_fAngle = fRadian * 180.f / PI;

		if (10.f < fDiagonal)
		{
			m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
			m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));
		}
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CSatelite::Late_Update()
{
	__super::Move_Frame();
}

void CSatelite::Render(HDC hDC)
{
	float fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 150;

	// Rectangle(hDC, m_tRectCollision.left + fScrollX, m_tRectCollision.top + fScrollY,
		// m_tRectCollision.right + fScrollX, m_tRectCollision.bottom + fScrollY);

	GdiAlphaBlend(hDC,
		m_tRect.left + (long)fScrollX,
		m_tRect.top + (long)fScrollY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		bf);
}

void CSatelite::Release()
{

}

void CSatelite::Making_Hitbox()
{
	float fX = Get_Info().fX;
	float fY = Get_Rect().bottom;

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_WIDEATTACK, CAbstractFactory<CPlayerAttack>::
		Create_Obj(ATT_LEVITATE, false, fX + 30.f, fY - 100.f, 200.f, 100.f, 0.f, 0.f, 0.f, 0.f, 0.2f, 200.f, 100.f, float(Get_TileCollision().bottom),
			CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).back()->Get_Info().fAtk, 500.f, 2.f, 2.f, 4.f, 90.f, 0.f, 0.1f, L"Satelite_Hitbox", {0, 0, 0}));
}