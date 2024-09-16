#include "stdafx.h"
#include "TileMgr.h"

#include "AbstractFactory.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"

CTileMgr* CTileMgr::m_pInstance = nullptr;

CTileMgr::CTileMgr()
	: m_lPickedTime(0)
{
	m_vecTileSeria.reserve(SERIA_TILEX * SERIA_TILEY);
	m_vecTileHendon.reserve(HENDON_TILEX * HENDON_TILEY);
	m_vecTileNest.reserve(NEST_TILEX * NEST_TILEY);
	m_vecTileAlfhlyra.reserve(ALFHLYRA_TILEX * ALFHLYRA_TILEY);
	m_vecTileReshipon1.reserve(RESHIPON1_TILEX * RESHIPON1_TILEY);
	m_vecTileReshipon2.reserve(RESHIPON2_TILEX * RESHIPON2_TILEY);
	m_vecTileSkasaRair.reserve(SKASARAIR_TILEX * SKASARAIR_TILEY);
}

CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Initialize()
{
	for (int i = 0; i < SERIA_TILEY; ++i)
	{
		for (int j = 0; j < SERIA_TILEX; ++j)
		{
			// Ÿ���� ������ ����ش�.
			float	fX = (float)(TILECX >> 1) + (j * TILECX);
			float	fY = (float)(TILECY >> 1) + (i * TILECY);

			// CTileŸ������ ���� ��ġ�� �°� Ÿ�� ����
			CObj*	pObj = CAbstractFactory<CTileNode>::Create_Obj(fX, fY);

			// Ÿ�Ϻ��Ϳ� �߰�
			m_vecTileSeria.push_back(pObj);
		}
	}

	for (int i = 0; i < HENDON_TILEY; ++i)
	{
		for (int j = 0; j < HENDON_TILEX; ++j)
		{
			// Ÿ���� ������ ����ش�.
			float	fX = (float)(TILECX >> 1) + (j * TILECX);
			float	fY = (float)(TILECY >> 1) + (i * TILECY);

			// CTileŸ������ ���� ��ġ�� �°� Ÿ�� ����
			CObj* pObj = CAbstractFactory<CTileNode>::Create_Obj(fX, fY);

			// Ÿ�Ϻ��Ϳ� �߰�
			m_vecTileHendon.push_back(pObj);
		}
	}

	for (int i = 0; i < NEST_TILEY; ++i)
	{
		for (int j = 0; j < NEST_TILEX; ++j)
		{
			// Ÿ���� ������ ����ش�.
			float	fX = (float)(TILECX >> 1) + (j * TILECX);
			float	fY = (float)(TILECY >> 1) + (i * TILECY);

			// CTileŸ������ ���� ��ġ�� �°� Ÿ�� ����
			CObj* pObj = CAbstractFactory<CTileNode>::Create_Obj(fX, fY);

			// Ÿ�Ϻ��Ϳ� �߰�
			m_vecTileNest.push_back(pObj);
		}
	}

	for (int i = 0; i < ALFHLYRA_TILEY; ++i)
	{
		for (int j = 0; j < ALFHLYRA_TILEX; ++j)
		{
			// Ÿ���� ������ ����ش�.
			float	fX = (float)(TILECX >> 1) + (j * TILECX);
			float	fY = (float)(TILECY >> 1) + (i * TILECY);

			// CTileŸ������ ���� ��ġ�� �°� Ÿ�� ����
			CObj* pObj = CAbstractFactory<CTileNode>::Create_Obj(fX, fY);

			// Ÿ�Ϻ��Ϳ� �߰�
			m_vecTileAlfhlyra.push_back(pObj);
		}
	}

	for (int i = 0; i < RESHIPON1_TILEY; ++i)
	{
		for (int j = 0; j < RESHIPON1_TILEX; ++j)
		{
			// Ÿ���� ������ ����ش�.
			float	fX = (float)(TILECX >> 1) + (j * TILECX);
			float	fY = (float)(TILECY >> 1) + (i * TILECY);

			// CTileŸ������ ���� ��ġ�� �°� Ÿ�� ����
			CObj* pObj = CAbstractFactory<CTileNode>::Create_Obj(fX, fY);

			// Ÿ�Ϻ��Ϳ� �߰�
			m_vecTileReshipon1.push_back(pObj);
		}
	}

	for (int i = 0; i < RESHIPON2_TILEY; ++i)
	{
		for (int j = 0; j < RESHIPON2_TILEX; ++j)
		{
			// Ÿ���� ������ ����ش�.
			float	fX = (float)(TILECX >> 1) + (j * TILECX);
			float	fY = (float)(TILECY >> 1) + (i * TILECY);

			// CTileŸ������ ���� ��ġ�� �°� Ÿ�� ����
			CObj* pObj = CAbstractFactory<CTileNode>::Create_Obj(fX, fY);

			// Ÿ�Ϻ��Ϳ� �߰�
			m_vecTileReshipon2.push_back(pObj);
		}
	}

	for (int i = 0; i < SKASARAIR_TILEY; ++i)
	{
		for (int j = 0; j < SKASARAIR_TILEX; ++j)
		{
			// Ÿ���� ������ ����ش�.
			float	fX = (float)(TILECX >> 1) + (j * TILECX);
			float	fY = (float)(TILECY >> 1) + (i * TILECY);

			// CTileŸ������ ���� ��ġ�� �°� Ÿ�� ����
			CObj* pObj = CAbstractFactory<CTileNode>::Create_Obj(fX, fY);

			// Ÿ�Ϻ��Ϳ� �߰�
			m_vecTileSkasaRair.push_back(pObj);
		}
	}
}

void CTileMgr::Update()
{
	if (SC_EDIT_SERIAROOM == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_SERIAROOM == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		for (auto& iter : m_vecTileSeria)
			iter->Update();
	}
	else if (SC_EDIT_HENDON == CSceneMgr::Get_Instance()->GetCurSceneType() ||
			 SC_HENDON == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		for (auto& iter : m_vecTileHendon)
			iter->Update();
	}
	else if (SC_EDIT_NEST == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_NEST == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		for (auto& iter : m_vecTileNest)
			iter->Update();
	}
	else if (SC_EDIT_ALFHLYRA == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_ALFHLYRA == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		for (auto& iter : m_vecTileAlfhlyra)
			iter->Update();
	}
	else if (SC_EDIT_RESHIPON1 == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_RESHIPON1 == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		for (auto& iter : m_vecTileReshipon1)
			iter->Update();
	}
	else if (SC_EDIT_RESHIPON2 == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_RESHIPON2 == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		for (auto& iter : m_vecTileReshipon2)
			iter->Update();
	}
	else if (SC_EDIT_SKASARAIR == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_SKASARAIR == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_EDIT_STOMPATH == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_STOMPATH == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		for (auto& iter : m_vecTileSkasaRair)
			iter->Update();
	}
}

void CTileMgr::Late_Update()
{
	if (SC_EDIT_SERIAROOM == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_SERIAROOM == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		for (auto& iter : m_vecTileSeria)
			iter->Late_Update();
	}
	else if (SC_EDIT_HENDON == CSceneMgr::Get_Instance()->GetCurSceneType() ||
			 SC_HENDON == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		for (auto& iter : m_vecTileHendon)
			iter->Late_Update();
	}
	else if (SC_EDIT_NEST == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_NEST == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		for (auto& iter : m_vecTileNest)
			iter->Late_Update();
	}
	else if (SC_EDIT_ALFHLYRA == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_ALFHLYRA == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		for (auto& iter : m_vecTileAlfhlyra)
			iter->Late_Update();
	}
	else if (SC_EDIT_RESHIPON1 == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_RESHIPON1 == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		for (auto& iter : m_vecTileReshipon1)
			iter->Late_Update();
	}
	else if (SC_EDIT_RESHIPON2 == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_RESHIPON2 == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		for (auto& iter : m_vecTileReshipon2)
			iter->Late_Update();
	}
	else if (SC_EDIT_SKASARAIR == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_SKASARAIR == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_EDIT_STOMPATH == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_STOMPATH == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		for (auto& iter : m_vecTileSkasaRair)
			iter->Late_Update();
	}
}

// Ÿ�� ���������� ����ȭ�� ������
void CTileMgr::Render(HDC hDC)
{
	// ��ó�� ȭ��� �������� �ʴ� 30 x 20���� Ÿ���� ���� �������ϸ� �������� ���ω� 
	/*for (auto& iter : m_vecTileSeria)
		iter->Render(hDC);*/

	// Ÿ�� �ø� ����ȭ
	// ��ũ���� Ÿ�� Size��ŭ �̵��Ǹ� ���� Ÿ���� Render���� �ʰ� ���� Ÿ���� Render�ȴ�
	int	iCullX = abs((int)CScrollMgr::Get_Instance()->Get_ScrollX() / TILECX);
	int	iCullY = abs((int)CScrollMgr::Get_Instance()->Get_ScrollY() / TILECY);

	// ���� ȭ��󿡼� Render�� Ÿ���� �ִ� �ε���, �� ������ ©���� ��츦 ������ �˳��ϰ� +2
	int	iMaxX = iCullX + (WINCX / TILECX) + 2;
	int	iMaxY = iCullY + (WINCY / TILECY) + 2;

	// Cull������ �ִ� �ε������� Render

	if (SC_EDIT_SERIAROOM == CSceneMgr::Get_Instance()->GetCurSceneType())//  ||
		// SC_SERIAROOM == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		for (int i = iCullY; i < iMaxY; ++i)
		{
			for (int j = iCullX; j < iMaxX; ++j)
			{
				// 1���� �����̹Ƿ� �ش� ������� �ε����� ���
				int	iIndex = i * SERIA_TILEX + j;

				// ���� ó��
				if (0 > iIndex || m_vecTileSeria.size() <= (size_t)iIndex)
					continue;

				float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
				float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

				if (0 == dynamic_cast<CTileNode*>(m_vecTileSeria[iIndex])->Get_Option())
				{
					HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
					HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

					Rectangle(hDC, m_vecTileSeria[iIndex]->Get_Rect().left + (int)fScrollX, m_vecTileSeria[iIndex]->Get_Rect().top + (int)fScrollY,
						m_vecTileSeria[iIndex]->Get_Rect().right + (int)fScrollX, m_vecTileSeria[iIndex]->Get_Rect().bottom + (int)fScrollY);

					SelectObject(hDC, oldBrush);
					DeleteObject(myBrush);
				}
				else
				{
					HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_vecTileSeria[iIndex]->Get_FrameKey());

					GdiTransparentBlt(hDC,
						m_vecTileSeria[iIndex]->Get_Rect().left + (long)fScrollX,
						m_vecTileSeria[iIndex]->Get_Rect().top + (long)fScrollY,
						(int)m_vecTileSeria[iIndex]->Get_Info().fCX,
						(int)m_vecTileSeria[iIndex]->Get_Info().fCY,
						hMemDC,
						0,
						0,
						30,
						30,
						RGB(255, 0, 255));
				}
			}
		}
	}
	else if (SC_EDIT_HENDON == CSceneMgr::Get_Instance()->GetCurSceneType()) // ||
			 // SC_HENDON == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		for (int i = iCullY; i < iMaxY; ++i)
		{
			for (int j = iCullX; j < iMaxX; ++j)
			{
				// 1���� �����̹Ƿ� �ش� ������� �ε����� ���
				int	iIndex = i * HENDON_TILEX + j;

				// ���� ó��
				if (0 > iIndex || m_vecTileHendon.size() <= (size_t)iIndex)
					continue;

				float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
				float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

				if (0 == dynamic_cast<CTileNode*>(m_vecTileHendon[iIndex])->Get_Option())
				{
					HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
					HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

					Rectangle(hDC, m_vecTileHendon[iIndex]->Get_Rect().left + (int)fScrollX, m_vecTileHendon[iIndex]->Get_Rect().top + (int)fScrollY,
						m_vecTileHendon[iIndex]->Get_Rect().right + (int)fScrollX, m_vecTileHendon[iIndex]->Get_Rect().bottom + (int)fScrollY);

					SelectObject(hDC, oldBrush);
					DeleteObject(myBrush);
				}
				else
				{
					HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_vecTileHendon[iIndex]->Get_FrameKey());

					GdiTransparentBlt(hDC,
						m_vecTileHendon[iIndex]->Get_Rect().left + (long)fScrollX,
						m_vecTileHendon[iIndex]->Get_Rect().top + (long)fScrollY,
						(int)m_vecTileHendon[iIndex]->Get_Info().fCX,
						(int)m_vecTileHendon[iIndex]->Get_Info().fCY,
						hMemDC,
						0,
						0,
						30,
						30,
						RGB(255, 0, 255));
				}
			}
		}
	}
	else if (SC_EDIT_NEST == CSceneMgr::Get_Instance()->GetCurSceneType()) // ||
		// SC_HENDON == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		for (int i = iCullY; i < iMaxY; ++i)
		{
			for (int j = iCullX; j < iMaxX; ++j)
			{
				// 1���� �����̹Ƿ� �ش� ������� �ε����� ���
				int	iIndex = i * NEST_TILEX + j;

				// ���� ó��
				if (0 > iIndex || m_vecTileNest.size() <= (size_t)iIndex)
					continue;

				float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
				float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

				if (0 == dynamic_cast<CTileNode*>(m_vecTileNest[iIndex])->Get_Option())
				{
					HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
					HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

					Rectangle(hDC, m_vecTileNest[iIndex]->Get_Rect().left + (int)fScrollX, m_vecTileNest[iIndex]->Get_Rect().top + (int)fScrollY,
						m_vecTileNest[iIndex]->Get_Rect().right + (int)fScrollX, m_vecTileNest[iIndex]->Get_Rect().bottom + (int)fScrollY);

					SelectObject(hDC, oldBrush);
					DeleteObject(myBrush);
				}
				else
				{
					HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_vecTileNest[iIndex]->Get_FrameKey());

					GdiTransparentBlt(hDC,
						m_vecTileNest[iIndex]->Get_Rect().left + (long)fScrollX,
						m_vecTileNest[iIndex]->Get_Rect().top + (long)fScrollY,
						(int)m_vecTileNest[iIndex]->Get_Info().fCX,
						(int)m_vecTileNest[iIndex]->Get_Info().fCY,
						hMemDC,
						0,
						0,
						30,
						30,
						RGB(255, 0, 255));
				}
			}
		}
	}
	else if (SC_EDIT_ALFHLYRA == CSceneMgr::Get_Instance()->GetCurSceneType()) // ||
		// SC_ALFHLYRA == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		for (int i = iCullY; i < iMaxY; ++i)
		{
			for (int j = iCullX; j < iMaxX; ++j)
			{
				// 1���� �����̹Ƿ� �ش� ������� �ε����� ���
				int	iIndex = i * ALFHLYRA_TILEX + j;

				// ���� ó��
				if (0 > iIndex || m_vecTileAlfhlyra.size() <= (size_t)iIndex)
					continue;

				float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
				float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

				if (0 == dynamic_cast<CTileNode*>(m_vecTileAlfhlyra[iIndex])->Get_Option())
				{
					HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
					HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

					Rectangle(hDC, m_vecTileAlfhlyra[iIndex]->Get_Rect().left + (int)fScrollX, m_vecTileAlfhlyra[iIndex]->Get_Rect().top + (int)fScrollY,
						m_vecTileAlfhlyra[iIndex]->Get_Rect().right + (int)fScrollX, m_vecTileAlfhlyra[iIndex]->Get_Rect().bottom + (int)fScrollY);

					SelectObject(hDC, oldBrush);
					DeleteObject(myBrush);
				}
				else
				{
					HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_vecTileAlfhlyra[iIndex]->Get_FrameKey());

					GdiTransparentBlt(hDC,
						m_vecTileAlfhlyra[iIndex]->Get_Rect().left + (long)fScrollX,
						m_vecTileAlfhlyra[iIndex]->Get_Rect().top + (long)fScrollY,
						(int)m_vecTileAlfhlyra[iIndex]->Get_Info().fCX,
						(int)m_vecTileAlfhlyra[iIndex]->Get_Info().fCY,
						hMemDC,
						0,
						0,
						30,
						30,
						RGB(255, 0, 255));
				}
			}
		}
	}
	else if (SC_EDIT_RESHIPON1 == CSceneMgr::Get_Instance()->GetCurSceneType()) // ||
		// SC_ALFHLYRA == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		for (int i = iCullY; i < iMaxY; ++i)
		{
			for (int j = iCullX; j < iMaxX; ++j)
			{
				// 1���� �����̹Ƿ� �ش� ������� �ε����� ���
				int	iIndex = i * RESHIPON1_TILEX + j;

				// ���� ó��
				if (0 > iIndex || m_vecTileReshipon1.size() <= (size_t)iIndex)
					continue;

				float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
				float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

				if (0 == dynamic_cast<CTileNode*>(m_vecTileReshipon1[iIndex])->Get_Option())
				{
					HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
					HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

					Rectangle(hDC, m_vecTileReshipon1[iIndex]->Get_Rect().left + (int)fScrollX, m_vecTileReshipon1[iIndex]->Get_Rect().top + (int)fScrollY,
						m_vecTileReshipon1[iIndex]->Get_Rect().right + (int)fScrollX, m_vecTileReshipon1[iIndex]->Get_Rect().bottom + (int)fScrollY);

					SelectObject(hDC, oldBrush);
					DeleteObject(myBrush);
				}
				else
				{
					HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_vecTileReshipon1[iIndex]->Get_FrameKey());

					GdiTransparentBlt(hDC,
						m_vecTileReshipon1[iIndex]->Get_Rect().left + (long)fScrollX,
						m_vecTileReshipon1[iIndex]->Get_Rect().top + (long)fScrollY,
						(int)m_vecTileReshipon1[iIndex]->Get_Info().fCX,
						(int)m_vecTileReshipon1[iIndex]->Get_Info().fCY,
						hMemDC,
						0,
						0,
						30,
						30,
						RGB(255, 0, 255));
				}
			}
		}
	}
	else if (SC_EDIT_RESHIPON2 == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		for (int i = iCullY; i < iMaxY; ++i)
		{
			for (int j = iCullX; j < iMaxX; ++j)
			{
				// 1���� �����̹Ƿ� �ش� ������� �ε����� ���
				int	iIndex = i * RESHIPON2_TILEX + j;

				// ���� ó��
				if (0 > iIndex || m_vecTileReshipon2.size() <= (size_t)iIndex)
					continue;

				float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
				float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

				if (0 == dynamic_cast<CTileNode*>(m_vecTileReshipon2[iIndex])->Get_Option())
				{
					HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
					HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

					Rectangle(hDC, m_vecTileReshipon2[iIndex]->Get_Rect().left + (int)fScrollX, m_vecTileReshipon2[iIndex]->Get_Rect().top + (int)fScrollY,
						m_vecTileReshipon2[iIndex]->Get_Rect().right + (int)fScrollX, m_vecTileReshipon2[iIndex]->Get_Rect().bottom + (int)fScrollY);

					SelectObject(hDC, oldBrush);
					DeleteObject(myBrush);
				}
				else
				{
					HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_vecTileReshipon2[iIndex]->Get_FrameKey());

					GdiTransparentBlt(hDC,
						m_vecTileReshipon2[iIndex]->Get_Rect().left + (long)fScrollX,
						m_vecTileReshipon2[iIndex]->Get_Rect().top + (long)fScrollY,
						(int)m_vecTileReshipon2[iIndex]->Get_Info().fCX,
						(int)m_vecTileReshipon2[iIndex]->Get_Info().fCY,
						hMemDC,
						0,
						0,
						30,
						30,
						RGB(255, 0, 255));
				}
			}
		}
	}
	else if (SC_EDIT_SKASARAIR == CSceneMgr::Get_Instance()->GetCurSceneType()||
			 SC_EDIT_STOMPATH == CSceneMgr::Get_Instance()->GetCurSceneType()) // ||
		// SC_SKASARAIR == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		for (int i = iCullY; i < iMaxY; ++i)
		{
			for (int j = iCullX; j < iMaxX; ++j)
			{
				// 1���� �����̹Ƿ� �ش� ������� �ε����� ���
				int	iIndex = i * SKASARAIR_TILEX + j;

				// ���� ó��
				if (0 > iIndex || m_vecTileSkasaRair.size() <= (size_t)iIndex)
					continue;

				float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
				float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

				if (0 == dynamic_cast<CTileNode*>(m_vecTileSkasaRair[iIndex])->Get_Option())
				{
					HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
					HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

					Rectangle(hDC, m_vecTileSkasaRair[iIndex]->Get_Rect().left + (int)fScrollX, m_vecTileSkasaRair[iIndex]->Get_Rect().top + (int)fScrollY,
						m_vecTileSkasaRair[iIndex]->Get_Rect().right + (int)fScrollX, m_vecTileSkasaRair[iIndex]->Get_Rect().bottom + (int)fScrollY);

					SelectObject(hDC, oldBrush);
					DeleteObject(myBrush);
				}
				else
				{
					HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_vecTileSkasaRair[iIndex]->Get_FrameKey());

					GdiTransparentBlt(hDC,
						m_vecTileSkasaRair[iIndex]->Get_Rect().left + (long)fScrollX,
						m_vecTileSkasaRair[iIndex]->Get_Rect().top + (long)fScrollY,
						(int)m_vecTileSkasaRair[iIndex]->Get_Info().fCX,
						(int)m_vecTileSkasaRair[iIndex]->Get_Info().fCY,
						hMemDC,
						0,
						0,
						30,
						30,
						RGB(255, 0, 255));
				}
			}
		}
	}
}

void CTileMgr::Release()
{
	for_each(m_vecTileSeria.begin(), m_vecTileSeria.end(), DeleteObj());
	m_vecTileSeria.clear();
	m_vecTileSeria.shrink_to_fit();

	for_each(m_vecTileHendon.begin(), m_vecTileHendon.end(), DeleteObj());
	m_vecTileHendon.clear();
	m_vecTileHendon.shrink_to_fit();

	for_each(m_vecTileNest.begin(), m_vecTileNest.end(), DeleteObj());
	m_vecTileNest.clear();
	m_vecTileNest.shrink_to_fit();

	for_each(m_vecTileAlfhlyra.begin(), m_vecTileAlfhlyra.end(), DeleteObj());
	m_vecTileAlfhlyra.clear();
	m_vecTileAlfhlyra.shrink_to_fit();

	for_each(m_vecTileReshipon1.begin(), m_vecTileReshipon1.end(), DeleteObj());
	m_vecTileReshipon1.clear();
	m_vecTileReshipon1.shrink_to_fit();

	for_each(m_vecTileReshipon2.begin(), m_vecTileReshipon2.end(), DeleteObj());
	m_vecTileReshipon2.clear();
	m_vecTileReshipon2.shrink_to_fit();

	for_each(m_vecTileSkasaRair.begin(), m_vecTileSkasaRair.end(), DeleteObj());
	m_vecTileSkasaRair.clear();
	m_vecTileSkasaRair.shrink_to_fit();
}

// ���콺�� Ÿ���� Ŭ���ϸ� ~ (���콺 ��ǥpt, DrawID, Image �ɼ�)
void CTileMgr::Picking(POINT pt, int _iDrawID, int _iOption)
{
	DWORD currentTime = GetTickCount();
	// ���� ȭ�� ��(800, 600)������ Ÿ�� ��ǥ�� ���� Ÿ���� Index�� ����
	int	x = pt.x / TILECX; 
	int	y = pt.y / TILECY;

	int iIndex = 0;

	if (SC_EDIT_SERIAROOM == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		iIndex = y * SERIA_TILEX + x;
	}
	else if (SC_EDIT_HENDON == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		iIndex = y * HENDON_TILEX + x;
	}
	else if (SC_EDIT_NEST == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		iIndex = y * NEST_TILEX + x;
	}
	else if (SC_EDIT_ALFHLYRA == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		iIndex = y * ALFHLYRA_TILEX + x;
	}
	else if (SC_EDIT_RESHIPON1 == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		iIndex = y * RESHIPON1_TILEX + x;
	}
	else if (SC_EDIT_RESHIPON2 == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		iIndex = y * RESHIPON2_TILEX + x;
	}
	else if (SC_EDIT_SKASARAIR == CSceneMgr::Get_Instance()->GetCurSceneType() ||
			 SC_EDIT_STOMPATH == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		iIndex = y * SKASARAIR_TILEX + x;
	}


	// ���� ó��
	if (SC_EDIT_SERIAROOM == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		if (0 > iIndex || m_vecTileSeria.size() <= size_t(iIndex))
			return;
	}
	else if (SC_EDIT_HENDON == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		if (0 > iIndex || m_vecTileHendon.size() <= size_t(iIndex))
			return;
	}
	else if (SC_EDIT_NEST == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		if (0 > iIndex || m_vecTileNest.size() <= size_t(iIndex))
			return;
	}
	else if (SC_EDIT_ALFHLYRA == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		if (0 > iIndex || m_vecTileAlfhlyra.size() <= size_t(iIndex))
			return;
	}
	else if (SC_EDIT_RESHIPON1 == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		if (0 > iIndex || m_vecTileReshipon1.size() <= size_t(iIndex))
			return;
	}
	else if (SC_EDIT_RESHIPON2 == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		if (0 > iIndex || m_vecTileReshipon2.size() <= size_t(iIndex))
			return;
	}
	else if (SC_EDIT_SKASARAIR == CSceneMgr::Get_Instance()->GetCurSceneType() ||
			 SC_EDIT_STOMPATH == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		if (0 > iIndex || m_vecTileSkasaRair.size() <= size_t(iIndex))
			return;
	}


	if (SC_EDIT_SERIAROOM == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		if (currentTime - m_lPickedTime > 100)
		{
			dynamic_cast<CTileNode*>(m_vecTileSeria[iIndex])->Set_DrawID(_iDrawID);
			dynamic_cast<CTileNode*>(m_vecTileSeria[iIndex])->Set_Option2();
			m_lPickedTime = GetTickCount();
		}
	}
	else if (SC_EDIT_HENDON == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		if (currentTime - m_lPickedTime > 100)
		{
			dynamic_cast<CTileNode*>(m_vecTileHendon[iIndex])->Set_DrawID(_iDrawID);
			dynamic_cast<CTileNode*>(m_vecTileHendon[iIndex])->Set_Option2();
			m_lPickedTime = GetTickCount();
		}
	}
	else if (SC_EDIT_NEST == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		if (currentTime - m_lPickedTime > 100)
		{
			dynamic_cast<CTileNode*>(m_vecTileNest[iIndex])->Set_DrawID(_iDrawID);
			dynamic_cast<CTileNode*>(m_vecTileNest[iIndex])->Set_Option2();
			m_lPickedTime = GetTickCount();
		}
	}
	else if (SC_EDIT_ALFHLYRA == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		if (currentTime - m_lPickedTime > 100)
		{
			dynamic_cast<CTileNode*>(m_vecTileAlfhlyra[iIndex])->Set_DrawID(_iDrawID);
			dynamic_cast<CTileNode*>(m_vecTileAlfhlyra[iIndex])->Set_Option2();
			m_lPickedTime = GetTickCount();
		}
	}
	else if (SC_EDIT_RESHIPON1 == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		if (currentTime - m_lPickedTime > 100)
		{
			dynamic_cast<CTileNode*>(m_vecTileReshipon1[iIndex])->Set_DrawID(_iDrawID);
			dynamic_cast<CTileNode*>(m_vecTileReshipon1[iIndex])->Set_Option2();
			m_lPickedTime = GetTickCount();
		}
	}
	else if (SC_EDIT_RESHIPON2 == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		if (currentTime - m_lPickedTime > 100)
		{
			dynamic_cast<CTileNode*>(m_vecTileReshipon2[iIndex])->Set_DrawID(_iDrawID);
			dynamic_cast<CTileNode*>(m_vecTileReshipon2[iIndex])->Set_Option2();
			m_lPickedTime = GetTickCount();
		}
	}
	else if (SC_EDIT_SKASARAIR == CSceneMgr::Get_Instance()->GetCurSceneType() ||
			 SC_EDIT_STOMPATH == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		if (currentTime - m_lPickedTime > 100)
		{
			dynamic_cast<CTileNode*>(m_vecTileSkasaRair[iIndex])->Set_DrawID(_iDrawID);
			dynamic_cast<CTileNode*>(m_vecTileSkasaRair[iIndex])->Set_Option2();
			m_lPickedTime = GetTickCount();
		}
	}
}

void CTileMgr::Save_Tile(const WCHAR* _filepath)
{
	HANDLE		hFile = CreateFile(_filepath, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	int		iDrawID(0), iOption(0);
	DWORD	dwByte(0);

	if (SC_EDIT_SERIAROOM == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_SERIAROOM == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		for (auto& iter : m_vecTileSeria)
		{
			iDrawID = dynamic_cast<CTileNode*>(iter)->Get_DrawID();
			iOption = dynamic_cast<CTileNode*>(iter)->Get_Option();

			WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
			WriteFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);
		}
	}
	else if (SC_EDIT_HENDON == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_HENDON == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		for (auto& iter : m_vecTileHendon)
		{
			iDrawID = dynamic_cast<CTileNode*>(iter)->Get_DrawID();
			iOption = dynamic_cast<CTileNode*>(iter)->Get_Option();

			WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
			WriteFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);
		}
	}
	else if (SC_EDIT_NEST == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_NEST == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		for (auto& iter : m_vecTileNest)
		{
			iDrawID = dynamic_cast<CTileNode*>(iter)->Get_DrawID();
			iOption = dynamic_cast<CTileNode*>(iter)->Get_Option();

			WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
			WriteFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);
		}
	}
	else if (SC_EDIT_ALFHLYRA == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_ALFHLYRA == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		for (auto& iter : m_vecTileAlfhlyra)
		{
			iDrawID = dynamic_cast<CTileNode*>(iter)->Get_DrawID();
			iOption = dynamic_cast<CTileNode*>(iter)->Get_Option();

			WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
			WriteFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);
		}
	}
	else if (SC_EDIT_RESHIPON1 == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_RESHIPON1 == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		for (auto& iter : m_vecTileReshipon1)
		{
			iDrawID = dynamic_cast<CTileNode*>(iter)->Get_DrawID();
			iOption = dynamic_cast<CTileNode*>(iter)->Get_Option();

			WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
			WriteFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);
		}
	}
	else if (SC_EDIT_RESHIPON2 == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_RESHIPON2 == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		for (auto& iter : m_vecTileReshipon2)
		{
			iDrawID = dynamic_cast<CTileNode*>(iter)->Get_DrawID();
			iOption = dynamic_cast<CTileNode*>(iter)->Get_Option();

			WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
			WriteFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);
		}
	}
	else if (SC_EDIT_SKASARAIR == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_SKASARAIR == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_EDIT_STOMPATH == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_STOMPATH == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		for (auto& iter : m_vecTileSkasaRair)
		{
			iDrawID = dynamic_cast<CTileNode*>(iter)->Get_DrawID();
			iOption = dynamic_cast<CTileNode*>(iter)->Get_Option();

			WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
			WriteFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);
		}
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, L"Tile Save", L"����", MB_OK);
}

void CTileMgr::Load_Tile(const WCHAR* _filepath)
{
	HANDLE		hFile = CreateFile(_filepath,
		GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	INFO	tInfo{};
	int		iDrawID(0), iOption(0);
	DWORD	dwByte(0);

	// Release();

	if (SC_EDIT_SERIAROOM == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_SERIAROOM == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		for (auto& Tile : m_vecTileSeria)
		{
			Safe_Delete(Tile);
		}
		m_vecTileSeria.clear();
		while (true)
		{
			{
				ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
				ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
				ReadFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);

				if (0 == dwByte)
					break;

				CObj* pObj = CAbstractFactory<CTileNode>::Create_Obj(tInfo.fX, tInfo.fY);
				dynamic_cast<CTileNode*>(pObj)->Set_DrawID(iDrawID);
				dynamic_cast<CTileNode*>(pObj)->Set_Option(iOption);

				m_vecTileSeria.push_back(pObj);
			}
		}
	}
	else if (SC_EDIT_HENDON == CSceneMgr::Get_Instance()->GetCurSceneType() || 
			SC_HENDON == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		for (auto& Tile : m_vecTileHendon)
		{
			Safe_Delete(Tile);
		}
		m_vecTileHendon.clear();
		while (true)
		{
			{
				ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
				ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
				ReadFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);

				if (0 == dwByte)
					break;

				CObj* pObj = CAbstractFactory<CTileNode>::Create_Obj(tInfo.fX, tInfo.fY);
				dynamic_cast<CTileNode*>(pObj)->Set_DrawID(iDrawID);
				dynamic_cast<CTileNode*>(pObj)->Set_Option(iOption);

				m_vecTileHendon.push_back(pObj);
			}
		}
	}
	else if (SC_EDIT_NEST == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_NEST == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		for (auto& Tile : m_vecTileNest)
		{
			Safe_Delete(Tile);
		}
		m_vecTileNest.clear();
		while (true)
		{
			{
				ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
				ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
				ReadFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);

				if (0 == dwByte)
					break;

				CObj* pObj = CAbstractFactory<CTileNode>::Create_Obj(tInfo.fX, tInfo.fY);
				dynamic_cast<CTileNode*>(pObj)->Set_DrawID(iDrawID);
				dynamic_cast<CTileNode*>(pObj)->Set_Option(iOption);

				m_vecTileNest.push_back(pObj);
			}
		}
	}
	else if (SC_EDIT_ALFHLYRA == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_ALFHLYRA == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		for (auto& Tile : m_vecTileAlfhlyra)
		{
			Safe_Delete(Tile);
		}
		m_vecTileAlfhlyra.clear();
		while (true)
		{
			{
				ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
				ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
				ReadFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);

				if (0 == dwByte)
					break;

				CObj* pObj = CAbstractFactory<CTileNode>::Create_Obj(tInfo.fX, tInfo.fY);
				dynamic_cast<CTileNode*>(pObj)->Set_DrawID(iDrawID);
				dynamic_cast<CTileNode*>(pObj)->Set_Option(iOption);

				m_vecTileAlfhlyra.push_back(pObj);
			}
		}
	}
	else if (SC_EDIT_RESHIPON1 == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_RESHIPON1 == CSceneMgr::Get_Instance()->GetCurSceneType())
		{
			for (auto& Tile : m_vecTileReshipon1)
			{
				Safe_Delete(Tile);
			}
			m_vecTileReshipon1.clear();
			while (true)
			{
				{
					ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
					ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
					ReadFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);

					if (0 == dwByte)
						break;

					CObj* pObj = CAbstractFactory<CTileNode>::Create_Obj(tInfo.fX, tInfo.fY);
					dynamic_cast<CTileNode*>(pObj)->Set_DrawID(iDrawID);
					dynamic_cast<CTileNode*>(pObj)->Set_Option(iOption);

					m_vecTileReshipon1.push_back(pObj);
				}
			}
			}
	else if (SC_EDIT_RESHIPON2 == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_RESHIPON2 == CSceneMgr::Get_Instance()->GetCurSceneType())
		{
			for (auto& Tile : m_vecTileReshipon2)
			{
				Safe_Delete(Tile);
			}
			m_vecTileReshipon2.clear();
			while (true)
			{
				{
					ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
					ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
					ReadFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);

					if (0 == dwByte)
						break;

					CObj* pObj = CAbstractFactory<CTileNode>::Create_Obj(tInfo.fX, tInfo.fY);
					dynamic_cast<CTileNode*>(pObj)->Set_DrawID(iDrawID);
					dynamic_cast<CTileNode*>(pObj)->Set_Option(iOption);

					m_vecTileReshipon2.push_back(pObj);
				}
			}
		}

	else if (SC_EDIT_SKASARAIR == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_SKASARAIR == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_EDIT_STOMPATH == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_STOMPATH == CSceneMgr::Get_Instance()->GetCurSceneType())
		{
			for (auto& Tile : m_vecTileSkasaRair)
			{
				Safe_Delete(Tile);
			}
			m_vecTileSkasaRair.clear();
			while (true)
			{
				{
					ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
					ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
					ReadFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);

					if (0 == dwByte)
						break;

					CObj* pObj = CAbstractFactory<CTileNode>::Create_Obj(tInfo.fX, tInfo.fY);
					dynamic_cast<CTileNode*>(pObj)->Set_DrawID(iDrawID);
					dynamic_cast<CTileNode*>(pObj)->Set_Option(iOption);

					m_vecTileSkasaRair.push_back(pObj);
				}
			}
			}

	CloseHandle(hFile);

	// MessageBox(g_hWnd, L"Tile Load", L"����", MB_OK);
}
