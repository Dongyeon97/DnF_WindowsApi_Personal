#include "stdafx.h"
#include "AI.h"

#include "State.h"
#include <assert.h>

AI::AI()
	: m_pOwner(nullptr)
	, m_pCurState(nullptr)
{
}

AI::~AI()
{
	Release();
}

void AI::Update()
{
	m_pCurState->Update();
}

void AI::Release()
{
	for (auto& iter : m_mapState)
	{
		Safe_Delete(iter.second);
	}
}

void AI::AddState(CState* _pState)
{
	CState* pState = GetState(_pState->GetType());
	assert(!pState);

	m_mapState.emplace(_pState->GetType(), _pState);
	_pState->m_pAI = this;
}

CState* AI::GetState(MON_STATE _eState)
{
	map<MON_STATE, CState*>::iterator iter  = m_mapState.find(_eState);
	if (iter == m_mapState.end())
		return nullptr;

	return iter->second;
}

void AI::SetCurState(MON_STATE _eState)
{
	m_pCurState = GetState(_eState);
	assert(m_pCurState);
}
