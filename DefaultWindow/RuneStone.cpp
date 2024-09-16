#include "stdafx.h"
#include "RuneStone.h"

#include "TimeMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

#include "AI.h"
#include "State.h"
#include "ObjMgr.h"
#include "PlayerAttack.h"
#include "PlayerAttack2.h"

CRuneStone::CRuneStone()
{
}


CRuneStone::~CRuneStone()
{
	Release();
}

void CRuneStone::Initialize()
{
	m_tInfo.fCX = 77.f;
	m_tInfo.fCY = 110.f;

	m_eMonType = NORMAL;

	m_fSpeed = 0.f;

	m_tInfo.fMaxHp = 10;
	m_tInfo.fHp = 10;

	m_tInfo.fMaxMp = 10000;
	m_tInfo.fMp = 10000;

	m_tInfo.fAtk = 0.f;

	// 피격 Rect 크기
	m_fCollisionSizeX = 77.f;
	m_fCollisionSizeY = 110.f;

	// 타일충돌 Rect 크기
	m_fTileCollisionSizeX = 64.f;
	m_fTileCollisionSizeY = 64.f;

	m_eRender = GAMEOBJECT;
	m_eCurState = MON_IDLE;

	m_fLifeTime = 5000.f;
}

int CRuneStone::Update()
{
	m_dwTime += CTimeMgr::Get_Instance()->GetfDT();
	m_tFrame.dwTime += CTimeMgr::Get_Instance()->GetfDT();

	LifeTimeOver();

	if (m_bDead)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
			Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX, m_tInfo.fY + 30.f, 48.f, 41.f, 0.f, 0.f, 0.f, 0.f, 0.48f, 48.f, 41.f, 0.f,
				0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, L"PlayerHit", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 6, 0, 0.07, 0. });

		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack2>::
			Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX - 50.f, m_tInfo.fY, 271.f, 261.f, 0.f, 0.f, 0.f, 0.f, 0.3f, 271.f, 261.f, 0.f,
				0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, L"PlayerHit_Daegak", { 0, 0, 0 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 2, 0, 0.1, 0. });
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_AlphaValue(180);

		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack2>::
			Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX, m_tInfo.fY, 133.f, 122.f, 0.f, 0.f, 0.f, 0.f, 0.3f, 133.f, 122.f, 0.f,
				0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, L"PlayerHit_Normal", { 0, 0, 0 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 2, 0, 0.1, 0. });
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_AlphaValue(180);
		return OBJ_DEAD;
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CRuneStone::Late_Update()
{

}

void CRuneStone::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	// 충돌 테스트용 렉트
	// HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	// HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	// Rectangle(hDC, m_tRectCollision.left + fScrollX, m_tRectCollision.top + fScrollY,
		// m_tRectCollision.right + fScrollX, m_tRectCollision.bottom + fScrollY);

	// SelectObject(hDC, oldBrush);
	// DeleteObject(myBrush);

	// Option이 1이면 렌더o, 0이면 렌더x
	if (1 == m_iOption)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + (long)fScrollX,
			m_tRect.top + (long)fScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hMemDC,
			m_iSpriteIndex * (int)m_tInfo.fCX,
			0,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(0, 255, 0));
	}
	else
	{

	}
}

void CRuneStone::Release()
{
	
}