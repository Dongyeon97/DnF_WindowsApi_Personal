#include "stdafx.h"
#include "Exp_Attack1.h"

#include "ObjMgr.h"

#include "Player.h"
#include "AI.h"
#include "Monster.h"
#include "MonsterAttack.h"
#include "SoundMgr.h"

CExp_Attack1::CExp_Attack1()
	: CState(MON_ATTACK1)
{
}

CExp_Attack1::~CExp_Attack1()
{
}

void CExp_Attack1::Update()
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
			if (0.65 < pMonster->Get_dwTime() && 0 == m_iAttackCount)
			{
				++m_iAttackCount;
				if (L"Expeller_L" == pMonster->Get_FrameKey())
				{
					// 피격 히트박스 생성
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_THRUST, true, fMonsterX - 100.f, fMonsterY + 20.f, 300.f, 100.f, 0, 180.f, 0.f, 0.f, 0.15f, 200.f, 150.f, pMonster->Get_Rect().bottom,
							pMonster->Get_Info().fAtk, 1.f, 4.f, 3.f, 0.f, 0.f, 180.f, 0.3f, L"Attack1", { 255, 255, 255 }));
				}
				else if (L"Expeller_R" == pMonster->Get_FrameKey())
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_THRUST, true, fMonsterX + 100.f, fMonsterY + 20.f, 300.f, 100.f, 0, 0.f, 0.f, 0.f, 0.15f, 200.f, 150.f, pMonster->Get_Rect().bottom,
							pMonster->Get_Info().fAtk, 1.f, 4.f, 3.f, 0.f, 0.f, 0.f, 0.3f, L"Attack1", { 255, 255, 255 }));
				}
			}

			if (1.2 < pMonster->Get_dwTime() && 1 == m_iAttackCount)
			{
				++m_iAttackCount;

				if (L"Player_LEFT" == pPlayer->Get_FrameKey())
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_WIDEATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_THRUST, false, fPlayerX + 40.f, pPlayer->Get_Rect().bottom - 150.f, 190.f, 306.f, 0, 0.f, 0.f, 0.f, 0.9f, 30.f, 250.f, pMonster->Get_Rect().bottom,
							pMonster->Get_Info().fAtk, 2.f, 4.f, 3.f, 0.f, 0.f, 0.f, 0.3f, L"Expeller_Sunder", { 0, 0, 0 }));
					CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_WIDEATTACK).back()->Set_Frame(tagFrame{ 0, 8, 0, 0.1, 0. });
				}
				else if (L"Player_RIGHT" == pPlayer->Get_FrameKey())
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_WIDEATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_THRUST, false, fPlayerX - 40.f, pPlayer->Get_Rect().bottom - 150.f, 190.f, 306.f, 0, 0.f, 0.f, 0.f, 0.9f, 30.f, 250.f, pMonster->Get_Rect().bottom,
							pMonster->Get_Info().fAtk, 2.f, 4.f, 3.f, 0.f, 0.f, 0.f, 0.3f, L"Expeller_Sunder", { 0, 0, 0 }));
					CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_WIDEATTACK).back()->Set_Frame(tagFrame{ 0, 8, 0, 0.1, 0. });
				}
				CSoundMgr::Get_Instance()->PlaySoundW(L"gn_jspike_02.wav", SOUND_EFFECT, g_fVolume);
			}

			if (1.49 < pMonster->Get_dwTime() && 2 == m_iAttackCount)
			{
				Exit();
				pMonster->Set_dwTime(0);
				m_iAttackCount = 0;

				switch (rand() % 2)
				{
				case 0:
					pMonster->Set_State(MON_STATE::MON_TRACE);
					m_pAI->SetCurState(MON_STATE::MON_TRACE);
					m_pAI->GetCurState()->Enter();
					break;

				case 1:
					pMonster->Set_State(MON_STATE::MON_ATTACK2);
					m_pAI->SetCurState(MON_STATE::MON_ATTACK2);
					m_pAI->GetCurState()->Enter();
					break;
				}
			}
		}
		// 누더기
		else if (L"LNudeogi" == pMonster->Get_FrameKey() || L"RNudeogi" == pMonster->Get_FrameKey())
		{
			// 1타
			if (0.6 < pMonster->Get_dwTime() && 0 == m_iAttackCount)
			{
				++m_iAttackCount;
				// 왼쪽 모션일 경우
				if (L"LNudeogi" == pMonster->Get_FrameKey())
				{
					// 피격 히트박스 생성
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_THRUST, true, fMonsterX - 100.f, fMonsterY + 20.f, 100.f, 100.f, 0, 180.f, 0.f, 0.f, 0.15f, 100.f, 100.f, pMonster->Get_TileCollision().bottom,
							pMonster->Get_Info().fAtk, 1.f, 6.f, 3.f, 0.f, 0.f, 180.f, 0.3f, L"Attack1", { 255, 255, 255 }));
				}
				else
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_THRUST, true, fMonsterX + 100.f, fMonsterY + 20.f, 100.f, 100.f, 0, 0.f, 0.f, 0.f, 0.15f, 100.f, 100.f, pMonster->Get_TileCollision().bottom,
							pMonster->Get_Info().fAtk, 1.f, 6.f, 3.f, 0.f, 0.f, 0.f, 0.3f, L"Attack1", { 255, 255, 255 }));
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
			// 1타
			if (0.6 < pMonster->Get_dwTime() && 0 == m_iAttackCount)
			{
				++m_iAttackCount;
				// 왼쪽 모션일 경우
				if (L"LToy" == pMonster->Get_FrameKey())
				{
					// 피격 히트박스 생성
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_THRUST, true, fMonsterX - 100.f, fMonsterY + 20.f, 100.f, 100.f, 0, 180.f, 0.f, 0.f, 0.15f, 100.f, 100.f, pMonster->Get_TileCollision().bottom,
							pMonster->Get_Info().fAtk, 1.f, 6.f, 3.f, 0.f, 0.f, 180.f, 0.3f, L"Attack1", { 255, 255, 255 }));
				}
				else
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_THRUST, true, fMonsterX + 100.f, fMonsterY + 20.f, 100.f, 100.f, 0, 0.f, 0.f, 0.f, 0.15f, 100.f, 100.f, pMonster->Get_TileCollision().bottom,
							pMonster->Get_Info().fAtk, 1.f, 6.f, 3.f, 0.f, 0.f, 0.f, 0.3f, L"Attack1", { 255, 255, 255 }));
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

void CExp_Attack1::LateUpdate()
{
}

void CExp_Attack1::Enter()
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

void CExp_Attack1::Exit()
{
	CMonster* pMonster = GetMonster();

	pMonster->Set_dwTime(0);
	m_iAttackCount = 0;
}
