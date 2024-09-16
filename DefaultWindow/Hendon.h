#pragma once
#include "Scene.h"
class CHendon :
    public CScene
{
public:
	CHendon();
	virtual ~CHendon();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

