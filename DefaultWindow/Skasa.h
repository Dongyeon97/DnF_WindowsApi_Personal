#pragma once
#include "Monster.h"
class CSkasa :
    public CMonster
{
public:
	CSkasa();
	virtual ~CSkasa();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	void	Making_Breath(float _fX, float _fY);

	void	Set_Pattern1(bool _bIsUsed) { m_bPattern1 = _bIsUsed; }

	bool	Get_Pattern1() { return m_bPattern1; }

public:
	void	Motion_Change();
	void	Update_Rect();

public:
	bool	m_IsDead;		// 사망모션 진행 여부

	bool	m_bPattern1;	// 1차 광폭화를 사용했는지 여부
};

