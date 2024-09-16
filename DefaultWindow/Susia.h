#pragma once
#include "Obj.h"
class CSusia :
    public CObj
{
public:
	CSusia();
	virtual ~CSusia();

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

