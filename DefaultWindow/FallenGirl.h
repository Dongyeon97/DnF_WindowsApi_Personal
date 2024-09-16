#pragma once
#include "Obj.h"
class CFallenGirl :
    public CObj
{
public:
	CFallenGirl();
	virtual ~CFallenGirl();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	virtual void Update_Rect();
	void Motion_Change();
};

