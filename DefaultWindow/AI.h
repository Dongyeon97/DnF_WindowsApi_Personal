#pragma once
#include "Define.h"

class CMonster;
class CState;

class AI
{
public:
	AI();
	~AI();

public:
	void Update();
	void Release();

public:
	void		AddState(CState* _pState);
	CState*		GetState(MON_STATE _eState);

	CState*		GetCurState() { return m_pCurState; }
	void		SetCurState(MON_STATE _eState);

	CMonster* GetOwner() { return m_pOwner; }

private:
	CMonster*				m_pOwner;		// AI�� ������ �ִ� ����
	map<MON_STATE, CState*>	m_mapState;		// AI�� ������ �ִ� ���°� ����ִ� map
	CState*					m_pCurState;	// AI�� ������ �ִ� ���� ����

	friend class CMonster;
};

