#pragma once
#include "Scene.h"
class CEdit_Reshipon2 : public CScene
{
public:
	CEdit_Reshipon2();
	virtual ~CEdit_Reshipon2();

public:

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	void		Key_Input();
};

