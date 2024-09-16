#include "stdafx.h"
#include "Exp_Appear.h"

#include "ObjMgr.h"

#include "Player.h"
#include "Monster.h"
#include "AI.h"

CExp_Appear::CExp_Appear()
	: CState(MON_APPEAR)
{
}

CExp_Appear::~CExp_Appear()
{
}

void CExp_Appear::Update()
{
	CMonster* pMonster = GetMonster();

	// 등장 스프라이트 출력

	if (2.3 < pMonster->Get_dwTime())
	{
		Exit();
		pMonster->Set_State(MON_STATE::MON_TRACE);
		m_pAI->SetCurState(MON_STATE::MON_TRACE);
		m_pAI->GetCurState()->Enter();
	}
}

void CExp_Appear::LateUpdate()
{
}

void CExp_Appear::Enter()
{
	CMonster* pMonster = GetMonster();

	// 등장모션동안 무적상태
	pMonster->Set_IsImmune(true);

	pMonster->Set_dwTime(0);
	m_iAttackCount = 0;
}

void CExp_Appear::Exit()
{
	CMonster* pMonster = GetMonster();

	// 무적 해제
	pMonster->Set_IsImmune(false);

	pMonster->Set_dwTime(0);
	m_iAttackCount = 0;
}
