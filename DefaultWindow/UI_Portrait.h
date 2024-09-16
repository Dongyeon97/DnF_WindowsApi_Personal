#pragma once
#include "UI.h"
class CUI_Portrait :
    public CUI
{
public:
	CUI_Portrait();
	virtual ~CUI_Portrait();

public:
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

