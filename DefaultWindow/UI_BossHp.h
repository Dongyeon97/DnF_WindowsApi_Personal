#pragma once
#include "UI.h"
class CUI_BossHp :
    public CUI
{
public:
	CUI_BossHp();
	virtual ~CUI_BossHp();

public:
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	double m_DrawRatio;
};

