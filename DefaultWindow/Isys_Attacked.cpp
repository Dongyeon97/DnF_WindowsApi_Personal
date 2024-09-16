#include "stdafx.h"
#include "Isys_Attacked.h"

#include "ObjMgr.h"
#include "TimeMgr.h"

#include "Player.h"
#include "Monster.h"
#include "AI.h"
#include "Effect.h"

CIsys_Attacked::CIsys_Attacked()
	: CState(BOSS_NORMAL_ATTACKED)
	, m_dwTime(0)
{
}

CIsys_Attacked::~CIsys_Attacked()
{
}

void CIsys_Attacked::Update()
{
	CMonster* pMonster = GetMonster();
	CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front();

	// Player의 위치 체크
	float fPlayerX = pPlayer->Get_Info().fX;
	float fPlayerY = pPlayer->Get_Info().fY;

	// 몬스터 자신의 위치 체크
	float fMonsterX = pMonster->Get_Info().fX;
	float fMonsterY = pMonster->Get_Info().fY;

	// 플레이어 x좌표 체크해서 좌우 이미지 반전
	if (fPlayerX < fMonsterX)
		pMonster->Set_FrameKey(L"Isys_LAttacked");
	else
		pMonster->Set_FrameKey(L"Isys_RAttacked");

	if (pMonster->m_tHitInfo.fKnockbackTime < pMonster->Get_dwTime())
	{
		Exit();
		pMonster->Set_State(MON_STATE::BOSS_TRACE);
		m_pAI->SetCurState(MON_STATE::BOSS_TRACE);
		m_pAI->GetCurState()->Enter();
	}
}

void CIsys_Attacked::LateUpdate()
{
}

void CIsys_Attacked::Enter()
{
	CMonster* pMonster = GetMonster();
	pMonster->Set_dwTime(0);

	// Player의 위치 체크
	CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front();
	float fPlayerX = pPlayer->Get_Info().fX;
	float fPlayerY = pPlayer->Get_Info().fY;

	// 몬스터 자신의 위치 체크
	float fMonsterX = pMonster->Get_Info().fX;
	float fMonsterY = pMonster->Get_Info().fY;

	// 플레이어 x좌표 체크해서 좌 우 피격이미지 출력
	if (fPlayerX < fMonsterX)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CEffect>::
			Create_Obj(ATT_JUSTEFFECT, false, pMonster->Get_Info().fX, pMonster->Get_Info().fY, 62.f, 73.f, 0.f, 0.f, 0.f, 0.f, 0.48f, 62.f, 73.f, float(pMonster->Get_TileCollision().bottom),
				0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, L"LHitEffect", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 6, 0, 0.07, 0. });
	}
	else
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CEffect>::
			Create_Obj(ATT_JUSTEFFECT, false, pMonster->Get_Info().fX, pMonster->Get_Info().fY, 62.f, 73.f, 0.f, 0.f, 0.f, 0.f, 0.48f, 62.f, 73.f, float(pMonster->Get_TileCollision().bottom),
				0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, L"RHitEffect", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 6, 0, 0.07, 0. });
	}
}

void CIsys_Attacked::Exit()
{
	CMonster* pMonster = GetMonster();
	pMonster->Set_dwTime(0);
}
