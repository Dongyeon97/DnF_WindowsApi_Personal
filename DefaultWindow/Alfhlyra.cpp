#include "stdafx.h"
#include "Alfhlyra.h"

// 매니저
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "SceneMgr.h"
#include "CollsionMgr.h"
#include "SoundMgr.h"

#include "Player.h"

// 몬스터 패턴
#include "AI.h"
#include "Expeller.h"
#include "Exp_Idle.h"
#include "Exp_Appear.h"
#include "Exp_Trace.h"
#include "Exp_Attack1.h"
#include "Exp_Attack2.h"
#include "Exp_NormalAttacked.h"
#include "Exp_ThrustAttacked.h"
#include "Exp_LevitateAttacked.h"
#include "Susia.h"
#include "Rinus.h"
#include "TownCutsin.h"

CAlfhlyra::CAlfhlyra()
{
}

CAlfhlyra::~CAlfhlyra()
{
	Release();
}

void CAlfhlyra::Initialize()
{
	CSoundMgr::Get_Instance()->PlayBGM(L"Alfhlyra.wav", g_fVolume);

	// 마을 컷신
	CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, CAbstractFactory<CTownCutsin>::Create_Obj(400.f, 300.f, 800.f, 600.f, 0.f, 2.f, L"Alfhlyra_Cutscene"));

	// NPC - 슈시아
	// CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, CAbstractFactory<CSusia>::Create_Obj(1130.f, 325.f, L"Susia"));

	// NPC - 라이너스
	// CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, CAbstractFactory<CRinus>::Create_Obj(610.f, 330.f, L"Rinus"));

	// 플레이어가 씬에 없다면 생성
	if (CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).empty())
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create_Obj());
	}
	CTileMgr::Get_Instance()->Initialize();
	CTileMgr::Get_Instance()->Load_Tile(L"../Image/Tile/Alfhlyra_Tile.dat");
}

int CAlfhlyra::Update()
{
	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();

	return 0;
}

void CAlfhlyra::Late_Update()
{
	// 알프라이라에서 헨돈마이어
	if ((320.f < CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Info().fY &&
		400.f >= CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Info().fY)
		&& CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Info().fX > 1490.f)
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_HENDON);
		CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Set_Pos(150.f, 430.f);
		CScrollMgr::Get_Instance()->Set_ScrollX(1000.f);
		CScrollMgr::Get_Instance()->Set_ScrollY(-100.f);
		dynamic_cast<CPlayer*> (CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front())->Set_PlayerState(CPlayer::PS_IDLE);
	}

	// 알프라이라에서 레쉬폰1로 진입
	if ((320.f < CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Info().fY &&
		704.f >= CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Info().fY)
		&& CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Info().fX < 50.f)
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_RESHIPON1);
		CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Set_Pos(1100.f, 400.f);
		CScrollMgr::Get_Instance()->Set_ScrollX(-650.f);
		CScrollMgr::Get_Instance()->Set_ScrollY(-100.f);
		dynamic_cast<CPlayer*> (CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front())->Set_PlayerState(CPlayer::PS_IDLE);
	}


	CCollsionMgr::Collision_RectExTile(CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER), CTileMgr::Get_Instance()->GetTileAlfhlyra());

	CTileMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
}

void CAlfhlyra::Render(HDC hDC)
{
	float		fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Alfhlyra");

	// 배경 이미지는 특정 색상을 제거할 필요가 없으므로 그냥 BitBlt로 송출
	BitBlt(hDC, (int)fScrollX, (int)fScrollY, ALFHLYRA_SIZEX, ALFHLYRA_SIZEY, hGroundDC, 0, 0, SRCCOPY);

	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
}

void CAlfhlyra::Release()
{
	// 씬 전환될 때, 플레이어, UI빼고 전부 삭제
	for (size_t i = OBJ_PLAYER_ATTACK; i < OBJ_END; ++i)
	{
		if (OBJ_UI != i && OBJ_MAINUI != i && OBJ_PLAYER != i
			&& OBJ_MOUSE != i && OBJ_MOUSEPOINT != i
			&& OBJ_INVEN != i && OBJ_INVENITEM != i && OBJ_STORE != i && OBJ_STOREITEM != i
			&& OBJ_SKILLICON != i && OBJ_EQUIPMENT != i && OBJ_MYINFO != i)
			CObjMgr::Get_Instance()->Delete_ID((OBJ_ID)i);
	}
	CSoundMgr::Get_Instance()->StopAll();
}