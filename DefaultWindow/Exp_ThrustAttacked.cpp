#include "stdafx.h"
#include "Exp_ThrustAttacked.h"

#include "ObjMgr.h"
#include "TimeMgr.h"

#include "Player.h"
#include "Monster.h"
#include "AI.h"
#include "Effect.h"

CExp_ThrustAttacked::CExp_ThrustAttacked()
	: CState(MON_THRUST_ATTACKED)
	, m_dwTime(0)
{
}

CExp_ThrustAttacked::~CExp_ThrustAttacked()
{
}

void CExp_ThrustAttacked::Update()
{
	// Player의 위치 체크
	CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front();
	float fPlayerX = pPlayer->Get_Info().fX;
	float fPlayerY = pPlayer->Get_Info().fY;

	// 몬스터 자신의 위치 체크
	CMonster* pMonster = GetMonster();
	float fMonsterX = pMonster->Get_Info().fX;
	float fMonsterY = pMonster->Get_Info().fY;

	// 익스펠러
	if (L"Expeller_L" == pMonster->Get_FrameKey() || L"Expeller_R" == pMonster->Get_FrameKey())
	{
		// 플레이어 x좌표 체크해서 좌우 이미지 반전
		if (fPlayerX < fMonsterX)
			pMonster->Set_FrameKey(L"Expeller_L");
		else
			pMonster->Set_FrameKey(L"Expeller_R");

		if (!pMonster->Get_KnockBack())
		{
			Exit();
			pMonster->Set_State(MON_STATE::MON_TRACE);
			m_pAI->SetCurState(MON_STATE::MON_TRACE);
			m_pAI->GetCurState()->Enter();
		}
	}
	// 누더기
	else if (L"LNudeogi" == pMonster->Get_FrameKey() || L"RNudeogi" == pMonster->Get_FrameKey())
	{
		// 플레이어 x좌표 체크해서 좌우 이미지 반전
		if (fPlayerX < fMonsterX)
			pMonster->Set_FrameKey(L"LNudeogi");
		else
			pMonster->Set_FrameKey(L"RNudeogi");

		if (!pMonster->Get_KnockBack())
		{
			Exit();
			pMonster->Set_State(MON_STATE::MON_TRACE);
			m_pAI->SetCurState(MON_STATE::MON_TRACE);
			m_pAI->GetCurState()->Enter();
		}
	}
	// 장난감 병정
	else if (L"LToy" == pMonster->Get_FrameKey() || L"RToy" == pMonster->Get_FrameKey())
	{
		// 플레이어 x좌표 체크해서 좌우 이미지 반전
		if (fPlayerX < fMonsterX)
			pMonster->Set_FrameKey(L"LToy");
		else
			pMonster->Set_FrameKey(L"RToy");

		if (!pMonster->Get_KnockBack())
		{
			Exit();
			pMonster->Set_State(MON_STATE::MON_TRACE);
			m_pAI->SetCurState(MON_STATE::MON_TRACE);
			m_pAI->GetCurState()->Enter();
		}
	}
}

void CExp_ThrustAttacked::LateUpdate()
{
}

void CExp_ThrustAttacked::Enter()
{
	CMonster* pMonster = GetMonster();
	CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front();
	pMonster->Set_dwTime(0);

	// Player의 위치 체크
	float fPlayerX = pPlayer->Get_Info().fX;
	float fPlayerY = pPlayer->Get_Info().fY;

	// 몬스터 자신의 위치 체크
	float fMonsterX = pMonster->Get_Info().fX;
	float fMonsterY = pMonster->Get_Info().fY;

	// 플레이어 x좌표 체크해서 좌 우 피격이미지 출력
	if (fPlayerX < fMonsterX)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CEffect>::
			Create_Obj(ATT_JUSTEFFECT, false, pMonster->Get_Info().fX, pMonster->Get_Info().fY, 62.f, 73.f, 0.f, 0.f, 0.f, 0.f, 0.48f, 62.f, 73.f, pMonster->Get_TileCollision().bottom,
				0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, L"LHitEffect", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 6, 0, 0.07, 0. });
	}
	else
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CEffect>::
			Create_Obj(ATT_JUSTEFFECT, false, pMonster->Get_Info().fX, pMonster->Get_Info().fY, 62.f, 73.f, 0.f, 0.f, 0.f, 0.f, 0.48f, 62.f, 73.f, pMonster->Get_TileCollision().bottom,
				0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, L"RHitEffect", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 6, 0, 0.07, 0. });
	}
}

void CExp_ThrustAttacked::Exit()
{
	CMonster* pMonster = GetMonster();
	pMonster->Set_dwTime(0);
}
