#pragma once
#include "Scene.h"
class CEdit_SeriaRoom :	public CScene
{
public:
	CEdit_SeriaRoom();
	virtual ~CEdit_SeriaRoom();

public:

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	void		Key_Input();
};

