#pragma once
#include "UI.h"
class CUI_Hp :
    public CUI
{
public:
	CUI_Hp();
	virtual ~CUI_Hp();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

