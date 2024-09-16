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
	// CObj을(를) 통해 상속됨
	virtual void Initialize() PURE;
	virtual int Update() PURE;
	virtual void Late_Update() PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release() PURE;

	// 모든 UI들이 공통으로 들고있으면 좋은것들
protected:
	
};

