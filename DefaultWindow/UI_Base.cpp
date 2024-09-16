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

		GdiTransparentBlt(hDC,			// ���� ����(���������� �׸��� �׸�) DC�� ����
			m_tRect.left, // ���� ���� ��ġ�� ��ǥ�� ���� (x,y ��ǥ)
			m_tRect.top,
			(int)m_tInfo.fCX,	// ���� ���� ����, ���� ����
			(int)m_tInfo.fCY,
			hMemDC,				// ��Ʈ���� ������ �ִ� DC ����
			0,					// ��Ʈ���� ����� ���� X,Y ��ǥ
			0,
			(int)m_tInfo.fCX,	// ������ ��Ʈ���� ����, ���� ������
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));
	}
}

void CUI_Base::Release()
{
}