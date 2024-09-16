#include "stdafx.h"
#include "Exp_Trace.h"

#include "ObjMgr.h"

#include "Player.h"
#include "Monster.h"
#include "AI.h"
#include "Isys.h"

CExp_Trace::CExp_Trace()
	: CState(MON_TRACE)
{
}

CExp_Trace::~CExp_Trace()
{
}

void CExp_Trace::Update()
{
	CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front();
	CMonster* pMonster = GetMonster();

	MoveToPlayer();
}

void CExp_Trace::LateUpdate()
{
}

void CExp_Trace::Enter()
{
	// Player�� ��ġ üũ
	CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front();
	float fPlayerX = pPlayer->Get_Info().fX;
	float fPlayerY = pPlayer->Get_Info().fY;

	// ���� �ڽ��� ��ġ üũ
	CMonster* pMonster = GetMonster();
	pMonster->Set_dwTime(0);
	m_iAttackCount = 0;

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

void CExp_Trace::Exit()
{
	CMonster* pMonster = GetMonster();

	pMonster->Set_dwTime(0);
	m_iAttackCount = 0;
}

void CExp_Trace::MoveToPlayer()
{
	// Player�� ��ġ üũ
	CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front();
	LONG fPlayerX = pPlayer->Get_TileCollisionCenter().x;	// y���� ��ȭ�� ���� TileCollision�� ������ �÷��̾� �������� ��´�
	LONG fPlayerY = pPlayer->Get_TileCollisionCenter().y;	// -> ���ʹ� �÷��̾ ������ �ص� �� �ڸ��� �ִٰ� �ν���

	// ���� �ڽ��� ��ġ üũ
	CMonster* pMonster = GetMonster();
	LONG fMonsterX = pMonster->Get_TileCollisionCenter().x;
	LONG fMonsterY = pMonster->Get_TileCollisionCenter().y;

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

	if (pPlayer)
	{
		float	fWidth = 0.f, fHeight = 0.f, fDiagonal = 0.f, fRadian = 0.f;

		fWidth = fPlayerX - fMonsterX;
		fHeight = fPlayerY - fMonsterY;

		fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		fRadian = acosf(fWidth / fDiagonal);

		if (fPlayerY > fMonsterY)
			fRadian = (2 * PI) - fRadian;

		if (abs(fDiagonal) > 20.f)
		{
			pMonster->Set_PosX(pMonster->Get_Speed() * cosf(fRadian));
			pMonster->Set_PosY(-pMonster->Get_Speed() * sinf(fRadian));
		}

		// ������ ���� ������ �÷��̾ ������ �����ϰԲ� �����ؾ� ��
		if (fDiagonal < pMonster->GetMonInfo().m_fAttRange && abs(fPlayerY - fMonsterY) < 5.f)
		{
			Exit();
			switch (rand() % 2)
			{
			case 0:
				pMonster->Set_State(MON_STATE::MON_ATTACK1);
				m_pAI->SetCurState(MON_STATE::MON_ATTACK1);
				m_pAI->GetCurState()->Enter();
				break;

			case 1:
				pMonster->Set_State(MON_STATE::MON_ATTACK2);
				m_pAI->SetCurState(MON_STATE::MON_ATTACK2);
				m_pAI->GetCurState()->Enter();
				break;
			}
		}
	}
}