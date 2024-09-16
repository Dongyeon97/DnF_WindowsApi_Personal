#pragma once
#include "Scene.h"
class CEdit_Hendon : public CScene
{
public:
	CEdit_Hendon();
	virtual ~CEdit_Hendon();

public:

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	void		Key_Input();
};

