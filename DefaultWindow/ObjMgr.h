#pragma once

#include "Player.h"
#include "AbstractFactory.h"
#include "Monster.h"
#include "Mouse.h"

class CObjMgr
{
public:
	CObjMgr();
	~CObjMgr();
public:
	static CObjMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CObjMgr;

		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static CObjMgr* m_pInstance;
public:
	CObj*			Get_Target(OBJ_ID eID, CObj* pObj);
	list<CObj*>		GetObjList(OBJ_ID _eID) { return m_ObjList[_eID]; }

public:
	void		Add_Object(OBJ_ID eID, CObj* pObj);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

	void		Delete_ID(OBJ_ID eID);
	void		Clear_RenderList();

private:
	list<CObj*>		m_ObjList[OBJ_END];
	list<CObj*>		m_RenderList[RENDER_END];
};