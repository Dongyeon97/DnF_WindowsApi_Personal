#pragma once
#include "Scene.h"
class CAlfhlyra :
    public CScene
{
public:
	CAlfhlyra();
	virtual ~CAlfhlyra();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

