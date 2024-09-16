#pragma once

#include "Define.h"

class CScrollMgr
{
public:
	CScrollMgr();
	~CScrollMgr();
public:
	static CScrollMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CScrollMgr;

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
	static CScrollMgr* m_pInstance;

public:
	void			Scroll_Lock();
	void			ScrollX_Fix(float _x);
	void			ScrollY_Fix(float _y);

public:
	void			Set_ScrollX(float _fSpeed) { m_fScrollX += _fSpeed; }
	void			Set_ScrollY(float _fSpeed) { m_fScrollY += _fSpeed; }

	float			Get_ScrollX() { return m_fScrollX; }
	float			Get_ScrollY() { return m_fScrollY; }

private:
	float				m_fScrollX;
	float				m_fScrollY;
};

