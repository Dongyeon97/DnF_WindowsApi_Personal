#pragma once

#include "Obj.h"

class CUI_Inven;

class CCollsionMgr
{
public:
	CCollsionMgr();
	~CCollsionMgr();
public:
	static CCollsionMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CCollsionMgr;

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
	static CCollsionMgr* m_pInstance;

public:
	static void	Collision_Rect1(list<CObj*> Dst, list<CObj*> Src);
	static void	Collision_Rect2(list<CObj*> Dst, list<CObj*> Src);
	static void	Collision_RectEx(list<CObj*> Dst, list<CObj*> Src);
	static bool	Check_Rect(CObj* pDst, CObj* pSrc, float* pX, float* pY);

	static void	Collision_AttackRectPM(list<CObj*> Dst, list<CObj*> Src);
	static void	Collision_AttackRectMP(list<CObj*> Src, list<CObj*> Dst);
	static void Collision_WAttackRectMP(list<CObj*> Src, list<CObj*> Dst);
	static bool Check_AttackRect(CObj* pDst, CObj* pSrc, float* pX, float* pY);
	static bool Check_AwakenAttackRect(CObj* pDst, CObj* pSrc, float* pX, float* pY);


	static void Collision_WAttackRectMP2(list<CObj*> Src, list<CObj*> Dst);
	static bool Check_AwakenAttackRect2(CObj* pDst, CObj* pSrc, float* pX, float* pY);

	static void Collision_WAttackRectPM(list<CObj*> Dst, list<CObj*> Src);
	static bool Check_WAttackRect(CObj* pDst, CObj* pSrc, float* pX, float* pY);

	static void	Collision_RectExTile(list<CObj*> Dst, vector<CObj*> Src);
	static bool	Check_TileRect(CObj* pDst, CObj* pSrc, float* pX, float *pY);

	static bool	Check_Sphere(CObj* pDst, CObj* pSrc);
	static void Collision_Sphere(list<CObj*> Dst, list<CObj*> Src);

	static void PlayItemSound(ITEM_TYPE _eItemType);

private:

	friend class CPlayer;
};