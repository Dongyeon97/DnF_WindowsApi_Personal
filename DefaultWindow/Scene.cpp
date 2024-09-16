#include "stdafx.h"
#include "Scene.h"
#include "ObjMgr.h"
#include "UI_Combo.h"

int CScene::m_iComboCount = 0;

CScene::CScene()
	: m_dwTime(0)
{
}


CScene::~CScene()
{
}

// ������ ���ϰ� ���� �ڸ����� ���� ������, �� �ڸ����� ���� ������ ����ִ� �Լ�
// ���⼭ m_iComboCount�� _iNum �Ű������� �ִ´�
int CScene::Get_ComboNumIndex(int _iNum, int _iIndex)
{
	return (_iNum / (int)pow(10, _iIndex - 1)) % 10;
}

void CScene::Draw_ComboFont(int _iComboCount)
{
	int n = _iComboCount;	// n : �޺� ī��Ʈ
	if (0 == m_iComboCount)
		return;

	int iCount = 0;
	while (n != 0)
	{
		n = n / 10;
		++iCount;		// iCount : �޺� ī��Ʈ�� �ڸ��� 
	}

	// ������ ���� �޺� ��Ʈ�� �����ش�
	if (!CObjMgr::Get_Instance()->GetObjList(OBJ_COMBOFONT).empty())
		CObjMgr::Get_Instance()->Delete_ID(OBJ_COMBOFONT);

	// �� �������� �ڸ������� �ݺ�
	for (int i = 1; i <= iCount; ++i)
	{
		int iResult = Get_ComboNumIndex(_iComboCount, i);

		CObjMgr::Get_Instance()->Add_Object(OBJ_COMBOFONT,
			CAbstractFactory<CUI_Combo>::
			Create_Obj(740.f - 27 * i, 390.f, 2.f, 0.f, 1.5f, iResult, L"ComboNumber"));
	}

	CObjMgr::Get_Instance()->Add_Object(OBJ_COMBOFONT,
		CAbstractFactory<CUI_Combo>::
		Create_Obj(710.f, 395.f, 2.f, 0.f, 1.5f, 2, L"Combo_Bonus"));
	CObjMgr::Get_Instance()->GetObjList(OBJ_COMBOFONT).back()->Set_ScaleX(154.f);
	CObjMgr::Get_Instance()->GetObjList(OBJ_COMBOFONT).back()->Set_ScaleY(16.f);
}