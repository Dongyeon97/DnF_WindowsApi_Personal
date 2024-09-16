#pragma once
#include "Scene.h"
class CEdit_SkasaRair :
    public CScene
{
public:
	CEdit_SkasaRair();
	virtual ~CEdit_SkasaRair();

public:

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	void		Key_Input();
};

