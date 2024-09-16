#pragma once
#include "Monster.h"
class CExpeller :
    public CMonster
{
public:
	CExpeller();
	virtual ~CExpeller();

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

