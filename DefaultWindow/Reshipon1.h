#pragma once
#include "Scene.h"
class CReshipon1 :
    public CScene
{
public:
	CReshipon1();
	virtual ~CReshipon1();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

