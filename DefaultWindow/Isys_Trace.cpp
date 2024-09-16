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
		// Player의 위치 체크
		CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front();
		float fPlayerX = pPlayer->Get_Info().fX;
		float fPlayerY = pPlayer->Get_Info().fY;

		// 몬스터 자신의 위치 체크
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
			// 플레이어 x좌표 체크해서 좌우 이미지 반전
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
	// Player의 위치 체크
	CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front();
	LONG fPlayerX = pPlayer->Get_TileCollisionCenter().x;	// y값의 변화가 적은 TileCollision의 중점을 플레이어 기준으로 잡는다
	LONG fPlayerY = pPlayer->Get_TileCollisionCenter().y;	// -> 몬스터는 플레이어가 점프를 해도 그 자리에 있다고 인식함

	// 몬스터 자신의 위치 체크
	CMonster* pMonster = GetMonster();
	LONG fMonsterX = pMonster->Get_TileCollisionCenter().x;
	LONG fMonsterY = pMonster->Get_TileCollisionCenter().y;	// 플레이어 TileCollision과 동일한 위치

	// 플레이어 x좌표 체크해서 좌우 이미지 반전
	if (L"LSkasa" == pMonster->Get_FrameKey() || L"RSkasa" == pMonster->Get_FrameKey())
	{
		if (fPlayerX < fMonsterX)
			pMonster->Set_FrameKey(L"LSkasa");
		else
			pMonster->Set_FrameKey(L"RSkasa");
	}
	else
	{
		// 플레이어 x좌표 체크해서 좌우 이미지 반전
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

		// 스카사
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
		// 이시스
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