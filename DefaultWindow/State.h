#pragma once
#include "Define.h"

class CMonster;
class AI;

class CState
{
public:
	// State�� �⺻ ������ ����
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
	int				m_iPatternCount;    // ���� ��� Ƚ��(�� 3�� �ݺ�)

protected:
	AI*				m_pAI;			// State�� �������� AI
	MON_STATE		m_eState;		// State�� ���� ����(enum)

	int				m_iAttackCount;

	friend class AI;
};

