#include "stdafx.h"
#include "ObjMgr.h"
#include "CollsionMgr.h"
#include "TileMgr.h"

CObjMgr*	CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}

CObjMgr::~CObjMgr()
{
	Release();
}

CObj* CObjMgr::Get_Target(OBJ_ID eID, CObj* pObj)
{
	if (m_ObjList[eID].empty())
		return nullptr;

	CObj*		pTarget = nullptr;
	float		fDistance = 0.f;

	for (auto& iter : m_ObjList[eID])
	{
		if (iter->Get_Dead())
			continue;

		float	fWidth = iter->Get_Info().fX - pObj->Get_Info().fX;
		float	fHeight = iter->Get_RectCollision().bottom - pObj->Get_Rect().bottom;

		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		if ((!pTarget) || (fDistance > fDiagonal))
		{
			pTarget = iter;
			fDistance = fDiagonal;
		}
	}

	return pTarget;
}

void CObjMgr::Add_Object(OBJ_ID eID, CObj* pObj)
{
	if (OBJ_END <= eID || nullptr == pObj)
		return;

	m_ObjList[eID].push_back(pObj);
}

void CObjMgr::Update(void)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			int	iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}
}

void CObjMgr::Late_Update(void)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->Late_Update();

			if (m_ObjList[i].empty())
				break;

			RENDERID		eID = iter->Get_RenderID();
			m_RenderList[eID].push_back(iter);
		}
	}
}

void CObjMgr::Render(HDC hDC)
{
	for (size_t i = 0; i < RENDER_END; ++i)
	{
		m_RenderList[i].sort([](CObj* pDst, CObj* pSrc) ->bool
			{
				return pDst->Get_TileCollision().bottom < pSrc->Get_TileCollision().bottom;
			});

		for (auto& iter : m_RenderList[i])
		{

			if(nullptr != iter)
				iter->Render(hDC);
		}

		m_RenderList[i].clear();
	}
}

void CObjMgr::Release(void)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), DeleteObj());
		m_ObjList[i].clear();
	}
}

// 정해진 OBJ타입만 골라서 ObjList에서 삭제시키는 함수
void CObjMgr::Delete_ID(OBJ_ID eID)
{
	for (auto& iter : m_ObjList[eID])
		Safe_Delete(iter);

	m_ObjList[eID].clear();
}

void CObjMgr::Clear_RenderList()
{
	m_RenderList->clear();
}
