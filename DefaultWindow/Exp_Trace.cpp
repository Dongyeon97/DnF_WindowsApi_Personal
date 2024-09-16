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
	// Player의 위치 체크
	CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front();
	float fPlayerX = pPlayer->Get_Info().fX;
	float fPlayerY = pPlayer->Get_Info().fY;

	// 몬스터 자신의 위치 체크
	CMonster* pMonster = GetMonster();
	pMonster->Set_dwTime(0);
	m_iAttackCount = 0;

	float fMonsterX = pMonster->Get_Info().fX;
	float fMonsterY = pMonster->Get_Info().fY;

	// 익스펠러
	if (L"Expeller_L" == pMonster->Get_FrameKey() || L"Expeller_R" == pMonster->Get_FrameKey())
	{
		// 플레이어 x좌표 체크해서 좌우 이미지 반전
		if (fPlayerX < fMonsterX)
			pMonster->Set_FrameKey(L"Expeller_L");
		else
			pMonster->Set_FrameKey(L"Expeller_R");
	}
	// 누더기
	else if (L"LNudeogi" == pMonster->Get_FrameKey() || L"RNudeogi" == pMonster->Get_FrameKey())
	{
		if (fPlayerX < fMonsterX)
			pMonster->Set_FrameKey(L"LNudeogi");
		else
			pMonster->Set_FrameKey(L"RNudeogi");
	}
	// 장난감 병정
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
	// Player의 위치 체크
	CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front();
	LONG fPlayerX = pPlayer->Get_TileCollisionCenter().x;	// y값의 변화가 적은 TileCollision의 중점을 플레이어 기준으로 잡는다
	LONG fPlayerY = pPlayer->Get_TileCollisionCenter().y;	// -> 몬스터는 플레이어가 점프를 해도 그 자리에 있다고 인식함

	// 몬스터 자신의 위치 체크
	CMonster* pMonster = GetMonster();
	LONG fMonsterX = pMonster->Get_TileCollisionCenter().x;
	LONG fMonsterY = pMonster->Get_TileCollisionCenter().y;

	// 익스펠러
	if (L"Expeller_L" == pMonster->Get_FrameKey() || L"Expeller_R" == pMonster->Get_FrameKey())
	{
		// 플레이어 x좌표 체크해서 좌우 이미지 반전
		if (fPlayerX < fMonsterX)
			pMonster->Set_FrameKey(L"Expeller_L");
		else
			pMonster->Set_FrameKey(L"Expeller_R");
	}
	// 누더기
	else if (L"LNudeogi" == pMonster->Get_FrameKey() || L"RNudeogi" == pMonster->Get_FrameKey())
	{
		if (fPlayerX < fMonsterX)
			pMonster->Set_FrameKey(L"LNudeogi");
		else
			pMonster->Set_FrameKey(L"RNudeogi");
	}
	// 장난감 병정
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

		// 몬스터의 공격 범위에 플레이어가 들어오면 공격하게끔 설계해야 함
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