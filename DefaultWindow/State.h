#pragma once
#include "Define.h"

class CMonster;
class AI;

class CState
{
public:
	// State는 기본 생성자 없음
	CState(MON_STATE _eState);
	virtual ~CState();

public:
	virtual void Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Enter() PURE;
	virtual void Exit() PURE;

public:
	AI*			GetAI() { return m_pAI; }
	MON_STATE	GetType() { return m_eState; }
	CMonster*	GetMonster();

	void		Set_PatternCount(int _iCount) { m_iPatternCount = _iCount; }

protected:
	int				m_iPatternCount;    // 패턴 사용 횟수(총 3번 반복)

protected:
	AI*				m_pAI;			// State를 보유중인 AI
	MON_STATE		m_eState;		// State의 현재 상태(enum)

	int				m_iAttackCount;

	friend class AI;
};

