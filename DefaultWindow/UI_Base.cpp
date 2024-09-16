#include "stdafx.h"
#include "UI_Base.h"

#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

CUI_Base::CUI_Base()
{
}

CUI_Base::~CUI_Base()
{
}

void CUI_Base::Initialize()
{
	m_eRender = UI;
}

int CUI_Base::Update()
{
	return 0;
}

void CUI_Base::Late_Update()
{
}

void CUI_Base::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	if (SC_LOGO != CSceneMgr::Get_Instance()->GetCurSceneType() &&
		SC_MENU != CSceneMgr::Get_Instance()->GetCurSceneType() &&
		SC_EDIT_SERIAROOM != CSceneMgr::Get_Instance()->GetCurSceneType() &&
		SC_EDIT_HENDON != CSceneMgr::Get_Instance()->GetCurSceneType() &&
		SC_EDIT_NEST != CSceneMgr::Get_Instance()->GetCurSceneType() &&
		SC_EDIT_ALFHLYRA != CSceneMgr::Get_Instance()->GetCurSceneType() && 
		SC_EDIT_RESHIPON1 != CSceneMgr::Get_Instance()->GetCurSceneType() && 
		SC_EDIT_RESHIPON2 != CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

		GdiTransparentBlt(hDC,			// 복사 받을(최종적으로 그림을 그릴) DC를 전달
			m_tRect.left, // 복사 받을 위치의 좌표를 전달 (x,y 좌표)
			m_tRect.top,
			(int)m_tInfo.fCX,	// 복사 받을 가로, 세로 길이
			(int)m_tInfo.fCY,
			hMemDC,				// 비트맵을 가지고 있는 DC 전달
			0,					// 비트맵을 출력할 시작 X,Y 좌표
			0,
			(int)m_tInfo.fCX,	// 복사할 비트맵의 가로, 세로 사이즈
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));
	}
}

void CUI_Base::Release()
{
}