#pragma once
#include "Monster.h"
class CRuneStone :
    public CMonster
{
public:
	CRuneStone();
	virtual ~CRuneStone();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

