#include "Logo.h"
#include "MyMenu.h"
#include "Edit_SeriaRoom.h"
#include "SeriaRoom.h"
#include "Edit_Hendon.h"
#include "Hendon.h"
#include "Edit_Nest.h"
#include "Nest.h"
#include "Edit_Alfhlyra.h"
#include "Alfhlyra.h"
#include "Edit_Reshipon1.h"
#include "Reshipon1.h"
#include "Edit_Reshipon2.h"
#include "Reshipon2.h"
#include "Edit_StomPath.h"
#include "StomPath.h"
#include "Edit_SkasaRair.h"
#include "SkasaRair.h"

class CSceneMgr
{
public:
	CSceneMgr();
	~CSceneMgr();
public:
	static CSceneMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CSceneMgr;

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
	static CSceneMgr* m_pInstance;

public:
	void		Scene_Change(SCENEID eID);

	void		Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();

	CScene*		Get_CurScene() { return m_pScene; }

	SCENEID		GetCurSceneType() { return m_eCurScene; }
	SCENEID		GetPreSceneType() { return m_ePreScene; }

private:
	CScene*				m_pScene;

	SCENEID				m_ePreScene;
	SCENEID				m_eCurScene;
};

// state 패턴 : FSM(finite state machine : 유한 상태 기계)을 기반으로 하는 객체의 상태, 자신이 취할 수 있는 유한한 개수의 상태를 가진다는 의미의 패턴
// 여러 개의 종류 중 한 타임에는 오직 하나의 상태만을 취하도록 설계하는 방법