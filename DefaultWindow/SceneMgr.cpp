#include "stdafx.h"
#include "SceneMgr.h"

CSceneMgr*	CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr() : m_eCurScene(SC_LOGO), m_ePreScene(SC_END), m_pScene(nullptr)
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(SCENEID eID)
{
	m_eCurScene = eID;

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);

		switch (m_eCurScene)
		{
		case SC_LOGO:
			m_pScene = new CLogo;
			break;

		case SC_MENU:
			m_pScene = new CMyMenu;
			break;

		case SC_EDIT_SERIAROOM:
			m_pScene = new CEdit_SeriaRoom;
			break;

		case SC_SERIAROOM:
			m_pScene = new CSeriaRoom;
			break;

		case SC_EDIT_HENDON:
			m_pScene = new CEdit_Hendon;
			break;

		case SC_HENDON:
			m_pScene = new CHendon;
			break;

		case SC_EDIT_NEST:
			m_pScene = new CEdit_Nest;
			break;

		case SC_NEST:
			m_pScene = new CNest;
			break;

			// EDIT_ALFHRA
		case SC_EDIT_ALFHLYRA:
			m_pScene = new CEdit_Alfhlyra;
			break;

			// ALFHRA
		case SC_ALFHLYRA:
			m_pScene = new CAlfhlyra;
			break;

			// EDIT_RESHIPON1
		case SC_EDIT_RESHIPON1:
			m_pScene = new CEdit_Reshipon1;
			break;

			// RESHIPON1
		case SC_RESHIPON1:
			m_pScene = new CReshipon1;
			break;

			// EDIT_RESHIPON2
		case SC_EDIT_RESHIPON2:
			m_pScene = new CEdit_Reshipon2;
			break;

			// RESHIPON2
		case SC_RESHIPON2:
			m_pScene = new CReshipon2;
			break;

			// EDIT_STOMPATH
		case SC_EDIT_STOMPATH:
			m_pScene = new CEdit_StomPath;
			break;

			// STOMPATH
		case SC_STOMPATH:
			m_pScene = new CStomPath;
			break;

			// EDIT_SKASARAIR
		case SC_EDIT_SKASARAIR:
			m_pScene = new CEdit_SkasaRair;
			break;

			// SKASARAIR
		case SC_SKASARAIR:
			m_pScene = new CSkasaRair;
			break;
		}

		// 새로 바뀌어진 씬 Initialize()
		m_pScene->Initialize();

		// 그리고 새롭게 바뀌어진 SCENEID를 이전 씬ID로 저장
		m_ePreScene = m_eCurScene;
	}
}

void CSceneMgr::Update()
{
	m_pScene->Update();
}

void CSceneMgr::Late_Update()
{
	m_pScene->Late_Update();
}

// 여기서 매개변수인 hDC는 MainGame의 hBackDC로써, 미리 그려줄 DC를 의미한다.(더블 버퍼링을 위해)
void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneMgr::Release()
{
	Safe_Delete(m_pScene);
}
