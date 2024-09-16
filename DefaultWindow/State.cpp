#include "stdafx.h"
#include "State.h"

#include "AI.h"
#include "Monster.h"

CState::CState(MON_STATE _eState)
	: m_eState(_eState)
	, m_iAttackCount(0)
	, m_iPatternCount(0)
{
}

CState::~CState()
{
}

CMonster* CState::GetMonster()
{
	return m_pAI->GetOwner();
}
