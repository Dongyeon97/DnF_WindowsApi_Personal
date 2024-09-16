#include "stdafx.h"
#include "Isys_Trace.h"

#include "ObjMgr.h"

#include "Player.h"
#include "Monster.h"
#include "AI.h"
#include "Isys.h"

CIsys_Trace::CIsys_Trace()
	: CState(BOSS_TRACE)
{
}

CIsys_Trace::~CIsys_Trace()
{
}

void CIsys_Trace::Update()
{
	CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front();
	CMonster* pMonster = GetMonster();

	float fHp = pMonster->Get_Info().fHp;
	float fMaxHp = pMonster->Get_Info().fMaxHp;

	MoveToPlayer();
}

void CIsys_Trace::LateUpdate()
{
}

void CIsys_Trace::Enter()
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

		if (L"LSkasa" == pMonster->Get_FrameKey() || L"RSkasa" == pMonster->Get_FrameKey())
		{
			if (fPlayerX < fMonsterX)
				pMonster->Set_FrameKey(L"LSkasa");
			else
				pMonster->Set_FrameKey(L"RSkasa");
		}
		else
		{
			// �÷��̾� x��ǥ üũ�ؼ� �¿� �̹��� ����
			if (fPlayerX < fMonsterX)
				pMonster->Set_FrameKey(L"Isys_LWalk");
			else
				pMonster->Set_FrameKey(L"Isys_RWalk");
		}
	}
}

void CIsys_Trace::Exit()
{
	CMonster* pMonster = GetMonster();

	pMonster->Set_dwTime(0);
	m_iAttackCount = 0;
}

void CIsys_Trace::MoveToPlayer()
{
	// Player�� ��ġ üũ
	CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front();
	LONG fPlayerX = pPlayer->Get_TileCollisionCenter().x;	// y���� ��ȭ�� ���� TileCollision�� ������ �÷��̾� �������� ��´�
	LONG fPlayerY = pPlayer->Get_TileCollisionCenter().y;	// -> ���ʹ� �÷��̾ ������ �ص� �� �ڸ��� �ִٰ� �ν���

	// ���� �ڽ��� ��ġ üũ
	CMonster* pMonster = GetMonster();
	LONG fMonsterX = pMonster->Get_TileCollisionCenter().x;
	LONG fMonsterY = pMonster->Get_TileCollisionCenter().y;	// �÷��̾� TileCollision�� ������ ��ġ

	// �÷��̾� x��ǥ üũ�ؼ� �¿� �̹��� ����
	if (L"LSkasa" == pMonster->Get_FrameKey() || L"RSkasa" == pMonster->Get_FrameKey())
	{
		if (fPlayerX < fMonsterX)
			pMonster->Set_FrameKey(L"LSkasa");
		else
			pMonster->Set_FrameKey(L"RSkasa");
	}
	else
	{
		// �÷��̾� x��ǥ üũ�ؼ� �¿� �̹��� ����
		if (fPlayerX < fMonsterX)
			pMonster->Set_FrameKey(L"Isys_LWalk");
		else
			pMonster->Set_FrameKey(L"Isys_RWalk");
	}

	if (pPlayer)
	{
		float	fWidth = 0.f, fHeight = 0.f, fDiagonal = 0.f, fRadian = 0.f;

		fWidth = float(fPlayerX - fMonsterX);
		fHeight = float(fPlayerY - fMonsterY);

		fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		fRadian = acosf(fWidth / fDiagonal);

		if (fPlayerY > fMonsterY)
			fRadian = (2 * PI) - fRadian;

		if (abs(fDiagonal) > 20.f)
		{
			pMonster->Set_PosX(pMonster->Get_Speed() * cosf(fRadian));
			pMonster->Set_PosY(-pMonster->Get_Speed() * sinf(fRadian));
		}

		// ��ī��
		if (L"LSkasa" == pMonster->Get_FrameKey() || L"RSkasa" == pMonster->Get_FrameKey())
		{
			if (fDiagonal < pMonster->GetMonInfo().m_fAttRange && abs(fPlayerY - fMonsterY) < 30.f)
			{
				Exit();
				switch (rand() % 3)
				{
				case 0:
					pMonster->Set_State(MON_STATE::BOSS_ATTACK1);
					m_pAI->SetCurState(MON_STATE::BOSS_ATTACK1);
					m_pAI->GetCurState()->Enter();
					break;

				case 1:
					pMonster->Set_State(MON_STATE::BOSS_ATTACK2);
					m_pAI->SetCurState(MON_STATE::BOSS_ATTACK2);
					m_pAI->GetCurState()->Enter();
					break;

				case 2:
					pMonster->Set_State(MON_STATE::BOSS_ATTACK3);
					m_pAI->SetCurState(MON_STATE::BOSS_ATTACK3);
					m_pAI->GetCurState()->Enter();
					break;
				}
			}
		}
		// �̽ý�
		else
		{
			if (fDiagonal < pMonster->GetMonInfo().m_fAttRange && abs(fPlayerY - fMonsterY) < 50.f)
			{
				Exit();
				switch (rand() % 5)
				{
				case 0:
					pMonster->Set_State(MON_STATE::BOSS_ATTACK1);
					m_pAI->SetCurState(MON_STATE::BOSS_ATTACK1);
					m_pAI->GetCurState()->Enter();
					break;

				case 1:
					pMonster->Set_State(MON_STATE::BOSS_ATTACK2);
					m_pAI->SetCurState(MON_STATE::BOSS_ATTACK2);
					m_pAI->GetCurState()->Enter();
					break;

				case 2:
					pMonster->Set_State(MON_STATE::BOSS_BACKSTEP);
					m_pAI->SetCurState(MON_STATE::BOSS_BACKSTEP);
					m_pAI->GetCurState()->Enter();
					break;

				case 3:
					pMonster->Set_State(MON_STATE::BOSS_ATTACK3);
					m_pAI->SetCurState(MON_STATE::BOSS_ATTACK3);
					m_pAI->GetCurState()->Enter();
					break;

				case 4:
					pMonster->Set_State(MON_STATE::BOSS_ATTACK4);
					m_pAI->SetCurState(MON_STATE::BOSS_ATTACK4);
					m_pAI->GetCurState()->Enter();
					break;
				}
			}
		}
	}
}