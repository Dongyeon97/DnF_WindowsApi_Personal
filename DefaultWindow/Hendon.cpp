#include "stdafx.h"
#include "Hendon.h"

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
#include "FallenGirl.h"
#include "Anise.h"
#include "Grandis.h"
#include "Kiri.h"

CHendon::CHendon()
{
}

CHendon::~CHendon()
{
	Release();
}

void CHendon::Initialize()
{
	CSoundMgr::Get_Instance()->PlayBGM(L"tavern.ogg", g_fVolume);

	// NPC - 아니스
	CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, CAbstractFactory<CAnise>::Create_Obj(1645.f, 255.f, L"Anise"));

	// NPC - 그란디스
	CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, CAbstractFactory<CGrandis>::Create_Obj(2400.f, 275.f, L"Grandis"));

	// NPC - 키리
	CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, CAbstractFactory<CKiri>::Create_Obj(2800.f, 285.f, L"Kiri"));

	// 플레이어가 씬에 없다면 생성
	if (CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).empty())
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create_Obj());
	}

	CTileMgr::Get_Instance()->Initialize();
	CTileMgr::Get_Instance()->Load_Tile(L"../Image/Tile/Hendon_Tile.dat");
}

int CHendon::Update()
{
	m_dwTime += CTimeMgr::Get_Instance()->GetfDT();
	if (3 < m_dwTime)
	{
		m_dwTime = 0;
		CScene::Reset_Combo();
	}

	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();

	return 0;
}

void CHendon::Late_Update()
{
	// 헨돈마이어에서 세리아룸으로 갔을때
	if ((590.f < CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Info().fX &&
		630.f >= CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Info().fX)
		&& CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Info().fY < 260.f)
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_SERIAROOM);
	}

	// 헨돈마이어에서 천공의 둥지로 갔을때
	else if ((320.f < CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Info().fY &&
			704.f >= CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Info().fY) 
			&& CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Info().fX > 3450.f)
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_NEST);
	}

	// 헨돈마이어에서 알프라이라로 갔을때
	else if ((320.f < CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Info().fY &&
		704.f >= CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Info().fY)
		&& CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Info().fX < 50.f)
	{
		SCENEID ePreScene = CSceneMgr::Get_Instance()->GetPreSceneType();
		CSceneMgr::Get_Instance()->Scene_Change(SC_ALFHLYRA);
		if (SC_HENDON == ePreScene)
		{
			CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Set_Pos(1400.f, 380.f);
			CScrollMgr::Get_Instance()->Set_ScrollX(-1200.f);
			CScrollMgr::Get_Instance()->Set_ScrollY(0.f);
			dynamic_cast<CPlayer*> (CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front())->Set_PlayerState(CPlayer::PS_IDLE);
		}
	}

	CCollsionMgr::Collision_RectExTile(CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER), CTileMgr::Get_Instance()->GetTileHendon());
	CCollsionMgr::Collision_AttackRectPM(CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER), CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_ATTACK));
	CCollsionMgr::Collision_WAttackRectPM(CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER), CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_WIDEATTACK));
	CCollsionMgr::Collision_AttackRectMP(CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER_ATTACK), CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER));
	CCollsionMgr::Collision_WAttackRectMP(CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER_WIDEATTACK), CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER));

	CObjMgr::Get_Instance()->Late_Update();
	CTileMgr::Get_Instance()->Late_Update();
}

void CHendon::Render(HDC hDC)
{
	float		fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	// "Ground"이미지는 MainGame에서 이미 Insert_bmp 되었음, 찾아오기만 하면 되는 상태
	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Hendon");

	// 배경 이미지는 특정 색상을 제거할 필요가 없으므로 그냥 BitBlt로 송출
	BitBlt(hDC, (int)fScrollX, (int)fScrollY, HENDON_SIZEX, HENDON_SIZEY, hGroundDC, 0, 0, SRCCOPY);

	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);

	Draw_ComboFont(m_iComboCount);
}

void CHendon::Release()
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
