#pragma once
#include "Obj.h"
class CStoreItem :
    public CObj
{
public:
	CStoreItem();
	virtual ~CStoreItem();

public:
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	int m_iIndex;
	int m_yIndex;
};

