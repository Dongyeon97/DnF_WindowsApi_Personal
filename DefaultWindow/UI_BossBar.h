#pragma once
#include "UI.h"
class CUI_BossBar :
    public CUI
{
public:
	CUI_BossBar();
	virtual ~CUI_BossBar();

public:
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

