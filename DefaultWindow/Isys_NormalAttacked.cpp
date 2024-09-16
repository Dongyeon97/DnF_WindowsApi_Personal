#include "stdafx.h"
#include "Isys_NormalAttacked.h"

#include "ObjMgr.h"
#include "TimeMgr.h"

#include "Player.h"
#include "Monster.h"
#include "AI.h"
#include "Effect.h"

CIsys_NormalAttacked::CIsys_NormalAttacked()
	: CState(BOSS_NORMAL_ATTACKED)
	, m_dwTime(0)
{
}

CIsys_NormalAttacked::~CIsys_NormalAttacked()
{
}

void CIsys_NormalAttacked::Update()
{
	// Player�� ��ġ üũ
	CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front();
	float fPlayerX = pPlayer->Get_Info().fX;
	float fPlayerY = pPlayer->Get_Info().fY;

	// ���� �ڽ��� ��ġ üũ
	CMonster* pMonster = GetMonster();
	float fMonsterX = pMonster->Get_Info().fX;
	float fMonsterY = pMonster->Get_Info().fY;

	// �÷��̾� x��ǥ üũ�ؼ� �¿� �̹��� ����
	if (fPlayerX < fMonsterX)
		pMonster->Set_FrameKey(L"Isys_LWalk");
	else
		pMonster->Set_FrameKey(L"Isys_RWalk");

	if (pMonster->m_tHitInfo.fKnockbackTime < pMonster->Get_dwTime())
	{
		Exit();
		pMonster->Set_State(MON_STATE::BOSS_TRACE);
		m_pAI->SetCurState(MON_STATE::BOSS_TRACE);
		m_pAI->GetCurState()->Enter();
	}
}

void CIsys_NormalAttacked::LateUpdate()
{
}

void CIsys_NormalAttacked::Enter()
{
	CMonster* pMonster = GetMonster();
	CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front();
	pMonster->Set_dwTime(0);

	// Player�� ��ġ üũ
	float fPlayerX = pPlayer->Get_Info().fX;
	float fPlayerY = pPlayer->Get_Info().fY;

	// ���� �ڽ��� ��ġ üũ
	float fMonsterX = pMonster->Get_Info().fX;
	float fMonsterY = pMonster->Get_Info().fY;

	// �÷��̾� x��ǥ üũ�ؼ� �� �� �ǰ��̹��� ���
	if (fPlayerX < fMonsterX)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CEffect>::
			Create_Obj(ATT_END, false, pMonster->Get_Info().fX, pMonster->Get_Info().fY + 30.f, 62.f, 73.f, 0.f, 0.f, 0.f, 0.f, 0.48f, 62.f, 73.f, pMonster->Get_TileCollision().bottom,
				0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, L"LHitEffect", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 6, 0, 0.07, 0. });
	}
	else
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CEffect>::
			Create_Obj(ATT_END, false, pMonster->Get_Info().fX, pMonster->Get_Info().fY + 30.f, 62.f, 73.f, 0.f, 0.f, 0.f, 0.f, 0.48f, 62.f, 73.f, pMonster->Get_TileCollision().bottom,
				0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, L"RHitEffect", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 6, 0, 0.07, 0. });
	}
}

void CIsys_NormalAttacked::Exit()
{
	CMonster* pMonster = GetMonster();
	pMonster->Set_dwTime(0);
}
