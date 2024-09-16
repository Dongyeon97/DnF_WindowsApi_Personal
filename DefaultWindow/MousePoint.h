#pragma once
#include "Obj.h"
class CMousePoint :
    public CObj
{
public:
	CMousePoint();
	virtual ~CMousePoint();
public:
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

