#pragma once
#include "UI.h"
class CUI_SkillIcon_2 :
    public CUI
{
public:
	CUI_SkillIcon_2();
	virtual ~CUI_SkillIcon_2();

public:
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

