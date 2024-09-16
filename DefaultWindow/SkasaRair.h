#pragma once
#include "Scene.h"
class CSkasaRair :
    public CScene
{
public:
	CSkasaRair();
	virtual ~CSkasaRair();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

