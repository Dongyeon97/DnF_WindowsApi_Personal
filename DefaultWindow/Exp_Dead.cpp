#include "stdafx.h"
#include "Exp_Dead.h"

#include "ObjMgr.h"

#include "Player.h"
#include "Monster.h"
#include "AI.h"
#include "SoundMgr.h"

CExp_Dead::CExp_Dead()
	: CState(MON_DEAD)
{
}

CExp_Dead::~CExp_Dead()
{
}

void CExp_Dead::Update()
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
		if (0 < pMonster->Get_dwTime() && 0 == m_iAttackCount)
		{
			++m_iAttackCount;
			// CSoundMgr::Get_Instance()->PlaySoundW(L"isys_die.ogg", SOUND_EFFECT, g_fVolume);
		}
		if (1.2 < pMonster->Get_dwTime() && 1 == m_iAttackCount)
		{
			Exit();
			pMonster->Set_dwTime(0);
			m_iAttackCount = 0;

			pMonster->Set_Dead(true);
		}
	}
	// 누더기
	else if (L"LNudeogi" == pMonster->Get_FrameKey() || L"RNudeogi" == pMonster->Get_FrameKey())
	{
		if (0 < pMonster->Get_dwTime() && 0 == m_iAttackCount)
		{
			++m_iAttackCount;
			// 사망 소리
			// CSoundMgr::Get_Instance()->PlaySoundW(L"isys_die.ogg", SOUND_EFFECT, g_fVolume);
		}
		if (1.0 < pMonster->Get_dwTime() && 1 == m_iAttackCount)
		{
			Exit();
			pMonster->Set_dwTime(0);
			m_iAttackCount = 0;

			pMonster->Set_Dead(true);
		}
	}
	// 장난감 병정
	else if (L"LToy" == pMonster->Get_FrameKey() || L"RToy" == pMonster->Get_FrameKey())
	{
		if (0 < pMonster->Get_dwTime() && 0 == m_iAttackCount)
		{
			++m_iAttackCount;
			// 사망 소리
			// CSoundMgr::Get_Instance()->PlaySoundW(L"isys_die.ogg", SOUND_EFFECT, g_fVolume);
		}
		if (1.0 < pMonster->Get_dwTime() && 1 == m_iAttackCount)
		{
			Exit();
			pMonster->Set_dwTime(0);
			m_iAttackCount = 0;

			pMonster->Set_Dead(true);
		}
	}
}

void CExp_Dead::LateUpdate()
{
}

void CExp_Dead::Enter()
{
	CMonster* pMonster = GetMonster();
	// pMonster->Set_dwTime(0);
	m_iAttackCount = 0;
}

void CExp_Dead::Exit()
{
	CMonster* pMonster = GetMonster();

	// pMonster->Set_dwTime(0);
	m_iAttackCount = 0;
}
