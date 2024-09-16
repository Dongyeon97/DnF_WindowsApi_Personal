#include "stdafx.h"
#include "Isys_Pattern2.h"
#include "ObjMgr.h"

#include "Player.h"
#include "AI.h"
#include "Monster.h"
#include "MonsterAttack.h"
#include "MonsterAttack2.h"
#include "Effect.h"
#include "SoundMgr.h"
#include "NonAlpha.h"

CIsys_Pattern2::CIsys_Pattern2()
	: CState(BOSS_PATTERN2)
{
}

CIsys_Pattern2::~CIsys_Pattern2()
{
}

void CIsys_Pattern2::Update()
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
		// 2차 광폭화 패턴 진입
		if (0 < pMonster->Get_dwTime() && 0 == m_iAttackCount)
		{
			++m_iAttackCount;
			// 이시스가 무적상태가 됨
			pMonster->Set_IsImmune(true);
			
			pMonster->Set_ScaleX(160.f);
			pMonster->Set_ScaleY(304.f);
			pMonster->Set_FrameKey(L"Isys_FlyingReady");
			pMonster->Set_State(BOSS_FLYINGREADY);
			CSoundMgr::Get_Instance()->PlaySoundW(L"isys_skill_06.ogg", SOUND_EFFECT3, g_fVolume + 0.2f);
		}
		else if (1.2 < pMonster->Get_dwTime() && 1 == m_iAttackCount)
		{
			++m_iAttackCount;

			// 날개 생성
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonsterAttack>::
				Create_Obj(ATT_JUSTEFFECT, true, fMonsterX - 45.f, fMonsterY - 115.f, 702.f, 524.f, 0.f, 180.f, 0.f, 0.f, 0.9f, 700, 350.f, pMonster->Get_Rect().bottom,
					pMonster->Get_Info().fAtk, 10.f, 5.f, 1.f, 3.5f, 90.f, 180.f, 1.f, L"Isys_JumpWing", { 255, 0, 255 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 6, 0, 0.125, 0. });
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_RenderID(BACKGROUNDEFFECT);

			pMonster->Set_ScaleX(371.f);
			pMonster->Set_ScaleY(373.f);
			pMonster->Set_FrameKey(L"Isys_FlyingReady2");
			pMonster->Set_State(BOSS_APPEAR);
		}
		else if (2.1 < pMonster->Get_dwTime() && 2 == m_iAttackCount)
		{
			++m_iAttackCount;
			// 점프 모션
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonsterAttack>::
				Create_Obj(ATT_JUSTEFFECT, true, fMonsterX - 80.f, fMonsterY - 200.f, 415.f, 636.f, 0.f, 180.f, 0.f, 0.f, 0.6f, 700, 350.f, pMonster->Get_Rect().bottom,
					pMonster->Get_Info().fAtk, 10.f, 5.f, 1.f, 3.5f, 90.f, 180.f, 1.f, L"Isys_JumpBeam", { 255, 255, 255 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 5, 0, 0.1, 0. });

			// 안개
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonsterAttack>::
				Create_Obj(ATT_JUSTEFFECT, true, fMonsterX + 50.f, fMonsterY + 50.f, 871.f, 419.f, 0.f, 180.f, 0.f, 0.f, 1.0f, 700, 350.f, pMonster->Get_Rect().bottom,
					pMonster->Get_Info().fAtk, 10.f, 5.f, 1.f, 3.5f, 90.f, 180.f, 1.f, L"Smoke_Jump_FloorTest", { 0, 0, 0 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 9, 0, 0.1, 0. });
			CSoundMgr::Get_Instance()->PlaySoundW(L"isys_wing_01.ogg", SOUND_EFFECT, g_fVolume + 0.2f);
			CSoundMgr::Get_Instance()->PlaySoundW(L"isys_meet_wing_disappear.ogg", SOUND_EFFECT2, g_fVolume + 0.2f);
			CSoundMgr::Get_Instance()->PlaySoundW(L"isys_meet_whirlwind.ogg", SOUND_EFFECT3, g_fVolume + 0.2f);

			// 가운데로 이동후 패턴시전
			pMonster->Set_Pos(NEST_SIZEX * 0.5f, 300.f);

			pMonster->Set_ScaleX(500.f);
			pMonster->Set_ScaleY(500.f);
			pMonster->Set_FrameKey(L"Isys_Flying");
			pMonster->Set_State(BOSS_FLYING);
		}
		// 1타
		else if (4 < pMonster->Get_dwTime() && 3 == m_iAttackCount)
		{
			++m_iAttackCount;
			for (int i = 0; i < 4; ++i)
			{
				Making_vortex(fMonsterX + rand() % 100, fMonsterY + 200.f, 3.f, rand() % 360, 8.f);
				Making_Thunder(rand() % (NEST_SIZEX), rand() % (NEST_SIZEY), 1.f);
			}
			CSoundMgr::Get_Instance()->PlaySoundW(L"isys_meet_whirlwind.ogg", SOUND_EFFECT3, g_fVolume + 0.2f);
		}
		// 1타 폭발
		else if (5 < pMonster->Get_dwTime() && 4 == m_iAttackCount)
		{
			++m_iAttackCount;
			for (int i = 0; i < 4; ++i)
			{
				Making_vortex(fMonsterX + rand() % 100, fMonsterY + 200.f, 3.f, rand() % 360, 8.f);
				Making_Thunder(rand() % (NEST_SIZEX), rand() % (NEST_SIZEY), 1.f);
			}
		}
		// 2타
		else if (6 < pMonster->Get_dwTime() && 5 == m_iAttackCount)
		{
			++m_iAttackCount;
			for (int i = 0; i < 4; ++i)
			{
				Making_vortex(fMonsterX + rand() % 100, fMonsterY + 200.f, 3.f, rand() % 360, 8.f);
				Making_Thunder(rand() % (NEST_SIZEX), rand() % (NEST_SIZEY), 1.f);
			}
			CSoundMgr::Get_Instance()->PlaySoundW(L"isys_meet_whirlwind.ogg", SOUND_EFFECT3, g_fVolume + 0.2f);
		}
		// 3타
		else if (7 < pMonster->Get_dwTime() && 6 == m_iAttackCount)
		{
			++m_iAttackCount;
			for (int i = 0; i < 4; ++i)
			{
				Making_vortex(fMonsterX + rand() % 100, fMonsterY + 200.f, 3.f, rand() % 360, 8.f);
				Making_Thunder(rand() % (NEST_SIZEX), rand() % (NEST_SIZEY), 1.f);
			}
		}
		// 4타
		else if (8 < pMonster->Get_dwTime() && 7 == m_iAttackCount)
		{
			++m_iAttackCount;
			for (int i = 0; i < 4; ++i)
			{
				Making_vortex(fMonsterX + rand() % 100, fMonsterY + 200.f, 3.f, rand() % 360, 8.f);
				Making_Thunder(rand() % (NEST_SIZEX), rand() % (NEST_SIZEY), 1.f);
			}
			CSoundMgr::Get_Instance()->PlaySoundW(L"isys_meet_whirlwind.ogg", SOUND_EFFECT3, g_fVolume + 0.2f);
		}
		// 5타
		else if (9 < pMonster->Get_dwTime() && 8 == m_iAttackCount)
		{
			++m_iAttackCount;
			for (int i = 0; i < 4; ++i)
			{
				Making_vortex(fMonsterX + rand() % 100, fMonsterY + 200.f, 3.f, rand() % 360, 8.f);
				Making_Thunder(rand() % (NEST_SIZEX), rand() % (NEST_SIZEY), 1.f);
			}
		}
		// 6타
		else if (10 < pMonster->Get_dwTime() && 9 == m_iAttackCount)
		{
			++m_iAttackCount;
			for (int i = 0; i < 4; ++i)
			{
				Making_vortex(fMonsterX + rand() % 100, fMonsterY + 200.f, 3.f, rand() % 360, 8.f);
				Making_Thunder(rand() % (NEST_SIZEX), rand() % (NEST_SIZEY), 1.f);
			}
			CSoundMgr::Get_Instance()->PlaySoundW(L"isys_meet_whirlwind.ogg", SOUND_EFFECT3, g_fVolume + 0.2f);
		}
		// 7타
		else if (11 < pMonster->Get_dwTime() && 10 == m_iAttackCount)
		{
			++m_iAttackCount;
			for (int i = 0; i < 4; ++i)
			{
				Making_vortex(fMonsterX + rand() % 100, fMonsterY + 200.f, 3.f, rand() % 360, 8.f);
				Making_Thunder(rand() % (NEST_SIZEX), rand() % (NEST_SIZEY), 1.f);
			}
		}
		// 8타
		else if (12 < pMonster->Get_dwTime() && 11 == m_iAttackCount)
		{
			++m_iAttackCount;
			for (int i = 0; i < 4; ++i)
			{
				Making_vortex(fMonsterX + rand() % 100, fMonsterY + 200.f, 3.f, rand() % 360, 8.f);
				Making_Thunder(rand() % (NEST_SIZEX), rand() % (NEST_SIZEY), 1.f);
			}
			CSoundMgr::Get_Instance()->PlaySoundW(L"isys_meet_whirlwind.ogg", SOUND_EFFECT3, g_fVolume + 0.2f);
		}
		// 9타
		else if (13 < pMonster->Get_dwTime() && 12 == m_iAttackCount)
		{
			++m_iAttackCount;
			for (int i = 0; i < 4; ++i)
			{
				Making_vortex(fMonsterX + rand() % 100, fMonsterY + 200.f, 3.f, rand() % 360, 8.f);
				Making_Thunder(rand() % (NEST_SIZEX), rand() % (NEST_SIZEY), 1.f);
			}
		}
		// 10타
		else if (14 < pMonster->Get_dwTime() && 13 == m_iAttackCount)
		{
			++m_iAttackCount;
			for (int i = 0; i < 4; ++i)
			{
				Making_vortex(fMonsterX + rand() % 100, fMonsterY + 200.f, 3.f, rand() % 360, 8.f);
				Making_Thunder(rand() % (NEST_SIZEX), rand() % (NEST_SIZEY), 1.f);
			}
			CSoundMgr::Get_Instance()->PlaySoundW(L"isys_meet_whirlwind.ogg", SOUND_EFFECT3, g_fVolume + 0.2f);
		}
		// 11타
		else if (15 < pMonster->Get_dwTime() && 14 == m_iAttackCount)
		{
			++m_iAttackCount;
			for (int i = 0; i < 4; ++i)
			{
				Making_vortex(fMonsterX + rand() % 100, fMonsterY + 200.f, 3.f, rand() % 360, 8.f);
				Making_Thunder(rand() % (NEST_SIZEX), rand() % (NEST_SIZEY), 1.f);
			}
		}
		// 12타
		else if (16 < pMonster->Get_dwTime() && 15 == m_iAttackCount)
		{
			++m_iAttackCount;
			for (int i = 0; i < 4; ++i)
			{
				Making_vortex(fMonsterX + rand() % 100, fMonsterY + 200.f, 3.f, rand() % 360, 8.f);
				Making_Thunder(rand() % (NEST_SIZEX), rand() % (NEST_SIZEY), 1.f);
			}
			CSoundMgr::Get_Instance()->PlaySoundW(L"isys_meet_whirlwind.ogg", SOUND_EFFECT3, g_fVolume + 0.2f);
		}

		// 패턴 종료 조건
		if (17.5 < pMonster->Get_dwTime())
		{
			Exit();
			pMonster->Set_State(MON_STATE::BOSS_TRACE);
			m_pAI->SetCurState(MON_STATE::BOSS_TRACE);
			m_pAI->GetCurState()->Enter();
		}
	}
}

void CIsys_Pattern2::LateUpdate()
{
}

void CIsys_Pattern2::Enter()
{
	CMonster* pMonster = GetMonster();
	pMonster->Set_dwTime(0);
	m_iAttackCount = 0;
}

void CIsys_Pattern2::Exit()
{
	CMonster* pMonster = GetMonster();

	// 사이즈 원래대로 돌림
	pMonster->Set_ScaleX(371.f);
	pMonster->Set_ScaleY(373.f);

	// 이시스 무적상태 해제
	pMonster->Set_IsImmune(false);
	pMonster->Set_dwTime(0);
	m_iAttackCount = 0;
}

void CIsys_Pattern2::Making_vortex(float _fX, float _fY, float _fSpeed, float _fAngle, float _fLifeTime)
{
	CMonster* pMonster = GetMonster();

	// 회오리 히트박스
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_WIDEATTACK, CAbstractFactory<CMonsterAttack>::
		Create_Obj(ATT_THRUST, false, _fX + 70.f, _fY + 50.f, 150.f, 300.f, _fSpeed, _fAngle, 0.f, 0.f, _fLifeTime, 150.f, 300.f, 0.f,
			pMonster->Get_Info().fAtk, 10.f, 0.f, 0.f, 2.f, 90.f, 0.f, 0.2f, L"Vortex_Hitbox", { 0, 0, 0 }));

	// 회오리 이펙트
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_WIDEATTACK, CAbstractFactory<CMonsterAttack>::
		Create_Obj(ATT_JUSTEFFECT, false, _fX, _fY, 393.f, 451.f, _fSpeed, _fAngle, 0.f, 0.f, _fLifeTime, 150.f, 300.f, 0.f,
			pMonster->Get_Info().fAtk, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.2f, L"Smoke_Up2", { 0, 0, 0 }));
	CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_WIDEATTACK).back()->Set_Frame(tagFrame{ 0, 8, 0, 0.2, 0. });
	CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_WIDEATTACK).back()->Set_RenderID(GAMEOBJECT);
}

void CIsys_Pattern2::Making_Thunder(float _fX, float _fY, float _fLifeTime)
{
	// 번개 이펙트
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_WIDEATTACK, CAbstractFactory<CMonsterAttack>::
		Create_Obj(ATT_JUSTEFFECT, false, _fX, _fY, 672.f, 693.f, 0.f, 0.f, 0.f, 0.f, _fLifeTime, 150.f, 300.f, 0.f,
			0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, L"Isys_MeetLightning", { 0, 0, 0 }));
	CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_WIDEATTACK).back()->Set_Frame(tagFrame{ 0, 11, 0, 0.085, 0. });
	CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_WIDEATTACK).back()->Set_RenderID(GAMEOBJECT);
}