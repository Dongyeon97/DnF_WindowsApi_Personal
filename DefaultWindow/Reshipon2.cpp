#include "stdafx.h"
#include "Reshipon2.h"

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
#include "Exp_Dead.h"

// NPC
#include "FallenGirl.h"

CReshipon2::CReshipon2()
{
}

CReshipon2::~CReshipon2()
{
	Release();
}

void CReshipon2::Initialize()
{
	CSoundMgr::Get_Instance()->PlayBGM(L"leshphon_boss.wav", g_fVolume);

	// NPC - 쓰러진 소녀 추가
	CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, CAbstractFactory<CFallenGirl>::Create_Obj(300.f, 300.f, L"Girl"));

	// 스톰패스에서 넘어온 경우 몬스터를 소환하지 않음
	SCENEID ePreScene = CSceneMgr::Get_Instance()->GetPreSceneType();
	if (SC_SKASARAIR == ePreScene)
	{
		
	}
	else
	{
		for (int i = 0; i < 4; ++i)
		{
			AI* pMonAI1 = new AI;
			pMonAI1->AddState(new CExp_Idle);
			pMonAI1->AddState(new CExp_Appear);
			pMonAI1->AddState(new CExp_Trace);
			pMonAI1->AddState(new CExp_Attack1);
			pMonAI1->AddState(new CExp_Attack2);
			pMonAI1->AddState(new CExp_NormalAttacked);
			pMonAI1->AddState(new CExp_ThrustAttacked);
			pMonAI1->AddState(new CExp_LevitateAttacked);
			pMonAI1->AddState(new CExp_Dead);
			pMonAI1->SetCurState(MON_IDLE);

			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, 
			CAbstractFactory<CExpeller>::Create_Obj(400.f + 150.f * i, 350.f, 350.f, 350.f, L"Expeller_L"));
			dynamic_cast<CMonster*>(CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER).back())->Set_AI(pMonAI1);
			dynamic_cast<CMonster*>(CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER).back())->SetMonInfo({ 200.f, 50.f });
		}
	}

	// 플레이어가 씬에 없다면 생성
	if (CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).empty())
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create_Obj());
	}
	CTileMgr::Get_Instance()->Initialize();
	CTileMgr::Get_Instance()->Load_Tile(L"../Image/Tile/Reshipon2_Tile.dat");
}

int CReshipon2::Update()
{
	m_dwTime += CTimeMgr::Get_Instance()->GetfDT();
	if (3 < m_dwTime)
	{
		m_dwTime = 0;
		CScene::Reset_Combo();
	}

	CTileMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();

	return 0;
}

void CReshipon2::Late_Update()
{
	// 레쉬폰 2에서 스톰패스로 갔을때
	if ((0 < CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_TileCollision().bottom &&
		600 >= CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_TileCollision().bottom)
		&& CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Info().fX < 100)
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_SKASARAIR);
		CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Set_Pos(1450.f, 380.f);
		CScrollMgr::Get_Instance()->Set_ScrollX(-1000.f);
		CScrollMgr::Get_Instance()->Set_ScrollY(0.f);
		dynamic_cast<CPlayer*> (CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front())->Set_PlayerState(CPlayer::PS_IDLE);
	}

	// 레싀폰2에서 레쉬폰1로 갔을때
	else if ((0.f < CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Info().fY &&
		600.f >= CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Info().fY)
		&& CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Info().fX > 1150.f)
	{
		SCENEID ePreScene = CSceneMgr::Get_Instance()->GetPreSceneType();
		CSceneMgr::Get_Instance()->Scene_Change(SC_RESHIPON1);
		if (SC_RESHIPON2 == ePreScene)
		{
			CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Set_Pos(150.f, 380.f);
			CScrollMgr::Get_Instance()->Set_ScrollX(700.f);
			CScrollMgr::Get_Instance()->Set_ScrollY(0.f);
			dynamic_cast<CPlayer*> (CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front())->Set_PlayerState(CPlayer::PS_IDLE);
		}
	}

	CCollsionMgr::Collision_RectExTile(CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER), CTileMgr::Get_Instance()->GetTileHendon());
	CCollsionMgr::Collision_AttackRectPM(CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER), CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_ATTACK));
	CCollsionMgr::Collision_WAttackRectPM(CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER), CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_WIDEATTACK));
	CCollsionMgr::Collision_AttackRectMP(CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER_ATTACK), CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER));
	CCollsionMgr::Collision_WAttackRectMP(CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER_WIDEATTACK), CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER));
	CCollsionMgr::Collision_WAttackRectMP2(CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER_WIDEATTACK), CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER));

	CTileMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
}

void CReshipon2::Render(HDC hDC)
{
	float		fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	// "Ground"이미지는 MainGame에서 이미 Insert_bmp 되었음, 찾아오기만 하면 되는 상태
	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Reshipon2");

	// 배경 이미지는 특정 색상을 제거할 필요가 없으므로 그냥 BitBlt로 송출
	BitBlt(hDC, (int)fScrollX, (int)fScrollY, RESHIPON2_SIZEX, RESHIPON2_SIZEY, hGroundDC, 0, 0, SRCCOPY);

	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);

	Draw_ComboFont(m_iComboCount);
}

void CReshipon2::Release()
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
