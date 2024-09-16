#pragma once
#include "Scene.h"
class CSeriaRoom :	public CScene
{
public:
	CSeriaRoom();
	virtual ~CSeriaRoom();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

