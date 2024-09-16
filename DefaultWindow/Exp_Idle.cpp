#include "stdafx.h"
#include "Exp_Idle.h"

#include "ObjMgr.h"

#include "Player.h"
#include "Monster.h"
#include "AI.h"

CExp_Idle::CExp_Idle()
	: CState(MON_IDLE)
{
}

CExp_Idle::~CExp_Idle()
{
}

void CExp_Idle::Update()
{
	// Player�� ��ġ üũ
	CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front();
	float fPlayerX = pPlayer->Get_Info().fX;
	float fPlayerY = pPlayer->Get_Info().fY;

	// ���� �ڽ��� ��ġ üũ
	CMonster* pMonster = GetMonster();
	float fMonsterX = pMonster->Get_Info().fX;
	float fMonsterY = pMonster->Get_Info().fY;

	// �ͽ��緯
	if (L"Expeller_L" == pMonster->Get_FrameKey() || L"Expeller_R" == pMonster->Get_FrameKey())
	{
		pMonster->Set_IsImmune(true);

		float fDistance = sqrtf(powf(fPlayerX - fMonsterX, 2) + powf(fPlayerY - fMonsterY, 2));

		// ������ �ν� ������ �÷��̾ ������
		if (fDistance < pMonster->GetMonInfo().m_fRecogRange)
		{
			Exit();
			pMonster->Set_State(MON_STATE::MON_APPEAR);
			m_pAI->SetCurState(MON_STATE::MON_APPEAR);
			m_pAI->GetCurState()->Enter();
		}
	}
	else if (L"LNudeogi" == pMonster->Get_FrameKey() || L"RNudeogi" == pMonster->Get_FrameKey())
	{
		float fDistance = sqrtf(powf(fPlayerX - fMonsterX, 2) + powf(fPlayerY - fMonsterY, 2));

		// ������ �ν� ������ �÷��̾ ������
		if (fDistance < pMonster->GetMonInfo().m_fRecogRange)
		{
			Exit();
			pMonster->Set_State(MON_STATE::MON_TRACE);
			m_pAI->SetCurState(MON_STATE::MON_TRACE);
			m_pAI->GetCurState()->Enter();
		}
	}
}

void CExp_Idle::LateUpdate()
{
}

void CExp_Idle::Enter()
{
	CMonster* pMonster = GetMonster();
	pMonster->Set_dwTime(0);
	m_iAttackCount = 0;
}

void CExp_Idle::Exit()
{
	CMonster* pMonster = GetMonster();

	pMonster->Set_dwTime(0);
	m_iAttackCount = 0;
}
