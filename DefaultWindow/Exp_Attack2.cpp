#include "stdafx.h"
#include "Exp_Attack2.h"

#include "ObjMgr.h"

#include "Player.h"
#include "AI.h"
#include "Monster.h"
#include "MonsterAttack.h"

CExp_Attack2::CExp_Attack2()
	: CState(MON_ATTACK2)
{
}

CExp_Attack2::~CExp_Attack2()
{
}

void CExp_Attack2::Update()
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
		// 익스펠러
		if (L"Expeller_L" == pMonster->Get_FrameKey() || L"Expeller_R" == pMonster->Get_FrameKey())
		{
			// 1타
			if (0.2 < pMonster->Get_dwTime() && 0 == m_iAttackCount)
			{
				// 좌측 공격 모션중에는 좌측에 피격판정
				++m_iAttackCount;
				if (L"Expeller_L" == pMonster->Get_FrameKey())
				{
					// 피격 히트박스 생성

				}
				else if (L"Expeller_R" == pMonster->Get_FrameKey())
				{

				}
			}

			if (1.1 < pMonster->Get_dwTime() && 1 == m_iAttackCount)
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
			if (0.6 < pMonster->Get_dwTime() && 0 == m_iAttackCount)
			{
				// 왼쪽 모션일 경우
				++m_iAttackCount;
				if (L"LNudeogi" == pMonster->Get_FrameKey())
				{
					// 피격 히트박스 생성
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_LEVITATE, true, fMonsterX - 100.f, fMonsterY + 20.f, 100.f, 100.f, 0, 180.f, 0.f, 0.f, 0.15f, 100.f, 100.f, pMonster->Get_TileCollision().bottom,
							pMonster->Get_Info().fAtk, 5.f, 0.5f, 3.f, 7.5f, 90.f, 180.f, 0.3f, L"Attack1", { 255, 255, 255 }));
				}
				else
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_LEVITATE, true, fMonsterX + 100.f, fMonsterY + 20.f, 100.f, 100.f, 0, 0.f, 0.f, 0.f, 0.15f, 100.f, 100.f, pMonster->Get_TileCollision().bottom,
							pMonster->Get_Info().fAtk, 5.f, 0.5f, 3.f, 7.5f, 90.f, 0.f, 0.3f, L"Attack1", { 255, 255, 255 }));
				}
			}
			if (1 < pMonster->Get_dwTime() && 1 == m_iAttackCount)
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
			if (0.6 < pMonster->Get_dwTime() && 0 == m_iAttackCount)
			{
				// 왼쪽 모션일 경우
				++m_iAttackCount;
				if (L"LToy" == pMonster->Get_FrameKey())
				{
					// 피격 히트박스 생성
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_LEVITATE, true, fMonsterX - 100.f, fMonsterY + 20.f, 100.f, 100.f, 0, 180.f, 0.f, 0.f, 0.15f, 100.f, 100.f, pMonster->Get_TileCollision().bottom,
							pMonster->Get_Info().fAtk, 5.f, 0.5f, 3.f, 7.5f, 90.f, 180.f, 0.3f, L"Attack1", { 255, 255, 255 }));
				}
				else
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_LEVITATE, true, fMonsterX + 100.f, fMonsterY + 20.f, 100.f, 100.f, 0, 0.f, 0.f, 0.f, 0.15f, 100.f, 100.f, pMonster->Get_TileCollision().bottom,
							pMonster->Get_Info().fAtk, 5.f, 0.5f, 3.f, 7.5f, 90.f, 0.f, 0.3f, L"Attack1", { 255, 255, 255 }));
				}
			}
			if (1 < pMonster->Get_dwTime() && 1 == m_iAttackCount)
			{
				Exit();
				pMonster->Set_State(MON_STATE::MON_TRACE);
				m_pAI->SetCurState(MON_STATE::MON_TRACE);
				m_pAI->GetCurState()->Enter();
			}
		}
	}
}

void CExp_Attack2::LateUpdate()
{
}

void CExp_Attack2::Enter()
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

		// 익스펠러
		if (L"Expeller_L" == pMonster->Get_FrameKey() || L"Expeller_R" == pMonster->Get_FrameKey())
		{
			// 플레이어 x좌표 체크해서 좌우 이미지 반전
			if (fPlayerX < fMonsterX)
				pMonster->Set_FrameKey(L"Expeller_L");
			else
				pMonster->Set_FrameKey(L"Expeller_R");
		}
		// 누더기
		else if (L"LNudeogi" == pMonster->Get_FrameKey() || L"RNudeogi" == pMonster->Get_FrameKey())
		{
			if (fPlayerX < fMonsterX)
				pMonster->Set_FrameKey(L"LNudeogi");
			else
				pMonster->Set_FrameKey(L"RNudeogi");
		}
		// 장난감 병정
		else if (L"LToy" == pMonster->Get_FrameKey() || L"RToy" == pMonster->Get_FrameKey())
		{
			if (fPlayerX < fMonsterX)
				pMonster->Set_FrameKey(L"LToy");
			else
				pMonster->Set_FrameKey(L"RToy");
		}
	}
}

void CExp_Attack2::Exit()
{
	CMonster* pMonster = GetMonster();

	pMonster->Set_dwTime(0);
	m_iAttackCount = 0;
}
