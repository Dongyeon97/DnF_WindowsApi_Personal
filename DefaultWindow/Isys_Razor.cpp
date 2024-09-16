#include "stdafx.h"
#include "Isys_Razor.h"

#include "ObjMgr.h"

#include "Player.h"
#include "AI.h"
#include "Monster.h"
#include "MonsterAttack.h"
#include "MonsterAttack2.h"
#include "SoundMgr.h"

CIsys_Razor::CIsys_Razor()
	: CState(BOSS_ATTACK4)
{
}

CIsys_Razor::~CIsys_Razor()
{
}

void CIsys_Razor::Update()
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
		if (0 < pMonster->Get_dwTime() && 0 == m_iAttackCount)
		{
			if (0.75 < pMonster->Get_dwTime())
			{
				++m_iAttackCount;

				CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonsterAttack>::
					Create_Obj(ATT_JUSTEFFECT, false, fMonsterX, fMonsterY, 236.f, 227.f, 0, 180.f, 0.f, 0.f, 1.f, 0.f, 0.f, pMonster->Get_Rect().bottom,
						pMonster->Get_Info().fAtk, 10.f, 5.f, 1.f, 3.5f, 90.f, 180.f, 1.f, L"Isys_LaiserStart", { 0, 0, 0 }));
				CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 15, 0, 0.065, 0. });
			}

			if (L"Isys8L" == pMonster->Get_FrameKey())
				pMonster->Set_PosX(4.5f);
			else
				pMonster->Set_PosX(-4.5f);
		}
		// 2타
		else if (0.90 < pMonster->Get_dwTime() && 1 == m_iAttackCount)
		{
			++m_iAttackCount;

			// 좌측 공격 모션중에는 좌측에 피격판정
			if (L"Isys8L" == pMonster->Get_FrameKey())
			{
				// 피격 히트박스 생성
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
					Create_Obj(ATT_THRUST, true, fMonsterX - 300.f, fMonsterY + 100.f, 400.f, 200.f, 0, 180.f, 0.f, 0.f, 1.f, 1000.f, 150.f, pMonster->Get_Rect().bottom,
						pMonster->Get_Info().fAtk, 10.f, 5.f, 1.f, 3.5f, 90.f, 180.f, 0.5f, L"Isys8L", { 0, 0, 0 }));

				CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonsterAttack2>::
					Create_Obj(ATT_JUSTEFFECT, true, fMonsterX - 400.f, fMonsterY - 45.f, 1031.f, 500.f, 0, 180.f, 0.f, 0.f, 1.f, 1031.f, 500.f, pMonster->Get_Rect().bottom,
						pMonster->Get_Info().fAtk, 10.f, 5.f, 1.f, 3.5f, 90.f, 180.f, 1.f, L"Isys_LRazor", { 0, 0, 0 }));
				CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 22, 0, 0.05, 0. });
				CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_RenderID(BACKGROUNDEFFECT);

				CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonsterAttack2>::
					Create_Obj(ATT_JUSTEFFECT, true, fMonsterX - 300.f, fMonsterY + 50.f, 912.f, 358.f, 0, 180.f, 0.f, 0.f, 1.f, 912.f, 358.f, pMonster->Get_Rect().bottom,
						pMonster->Get_Info().fAtk, 10.f, 5.f, 1.f, 3.5f, 90.f, 180.f, 1.f, L"Isys_RazorLineL", { 0, 0, 0 }));
				CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 2, 0, 0.334, 0. });
			}
			else if (L"Isys8" == pMonster->Get_FrameKey())
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
					Create_Obj(ATT_THRUST, true, fMonsterX + 300.f, fMonsterY + 100.f, 400.f, 200.f, 0, 0.f, 0.f, 0.f, 1.f, 1000.f, 150.f, pMonster->Get_Rect().bottom,
						pMonster->Get_Info().fAtk, 10.f, 5.f, 1.f, 3.5f, 90.f, 0.f, 1.f, L"Isys8", { 0, 0, 0 }));

				CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonsterAttack2>::
					Create_Obj(ATT_JUSTEFFECT, true, fMonsterX + 400.f, fMonsterY - 45.f, 1031.f, 500.f, 0, 180.f, 0.f, 0.f, 1.f, 1031.f, 500.f, pMonster->Get_Rect().bottom,
						pMonster->Get_Info().fAtk, 10.f, 5.f, 1.f, 3.5f, 90.f, 180.f, .5f, L"Isys_RRazor", { 0, 0, 0 }));
				CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 22, 0, 0.05, 0. });
				CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_RenderID(BACKGROUNDEFFECT);

				CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonsterAttack2>::
					Create_Obj(ATT_JUSTEFFECT, true, fMonsterX + 300.f, fMonsterY + 50.f, 912.f, 358.f, 0, 180.f, 0.f, 0.f, 1.f, 912.f, 358.f, pMonster->Get_Rect().bottom,
						pMonster->Get_Info().fAtk, 10.f, 5.f, 1.f, 3.5f, 90.f, 180.f, 1.f, L"Isys_RazorLine", { 0, 0, 0 }));
				CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 2, 0, 0.334, 0. });
			}
			CSoundMgr::Get_Instance()->PlaySoundW(L"isys_laser_charge.ogg", SOUND_EFFECT, g_fVolume);
			CSoundMgr::Get_Instance()->PlaySoundW(L"isys_laser_ready.ogg", SOUND_EFFECT2, g_fVolume);
		}

		if (1.45 < pMonster->Get_dwTime() && 2 == m_iAttackCount)
		{
			if (L"Isys8L" == pMonster->Get_FrameKey())
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonsterAttack2>::
					Create_Obj(ATT_JUSTEFFECT, true, fMonsterX - 450.f, fMonsterY + 200.f, 625.f, 200.f, 0, 180.f, 0.f, 0.f, 1.f, 912.f, 358.f, pMonster->Get_Rect().bottom,
						pMonster->Get_Info().fAtk, 10.f, 5.f, 1.f, 3.5f, 90.f, 180.f, 1.f, L"LaiserAfterEffectL", { 0, 0, 0 }));
				CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 21, 0, 0.05, 0. });
			}
			else
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonsterAttack2>::
					Create_Obj(ATT_JUSTEFFECT, true, fMonsterX + 450.f, fMonsterY + 200.f, 625.f, 200.f, 0, 180.f, 0.f, 0.f, 1.f, 912.f, 358.f, pMonster->Get_Rect().bottom,
						pMonster->Get_Info().fAtk, 10.f, 5.f, 1.f, 3.5f, 90.f, 180.f, 1.f, L"LaiserAfterEffect", { 0, 0, 0 }));
				CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 21, 0, 0.05, 0. });
			}
		}
		if (1.5 < pMonster->Get_dwTime())
		{
			CSoundMgr::Get_Instance()->PlaySoundW(L"isys_floor_explo_02.ogg", SOUND_EFFECT, g_fVolume);

			Exit();
			pMonster->Set_State(MON_STATE::BOSS_TRACE);
			m_pAI->SetCurState(MON_STATE::BOSS_TRACE);
			m_pAI->GetCurState()->Enter();
		}
	}
}

void CIsys_Razor::LateUpdate()
{
}

void CIsys_Razor::Enter()
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

		if (fPlayerX < fMonsterX)
			pMonster->Set_FrameKey(L"Isys8L");
		else
			pMonster->Set_FrameKey(L"Isys8");
	}
}

void CIsys_Razor::Exit()
{
	CMonster* pMonster = GetMonster();

	pMonster->Set_dwTime(0);
	m_iAttackCount = 0;
}