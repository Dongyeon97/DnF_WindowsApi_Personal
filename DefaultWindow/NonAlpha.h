#pragma once
#include "Obj.h"
class CNonAlpha :
    public CObj
{
public:
	CNonAlpha();
	virtual ~CNonAlpha();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;
};

