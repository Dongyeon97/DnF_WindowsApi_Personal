#pragma once
#include "Scene.h"
class CEdit_Alfhlyra :
    public CScene
{
public:
	CEdit_Alfhlyra();
	virtual ~CEdit_Alfhlyra();

public:

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	void		Key_Input();
};

