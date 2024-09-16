#pragma once
#include "Obj.h"

class AI;

// ���Ͱ� ������ �־�� �� ���� ����ü
struct tMInfo
{
	float	m_fRecogRange;	// �ν� ����
	float	m_fAttRange;	// ���� ����
};

class CMonster :
	public CObj
{
public:
	CMonster();
	virtual ~CMonster();

public:
	virtual void Initialize() PURE;
	virtual int Update() PURE;
	virtual void Late_Update() PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release() PURE;

public:
	void		Set_State(MON_STATE _eState) { m_eCurState = _eState; };
	MON_STATE	Get_State() { return m_eCurState; }

	void	Set_AI(AI* _pAI);
	AI*		Get_AI() { return m_pAI; }

public:
	void			SetMonInfo(const tMInfo& _tMonInfo) { m_tMonInfo = _tMonInfo; }
	const tMInfo&	GetMonInfo() { return m_tMonInfo; }

protected:
	tMInfo		m_tMonInfo;
	AI*			m_pAI;			// ���Ͱ� ������ �ִ� AI
};

