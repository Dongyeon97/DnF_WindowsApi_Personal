#include "stdafx.h"
#include "Isys_Appear.h"

#include "ObjMgr.h"

#include "Player.h"
#include "Monster.h"
#include "AI.h"
#include "Effect.h"
#include "MonsterAttack.h"
#include "MonsterAttack2.h"
#include "SoundMgr.h"

CIsys_Appear::CIsys_Appear()
	: CState(BOSS_APPEAR)
{
}

CIsys_Appear::~CIsys_Appear()
{
}

void CIsys_Appear::Update()
{
	CMonster* pMonster = GetMonster();

	float fMonsterX = pMonster->Get_Info().fX;
	float fMonsterY = pMonster->Get_Info().fY;

	// 등장 스프라이트 출력
	if (0 < pMonster->Get_dwTime() && 0 == m_iAttackCount)
	{
		++m_iAttackCount;
		/*pMonster->Set_FrameKey(L"Isys_FlyingReady");
		pMonster->Set_ScaleX(160.f);
		pMonster->Set_ScaleY(304.f);

		pMonster->Set_Frame(tagFrame{ 0, 7, 0, 0.3, 0.});*/

		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonsterAttack>::
			Create_Obj(ATT_JUSTEFFECT, true, fMonsterX - 117.f, fMonsterY - 200.f, 817.f, 1011.f, 0.f, 180.f, 0.f, 0.f, 4.f, 700, 350.f, pMonster->Get_Rect().bottom,
				pMonster->Get_Info().fAtk, 10.f, 5.f, 1.f, 3.5f, 90.f, 180.f, 1.f, L"Isys_MeetFeatherEffect", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 29, 0, 0.1334, 0. });
		CSoundMgr::Get_Instance()->PlaySoundW(L"isys_meet_eyelight.ogg", SOUND_EFFECT, g_fVolume);


		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonsterAttack2>::
			Create_Obj(ATT_JUSTEFFECT, true, fMonsterX - 82.f, fMonsterY - 170.f, 676.f, 572.f, 0.f, 180.f, 0.f, 0.f, 4.f, 700, 350.f, pMonster->Get_Rect().bottom,
				pMonster->Get_Info().fAtk, 10.f, 5.f, 1.f, 3.5f, 90.f, 180.f, 1.f, L"Isys_WingMeet", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 36, 0, 0.11, 0. });
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_RenderID(BACKGROUNDEFFECT);

		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonsterAttack>::
			Create_Obj(ATT_JUSTEFFECT, true, fMonsterX - 230.f, fMonsterY - 200.f, 672.f, 693.f, 0.f, 180.f, 0.f, 0.f, 1.f, 700, 350.f, pMonster->Get_Rect().bottom,
				pMonster->Get_Info().fAtk, 10.f, 5.f, 1.f, 3.5f, 90.f, 180.f, 1.f, L"Isys_MeetLightning", { 0, 0, 0 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 11, 0, 0.085, 0. });
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_RenderID(BACKGROUNDEFFECT);
		CSoundMgr::Get_Instance()->PlaySoundW(L"isys_meet_lightning.ogg", SOUND_EFFECT2, g_fVolume);
	}

	if (4 < pMonster->Get_dwTime())
	{
		CSoundMgr::Get_Instance()->PlaySoundW(L"isys_meet_wing_disappear.ogg", SOUND_EFFECT3, g_fVolume);
		Exit();
		pMonster->Set_State(MON_STATE::BOSS_TRACE);
		m_pAI->SetCurState(MON_STATE::BOSS_TRACE);
		m_pAI->GetCurState()->Enter();
	}
}

void CIsys_Appear::LateUpdate()
{
}

void CIsys_Appear::Enter()
{
	CMonster* pMonster = GetMonster();
	pMonster->Set_IsImmune(true);
	pMonster->Set_dwTime(0);
	m_iAttackCount = 0;
}

void CIsys_Appear::Exit()
{
	CMonster* pMonster = GetMonster();

	// 무적 해제
	pMonster->Set_IsImmune(false);
	pMonster->Set_dwTime(0);
	m_iAttackCount = 0;
}
