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

// 정수와 구하고 싶은 자릿수를 집어 넣으면, 그 자릿수가 무슨 수인지 뱉어주는 함수
// 여기서 m_iComboCount를 _iNum 매개변수로 넣는다
int CScene::Get_ComboNumIndex(int _iNum, int _iIndex)
{
	return (_iNum / (int)pow(10, _iIndex - 1)) % 10;
}

void CScene::Draw_ComboFont(int _iComboCount)
{
	int n = _iComboCount;	// n : 콤보 카운트
	if (0 == m_iComboCount)
		return;

	int iCount = 0;
	while (n != 0)
	{
		n = n / 10;
		++iCount;		// iCount : 콤보 카운트의 자리수 
	}

	// 이전에 생긴 콤보 폰트를 지워준다
	if (!CObjMgr::Get_Instance()->GetObjList(OBJ_COMBOFONT).empty())
		CObjMgr::Get_Instance()->Delete_ID(OBJ_COMBOFONT);

	// 뜬 데미지의 자리수까지 반복
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