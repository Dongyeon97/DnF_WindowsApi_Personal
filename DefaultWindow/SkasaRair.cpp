#include "stdafx.h"
#include "SkasaRair.h"

// 매니저
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "SceneMgr.h"
#include "CollsionMgr.h"
#include "SoundMgr.h"

#include "Player.h"

// 보스 패턴
#include "Skasa.h"
#include "AI.h"
#include "Isys.h"
#include "Isys_Appear.h"
#include "Isys_Idle.h"
#include "Isys_Trace.h"
#include "Isys_PrePattern.h"
#include "Isys_Attack1.h"
#include "Isys_Attack2.h"
#include "Isys_Attack3.h"
#include "Isys_Razor.h"
#include "Isys_BackStep.h"
#include "Isys_Pattern1.h"
#include "Isys_Attacked.h"
#include "Isys_NormalAttacked.h"
#include "Isys_ThrustAttacked.h"
#include "Isys_LevitateAttacked.h"
#include "Isys_Dead.h"

// 던전 컷신
#include "TownCutsin.h"
#include "Toy.h"

CSkasaRair::CSkasaRair()
{
}

CSkasaRair::~CSkasaRair()
{
	Release();
}

void CSkasaRair::Initialize()
{
	CSoundMgr::Get_Instance()->PlayBGM(L"StomPassBoss.wav", g_fVolume);
	CSoundMgr::Get_Instance()->PlaySoundW(L"SkasaStart.wav", SOUND_EFFECT, g_fVolume);

	// 마을 컷신
	// CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, CAbstractFactory<CTownCutsin>::Create_Obj(400.f, 300.f, 800.f, 600.f, 0.f, 2.f, L"Stompassmap"));

	// 스카사
	AI* pBossAI2 = new AI;
	pBossAI2->AddState(new CIsys_Idle);
	pBossAI2->AddState(new CIsys_Trace);
	pBossAI2->AddState(new CIsys_Attack1);
	pBossAI2->AddState(new CIsys_Attack2);
	pBossAI2->AddState(new CIsys_Attack3);
	pBossAI2->AddState(new CIsys_Dead);
	pBossAI2->SetCurState(BOSS_IDLE);

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CSkasa>::Create_Obj(600.f, 150.f, 512.f, 512.f, L"RSkasa"));
	dynamic_cast<CMonster*>(CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER).back())->Set_AI(pBossAI2);
	dynamic_cast<CMonster*>(CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER).back())->SetMonInfo({ 600.f, 75.f });

	// 플레이어가 씬에 없다면 생성
	if (CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).empty())
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create_Obj());
	}
	CTileMgr::Get_Instance()->Initialize();
	CTileMgr::Get_Instance()->Load_Tile(L"../Image/Tile/SkasaRair_Tile.dat");
}

int CSkasaRair::Update()
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

void CSkasaRair::Late_Update()
{
	// 스카사의 레어에서 스톰패스로 갔을때
	if ((0.f < CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Info().fY &&
		600.f >= CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Info().fY)
		&& CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Info().fX > 1550.f)
	{
		SCENEID ePreScene = CSceneMgr::Get_Instance()->GetPreSceneType();
		CSceneMgr::Get_Instance()->Scene_Change(SC_RESHIPON2);
		if (SC_SKASARAIR == ePreScene)
		{
			CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Set_Pos(150.f, 400.f);
			CScrollMgr::Get_Instance()->Set_ScrollX(1200.f);
			CScrollMgr::Get_Instance()->Set_ScrollY(-50.f);
			dynamic_cast<CPlayer*> (CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front())->Set_PlayerState(CPlayer::PS_IDLE);
		}
	}

	CCollsionMgr::Collision_RectExTile(CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER), CTileMgr::Get_Instance()->GetTileHendon());
	CCollsionMgr::Collision_AttackRectPM(CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER), CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_ATTACK));
	CCollsionMgr::Collision_WAttackRectPM(CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER), CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_WIDEATTACK));
	CCollsionMgr::Collision_AttackRectMP(CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER_ATTACK), CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER));
	CCollsionMgr::Collision_WAttackRectMP(CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER_WIDEATTACK), CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER));
	CCollsionMgr::Collision_WAttackRectMP2(CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER_WIDEATTACK), CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER));

	CObjMgr::Get_Instance()->Late_Update();
	CTileMgr::Get_Instance()->Late_Update();
}

void CSkasaRair::Render(HDC hDC)
{
	float		fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	// "Ground"이미지는 MainGame에서 이미 Insert_bmp 되었음, 찾아오기만 하면 되는 상태
	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"SkasaRair");

	// 배경 이미지는 특정 색상을 제거할 필요가 없으므로 그냥 BitBlt로 송출
	BitBlt(hDC, (int)fScrollX, (int)fScrollY, SKASARAIR_SIZEX, SKASARAIR_SIZEY, hGroundDC, 0, 0, SRCCOPY);

	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);

	Draw_ComboFont(m_iComboCount);
}

void CSkasaRair::Release()
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
	CBmpMgr::Get_Instance()->Release_Bmp(L"LSkasa");
	CBmpMgr::Get_Instance()->Release_Bmp(L"RSkasa");
	CBmpMgr::Get_Instance()->Release_Bmp(L"IceMagic");
	CBmpMgr::Get_Instance()->Release_Bmp(L"SkasaIcon");
}
