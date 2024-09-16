#include "stdafx.h"
#include "Isys_BackStep.h"

#include "ObjMgr.h"

#include "Player.h"
#include "AI.h"
#include "Monster.h"
#include "MonsterAttack.h"
#include "SoundMgr.h"

CIsys_BackStep::CIsys_BackStep()
	: CState(BOSS_BACKSTEP)
{
}

CIsys_BackStep::~CIsys_BackStep()
{
}

void CIsys_BackStep::Update()
{
	// Player의 위치 체크
	CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front();
	float fPlayerX = pPlayer->Get_Info().fX;
	float fPlayerY = pPlayer->Get_Info().fY;

	// 몬스터 자신의 위치 체크
	CMonster* pMonster = GetMonster();
	float fMonsterX = pMonster->Get_Info().fX;
	float fMonsterY = pMonster->Get_Info().fY;

	if (pPlayer)
	{
		// 1타
		if (0.08 < pMonster->Get_dwTime() && 0 == m_iAttackCount)
		{
			++m_iAttackCount;
			if (L"Isys_LBackStep" == pMonster->Get_FrameKey())
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
					Create_Obj(ATT_THRUST, true, fMonsterX - 50.f, fMonsterY + 100.f, 100.f, 100.f, 0, 180.f, 0.f, 0.f, 0.1f, 100.f, 100.f, pMonster->Get_Rect().bottom,
						pMonster->Get_Info().fAtk, 1.f, 4.f, 2.f, 6.5f, 90.f, 180.f, 0.25f, L"Isys_LAttack", { 0, 0, 0 }));
			}
			else if (L"Isys_RBackStep" == pMonster->Get_FrameKey())
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
					Create_Obj(ATT_THRUST, true, fMonsterX + 50.f, fMonsterY + 100.f, 100.f, 100.f, 0, 0.f, 0.f, 0.f, 0.1f, 100.f, 100.f, pMonster->Get_Rect().bottom,
						pMonster->Get_Info().fAtk, 1.f, 4.f, 2.f, 6.5f, 90.f, 0.f, 0.25f, L"Isys_RAttack", { 0, 0, 0 }));
			}
			switch (rand() % 3)
			{
			case 0:
				CSoundMgr::Get_Instance()->PlaySoundW(L"isys_atk_01.ogg", SOUND_EFFECT, g_fVolume);
				break;

			case 1:
				CSoundMgr::Get_Instance()->PlaySoundW(L"isys_atk_02.ogg", SOUND_EFFECT, g_fVolume);
				break;

			case 2:
				CSoundMgr::Get_Instance()->PlaySoundW(L"isys_atk_03.ogg", SOUND_EFFECT, g_fVolume);
				break;
			}
		}
		// 백스탭
		else if (0.15 < pMonster->Get_dwTime() && 1 == m_iAttackCount)
		{
			if (L"Isys_LBackStep" == pMonster->Get_FrameKey())
			{
				pMonster->Set_PosX(6.f);
			}
			else if (L"Isys_RBackStep" == pMonster->Get_FrameKey())
			{
				pMonster->Set_PosX(-6.f);
			}
		}

		if (0.62 < pMonster->Get_dwTime())
		{
			Exit();
			pMonster->Set_State(MON_STATE::BOSS_TRACE);
			m_pAI->SetCurState(MON_STATE::BOSS_TRACE);
			m_pAI->GetCurState()->Enter();
		}
	}
}

void CIsys_BackStep::LateUpdate()
{

}

void CIsys_BackStep::Enter()
{
	CMonster* pMonster = GetMonster();
	pMonster->Set_dwTime(0);
	m_iAttackCount = 0;
	if (pMonster)
	{
		// Player의 위치 체크
		CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front();
		float fPlayerX = pPlayer->Get_Info().fX;
		float fPlayerY = pPlayer->Get_Info().fY;

		// 몬스터 자신의 위치 체크
		CMonster* pMonster = GetMonster();
		float fMonsterX = pMonster->Get_Info().fX;
		float fMonsterY = pMonster->Get_Info().fY;

		// 플레이어 x좌표 체크해서 좌우 이미지 반전
		if (fPlayerX < fMonsterX)
			pMonster->Set_FrameKey(L"Isys_LBackStep");
		else
			pMonster->Set_FrameKey(L"Isys_RBackStep");
	}
}

void CIsys_BackStep::Exit()
{
	CMonster* pMonster = GetMonster();

	pMonster->Set_dwTime(0);
	m_iAttackCount = 0;
}