#pragma once
#include "Scene.h"
class CEdit_Reshipon1 : public CScene
{
public:
	CEdit_Reshipon1();
	virtual ~CEdit_Reshipon1();

public:

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	void		Key_Input();
};

