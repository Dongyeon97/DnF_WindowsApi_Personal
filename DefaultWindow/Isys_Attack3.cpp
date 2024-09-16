#include "stdafx.h"
#include "Isys_Attack3.h"

#include "ObjMgr.h"
#include "SoundMgr.h"

#include "Player.h"
#include "AI.h"
#include "Monster.h"
#include "MonsterAttack.h"
#include "MonsterAttack2.h"
#include "Skasa.h"

CIsys_Attack3::CIsys_Attack3()
	: CState(BOSS_ATTACK3)
{
}

CIsys_Attack3::~CIsys_Attack3()
{
}

void CIsys_Attack3::Update()
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
			if (0 < pMonster->Get_dwTime() && 0 == m_iAttackCount)
			{
				if (L"LSkasa" == pMonster->Get_FrameKey())
				{
					pMonster->Set_PosX(5.f);
				}
				else if (L"RSkasa" == pMonster->Get_FrameKey())
				{
					pMonster->Set_PosX(-5.f);
				}
			}

			// 브레스 얼음기둥 생성
			if (1.5 < pMonster->Get_dwTime() && 0 == m_iAttackCount)
			{
				++m_iAttackCount;
				CSoundMgr::Get_Instance()->PlaySoundW(L"SkasaBress.wav", SOUND_EFFECT, g_fVolume);
				if (L"LSkasa" == pMonster->Get_FrameKey())
				{
					// 위
					dynamic_cast<CSkasa*>(pMonster)->Making_Breath(fMonsterX - 200.f, fMonsterY + 70.f);

					// 가운데
					dynamic_cast<CSkasa*>(pMonster)->Making_Breath(fMonsterX - 200.f, fMonsterY + 100.f);

					// 아래
					dynamic_cast<CSkasa*>(pMonster)->Making_Breath(fMonsterX - 200.f, fMonsterY + 130.f);
				}
				else if (L"RSkasa" == pMonster->Get_FrameKey())
				{
					// 위
					dynamic_cast<CSkasa*>(pMonster)->Making_Breath(fMonsterX + 200.f, fMonsterY + 70.f);

					// 가운데
					dynamic_cast<CSkasa*>(pMonster)->Making_Breath(fMonsterX + 200.f, fMonsterY + 100.f);

					// 아래
					dynamic_cast<CSkasa*>(pMonster)->Making_Breath(fMonsterX + 200.f, fMonsterY + 130.f);
				}
			}
			if (1.6 < pMonster->Get_dwTime() && 1 == m_iAttackCount)
			{
				++m_iAttackCount;
				if (L"LSkasa" == pMonster->Get_FrameKey())
				{
					// 위
					dynamic_cast<CSkasa*>(pMonster)->Making_Breath(fMonsterX - 350.f, fMonsterY + 40.f);

					// 가운데
					dynamic_cast<CSkasa*>(pMonster)->Making_Breath(fMonsterX - 350.f, fMonsterY + 100.f);

					// 아래
					dynamic_cast<CSkasa*>(pMonster)->Making_Breath(fMonsterX - 350.f, fMonsterY + 160.f);
				}
				else if (L"RSkasa" == pMonster->Get_FrameKey())
				{
					// 위
					dynamic_cast<CSkasa*>(pMonster)->Making_Breath(fMonsterX + 350.f, fMonsterY + 40.f);

					// 가운데
					dynamic_cast<CSkasa*>(pMonster)->Making_Breath(fMonsterX + 350.f, fMonsterY + 100.f);

					// 아래
					dynamic_cast<CSkasa*>(pMonster)->Making_Breath(fMonsterX + 350.f, fMonsterY + 160.f);
				}
			}
			if (1.7 < pMonster->Get_dwTime() && 2 == m_iAttackCount)
			{
				++m_iAttackCount;
				if (L"LSkasa" == pMonster->Get_FrameKey())
				{
					// 위
					dynamic_cast<CSkasa*>(pMonster)->Making_Breath(fMonsterX - 500.f, fMonsterY + 10.f);

					// 가운데
					dynamic_cast<CSkasa*>(pMonster)->Making_Breath(fMonsterX - 500.f, fMonsterY + 100.f);

					// 아래
					dynamic_cast<CSkasa*>(pMonster)->Making_Breath(fMonsterX - 500.f, fMonsterY + 190.f);
				}
				else if (L"RSkasa" == pMonster->Get_FrameKey())
				{
					// 위
					dynamic_cast<CSkasa*>(pMonster)->Making_Breath(fMonsterX + 500.f, fMonsterY + 10.f);

					// 가운데
					dynamic_cast<CSkasa*>(pMonster)->Making_Breath(fMonsterX + 500.f, fMonsterY + 100.f);

					// 아래
					dynamic_cast<CSkasa*>(pMonster)->Making_Breath(fMonsterX + 500.f, fMonsterY + 190.f);
				}
			}
			if (1.8 < pMonster->Get_dwTime() && 3 == m_iAttackCount)
			{
				++m_iAttackCount;
				if (L"LSkasa" == pMonster->Get_FrameKey())
				{
					// 위
					dynamic_cast<CSkasa*>(pMonster)->Making_Breath(fMonsterX - 650.f, fMonsterY - 20.f);

					// 가운데
					dynamic_cast<CSkasa*>(pMonster)->Making_Breath(fMonsterX - 650.f, fMonsterY + 100.f);

					// 아래
					dynamic_cast<CSkasa*>(pMonster)->Making_Breath(fMonsterX - 650.f, fMonsterY + 220.f);
				}
				else if (L"RSkasa" == pMonster->Get_FrameKey())
				{
					// 위
					dynamic_cast<CSkasa*>(pMonster)->Making_Breath(fMonsterX + 650.f, fMonsterY - 20.f);

					// 가운데
					dynamic_cast<CSkasa*>(pMonster)->Making_Breath(fMonsterX + 650.f, fMonsterY + 100.f);

					// 아래
					dynamic_cast<CSkasa*>(pMonster)->Making_Breath(fMonsterX + 650.f, fMonsterY + 220.f);
				}
			}
			if (1.9 < pMonster->Get_dwTime() && 4 == m_iAttackCount)
			{
				++m_iAttackCount;
				if (L"LSkasa" == pMonster->Get_FrameKey())
				{
					// 위
					dynamic_cast<CSkasa*>(pMonster)->Making_Breath(fMonsterX - 800.f, fMonsterY - 50.f);

					// 가운데
					dynamic_cast<CSkasa*>(pMonster)->Making_Breath(fMonsterX - 800.f, fMonsterY + 100.f);

					// 아래
					dynamic_cast<CSkasa*>(pMonster)->Making_Breath(fMonsterX - 800.f, fMonsterY + 250.f);
				}
				else if (L"RSkasa" == pMonster->Get_FrameKey())
				{
					// 위
					dynamic_cast<CSkasa*>(pMonster)->Making_Breath(fMonsterX + 800.f, fMonsterY - 50.f);

					// 가운데
					dynamic_cast<CSkasa*>(pMonster)->Making_Breath(fMonsterX + 800.f, fMonsterY + 100.f);

					// 아래
					dynamic_cast<CSkasa*>(pMonster)->Making_Breath(fMonsterX + 800.f, fMonsterY + 250.f);
				}
			}
			if (2.5 < pMonster->Get_dwTime())
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

				if (fPlayerX < fMonsterX)
					pMonster->Set_Pos(fPlayerX + 50.f, pPlayer->Get_RectCollision().top);
				else
					pMonster->Set_Pos(fPlayerX - 50.f, pPlayer->Get_RectCollision().top);

				if (fPlayerX < fMonsterX)
					pMonster->Set_FrameKey(L"Isys6L");
				else
					pMonster->Set_FrameKey(L"Isys6");
				fMonsterX = pMonster->Get_Info().fX;
				fMonsterY = pMonster->Get_Info().fY;

				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_WIDEATTACK, CAbstractFactory<CMonsterAttack2>::
					Create_Obj(ATT_JUSTEFFECT, false, fMonsterX, fMonsterY, 316.f, 313.f, 0.f, 0.f, 0.f, 0.f, 0.5f, 316.f, 313.f, 0.f,
						0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, L"Isys_LightningEffect2Test", { 0, 0, 0 }));
				CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_WIDEATTACK).back()->Set_Frame(tagFrame{ 0, 18, 0, 0.03, 0. });
				CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_WIDEATTACK).back()->Set_RenderID(EFFECT);
				CSoundMgr::Get_Instance()->PlaySoundW(L"isys_teleport_appear.ogg", SOUND_EFFECT, g_fVolume);
			}
			// 2타
			else if (1.3 < pMonster->Get_dwTime() && 1 == m_iAttackCount)
			{
				++m_iAttackCount;
				// 좌측 공격 모션중에는 좌측에 피격판정
				if (L"Isys6L" == pMonster->Get_FrameKey())
				{
					// 피격 히트박스 생성
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_LEVITATE, true, fMonsterX - 100.f, fMonsterY + 100.f, 200.f, 100.f, 0, 180.f, 0.f, 0.f, 0.2f, 80.f, 100.f, pMonster->Get_Rect().bottom,
							pMonster->Get_Info().fAtk, 10.f, 20.f, 10.f, 3.5f, 90.f, 180.f, 1.f, L"Isys6L", { 0, 0, 0 }));

					CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonsterAttack2>::
						Create_Obj(ATT_JUSTEFFECT, true, fMonsterX - 130.f, fMonsterY + 80.f, 160.f, 160.f, 0.f, 180.f, 0.f, 0.f, 0.6f, 700, 350.f, pMonster->Get_Rect().bottom,
							pMonster->Get_Info().fAtk, 10.f, 5.f, 1.f, 3.5f, 90.f, 180.f, 1.f, L"Isys_AttackGrabL", { 0, 0, 0 }));
					CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 4, 0, 0.12, 0. });
					CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_RenderID(EFFECT);
				}
				else if (L"Isys6" == pMonster->Get_FrameKey())
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_LEVITATE, true, fMonsterX + 100.f, fMonsterY + 100.f, 200.f, 100.f, 0, 0.f, 0.f, 0.f, 0.2f, 80.f, 100.f, pMonster->Get_Rect().bottom,
							pMonster->Get_Info().fAtk, 10.f, 20.f, 10.f, 3.5f, 90.f, 0.f, 1.f, L"Isys6", { 0, 0, 0 }));

					CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonsterAttack2>::
						Create_Obj(ATT_JUSTEFFECT, true, fMonsterX + 130.f, fMonsterY + 80.f, 160.f, 160.f, 0.f, 180.f, 0.f, 0.f, 0.6f, 700, 350.f, pMonster->Get_Rect().bottom,
							pMonster->Get_Info().fAtk, 10.f, 5.f, 1.f, 3.5f, 90.f, 180.f, 1.f, L"Isys_AttackGrab", { 0, 0, 0 }));
					CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 4, 0, 0.12, 0. });
					CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_RenderID(EFFECT);
				}
			}

			else if (1.6 < pMonster->Get_dwTime() && 2 == m_iAttackCount)
			{
				++m_iAttackCount;
				CSoundMgr::Get_Instance()->PlaySoundW(L"isys_atk_02.ogg", SOUND_EFFECT, g_fVolume);
			}

			if (1.8 < pMonster->Get_dwTime())
			{
				Exit();
				pMonster->Set_State(MON_STATE::BOSS_TRACE);
				m_pAI->SetCurState(MON_STATE::BOSS_TRACE);
				m_pAI->GetCurState()->Enter();
			}
		}
	}
}

void CIsys_Attack3::LateUpdate()
{
}

void CIsys_Attack3::Enter()
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
				pMonster->Set_FrameKey(L"Isys_LBackStep");
			else
				pMonster->Set_FrameKey(L"Isys_RBackStep");

			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_WIDEATTACK, CAbstractFactory<CMonsterAttack>::
				Create_Obj(ATT_JUSTEFFECT, false, fMonsterX, fMonsterY, 564.f, 271.f, 0.f, 0.f, 0.f, 0.f, 0.5f, 564.f, 271.f, 0.f,
					0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, L"Isys_LightningEffect1", { 0, 0, 0 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_WIDEATTACK).back()->Set_Frame(tagFrame{ 0, 8, 0, 0.06, 0. });
			CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_WIDEATTACK).back()->Set_RenderID(EFFECT);
			CSoundMgr::Get_Instance()->PlaySoundW(L"isys_teleport_disappear.ogg", SOUND_EFFECT, g_fVolume);
		}
	}
}

void CIsys_Attack3::Exit()
{
	CMonster* pMonster = GetMonster();

	pMonster->Set_dwTime(0);
	m_iAttackCount = 0;
}