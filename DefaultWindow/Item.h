#pragma once
#include "Obj.h"
class CItem :
    public CObj
{
public:
	CItem();
	virtual ~CItem();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	int m_xIndex;
	int m_yIndex;
};