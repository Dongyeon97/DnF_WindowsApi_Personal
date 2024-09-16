#pragma once
#include "Obj.h"
#include "ObjMgr.h"
class CUI :
    public CObj
{
public:
	CUI();
	virtual ~CUI();

public:
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() PURE;
	virtual int Update() PURE;
	virtual void Late_Update() PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release() PURE;

	// ��� UI���� �������� ��������� �����͵�
protected:
	
};

