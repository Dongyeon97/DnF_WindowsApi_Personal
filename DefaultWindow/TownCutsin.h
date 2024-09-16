#pragma once
#include "Obj.h"
class CTownCutsin :
    public CObj
{
public:
	CTownCutsin();
	virtual ~CTownCutsin();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;
};