#pragma once
#include "Obj.h"
class CMonsterAttack2 :
    public CObj
{
public:
	CMonsterAttack2();
	virtual ~CMonsterAttack2();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;

	void Move_Frame();
};

