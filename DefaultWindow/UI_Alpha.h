#pragma once
#include "UI.h"
class CUI_Alpha :
    public CUI
{
public:
	CUI_Alpha();
	virtual ~CUI_Alpha();

public:
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

