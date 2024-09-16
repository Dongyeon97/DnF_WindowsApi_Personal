#include "stdafx.h"
#include "Define.h"
#include "Monster.h"

#include "TimeMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

#include "AI.h"
#include "State.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
	
}
void CMonster::Set_AI(AI* _pAI)
{
	m_pAI = _pAI;
	m_pAI->m_pOwner = this;
}
