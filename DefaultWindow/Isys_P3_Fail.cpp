#include "stdafx.h"
#include "Isys_P3_Fail.h"
#include "ObjMgr.h"

#include "Player.h"
#include "AI.h"
#include "Monster.h"
#include "MonsterAttack.h"
#include "MonsterAttack2.h"
#include "Effect.h"
#include "SoundMgr.h"
#include "NonAlpha.h"

CIsys_P3_Fail::CIsys_P3_Fail()
	: CState(BOSS_PATTERN3_FAIL)
{

}

CIsys_P3_Fail::~CIsys_P3_Fail()
{
}

void CIsys_P3_Fail::Update()
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
			// 맵 가운데로 와서 내려찍는 모션
			pMonster->Set_ScaleX(371.f);
			pMonster->Set_ScaleY(373.f);
			pMonster->Set_FrameKey(L"Isys_FlyingReady2");
			pMonster->Set_State(BOSS_APPEAR);
			pMonster->Set_Pos(NEST_SIZEX * 0.5f, 500.f);

			fMonsterX = pMonster->Get_Info().fX;
			fMonsterY = pMonster->Get_Info().fY;

			for (int i = 0; i < 12; ++i)
			{
				Making_Thunder(float(rand() % NEST_SIZEX), float(200 + rand() % 600), 1.f);
			}
			// 날개 생성
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonsterAttack>::
				Create_Obj(ATT_JUSTEFFECT, true, fMonsterX - 45.f, fMonsterY - 115.f, 702.f, 524.f, 0.f, 180.f, 0.f, 0.f, 2.5f, 700, 350.f, pMonster->Get_Rect().bottom,
					pMonster->Get_Info().fAtk, 10.f, 5.f, 1.f, 3.5f, 90.f, 180.f, 1.f, L"Isys_JumpWing", { 255, 0, 255 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 0, 0, 2.5, 0. });
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_RenderID(BACKGROUNDEFFECT);

			// MeetLightning
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonsterAttack>::
				Create_Obj(ATT_JUSTEFFECT, true, fMonsterX - 230.f, fMonsterY - 200.f, 672.f, 693.f, 0.f, 180.f, 0.f, 0.f, 1.f, 700, 350.f, pMonster->Get_Rect().bottom,
					pMonster->Get_Info().fAtk, 10.f, 5.f, 1.f, 3.5f, 90.f, 180.f, 1.f, L"Isys_MeetLightning", { 0, 0, 0 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 11, 0, 0.085, 0. });
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_RenderID(BACKGROUNDEFFECT);
			CSoundMgr::Get_Instance()->PlaySoundW(L"isys_meet_lightning.ogg", SOUND_EFFECT2, g_fVolume);

			// 지진1
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
				Create_Obj(ATT_LEVITATE, false, fMonsterX, fMonsterY + 150.f, 420.f, 167.f, 0, 0.f, 0.f, 0.f, 1.25f, 420.f, 167.f, pMonster->Get_TileCollision().bottom,
					pMonster->Get_Info().fAtk, 1.f, 4.f, 2.f, 5.f, 90.f, 0.f, 0.5f, L"Isys_ChopFirstFloor", { 255, 255, 255 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_ATTACK).back()->Set_RenderID(BACKGROUNDEFFECT);
			CSoundMgr::Get_Instance()->PlaySoundW(L"isys_wing_01.ogg", SOUND_EFFECT, g_fVolume + 0.2f);

			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
				Create_Obj(ATT_LEVITATE, true, fPlayerX, pPlayer->Get_TileCollision().bottom - 32, NEST_SIZEX, NEST_SIZEY, 0.f, 0.f, 0.f, 0.f, 1.f, NEST_SIZEX, NEST_SIZEY, pPlayer->Get_TileCollision().bottom - 32,
					pMonster->Get_Info().fAtk, 10000.f, 0.f, 0.f, 10.f, 90.f, 0.f, 0.2f, L"Isys_Awaken", { 0, 0, 0 }));
		}
		else if (1.25 < pMonster->Get_dwTime() && 1 == m_iAttackCount)
		{
			++m_iAttackCount;
			// 지진2
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
				Create_Obj(ATT_LEVITATE, false, fMonsterX, fMonsterY + 150.f, 600.f, 237.f, 0, 0.f, 0.f, 0.f, 1.25f, 600.f, 237.f, pMonster->Get_TileCollision().bottom,
					pMonster->Get_Info().fAtk, 1.f, 4.f, 2.f, 5.f, 90.f, 0.f, 0.5f, L"Isys_ChopSecondFloor", { 255, 255, 255 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_ATTACK).back()->Set_RenderID(BACKGROUNDEFFECT);
		}
		// 패턴 종료 조건
		if (2.5 < pMonster->Get_dwTime())
		{
			Exit();
			pMonster->Set_State(MON_STATE::BOSS_PATTERN3);
			m_pAI->SetCurState(MON_STATE::BOSS_PATTERN3);
			m_pAI->GetCurState()->Enter();
			m_pAI->GetCurState()->Set_PatternCount(0);
		}
	}
}

void CIsys_P3_Fail::LateUpdate()
{
}

void CIsys_P3_Fail::Enter()
{
	CMonster* pMonster = GetMonster();
	pMonster->Set_dwTime(0);
	m_iAttackCount = 0;
}

void CIsys_P3_Fail::Exit()
{
	CMonster* pMonster = GetMonster();
	pMonster->Set_dwTime(0);
	m_iAttackCount = 0;
}

void CIsys_P3_Fail::Making_Thunder(float _fX, float _fY, float _fLifeTime)
{
	// 번개 이펙트
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_WIDEATTACK, CAbstractFactory<CMonsterAttack>::
		Create_Obj(ATT_JUSTEFFECT, false, _fX, _fY, 672.f, 693.f, 0.f, 0.f, 0.f, 0.f, _fLifeTime, 150.f, 300.f, 0.f,
			0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, L"Isys_MeetLightning", { 0, 0, 0 }));
	CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_WIDEATTACK).back()->Set_Frame(tagFrame{ 0, 11, 0, 0.085, 0. });
	CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_WIDEATTACK).back()->Set_RenderID(GAMEOBJECT);
}
