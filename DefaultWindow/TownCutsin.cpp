#include "stdafx.h"
#include "TownCutsin.h"

#include "TimeMgr.h"
#include "ScrollMgr.h"
#include "CollsionMgr.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "MonsterAttack2.h"
#include "SoundMgr.h"

CTownCutsin::CTownCutsin()
{
}

CTownCutsin::~CTownCutsin()
{
	Release();
}

void CTownCutsin::Initialize()
{
	m_eRender = EFFECT;

	// 타일충돌 Rect 크기
	m_fTileCollisionSizeX = 64.f;
	m_fTileCollisionSizeY = 64.f;
}

int CTownCutsin::Update()
{
	m_dwTime += CTimeMgr::Get_Instance()->GetfDT();
	m_tFrame.dwTime += CTimeMgr::Get_Instance()->GetfDT();
	m_iAlpha -= 2.5;

	LifeTimeOver();

	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CTownCutsin::Late_Update()
{
	__super::Move_Frame();
}

void CTownCutsin::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	// 알파 블렌딩
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = m_iAlpha;

	if (L"Isys_Wind" == Get_FrameKey())
	{
		GdiAlphaBlend(hDC,
			m_tRect.left,
			m_tRect.top,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hMemDC,
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			bf);
	}
	else
	{
		GdiAlphaBlend(hDC,
			m_tRect.left,
			m_tRect.top,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hMemDC,
			0,
			m_tFrame.iFrameStart * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			bf);
	}
}

void CTownCutsin::Release()
{
}