#pragma once
#include "Scene.h"
class CEdit_Nest :
    public CScene
{
public:
	CEdit_Nest();
	virtual ~CEdit_Nest();

public:

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	void		Key_Input();
};

