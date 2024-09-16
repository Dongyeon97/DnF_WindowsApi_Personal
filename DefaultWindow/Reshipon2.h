#pragma once
#include "Scene.h"
class CReshipon2 :
    public CScene
{
public:
	CReshipon2();
	virtual ~CReshipon2();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

