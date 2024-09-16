#include "stdafx.h"
#include "Isys_Pattern1.h"

#include "ObjMgr.h"

#include "Player.h"
#include "AI.h"
#include "Monster.h"
#include "MonsterAttack.h"
#include "MonsterAttack2.h"
#include "Effect.h"
#include "SoundMgr.h"

CIsys_Pattern1::CIsys_Pattern1()
	: CState(BOSS_PATTERN1)
{
}

CIsys_Pattern1::~CIsys_Pattern1()
{
}

void CIsys_Pattern1::Update()
{
	// Player�� ��ġ üũ
	CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front();
	float fPlayerX = pPlayer->Get_Info().fX;
	float fPlayerY = pPlayer->Get_Info().fY;

	// ���� �ڽ��� ��ġ üũ
	CMonster* pMonster = GetMonster();
	float fMonsterX = pMonster->Get_Info().fX;
	float fMonsterY = pMonster->Get_Info().fY;

	if (pPlayer)
	{
		// 1�� ����ȭ ���� ����
		if (0 < pMonster->Get_dwTime() && 0 == m_iAttackCount)
		{
			++m_iAttackCount;
			// �̽ý��� �������°� ��
			pMonster->Set_IsImmune(true);
			
		}
		else if (1.4 < pMonster->Get_dwTime() && 1 == m_iAttackCount)
		{
			++m_iAttackCount;
			// ���� ���
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonsterAttack>::
				Create_Obj(ATT_JUSTEFFECT, true, fMonsterX - 80.f, fMonsterY - 200.f, 415.f, 636.f, 0.f, 180.f, 0.f, 0.f, 0.6f, 700, 350.f, pMonster->Get_Rect().bottom,
					pMonster->Get_Info().fAtk, 10.f, 5.f, 1.f, 3.5f, 90.f, 180.f, 1.f, L"Isys_JumpBeam", { 255, 255, 255 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 5, 0, 0.1, 0. });

			// �Ȱ�
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonsterAttack>::
				Create_Obj(ATT_JUSTEFFECT, true, fMonsterX + 50.f, fMonsterY + 50.f, 871.f, 419.f, 0.f, 180.f, 0.f, 0.f, 1.0f, 700, 350.f, pMonster->Get_Rect().bottom,
					pMonster->Get_Info().fAtk, 10.f, 5.f, 1.f, 3.5f, 90.f, 180.f, 1.f, L"Smoke_Jump_FloorTest", { 0, 0, 0 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 9, 0, 0.1, 0. });
			CSoundMgr::Get_Instance()->PlaySoundW(L"isys_wing_01.ogg", SOUND_EFFECT, g_fVolume);

			// ����� �̵��� ���Ͻ���
			pMonster->Set_Pos(NEST_SIZEX * 0.5f, 300.f);

			pMonster->Set_ScaleX(500.f);
			pMonster->Set_ScaleY(500.f);
			pMonster->Set_FrameKey(L"Isys_Flying");
			pMonster->Set_State(BOSS_FLYING);
		}
		// 1Ÿ
		else if (2 < pMonster->Get_dwTime() && 2 == m_iAttackCount)
		{
			++m_iAttackCount;
			
			DropGuideFeather();
		}
		// 1Ÿ ����
		else if (2.5 < pMonster->Get_dwTime() && 3 == m_iAttackCount)
		{
			++m_iAttackCount;

			pMonster->Set_State(BOSS_ONEHANDUP);
			DropGuideFeather();
		}
		// 2Ÿ
		else if (3 < pMonster->Get_dwTime() && 4 == m_iAttackCount)
		{
			++m_iAttackCount;

			DropGuideFeather();
		}
		// 3Ÿ
		else if (3.5 < pMonster->Get_dwTime() && 4 == m_iAttackCount)
		{
			++m_iAttackCount;

			pMonster->Set_State(BOSS_TWOHANDUP);
			DropGuideFeather();
		}
		// 4Ÿ
		else if (4 < pMonster->Get_dwTime() && 5 == m_iAttackCount)
		{
			++m_iAttackCount;

			DropGuideFeather();
		}
		// 5Ÿ
		else if (4.5 < pMonster->Get_dwTime() && 6 == m_iAttackCount)
		{
			++m_iAttackCount;

			pMonster->Set_State(BOSS_ONEHANDUP);
			DropGuideFeather();
		}
		// 6Ÿ
		else if (5 < pMonster->Get_dwTime() && 7 == m_iAttackCount)
		{
			++m_iAttackCount;

			DropGuideFeather();
		}
		// 7Ÿ
		else if (5.5 < pMonster->Get_dwTime() && 8 == m_iAttackCount)
		{
			++m_iAttackCount;

			pMonster->Set_State(BOSS_TWOHANDUP);
			DropGuideFeather();
		}
		// 8Ÿ
		else if (6 < pMonster->Get_dwTime() && 9 == m_iAttackCount)
		{
			++m_iAttackCount;

			DropGuideFeather();
		}
		// 9Ÿ
		else if (6.5 < pMonster->Get_dwTime() && 10 == m_iAttackCount)
		{
			++m_iAttackCount;

			pMonster->Set_State(BOSS_ONEHANDUP);
			DropGuideFeather();
		}
		// 10Ÿ
		else if (7 < pMonster->Get_dwTime() && 11 == m_iAttackCount)
		{
			++m_iAttackCount;

			DropGuideFeather();
		}
		// 11Ÿ
		else if (7.5 < pMonster->Get_dwTime() && 12 == m_iAttackCount)
		{
			++m_iAttackCount;

			pMonster->Set_State(BOSS_TWOHANDUP);
			DropGuideFeather();
		}
		// 12Ÿ
		else if (8 < pMonster->Get_dwTime() && 13 == m_iAttackCount)
		{
			++m_iAttackCount;

			DropGuideFeather();
		}
		// 13Ÿ
		else if (8.5 < pMonster->Get_dwTime() && 14 == m_iAttackCount)
		{
			++m_iAttackCount;

			DropGuideFeather();
		}
		// 14Ÿ
		else if (9 < pMonster->Get_dwTime() && 15 == m_iAttackCount)
		{
			++m_iAttackCount;

			DropGuideFeather();
		}
		// 14Ÿ
		else if (9.5 < pMonster->Get_dwTime() && 16 == m_iAttackCount)
		{
			++m_iAttackCount;

			DropGuideFeather();
		}
		// 15Ÿ
		else if (10 < pMonster->Get_dwTime() && 17 == m_iAttackCount)
		{
			++m_iAttackCount;

			DropGuideFeather();
		}
		// ��Ÿ - �ѹ��� �Ҹ�������
		else if (11.5 < pMonster->Get_dwTime() && 18 == m_iAttackCount)
		{
			++m_iAttackCount;

			// �밢��
			for (int i = 0; i < 8; ++i)
				DropFeather(200.f + (NEST_SIZEX * i * 0.1f), 250.f + (50.f * i), 250.f + (50.f * i));
			for (int i = 0; i < 8; ++i)
				DropFeather(200.f + (NEST_SIZEX * i * 0.1f), 750.f - (50.f * i), 750.f - (50.f * i));
		}
		else if (13 < pMonster->Get_dwTime() && 19 == m_iAttackCount)
		{
			++m_iAttackCount;

			// �ܰ� ����
			for (int i = 0; i < 8; ++i)
				DropFeather(200.f + (NEST_SIZEX * i * 0.1f), 250.f, 250.f);
			for (int i = 0; i < 8; ++i)
				DropFeather(200.f + (NEST_SIZEX * i * 0.1f), 750.f, 750.f);

			// �ܰ� ����
			for (int i = 0; i < 8; ++i)
				DropFeather(200.f, 250.f + (50.f * i), 250.f + (50.f * i));
			for (int i = 0; i < 8; ++i)
				DropFeather(1300.f, 250.f + (50.f * i), 250.f + (50.f * i));
		}

		// ���� ���� ����
		if (16 < pMonster->Get_dwTime())
		{
			Exit();
			pMonster->Set_State(MON_STATE::BOSS_TRACE);
			m_pAI->SetCurState(MON_STATE::BOSS_TRACE);
			m_pAI->GetCurState()->Enter();
		}
	}
}

void CIsys_Pattern1::LateUpdate()
{
}

void CIsys_Pattern1::Enter()
{
	CMonster* pMonster = GetMonster();
	pMonster->Set_dwTime(0);
	m_iAttackCount = 0;
}

void CIsys_Pattern1::Exit()
{
	CMonster* pMonster = GetMonster();

	// ������ ������� ����
	pMonster->Set_ScaleX(371.f);
	pMonster->Set_ScaleY(373.f);

	// �̽ý� �������� ����
	pMonster->Set_IsImmune(false);
	pMonster->Set_dwTime(0);
	m_iAttackCount = 0;
}

void CIsys_Pattern1::DropFeather(float _fX, float _fY, float _fEndY)
{
	CMonster* pMonster = GetMonster();

	// ����
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_WIDEATTACK, CAbstractFactory<CMonsterAttack>::
		Create_Obj(ATT_THRUST, true, _fX, _fY - 1000.f, 70.f, 140.f, 40.f, 270.f, 0.f, _fEndY + 140.f, 3.f, 70.f, 140.f, 0.f,
			pMonster->Get_Info().fAtk, 10.f, 0.f, 0.f, 2.f, 90.f, 0.f, 0.2f, L"Isys_Feather", { 0, 0, 0 }));
	CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_WIDEATTACK).back()->Set_RenderID(GAMEOBJECT);

	// ���� ����
	CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonsterAttack>::
		Create_Obj(ATT_JUSTEFFECT, false, _fX, _fY + 30.f, 420.f, 650.f, 0.f, 0.f, 0.f, 0.f, 0.7f, 400.f, 400.f, pMonster->Get_Rect().bottom,
			pMonster->Get_Info().fAtk, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.1f, L"FeatherLineTest2", { 0, 0, 0 }));
	CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 6, 1, 0.1, 0. });
	CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_RenderID(GAMEOBJECT);

	// ������
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_WIDEATTACK, CAbstractFactory<CMonsterAttack>::
		Create_Obj(ATT_JUSTEFFECT, false, _fX, _fY - 100.f, 400.f, 400.f, 0.f, 0.f, 0.f, 0.f, 0.6f, 400.f, 400.f, pMonster->Get_Rect().bottom,
			pMonster->Get_Info().fAtk, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.1f, L"Isys_FeatherAttackPos2", { 255, 255, 255 }));
	CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_WIDEATTACK).back()->Set_Frame(tagFrame{ 0, 5, 0, 0.1, 0. });
	CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_WIDEATTACK).back()->Set_RenderID(BACKGROUNDEFFECT);
}

// ���� ����߸��� ���
void CIsys_Pattern1::DropGuideFeather()
{
	// Player�� ��ġ üũ
	CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front();
	CMonster* pMonster = GetMonster();
	float fPlayerX = pPlayer->Get_Info().fX;
	float fPlayerY = pPlayer->Get_Info().fY;

	switch (rand() % 3)
	{
	case 0:
		CSoundMgr::Get_Instance()->PlaySoundW(L"isys_atk_01.ogg", SOUND_EFFECT, g_fVolume);
		break;

	case 1:
		CSoundMgr::Get_Instance()->PlaySoundW(L"isys_atk_02.ogg", SOUND_EFFECT, g_fVolume);
		break;

	case 2:
		CSoundMgr::Get_Instance()->PlaySoundW(L"isys_atk_03.ogg", SOUND_EFFECT, g_fVolume);
		break;
	}

	// ����
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_WIDEATTACK, CAbstractFactory<CMonsterAttack>::
		Create_Obj(ATT_THRUST, true, fPlayerX, fPlayerY - 1000.f, 70.f, 140.f, 35.f, 270.f, 0.f, pPlayer->Get_TileCollision().bottom, 12.f, 70.f, 140.f, pMonster->Get_Rect().bottom,
			pMonster->Get_Info().fAtk, 10.f, 0.f, 0.f, 2.f, 90.f, 0.f, 0.2f, L"Isys_Feather", { 0, 0, 0 }));
	CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_WIDEATTACK).back()->Set_RenderID(GAMEOBJECT);

	// ���� ����
	CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonsterAttack>::
		Create_Obj(ATT_JUSTEFFECT, false, fPlayerX + 30.f, pPlayer->Get_TileCollision().bottom - 350.f, 420.f, 650.f, 0.f, 0.f, 0.f, 0.f, 0.7f, 400.f, 400.f, pMonster->Get_Rect().bottom,
			pMonster->Get_Info().fAtk, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.1f, L"FeatherLineTest2", { 0, 0, 0 }));
	CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 6, 1, 0.1, 0. });
	CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_RenderID(GAMEOBJECT);

	// ������
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_WIDEATTACK, CAbstractFactory<CMonsterAttack>::
		Create_Obj(ATT_JUSTEFFECT, false, fPlayerX, pPlayer->Get_TileCollision().bottom - 100.f, 400.f, 400.f, 0.f, 0.f, 0.f, 0.f, 0.6f, 400.f, 400.f, pMonster->Get_Rect().bottom,
			pMonster->Get_Info().fAtk, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.1f, L"Isys_FeatherAttackPos2", { 255, 255, 255 }));
	CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_WIDEATTACK).back()->Set_Frame(tagFrame{ 0, 5, 0, 0.1, 0. });
	CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_WIDEATTACK).back()->Set_RenderID(BACKGROUNDEFFECT);

}
