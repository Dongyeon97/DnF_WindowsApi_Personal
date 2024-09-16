#pragma once
#include "Monster.h"
class CNudeogi :
    public CMonster
{
public:
	CNudeogi();
	virtual ~CNudeogi();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void	Motion_Change();
	void	Update_Rect();
};