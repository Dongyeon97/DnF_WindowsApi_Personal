#pragma once

#include "MyBitmap.h"

class CBmpMgr
{
public:
	CBmpMgr();
	~CBmpMgr();
public:
	static CBmpMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CBmpMgr;

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
	static CBmpMgr* m_pInstance;

public:
	void		Insert_Bmp(const TCHAR* pFilePath, const TCHAR* pImgKey);
	void		Release_Bmp(const TCHAR* pImgKey);
	HDC			Find_Img(const TCHAR* pImgKey);
	void		Release(void);


private:
	map<const TCHAR*, CMyBitmap*>		m_mapBit;
};

