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

// state ���� : FSM(finite state machine : ���� ���� ���)�� ������� �ϴ� ��ü�� ����, �ڽ��� ���� �� �ִ� ������ ������ ���¸� �����ٴ� �ǹ��� ����
// ���� ���� ���� �� �� Ÿ�ӿ��� ���� �ϳ��� ���¸��� ���ϵ��� �����ϴ� ���