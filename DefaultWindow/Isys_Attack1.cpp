#include "stdafx.h"
#include "Isys_Attack1.h"

#include "ObjMgr.h"
#include "SoundMgr.h"

#include "Player.h"
#include "AI.h"
#include "Monster.h"
#include "MonsterAttack.h"

CIsys_Attack1::CIsys_Attack1()
	: CState(BOSS_ATTACK1)
{
}

CIsys_Attack1::~CIsys_Attack1()
{
}

void CIsys_Attack1::Update()
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
		// 스카사
		if (L"LSkasa" == pMonster->Get_FrameKey() || L"RSkasa" == pMonster->Get_FrameKey())
		{
			// 1타
			if (0.6 < pMonster->Get_dwTime() && 0 == m_iAttackCount)
			{
				++m_iAttackCount;
				// 좌측 공격 모션중에는 좌측에 피격판정
				if (L"LSkasa" == pMonster->Get_FrameKey())
				{
					// 피격 히트박스 생성
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_THRUST, true, fMonsterX - 100.f, fMonsterY + 100.f, 150.f, 220.f, 0, 180.f, 0.f, 0.f, 0.2f, 150.f, 220.f, float(pMonster->Get_Rect().bottom),
							pMonster->Get_Info().fAtk, 1.f, 4.f, 3.f, 4.f, 90.f, 180.f, 0.3f, L"Isys_LAttack", { 0, 0, 0 }));
				}
				else if (L"RSkasa" == pMonster->Get_FrameKey())
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_THRUST, true, fMonsterX + 100.f, fMonsterY + 100.f, 150.f, 220.f, 0, 0.f, 0.f, 0.f, 0.2f, 150.f, 220.f, float(pMonster->Get_Rect().bottom),
							pMonster->Get_Info().fAtk, 1.f, 4.f, 3.f, 4.f, 90.f, 0.f, 0.3f, L"Isys_RAttack", { 0, 0, 0 }));
				}
				CSoundMgr::Get_Instance()->PlaySoundW(L"SkasaWingStart.wav", SOUND_EFFECT, g_fVolume);
			}
			if (1 < pMonster->Get_dwTime())
			{
				Exit();
				pMonster->Set_State(MON_STATE::BOSS_TRACE);
				m_pAI->SetCurState(MON_STATE::BOSS_TRACE);
				m_pAI->GetCurState()->Enter();
			}
		}
		// 이시스
		else
		{
			// 1타
			if (0.7 < pMonster->Get_dwTime() && 0 == m_iAttackCount)
			{
				++m_iAttackCount;
				// 좌측 공격 모션중에는 좌측에 피격판정
				if (L"Isys_LAttack" == pMonster->Get_FrameKey())
				{
					// 피격 히트박스 생성
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_THRUST, true, fMonsterX - 100.f, fMonsterY + 100.f, 150.f, 220.f, 0, 180.f, 0.f, 0.f, 0.2f, 150.f, 220.f, float(pMonster->Get_Rect().bottom),
							pMonster->Get_Info().fAtk, 1.f, 4.f, 3.f, 4.f, 90.f, 180.f, 0.3f, L"Isys_LAttack", { 0, 0, 0 }));
				}
				else if (L"Isys_RAttack" == pMonster->Get_FrameKey())
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_THRUST, true, fMonsterX + 100.f, fMonsterY + 100.f, 150.f, 220.f, 0, 0.f, 0.f, 0.f, 0.2f, 150.f, 220.f, float(pMonster->Get_Rect().bottom),
							pMonster->Get_Info().fAtk, 1.f, 4.f, 3.f, 4.f, 90.f, 0.f, 0.3f, L"Isys_RAttack", { 0, 0, 0 }));
				}
				CSoundMgr::Get_Instance()->PlaySoundW(L"isys_atk_03.ogg", SOUND_EFFECT, g_fVolume);
			}

			if (1.02 < pMonster->Get_dwTime() && 1 == m_iAttackCount)
			{
				Exit();
				pMonster->Set_dwTime(0);
				m_iAttackCount = 0;

				switch (rand() % 2)
				{
				case 0:
					pMonster->Set_State(MON_STATE::BOSS_TRACE);
					m_pAI->SetCurState(MON_STATE::BOSS_TRACE);
					m_pAI->GetCurState()->Enter();
					break;

				case 1:
					pMonster->Set_State(MON_STATE::BOSS_ATTACK2);
					m_pAI->SetCurState(MON_STATE::BOSS_ATTACK2);
					m_pAI->GetCurState()->Enter();
					break;
				}
			}
		}
	}
}

void CIsys_Attack1::LateUpdate()
{
}

void CIsys_Attack1::Enter()
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
		if (L"LSkasa" == pMonster->Get_FrameKey() || L"RSkasa" == pMonster->Get_FrameKey())
		{
			if (fPlayerX < fMonsterX)
				pMonster->Set_FrameKey(L"LSkasa");
			else
				pMonster->Set_FrameKey(L"RSkasa");
		}
		else
		{
			if (fPlayerX < fMonsterX)
				pMonster->Set_FrameKey(L"Isys_LAttack");
			else
				pMonster->Set_FrameKey(L"Isys_RAttack");
		}
	}
}

void CIsys_Attack1::Exit()
{
	CMonster* pMonster = GetMonster();

	pMonster->Set_dwTime(0);
	m_iAttackCount = 0;
}
