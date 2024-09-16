#include "stdafx.h"
#include "MyMenu.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "MyButton.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
#include "MousePoint.h"
#include "UI_Alpha.h"


CMyMenu::CMyMenu()
{
}


CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize()
{
	CSoundMgr::Get_Instance()->PlayBGM(L"Title.wav", g_fVolume);

	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Button_Start.bmp", L"Start");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Edit.bmp", L"Edit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Button_Exit.bmp", L"Exit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Logo/Logo2.bmp", L"Logo2");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Menu.bmp", L"Menu");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mouse/Mouse.bmp", L"Mouse");

	CObj*		pButton = CAbstractFactory<CMyButton>::Create_Obj(400.f, 550.f);
	pButton->Set_FrameKey(L"Start");
	pButton->Set_ScaleX(168.f);
	pButton->Set_ScaleY(45.f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pButton);

	pButton = CAbstractFactory<CMyButton>::Create_Obj(400.f, 400.f);
	pButton->Set_FrameKey(L"Edit");
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pButton);

	pButton = CAbstractFactory<CMyButton>::Create_Obj(650.f, 550.f);
	pButton->Set_FrameKey(L"Exit");
	pButton->Set_ScaleX(75.f);
	pButton->Set_ScaleY(21.f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pButton);

	pButton = CAbstractFactory<CMyButton>::Create_Obj(0.f, 0.f, 403.f, 274.f, L"Logo2");
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pButton);

	POINT	ptMouse{};					// ���콺 ������ ��ġ�� ������ POINT����
	GetCursorPos(&ptMouse);				// ���콺 ������ ��ġ�� �����ͼ� ������ ����
	ScreenToClient(g_hWnd, &ptMouse);	// ���� ������ â�� �´� ��ǥ�� �缳��

	CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CMouse>::Create_Obj(ptMouse.x, ptMouse.y, L"Mouse"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSEPOINT, CAbstractFactory<CMousePoint>::Create_Obj(ptMouse.x - 16.f, ptMouse.y - 16.f, L"MousePoint"));
}

int CMyMenu::Update()
{
	CObjMgr::Get_Instance()->Update();
	
	return 0;
}

void CMyMenu::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CMyMenu::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Logo");

	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CMyMenu::Release()
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_UI);
	for (size_t i = OBJ_PLAYER_ATTACK; i < OBJ_END; ++i)
	{
		if (OBJ_MAINUI != i && OBJ_PLAYER != i
			&& OBJ_MOUSE != i && OBJ_MOUSEPOINT != i
			&& OBJ_INVEN != i && OBJ_INVENITEM != i
			&& OBJ_STORE != i && OBJ_STOREITEM != i && OBJ_MYINFO != i
			&& OBJ_SKILLICON != i && OBJ_EQUIPMENT != i)
			CObjMgr::Get_Instance()->Delete_ID((OBJ_ID)i);
	}
	CSoundMgr::Get_Instance()->StopAll();
}
