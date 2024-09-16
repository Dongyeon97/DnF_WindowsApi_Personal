#pragma once
#include "UI.h"
class CUI_Font :
    public CUI
{
public:
	CUI_Font();
	virtual ~CUI_Font();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

