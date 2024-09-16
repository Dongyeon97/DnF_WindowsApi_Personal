#pragma once
#include "Scene.h"
class CStomPath :
    public CScene
{
public:
	CStomPath();
	virtual ~CStomPath();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

