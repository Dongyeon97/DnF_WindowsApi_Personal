#pragma once
#include "Obj.h"
class CSatelite :
    public CObj
{
public:
	CSatelite();
	virtual ~CSatelite();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;

	void	Making_Hitbox();

private:
	double	m_HitTerm;
};

