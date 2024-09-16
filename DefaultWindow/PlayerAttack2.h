#pragma once
#include "Obj.h"
class CPlayerAttack2 :
    public CObj
{
public:
	CPlayerAttack2();
	virtual ~CPlayerAttack2();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;
};

