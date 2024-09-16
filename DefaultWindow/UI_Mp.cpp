#include "stdafx.h"
#include "UI_Mp.h"

#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

CUI_Mp::CUI_Mp()
{
}

CUI_Mp::~CUI_Mp()
{
}

void CUI_Mp::Initialize()
{
	m_eRender = UI;

	m_bOpened = true;
}

int CUI_Mp::Update()
{
	m_eRender = UI;
	return 0;
}

void CUI_Mp::Late_Update()
{

}

void CUI_Mp::Render(HDC hDC)
{
	if (SC_LOGO != CSceneMgr::Get_Instance()->GetCurSceneType() &&
		SC_MENU != CSceneMgr::Get_Instance()->GetCurSceneType() &&
		SC_EDIT_SERIAROOM != CSceneMgr::Get_Instance()->GetCurSceneType() &&
		SC_EDIT_HENDON != CSceneMgr::Get_Instance()->GetCurSceneType() &&
		SC_EDIT_NEST != CSceneMgr::Get_Instance()->GetCurSceneType() &&
		SC_EDIT_ALFHLYRA != CSceneMgr::Get_Instance()->GetCurSceneType() &&
		SC_EDIT_RESHIPON1 != CSceneMgr::Get_Instance()->GetCurSceneType() &&
		SC_EDIT_RESHIPON2 != CSceneMgr::Get_Instance()->GetCurSceneType())
	{
		HDC	hMpDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

		CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front();

		float fMpRatio = pPlayer->Get_Info().fMp / pPlayer->Get_Info().fMaxMp;

		if (0 == fMpRatio)
			return;

		GdiTransparentBlt(hDC,
			m_tRect.left + 732,
			(m_tRect.top + 524) + int((m_tInfo.fCY) * (1.f - fMpRatio)),
			(int)m_tInfo.fCX,
			(int)(m_tInfo.fCY * fMpRatio),
			hMpDC,
			0,
			int((m_tInfo.fCY) * (1.f - fMpRatio)),
			(int)m_tInfo.fCX,
			(int)(m_tInfo.fCY * fMpRatio),
			RGB(255, 0, 255));
	}
}

void CUI_Mp::Release()
{
}
