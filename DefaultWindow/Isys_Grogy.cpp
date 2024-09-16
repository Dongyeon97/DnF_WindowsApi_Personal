#include "stdafx.h"
#include "Isys_Grogy.h"

#include "ObjMgr.h"

#include "Player.h"
#include "AI.h"
#include "Monster.h"
#include "MonsterAttack.h"
#include "MonsterAttack2.h"
#include "Effect.h"
#include "SoundMgr.h"

CIsys_Grogy::CIsys_Grogy()
	: CState(BOSS_GROGY)
{
}

CIsys_Grogy::~CIsys_Grogy()
{
}

void CIsys_Grogy::Update()
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
		if (0 < pMonster->Get_dwTime() && 0 == m_iAttackCount)
		{
			++m_iAttackCount;

			// 안개
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonsterAttack>::
				Create_Obj(ATT_JUSTEFFECT, true, fMonsterX + 50.f, fMonsterY + 50.f, 871.f, 419.f, 0.f, 180.f, 0.f, 0.f, 1.0f, 700, 350.f, pMonster->Get_Rect().bottom,
					pMonster->Get_Info().fAtk, 10.f, 5.f, 1.f, 3.5f, 90.f, 180.f, 1.f, L"Smoke_Jump_FloorTest", { 0, 0, 0 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 9, 0, 0.1, 0. });
			CSoundMgr::Get_Instance()->PlaySoundW(L"isys_dmg_02.ogg", SOUND_EFFECT, g_fVolume);

			// 가운데로 이동후 그로기모션
			pMonster->Set_Pos(NEST_SIZEX * 0.5f, 300.f);

			pMonster->Set_ScaleX(371.f);
			pMonster->Set_ScaleY(373.f);
			pMonster->Set_State(BOSS_GROGY);

			// 플레이어에게 그로기 버프 10초 부여
			dynamic_cast<CPlayer*>(pPlayer)->Set_GrogyBuff(20);
		}

		// 그로기 종료 조건
		if (10 < pMonster->Get_dwTime())
		{
			Exit();
			pMonster->Set_State(MON_STATE::BOSS_TRACE);
			m_pAI->SetCurState(MON_STATE::BOSS_TRACE);
			m_pAI->GetCurState()->Enter();
		}
	}
}

void CIsys_Grogy::LateUpdate()
{
}

void CIsys_Grogy::Enter()
{
	// Player의 위치 체크
	CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front();
	float fPlayerX = pPlayer->Get_Info().fX;
	float fPlayerY = pPlayer->Get_Info().fY;

	// 몬스터 자신의 위치 체크
	CMonster* pMonster = GetMonster();
	float fMonsterX = pMonster->Get_Info().fX;
	float fMonsterY = pMonster->Get_Info().fY;

	pMonster->Set_dwTime(0);
	m_iAttackCount = 0;

	if (fPlayerX < fMonsterX)
		pMonster->Set_FrameKey(L"Isys_LAttacked");
	else
		pMonster->Set_FrameKey(L"Isys_RAttacked");
}

void CIsys_Grogy::Exit()
{
	CMonster* pMonster = GetMonster();
	pMonster->Set_dwTime(0);
	m_iAttackCount = 0;
}