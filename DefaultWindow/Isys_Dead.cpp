#include "stdafx.h"
#include "Isys_Dead.h"

#include "ObjMgr.h"
#include "SoundMgr.h"

#include "Player.h"
#include "AI.h"
#include "Monster.h"
#include "MonsterAttack.h"

CIsys_Dead::CIsys_Dead()
	: CState(BOSS_DEAD)
{
}

CIsys_Dead::~CIsys_Dead()
{
}

void CIsys_Dead::Update()
{
	// Player�� ��ġ üũ
	CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front();

	// ���� �ڽ��� ��ġ üũ
	CMonster* pMonster = GetMonster();

	if (pPlayer)
	{
		// ��ī��
		if (L"LSkasa" == pMonster->Get_FrameKey() || L"RSkasa" == pMonster->Get_FrameKey())
		{
			if (0 < pMonster->Get_dwTime() && 0 == m_iAttackCount)
			{
				++m_iAttackCount;

				// ��� ����
				CSoundMgr::Get_Instance()->PlaySoundW(L"SkasaDead.wav", SOUND_EFFECT, g_fVolume);
			}

			if (3 < pMonster->Get_dwTime() && 1 == m_iAttackCount)
			{
				Exit();
				CSoundMgr::Get_Instance()->StopAll();
				pMonster->Set_dwTime(0);
				m_iAttackCount = 0;

				pMonster->Set_Dead(true);
			}
		}
		// �̽ý�
		else
		{
			if (0 < pMonster->Get_dwTime() && 0 == m_iAttackCount)
			{
				++m_iAttackCount;

				CSoundMgr::Get_Instance()->PlaySoundW(L"isys_die.ogg", SOUND_EFFECT, g_fVolume);
			}

			if (4.8 < pMonster->Get_dwTime() && 1 == m_iAttackCount)
			{
				Exit();
				CSoundMgr::Get_Instance()->StopAll();
				pMonster->Set_dwTime(0);
				m_iAttackCount = 0;

				pMonster->Set_Dead(true);
			}
		}
	}
}

void CIsys_Dead::LateUpdate()
{
}

void CIsys_Dead::Enter()
{
	CMonster* pMonster = GetMonster();
	// pMonster->Set_dwTime(0);
	m_iAttackCount = 0;
	if (pMonster)
	{
		// Player�� ��ġ üũ
		CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front();
		float fPlayerX = pPlayer->Get_Info().fX;
		float fPlayerY = pPlayer->Get_Info().fY;

		// ���� �ڽ��� ��ġ üũ
		CMonster* pMonster = GetMonster();
		float fMonsterX = pMonster->Get_Info().fX;
		float fMonsterY = pMonster->Get_Info().fY;

		// ��ī��
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
				pMonster->Set_FrameKey(L"Isys_LAttacked");
			else
				pMonster->Set_FrameKey(L"Isys_RAttacked");
		}
	}
}

void CIsys_Dead::Exit()
{
	CMonster* pMonster = GetMonster();

	// pMonster->Set_dwTime(0);
	m_iAttackCount = 0;
}
