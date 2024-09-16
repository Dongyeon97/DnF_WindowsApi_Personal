#include "stdafx.h"
#include "UI_Hp.h"

#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

CUI_Hp::CUI_Hp()
{
}

CUI_Hp::~CUI_Hp()
{
}

void CUI_Hp::Initialize()
{
	m_eRender = UI;

	m_bOpened = true;
}

int CUI_Hp::Update()
{
	m_eRender = UI;

	return 0;
}

void CUI_Hp::Late_Update()
{
}

void CUI_Hp::Render(HDC hDC)
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

		float fHpRatio = pPlayer->Get_Info().fHp / pPlayer->Get_Info().fMaxHp;

		if (0 == fHpRatio)
			return;

		GdiTransparentBlt(hDC,
			m_tRect.left + 13,
			(m_tRect.top + 524) + int((m_tInfo.fCY) * (1.f - fHpRatio)),
			(int)m_tInfo.fCX,
			(int)(m_tInfo.fCY * fHpRatio),
			hMpDC,
			0,
			int((m_tInfo.fCY) * (1.f - fHpRatio)),
			(int)m_tInfo.fCX,
			(int)(m_tInfo.fCY * fHpRatio),
			RGB(255, 0, 255));
	}
}

void CUI_Hp::Release()
{
}
