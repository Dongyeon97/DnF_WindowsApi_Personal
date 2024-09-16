#include "stdafx.h"
#include "Isys_PrePattern.h"

#include "ObjMgr.h"
#include "SoundMgr.h"

#include "Player.h"
#include "AI.h"
#include "Monster.h"
#include "MonsterAttack.h"
#include "Effect.h"
#include "Isys.h"

CIsys_PrePattern::CIsys_PrePattern()
	: CState(BOSS_PREPATTERN)
{
}

CIsys_PrePattern::~CIsys_PrePattern()
{
}

void CIsys_PrePattern::Update()
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
		// 날갯짓 모션
		if (0 < pMonster->Get_dwTime() && 0 == m_iAttackCount)
		{
			pMonster->Set_IsImmune(true);

			++m_iAttackCount;
			// 날개 생성
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonsterAttack>::
				Create_Obj(ATT_JUSTEFFECT, true, fMonsterX - 45.f, fMonsterY - 115.f, 702.f, 524.f, 0.f, 180.f, 0.f, 0.f, 1.4f, 700, 350.f, pMonster->Get_Rect().bottom,
					pMonster->Get_Info().fAtk, 10.f, 5.f, 1.f, 3.5f, 90.f, 180.f, 1.f, L"Isys_JumpWing", { 255, 0, 255 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 6, 0, 0.2, 0. });
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_RenderID(BACKGROUNDEFFECT);
		}
		Exit();
		pMonster->Set_dwTime(0);
		pMonster->Set_State(MON_STATE::BOSS_PATTERN1);
		m_pAI->SetCurState(MON_STATE::BOSS_PATTERN1);
		m_pAI->GetCurState()->Enter();
	}
}

void CIsys_PrePattern::LateUpdate()
{
}

void CIsys_PrePattern::Enter()
{
	CMonster* pMonster = GetMonster();
	pMonster->Set_dwTime(0);
	m_iAttackCount = 0;
	if (pMonster)
	{
		pMonster->Set_FrameKey(L"Isys_FlyingReady2");
		CSoundMgr::Get_Instance()->PlaySoundW(L"isys_p1_start.ogg", SOUND_EFFECT, g_fVolume);
		CSoundMgr::Get_Instance()->PlaySoundW(L"isys_skill_06.ogg", SOUND_EFFECT2, g_fVolume);
	}
}

void CIsys_PrePattern::Exit()
{
	CMonster* pMonster = GetMonster();

	pMonster->Set_dwTime(0);
	m_iAttackCount = 0;
}
