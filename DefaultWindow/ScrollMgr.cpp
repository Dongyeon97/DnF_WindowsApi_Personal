#include "stdafx.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"

CScrollMgr* CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr() : m_fScrollX(0.f), m_fScrollY(0.f)
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Scroll_Lock()
{
	// 세리아방, 세리아방 에딧인 경우 스크롤 제한
	if (SC_SERIAROOM == CSceneMgr::Get_Instance()->GetCurSceneType() || 
		SC_EDIT_SERIAROOM == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		if (0.f < m_fScrollX)
			m_fScrollX = 0.f;

		if (0.f < m_fScrollY)
			m_fScrollY = 0.f;

		if (m_fScrollX < WINCX - SERIAROOM_SIZEX)
			m_fScrollX = WINCX - SERIAROOM_SIZEX;

		if (m_fScrollY < WINCY - SERIAROOM_SIZEY)
			m_fScrollY = WINCY - SERIAROOM_SIZEY;
	}

	// 헨돈마이어, 헨돈마이어 에딧인 경우 스크롤 제한
	if (SC_HENDON == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_EDIT_HENDON == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		if (0.f < m_fScrollX)
			m_fScrollX = 0.f;

		if (0.f < m_fScrollY)
			m_fScrollY = 0.f;

		if (m_fScrollX < WINCX - HENDON_SIZEX)
			m_fScrollX = WINCX - HENDON_SIZEX;

		if (m_fScrollY < WINCY - HENDON_SIZEY)
			m_fScrollY = WINCY - HENDON_SIZEY;
	}

	// 천공의 둥지, 천공의 둥지 에딧인 경우 스크롤 제한
	if (SC_NEST == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_EDIT_NEST == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		if (0.f < m_fScrollX)
			m_fScrollX = 0.f;

		if (0.f < m_fScrollY)
			m_fScrollY = 0.f;

		if (m_fScrollX < WINCX - NEST_SIZEX)
			m_fScrollX = WINCX - NEST_SIZEX;

		if (m_fScrollY < WINCY - NEST_SIZEY)
			m_fScrollY = WINCY - NEST_SIZEY;
	}

	// 알프라이라, 알프라이라 에딧인 경우 스크롤 제한
	if (SC_ALFHLYRA == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_EDIT_ALFHLYRA == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		if (0.f < m_fScrollX)
			m_fScrollX = 0.f;

		if (0.f < m_fScrollY)
			m_fScrollY = 0.f;

		if (m_fScrollX < WINCX - ALFHLYRA_SIZEX)
			m_fScrollX = WINCX - ALFHLYRA_SIZEX;

		if (m_fScrollY < WINCY - ALFHLYRA_SIZEY)
			m_fScrollY = WINCY - ALFHLYRA_SIZEY;
	}

	// 레쉬폰1, 레쉬폰1 에딧인 경우 스크롤 제한
	if (SC_RESHIPON1== CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_EDIT_RESHIPON1 == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		if (0.f < m_fScrollX)
			m_fScrollX = 0.f;

		if (0.f < m_fScrollY)
			m_fScrollY = 0.f;

		if (m_fScrollX < WINCX - RESHIPON1_SIZEX)
			m_fScrollX = WINCX - RESHIPON1_SIZEX;

		if (m_fScrollY < WINCY - RESHIPON1_SIZEY)
			m_fScrollY = WINCY - RESHIPON1_SIZEY;
	}

	// 레쉬폰2, 레쉬폰2 에딧인 경우 스크롤 제한
	if (SC_RESHIPON2 == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_EDIT_RESHIPON2 == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		if (0.f < m_fScrollX)
			m_fScrollX = 0.f;

		if (0.f < m_fScrollY)
			m_fScrollY = 0.f;

		if (m_fScrollX < WINCX - RESHIPON2_SIZEX)
			m_fScrollX = WINCX - RESHIPON2_SIZEX;

		if (m_fScrollY < WINCY - RESHIPON2_SIZEY)
			m_fScrollY = WINCY - RESHIPON2_SIZEY;
	}

	// 스톰패스, 스톰패스 에딧인 경우 스크롤 제한
	if (SC_STOMPATH == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_EDIT_STOMPATH == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		if (0.f < m_fScrollX)
			m_fScrollX = 0.f;

		if (0.f < m_fScrollY)
			m_fScrollY = 0.f;

		if (m_fScrollX < WINCX - STOMPATH_SIZEX)
			m_fScrollX = WINCX - STOMPATH_SIZEX;

		if (m_fScrollY < WINCY - STOMPATH_SIZEY)
			m_fScrollY = WINCY - STOMPATH_SIZEY;
	}

	// 스카사의 레어, 스카사의 레어 에딧인 경우 스크롤 제한
	if (SC_SKASARAIR == CSceneMgr::Get_Instance()->GetCurSceneType() ||
		SC_EDIT_SKASARAIR == CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		if (0.f < m_fScrollX)
			m_fScrollX = 0.f;

		if (0.f < m_fScrollY)
			m_fScrollY = 0.f;

		if (m_fScrollX < WINCX - SKASARAIR_SIZEX)
			m_fScrollX = WINCX - SKASARAIR_SIZEX;
								 
		if (m_fScrollY < WINCY - SKASARAIR_SIZEY)
			m_fScrollY = WINCY - SKASARAIR_SIZEY;
	}
}

void CScrollMgr::ScrollX_Fix(float _x)
{
	m_fScrollX = _x;
}

void CScrollMgr::ScrollY_Fix(float _y)
{
	m_fScrollY = _y;
}
