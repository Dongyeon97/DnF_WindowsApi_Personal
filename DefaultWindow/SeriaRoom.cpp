#include "stdafx.h"
#include "SeriaRoom.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "CollsionMgr.h"
#include "SoundMgr.h"

#include "Player.h"
#include "Seria.h"
#include "UI_Base.h"
#include "UI_Hp.h"
#include "UI_Mp.h"
#include "UI_Inven.h"
#include "UI_Shop.h"
#include "UI_Alpha.h"
#include "UI_AlphaObject.h"
#include "UI_Info.h"

CSeriaRoom::CSeriaRoom()
{
}

CSeriaRoom::~CSeriaRoom()
{
	Release();
}

// 세리아방이 첫 시작화면이라 이것저것 작업이 많음
void CSeriaRoom::Initialize()
{
	// 메인 UI
	CObjMgr::Get_Instance()->Add_Object(OBJ_MAINUI, CAbstractFactory<CUI_Base>::Create_Obj(400.f, 300.f, 800.f, 600.f, L"UIBase"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MAINUI, CAbstractFactory<CUI_Hp>::Create_Obj(0.f, 0.f, 56.f, 56.f, L"UIHp"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MAINUI, CAbstractFactory<CUI_Mp>::Create_Obj(0.f, 0.f, 56.f, 56.f, L"UIMp"));

	// 브금
	CSoundMgr::Get_Instance()->PlayBGM(L"seria_gate.wav", g_fVolume);

	// 세리아
	CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, CAbstractFactory<CSeria>::Create_Obj(SERIAROOM_SIZEX * 0.5f, SERIAROOM_SIZEY * 0.5f + 30.f, L"Seria"));

	// 플레이어가 씬에 없다면 생성
	if (CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).empty())
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create_Obj());
	}
	CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Set_Pos((SERIAROOM_SIZEX * 0.5f), 550.f);
	dynamic_cast<CPlayer*> (CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front())->Set_PlayerState(CPlayer::PS_IDLE);
	CScrollMgr::Get_Instance()->ScrollX_Fix(-110.f);
	CScrollMgr::Get_Instance()->ScrollY_Fix(-250.f);

	// 타일 매니저
	CTileMgr::Get_Instance()->Initialize();
	CTileMgr::Get_Instance()->Load_Tile(L"../Image/Tile/SeriaRoom_Tile.dat");

	// < UI >
	// 인벤토리
	if (CObjMgr::Get_Instance()->GetObjList(OBJ_INVEN).empty())
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_INVEN, CAbstractFactory<CUI_Inven>::Create_Obj(630.f, 265.f, 260.f, 530.f, L"UIinven"));
		dynamic_cast<CUI_Inven*>((CObjMgr::Get_Instance()->GetObjList(OBJ_INVEN)).front())->Set_Render(false);
	}

	// 상점
	if (CObjMgr::Get_Instance()->GetObjList(OBJ_STORE).empty())
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_STORE, CAbstractFactory<CUI_Store>::Create_Obj(200.f, 300.f, 368.f, 464.f, L"UIstore2"));
		dynamic_cast<CUI_Store*>((CObjMgr::Get_Instance()->GetObjList(OBJ_STORE)).front())->Set_Render(false);
	}

	// 내정보
	if (CObjMgr::Get_Instance()->GetObjList(OBJ_MYINFO).empty())
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MYINFO, CAbstractFactory<CUI_Info>::Create_Obj(260.f, 300.f, 246.f, 279.f, L"UIState"));
		dynamic_cast<CUI_Info*>((CObjMgr::Get_Instance()->GetObjList(OBJ_MYINFO)).front())->Set_Render(false);
	}
}

int CSeriaRoom::Update()
{
	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	return 0;
}

void CSeriaRoom::Late_Update()
{
	// 세리아방에서 헨돈마이어로 갔을때
	if ((SERIAROOM_SIZEX * 0.5f - 200.f) < CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Info().fX &&
		(SERIAROOM_SIZEX * 0.5f + 200.f) >= CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Info().fX &&
		CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Info().fY > 620.f)
	{
		SCENEID ePreScene = CSceneMgr::Get_Instance()->GetPreSceneType();
		CSceneMgr::Get_Instance()->Scene_Change(SC_HENDON);
		if (SC_SERIAROOM == ePreScene)
		{
			CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Set_Pos(610.f, 280.f);
			CScrollMgr::Get_Instance()->Set_ScrollX(-100.f);
			CScrollMgr::Get_Instance()->Set_ScrollY(100.f);
			dynamic_cast<CPlayer*> (CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front())->Set_PlayerState(CPlayer::PS_IDLE);
		}
	}
	CCollsionMgr::Collision_RectExTile(CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER), CTileMgr::Get_Instance()->GetTileSeria());

	CObjMgr::Get_Instance()->Late_Update();
	CTileMgr::Get_Instance()->Late_Update();
}

void CSeriaRoom::Render(HDC hDC)
{
	float		fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"SeriaRoom");

	BitBlt(hDC, (int)fScrollX, (int)fScrollY, SERIAROOM_SIZEX, SERIAROOM_SIZEY, hGroundDC, 0, 0, SRCCOPY);

	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
}

void CSeriaRoom::Release()
{
	// 씬 전환될 때, 플레이어, UI빼고 전부 삭제
	for (size_t i = OBJ_PLAYER_ATTACK; i < OBJ_END; ++i)
	{
		if(OBJ_UI != i && OBJ_MAINUI != i && OBJ_PLAYER != i 
		&& OBJ_MOUSE != i && OBJ_MOUSEPOINT != i
		&& OBJ_INVEN != i && OBJ_INVENITEM != i && OBJ_STORE != i && OBJ_STOREITEM != i
		&& OBJ_SKILLICON != i && OBJ_EQUIPMENT != i && OBJ_MYINFO != i)
			CObjMgr::Get_Instance()->Delete_ID((OBJ_ID)i);
	}

	CSoundMgr::Get_Instance()->StopAll();
}
