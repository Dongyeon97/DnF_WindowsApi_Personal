#include "stdafx.h"
#include "Exp_Attack2.h"

#include "ObjMgr.h"

#include "Player.h"
#include "AI.h"
#include "Monster.h"
#include "MonsterAttack.h"

CExp_Attack2::CExp_Attack2()
	: CState(MON_ATTACK2)
{
}

CExp_Attack2::~CExp_Attack2()
{
}

void CExp_Attack2::Update()
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
		// �ͽ��緯
		if (L"Expeller_L" == pMonster->Get_FrameKey() || L"Expeller_R" == pMonster->Get_FrameKey())
		{
			// 1Ÿ
			if (0.2 < pMonster->Get_dwTime() && 0 == m_iAttackCount)
			{
				// ���� ���� ����߿��� ������ �ǰ�����
				++m_iAttackCount;
				if (L"Expeller_L" == pMonster->Get_FrameKey())
				{
					// �ǰ� ��Ʈ�ڽ� ����

				}
				else if (L"Expeller_R" == pMonster->Get_FrameKey())
				{

				}
			}

			if (1.1 < pMonster->Get_dwTime() && 1 == m_iAttackCount)
			{
				Exit();
				pMonster->Set_State(MON_STATE::MON_TRACE);
				m_pAI->SetCurState(MON_STATE::MON_TRACE);
				m_pAI->GetCurState()->Enter();
			}
		}
		// ������
		else if (L"LNudeogi" == pMonster->Get_FrameKey() || L"RNudeogi" == pMonster->Get_FrameKey())
		{
			if (0.6 < pMonster->Get_dwTime() && 0 == m_iAttackCount)
			{
				// ���� ����� ���
				++m_iAttackCount;
				if (L"LNudeogi" == pMonster->Get_FrameKey())
				{
					// �ǰ� ��Ʈ�ڽ� ����
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_LEVITATE, true, fMonsterX - 100.f, fMonsterY + 20.f, 100.f, 100.f, 0, 180.f, 0.f, 0.f, 0.15f, 100.f, 100.f, pMonster->Get_TileCollision().bottom,
							pMonster->Get_Info().fAtk, 5.f, 0.5f, 3.f, 7.5f, 90.f, 180.f, 0.3f, L"Attack1", { 255, 255, 255 }));
				}
				else
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_LEVITATE, true, fMonsterX + 100.f, fMonsterY + 20.f, 100.f, 100.f, 0, 0.f, 0.f, 0.f, 0.15f, 100.f, 100.f, pMonster->Get_TileCollision().bottom,
							pMonster->Get_Info().fAtk, 5.f, 0.5f, 3.f, 7.5f, 90.f, 0.f, 0.3f, L"Attack1", { 255, 255, 255 }));
				}
			}
			if (1 < pMonster->Get_dwTime() && 1 == m_iAttackCount)
			{
				Exit();
				pMonster->Set_State(MON_STATE::MON_TRACE);
				m_pAI->SetCurState(MON_STATE::MON_TRACE);
				m_pAI->GetCurState()->Enter();
			}
		}
		// �峭�� ����
		else if (L"LToy" == pMonster->Get_FrameKey() || L"RToy" == pMonster->Get_FrameKey())
		{
			if (0.6 < pMonster->Get_dwTime() && 0 == m_iAttackCount)
			{
				// ���� ����� ���
				++m_iAttackCount;
				if (L"LToy" == pMonster->Get_FrameKey())
				{
					// �ǰ� ��Ʈ�ڽ� ����
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_LEVITATE, true, fMonsterX - 100.f, fMonsterY + 20.f, 100.f, 100.f, 0, 180.f, 0.f, 0.f, 0.15f, 100.f, 100.f, pMonster->Get_TileCollision().bottom,
							pMonster->Get_Info().fAtk, 5.f, 0.5f, 3.f, 7.5f, 90.f, 180.f, 0.3f, L"Attack1", { 255, 255, 255 }));
				}
				else
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
						Create_Obj(ATT_LEVITATE, true, fMonsterX + 100.f, fMonsterY + 20.f, 100.f, 100.f, 0, 0.f, 0.f, 0.f, 0.15f, 100.f, 100.f, pMonster->Get_TileCollision().bottom,
							pMonster->Get_Info().fAtk, 5.f, 0.5f, 3.f, 7.5f, 90.f, 0.f, 0.3f, L"Attack1", { 255, 255, 255 }));
				}
			}
			if (1 < pMonster->Get_dwTime() && 1 == m_iAttackCount)
			{
				Exit();
				pMonster->Set_State(MON_STATE::MON_TRACE);
				m_pAI->SetCurState(MON_STATE::MON_TRACE);
				m_pAI->GetCurState()->Enter();
			}
		}
	}
}

void CExp_Attack2::LateUpdate()
{
}

void CExp_Attack2::Enter()
{
	CMonster* pMonster = GetMonster();
	pMonster->Set_dwTime(0);
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

		// �ͽ��緯
		if (L"Expeller_L" == pMonster->Get_FrameKey() || L"Expeller_R" == pMonster->Get_FrameKey())
		{
			// �÷��̾� x��ǥ üũ�ؼ� �¿� �̹��� ����
			if (fPlayerX < fMonsterX)
				pMonster->Set_FrameKey(L"Expeller_L");
			else
				pMonster->Set_FrameKey(L"Expeller_R");
		}
		// ������
		else if (L"LNudeogi" == pMonster->Get_FrameKey() || L"RNudeogi" == pMonster->Get_FrameKey())
		{
			if (fPlayerX < fMonsterX)
				pMonster->Set_FrameKey(L"LNudeogi");
			else
				pMonster->Set_FrameKey(L"RNudeogi");
		}
		// �峭�� ����
		else if (L"LToy" == pMonster->Get_FrameKey() || L"RToy" == pMonster->Get_FrameKey())
		{
			if (fPlayerX < fMonsterX)
				pMonster->Set_FrameKey(L"LToy");
			else
				pMonster->Set_FrameKey(L"RToy");
		}
	}
}

void CExp_Attack2::Exit()
{
	CMonster* pMonster = GetMonster();

	pMonster->Set_dwTime(0);
	m_iAttackCount = 0;
}
