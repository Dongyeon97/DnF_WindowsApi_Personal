#include "stdafx.h"
#include "Isys_Idle.h"

#include "ObjMgr.h"

#include "Player.h"
#include "Monster.h"
#include "AI.h"

CIsys_Idle::CIsys_Idle()
	: CState(BOSS_IDLE)
{
}

CIsys_Idle::~CIsys_Idle()
{
}

void CIsys_Idle::Update()
{
	// Player의 위치 체크
	CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front();
	float fPlayerX = pPlayer->Get_Info().fX;
	float fPlayerY = pPlayer->Get_Info().fY;

	// 몬스터 자신의 위치 체크
	CMonster* pMonster = GetMonster();
	float fMonsterX = pMonster->Get_Info().fX;
	float fMonsterY = pMonster->Get_Info().fY;

	float fDistance = sqrtf(powf(fPlayerX - fMonsterX, 2) + powf(fPlayerY - fMonsterY, 2));

	// 스카사
	if (L"LSkasa" == pMonster->Get_FrameKey() || L"RSkasa" == pMonster->Get_FrameKey())
	{
		if (fDistance < pMonster->GetMonInfo().m_fRecogRange)
		{
			Exit();
			pMonster->Set_State(MON_STATE::BOSS_TRACE);
			m_pAI->SetCurState(MON_STATE::BOSS_TRACE);
			m_pAI->GetCurState()->Enter();
		}
	}
	// 이시스
	else if (fDistance < pMonster->GetMonInfo().m_fRecogRange)
	{
		Exit();
		pMonster->Set_State(MON_STATE::BOSS_APPEAR);
		m_pAI->SetCurState(MON_STATE::BOSS_APPEAR);
		m_pAI->GetCurState()->Enter();
	}
}

void CIsys_Idle::LateUpdate()
{
}

void CIsys_Idle::Enter()
{
	CMonster* pMonster = GetMonster();

	pMonster->Set_dwTime(0);
	m_iAttackCount = 0;
}

void CIsys_Idle::Exit()
{
	CMonster* pMonster = GetMonster();

	pMonster->Set_dwTime(0);
	m_iAttackCount = 0;
}
