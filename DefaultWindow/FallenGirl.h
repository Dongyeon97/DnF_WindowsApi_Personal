#pragma once
#include "Obj.h"
class CFallenGirl :
    public CObj
{
public:
	CFallenGirl();
	virtual ~CFallenGirl();

public:
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	virtual void Update_Rect();
	void Motion_Change();
};

