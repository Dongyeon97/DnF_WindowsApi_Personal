#include "stdafx.h"
#include "Edit_Reshipon1.h"
#include "BmpMgr.h"
#include "TileMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"

CEdit_Reshipon1::CEdit_Reshipon1()
{
}

CEdit_Reshipon1::~CEdit_Reshipon1()
{
	Release();
}

void CEdit_Reshipon1::Initialize()
{
}

int CEdit_Reshipon1::Update()
{
	Key_Input();

	CTileMgr::Get_Instance()->Update();

	return 0;
}

void CEdit_Reshipon1::Late_Update()
{
	CTileMgr::Get_Instance()->Late_Update();
}

void CEdit_Reshipon1::Render(HDC hDC)
{
	float		fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	// "Ground"이미지는 MainGame에서 이미 Insert_bmp 되었음, 찾아오기만 하면 되는 상태
	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Reshipon1");

	// 배경 이미지는 특정 색상을 제거할 필요가 없으므로 그냥 BitBlt로 송출
	BitBlt(hDC, (int)fScrollX, (int)fScrollY, RESHIPON1_SIZEX, RESHIPON1_SIZEY, hGroundDC, 0, 0, SRCCOPY);

	CTileMgr::Get_Instance()->Render(hDC);
}

void CEdit_Reshipon1::Release()
{
}

void CEdit_Reshipon1::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_ScrollX(12.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_ScrollX(-12.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		CScrollMgr::Get_Instance()->Set_ScrollY(12.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		CScrollMgr::Get_Instance()->Set_ScrollY(-12.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
	{
		POINT pt{};
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CTileMgr::Get_Instance()->Picking(pt, 1, 0);
	}

	if (CKeyMgr::Get_Instance()->Key_Down('S'))
		CTileMgr::Get_Instance()->Save_Tile(L"../Image/Tile/Reshipon1_Tile.dat");

	if (CKeyMgr::Get_Instance()->Key_Down('L'))
		CTileMgr::Get_Instance()->Load_Tile(L"../Image/Tile/Reshipon1_Tile.dat");

	if (CKeyMgr::Get_Instance()->Key_Down(VK_BACK))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
		return;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('1'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_EDIT_SERIAROOM);
		return;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('2'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_EDIT_HENDON);
		return;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('3'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_EDIT_NEST);
		return;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('4'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_EDIT_ALFHLYRA);
		return;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('6'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_EDIT_RESHIPON2);
		return;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('7'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_EDIT_SKASARAIR);
		return;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('8'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_EDIT_STOMPATH);
		return;
	}
}