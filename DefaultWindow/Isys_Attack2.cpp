#include "stdafx.h"
#include "Isys_Attack2.h"

#include "ObjMgr.h"

#include "Player.h"
#include "AI.h"
#include "Monster.h"
#include "MonsterAttack.h"
#include "MonsterAttack2.h"
#include "SoundMgr.h"

CIsys_Attack2::CIsys_Attack2()
	: CState(BOSS_ATTACK2)
{
}

CIsys_Attack2::~CIsys_Attack2()
{
}

void CIsys_Attack2::Update()
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
		// 스카사 - 돌진
		if (L"LSkasa" == pMonster->Get_FrameKey() || L"RSkasa" == pMonster->Get_FrameKey())
		{
			// 돌진 준비자세
			if (0 < pMonster->Get_dwTime() && 0 == m_iAttackCount)
			{
				if(0.8 < pMonster->Get_dwTime())
					++m_iAttackCount;
				// 좌측 공격 모션중에는 좌측에 피격판정
				if (L"LSkasa" == pMonster->Get_FrameKey())
				{
					pMonster->Set_PosX(2.f);
					pMonster->Set_PosY(-0.5f);
				}
				else if (L"RSkasa" == pMonster->Get_FrameKey())
				{
					pMonster->Set_PosX(-2.f);
					pMonster->Set_PosY(-0.5f);
				}
			}
			// 돌진
			if (0.8 < pMonster->Get_dwTime())
			{
				if (L"LSkasa" == pMonster->Get_FrameKey())
				{
					pMonster->Set_PosX(-10.f);
				}
				else if (L"RSkasa" == pMonster->Get_FrameKey())
				{
					pMonster->Set_PosX(10.f);
				}
			}
			if (0.8 < pMonster->Get_dwTime() && 1 == m_iAttackCount)
			{
				++m_iAttackCount;
				CSoundMgr::Get_Instance()->PlaySoundW(L"SkasaWing.wav", SOUND_EFFECT, g_fVolume);
				if (L"LSkasa" == pMonster->Get_FrameKey())
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_THRUST, true, fMonsterX, fMonsterY + 100.f, 250.f, 250.f, 0, 180.f, 0.f, 0.f, 0.2f, 250.f, 250.f, float(pMonster->Get_Rect().bottom),
							pMonster->Get_Info().fAtk, 1.f, 4.f, 3.f, 4.f, 90.f, 180.f, 0.3f, L"Isys_LAttack", { 0, 0, 0 }));
				}
				else if (L"RSkasa" == pMonster->Get_FrameKey())
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_THRUST, true, fMonsterX, fMonsterY + 100.f, 250.f, 250.f, 0, 180.f, 0.f, 0.f, 0.2f, 250.f, 250.f, float(pMonster->Get_Rect().bottom),
							pMonster->Get_Info().fAtk, 1.f, 4.f, 3.f, 4.f, 90.f, 0.f, 0.3f, L"Isys_LAttack", { 0, 0, 0 }));
				}
			}
			if (1 < pMonster->Get_dwTime() && 2 == m_iAttackCount)
			{
				++m_iAttackCount;
				if (L"LSkasa" == pMonster->Get_FrameKey())
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_THRUST, true, fMonsterX, fMonsterY + 100.f, 250.f, 250.f, 0, 180.f, 0.f, 0.f, 0.2f, 250.f, 250.f, float(pMonster->Get_Rect().bottom),
							pMonster->Get_Info().fAtk, 1.f, 4.f, 3.f, 4.f, 90.f, 180.f, 0.3f, L"Isys_LAttack", { 0, 0, 0 }));
				}
				else if (L"RSkasa" == pMonster->Get_FrameKey())
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_THRUST, true, fMonsterX, fMonsterY + 100.f, 250.f, 250.f, 0, 180.f, 0.f, 0.f, 0.2f, 250.f, 250.f, float(pMonster->Get_Rect().bottom),
							pMonster->Get_Info().fAtk, 1.f, 4.f, 3.f, 4.f, 90.f, 0.f, 0.3f, L"Isys_LAttack", { 0, 0, 0 }));
				}
			}
			if (1.2 < pMonster->Get_dwTime() && 3 == m_iAttackCount)
			{
				++m_iAttackCount;
				if (L"LSkasa" == pMonster->Get_FrameKey())
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_THRUST, true, fMonsterX, fMonsterY + 100.f, 250.f, 250.f, 0, 180.f, 0.f, 0.f, 0.2f, 250.f, 250.f, float(pMonster->Get_Rect().bottom),
							pMonster->Get_Info().fAtk, 1.f, 4.f, 3.f, 4.f, 90.f, 180.f, 0.3f, L"Isys_LAttack", { 0, 0, 0 }));
				}
				else if (L"RSkasa" == pMonster->Get_FrameKey())
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_THRUST, true, fMonsterX, fMonsterY + 100.f, 250.f, 250.f, 0, 180.f, 0.f, 0.f, 0.2f, 250.f, 250.f, float(pMonster->Get_Rect().bottom),
							pMonster->Get_Info().fAtk, 1.f, 4.f, 3.f, 4.f, 90.f, 0.f, 0.3f, L"Isys_LAttack", { 0, 0, 0 }));
				}
			}
			if (1.4 < pMonster->Get_dwTime() && 4 == m_iAttackCount)
			{
				++m_iAttackCount;
				if (L"LSkasa" == pMonster->Get_FrameKey())
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_THRUST, true, fMonsterX, fMonsterY + 100.f, 250.f, 250.f, 0, 180.f, 0.f, 0.f, 0.2f, 250.f, 250.f, float(pMonster->Get_Rect().bottom),
							pMonster->Get_Info().fAtk, 1.f, 4.f, 3.f, 4.f, 90.f, 180.f, 0.3f, L"Isys_LAttack", { 0, 0, 0 }));
				}
				else if (L"RSkasa" == pMonster->Get_FrameKey())
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_THRUST, true, fMonsterX, fMonsterY + 100.f, 250.f, 250.f, 0, 180.f, 0.f, 0.f, 0.2f, 250.f, 250.f, float(pMonster->Get_Rect().bottom),
							pMonster->Get_Info().fAtk, 1.f, 4.f, 3.f, 4.f, 90.f, 0.f, 0.3f, L"Isys_LAttack", { 0, 0, 0 }));
				}
			}
			if (1.6 < pMonster->Get_dwTime())
			{
				Exit();
				pMonster->Set_State(MON_STATE::BOSS_TRACE);
				m_pAI->SetCurState(MON_STATE::BOSS_TRACE);
				m_pAI->GetCurState()->Enter();
			}
		}
		// 이시스 - 옆차기 후 연쇄폭발
		else
		{
			// 1타
			if (0.48 < pMonster->Get_dwTime() && 0 == m_iAttackCount)
			{
				++m_iAttackCount;
				// 좌측 공격 모션중에는 좌측에 피격판정
				if (L"Isys_LAttack2" == pMonster->Get_FrameKey())
				{
					// 피격 히트박스 생성
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_THRUST, true, fMonsterX - 100.f, fMonsterY + 100.f, 250.f, 200.f, 0.f, 180.f, 0.f, 0.f, 0.2f, 250.f, 200.f, pMonster->Get_Rect().bottom,
							pMonster->Get_Info().fAtk, 1.f, 4.f, 2.f, 6.5f, 90.f, 180.f, 0.4f, L"Isys_LAttack2", { 0, 0, 0 }));

					CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_JUSTEFFECT, true, fMonsterX - 100.f, fMonsterY + 60.f, 700.f, 350.f, 5.f, 180.f, 0.f, 0.f, 0.5f, 700, 350.f, pMonster->Get_Rect().bottom,
							pMonster->Get_Info().fAtk, 10.f, 5.f, 1.f, 3.5f, 90.f, 180.f, 1.f, L"Isys_LAttack2_Effect", { 0, 0, 0 }));
					CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 9, 0, 0.05, 0. });
				}
				else if (L"Isys_RAttack2" == pMonster->Get_FrameKey())
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_THRUST, true, fMonsterX + 100.f, fMonsterY + 100.f, 250.f, 200.f, 0, 0.f, 0.f, 0.f, 0.2f, 250.f, 200.f, pMonster->Get_Rect().bottom,
							pMonster->Get_Info().fAtk, 1.f, 4.f, 2.f, 6.5f, 90.f, 0.f, 0.4f, L"Isys_RAttack2", { 0, 0, 0 }));

					CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_JUSTEFFECT, true, fMonsterX + 100.f, fMonsterY + 60.f, 700.f, 350.f, 5.f, 0.f, 0.f, 0.f, 0.5f, 700, 350.f, pMonster->Get_Rect().bottom,
							pMonster->Get_Info().fAtk, 10.f, 5.f, 1.f, 3.5f, 90.f, 180.f, 1.f, L"Isys_RAttack2_Effect", { 0, 0, 0 }));
					CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 9, 0, 0.05, 0. });

				}
				CSoundMgr::Get_Instance()->PlaySoundW(L"isys_lowkick_atk.ogg", SOUND_EFFECT, g_fVolume);
				CSoundMgr::Get_Instance()->PlaySoundW(L"isys_finalatk_feather.ogg", SOUND_EFFECT2, g_fVolume);
			}

			// 발 휘두르기 자세로 잠시 정지
			if (0.48 < pMonster->Get_dwTime() && 1 == m_iAttackCount)
			{
				++m_iAttackCount;
				pMonster->Set_StopMotion(true);
			}

			// 1초뒤 행동 재개
			if (1.45 < pMonster->Get_dwTime() && 2 == m_iAttackCount)
			{
				++m_iAttackCount;
				pMonster->Set_StopMotion(false);
			}

			// 2타
			if (2.10 < pMonster->Get_dwTime() && 3 == m_iAttackCount)
			{
				++m_iAttackCount;
				// 좌측 공격 모션중에는 좌측에 피격판정
				if (L"Isys_LAttack2" == pMonster->Get_FrameKey())
				{
					// 피격 히트박스 생성
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_LEVITATE, true, fMonsterX - 100.f, fMonsterY + 100.f, 200.f, 100.f, 0, 180.f, 0.f, 0.f, 0.2f, 200.f, 100.f, pMonster->Get_Rect().bottom,
							pMonster->Get_Info().fAtk, 1.f, 4.f, 2.f, 5.f, 90.f, 180.f, 0.85f, L"Isys_LAttack2", { 0, 0, 0 }));

					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_LEVITATE, false, fMonsterX - 100.f, fMonsterY + 125.f, 420.f, 167.f, 0, 0.f, 0.f, 0.f, 0.3f, 420.f, 167.f, pMonster->Get_TileCollision().bottom,
							pMonster->Get_Info().fAtk, 1.f, 4.f, 2.f, 5.f, 90.f, 0.f, 0.5f, L"Isys_ChopFirstFloor", { 255, 255, 255 }));
				}
				else if (L"Isys_RAttack2" == pMonster->Get_FrameKey())
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_LEVITATE, true, fMonsterX + 100.f, fMonsterY + 100.f, 200.f, 100.f, 0, 0.f, 0.f, 0.f, 0.2f, 100.f, 200.f, pMonster->Get_Rect().bottom,
							pMonster->Get_Info().fAtk, 1.f, 4.f, 2.f, 5.f, 90.f, 0.f, 0.85f, L"Isys_RAttack2", { 0, 0, 0 }));

					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_LEVITATE, false, fMonsterX + 100.f, fMonsterY + 125.f, 420.f, 167.f, 0, 0.f, 0.f, 0.f, 0.3f, 420.f, 167.f, pMonster->Get_TileCollision().bottom,
							pMonster->Get_Info().fAtk, 1.f, 4.f, 2.f, 5.f, 90.f, 0.f, 0.5f, L"Isys_ChopFirstFloor", { 255, 255, 255 }));
				}
				CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_ATTACK).back()->Set_RenderID(BACKGROUNDEFFECT);
				CSoundMgr::Get_Instance()->PlaySoundW(L"isys_floor_explo_02.ogg", SOUND_EFFECT, g_fVolume);
			}

			if (2.15 < pMonster->Get_dwTime() && 4 == m_iAttackCount)
			{
				++m_iAttackCount;
				Explosion(310, pMonster->Get_Info().fY - 1000);
			}
			if (2.2 < pMonster->Get_dwTime() && 5 == m_iAttackCount)
			{
				++m_iAttackCount;
				Explosion(380, pMonster->Get_Info().fY - 1000);
			}
			if (2.25 < pMonster->Get_dwTime() && 6 == m_iAttackCount)
			{
				++m_iAttackCount;
				Explosion(450, pMonster->Get_Info().fY - 1000);
			}
			if (2.3 < pMonster->Get_dwTime() && 7 == m_iAttackCount)
			{
				++m_iAttackCount;
				Explosion(520, pMonster->Get_Info().fY - 1000);
			}
			if (2.35 < pMonster->Get_dwTime() && 8 == m_iAttackCount)
			{
				++m_iAttackCount;
				Explosion(590, pMonster->Get_Info().fY - 1000);
			}

			if (2.4 < pMonster->Get_dwTime() && 9 == m_iAttackCount)
			{
				++m_iAttackCount;
				if (L"Isys_LAttack2" == pMonster->Get_FrameKey())
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_LEVITATE, false, fMonsterX - 100.f, fMonsterY + 125.f, 600.f, 237.f, 0, 0.f, 0.f, 0.f, 0.2f, 600.f, 237.f, pMonster->Get_TileCollision().bottom,
							pMonster->Get_Info().fAtk, 1.f, 4.f, 2.f, 10.f, 90.f, 0.f, 0.5f, L"Isys_ChopSecondFloor", { 255, 255, 255 }));
				}
				else if (L"Isys_RAttack2" == pMonster->Get_FrameKey())
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_LEVITATE, false, fMonsterX + 100.f, fMonsterY + 125.f, 600.f, 237.f, 0, 0.f, 0.f, 0.f, 0.5f, 600.f, 237.f, pMonster->Get_TileCollision().bottom,
							pMonster->Get_Info().fAtk, 1.f, 4.f, 2.f, 10.f, 90.f, 0.f, 0.5f, L"Isys_ChopSecondFloor", { 255, 255, 255 }));
				}
				CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_ATTACK).back()->Set_RenderID(BACKGROUNDEFFECT);
			}

			if (2.45 < pMonster->Get_dwTime())
			{
				Exit();
				pMonster->Set_State(MON_STATE::BOSS_TRACE);
				m_pAI->SetCurState(MON_STATE::BOSS_TRACE);
				m_pAI->GetCurState()->Enter();
			}
		}
	}
}

void CIsys_Attack2::LateUpdate()
{
}

void CIsys_Attack2::Enter()
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
				pMonster->Set_FrameKey(L"Isys_LAttack2");
			else
				pMonster->Set_FrameKey(L"Isys_RAttack2");
		}
	}
}

void CIsys_Attack2::Exit()
{
	CMonster* pMonster = GetMonster();

	pMonster->Set_dwTime(0);
	m_iAttackCount = 0;
}

void CIsys_Attack2::Explosion(float _fX, float _fY)
{
	CMonster* pMonster = GetMonster();

	// Player의 위치 체크
	CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front();
	float fPlayerX = pPlayer->Get_Info().fX;
	float fPlayerY = pPlayer->Get_Info().fY;

	float fDst;

	if (L"Isys_LAttack2" == pMonster->Get_FrameKey())
	{
		switch (rand() % 2)
		{
		case 0:
			fDst = pMonster->Get_TileCollision().bottom + (rand() % 50);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
				Create_Obj(ATT_THRUST, false, pMonster->Get_Info().fX - _fX, _fY - 200.f, 420.f, 525.f, 40.f, 270.f, 0.f, fDst, 1.3f, 100.f, 200.f, pMonster->Get_Rect().bottom,
					pMonster->Get_Info().fAtk, 10.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.2f, L"Isys_FeatherAttack", { 255, 255, 255 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_ATTACK).back()->Set_Frame(tagFrame{ 0, 12, 0, 0.1, 0. });
			break;

		case 1:
			fDst = pMonster->Get_TileCollision().top - (rand() % 50);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
				Create_Obj(ATT_THRUST, false, pMonster->Get_Info().fX - _fX, _fY - 200.f, 420.f, 525.f, 40.f, 270.f, 0.f, fDst, 1.3f, 100.f, 200.f, pMonster->Get_Rect().bottom,
					pMonster->Get_Info().fAtk, 10.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.2f, L"Isys_FeatherAttack", { 255, 255, 255 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_ATTACK).back()->Set_Frame(tagFrame{ 0, 12, 0, 0.1, 0. });
			break;
		}

		// 마법진
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonsterAttack>::
			Create_Obj(ATT_JUSTEFFECT, false, pMonster->Get_Info().fX - _fX, fDst - 100.f, 400.f, 400.f, 0.f, 0.f, 0.f, 0.f, 1.0f, 400.f, 400.f, pMonster->Get_Rect().bottom,
				pMonster->Get_Info().fAtk, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.1f, L"Isys_FeatherAttackPos2", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 5, 0, 0.2, 0. });
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_RenderID(BACKGROUNDEFFECT);
	}
	else
	{
		switch (rand() % 2)
		{
		case 0:
			fDst = pMonster->Get_TileCollision().bottom + (rand() % 50);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
				Create_Obj(ATT_THRUST, false, pMonster->Get_Info().fX + _fX, _fY - 200.f, 420.f, 525.f, 40.f, 270.f, 0.f, fDst, 1.3f, 100.f, 200.f, pMonster->Get_Rect().bottom,
					pMonster->Get_Info().fAtk, 10.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.2f, L"Isys_FeatherAttack", { 255, 255, 255 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_ATTACK).back()->Set_Frame(tagFrame{ 0, 12, 0, 0.1, 0. });
			break;

		case 1:
			fDst = pMonster->Get_TileCollision().top - (rand() % 50);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
				Create_Obj(ATT_THRUST, false, pMonster->Get_Info().fX + _fX, _fY - 200.f, 420.f, 525.f, 40.f, 270.f, 0.f, fDst, 1.3f, 100.f, 200.f, pMonster->Get_Rect().bottom,
					pMonster->Get_Info().fAtk, 10.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.2f, L"Isys_FeatherAttack", { 255, 255, 255 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_ATTACK).back()->Set_Frame(tagFrame{ 0, 12, 0, 0.1, 0. });
			break;
		}

		// 마법진
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonsterAttack>::
			Create_Obj(ATT_JUSTEFFECT, false, pMonster->Get_Info().fX + _fX, fDst - 100.f, 400.f, 400.f, 0.f, 0.f, 0.f, 0.f, 1.0f, 400.f, 400.f, pMonster->Get_Rect().bottom,
				pMonster->Get_Info().fAtk, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.1f, L"Isys_FeatherAttackPos2", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 5, 0, 0.2, 0. });
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_RenderID(BACKGROUNDEFFECT);
	}
}
