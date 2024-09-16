#include "stdafx.h"
#include "Reshipon1.h"

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
#include "Nudeogi.h"
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
#include "TownCutsin.h"

CReshipon1::CReshipon1()
{
}

CReshipon1::~CReshipon1()
{
	Release();
}

void CReshipon1::Initialize()
{
	CSoundMgr::Get_Instance()->PlayBGM(L"leshphon.wav", g_fVolume);

	// 마을 컷신
	CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, CAbstractFactory<CTownCutsin>::Create_Obj(400.f, 300.f, 800.f, 600.f, 0.f, 2.f, L"CutScene"));

	// 레쉬폰2에서 넘어온 경우 몬스터를 소환하지 않음
	SCENEID ePreScene = CSceneMgr::Get_Instance()->GetPreSceneType();
	if (SC_RESHIPON2 == ePreScene)
	{

	}
	else
	{
		for (int i = 0; i < 4; ++i)
		{
			AI* pMonAI1 = new AI;
			pMonAI1->AddState(new CExp_Idle);
			pMonAI1->AddState(new CExp_Trace);
			pMonAI1->AddState(new CExp_Attack1);
			pMonAI1->AddState(new CExp_Attack2);
			pMonAI1->AddState(new CExp_NormalAttacked);
			pMonAI1->AddState(new CExp_ThrustAttacked);
			pMonAI1->AddState(new CExp_LevitateAttacked);
			pMonAI1->AddState(new CExp_Dead);
			pMonAI1->SetCurState(MON_IDLE);

			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER,
				CAbstractFactory<CNudeogi>::Create_Obj(200.f + (200.f * i), 350.f, 500.f, 500.f, L"LNudeogi"));
			dynamic_cast<CMonster*>(CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER).back())->Set_AI(pMonAI1);
			dynamic_cast<CMonster*>(CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER).back())->SetMonInfo({ 200.f, 100.f });
		}
	}

	// 플레이어가 씬에 없다면 생성
	if (CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).empty())
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create_Obj());
	}
	CTileMgr::Get_Instance()->Initialize();
	CTileMgr::Get_Instance()->Load_Tile(L"../Image/Tile/Reshipon1_Tile.dat");
}

int CReshipon1::Update()
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

void CReshipon1::Late_Update()
{
	// 레쉬폰1 에서 레쉬폰2로
	if ((0.f < CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Info().fY &&
		600.f >= CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Info().fY)
		&& CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Info().fX < 50.f)
	{
		SCENEID ePreScene = CSceneMgr::Get_Instance()->GetPreSceneType();
		CSceneMgr::Get_Instance()->Scene_Change(SC_RESHIPON2);
		if (SC_RESHIPON1 == ePreScene)
		{
			CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Set_Pos(1100.f, 400.f);
			CScrollMgr::Get_Instance()->Set_ScrollX(-650.f);
			CScrollMgr::Get_Instance()->Set_ScrollY(-100.f);
			dynamic_cast<CPlayer*> (CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front())->Set_PlayerState(CPlayer::PS_IDLE);
		}
	}
	// 레쉬폰1 에서 알프라이라로
	if ((0.f < CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Info().fY &&
		600.f >= CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Info().fY)
		&& CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Info().fX > 1150.f)
	{
		SCENEID ePreScene = CSceneMgr::Get_Instance()->GetPreSceneType();
		CSceneMgr::Get_Instance()->Scene_Change(SC_ALFHLYRA);
		if (SC_RESHIPON1 == ePreScene)
		{
			CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Set_Pos(150.f, 400.f);
			CScrollMgr::Get_Instance()->Set_ScrollX(1200.f);
			CScrollMgr::Get_Instance()->Set_ScrollY(-100.f);
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

void CReshipon1::Render(HDC hDC)
{
	float		fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	// "Ground"이미지는 MainGame에서 이미 Insert_bmp 되었음, 찾아오기만 하면 되는 상태
	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Reshipon1");

	// 배경 이미지는 특정 색상을 제거할 필요가 없으므로 그냥 BitBlt로 송출
	BitBlt(hDC, (int)fScrollX, (int)fScrollY, RESHIPON1_SIZEX, RESHIPON1_SIZEY, hGroundDC, 0, 0, SRCCOPY);

	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);

	Draw_ComboFont(m_iComboCount);
}

void CReshipon1::Release()
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
