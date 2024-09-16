#include "stdafx.h"
#include "Nest.h"

#include "ObjMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "CollsionMgr.h"
#include "SoundMgr.h"

#include "Player.h"

// ���� ����
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
#include "Isys_Pattern2.h"
#include "Isys_Pattern3.h"
#include "Isys_P3_Fail.h"
#include "Isys_Attacked.h"
#include "Isys_NormalAttacked.h"
#include "Isys_ThrustAttacked.h"
#include "Isys_LevitateAttacked.h"
#include "Isys_Grogy.h"
#include "Isys_Dead.h"
#include "TownCutsin.h"

CNest::CNest()
	: m_TabTime(0)
	, m_eWeather(DARK)
{
}

CNest::~CNest()
{
	Release();
}

void CNest::Initialize()
{
	// - �ʻ�ȭ -
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Monicon.bmp", L"Isys_Portrait");

	// - ����� / ������ �غ� -
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_FlyingReady2.bmp", L"Isys_FlyingReady2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_FlyingReady.bmp", L"Isys_FlyingReady");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Pattern/MeetLightning.bmp", L"Isys_MeetLightning");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_MeetFeatherEffect.bmp", L"Isys_MeetFeatherEffect");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_WingMeet.bmp", L"Isys_WingMeet");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Pattern/Isys_JumpWing.bmp", L"Isys_JumpWing");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Pattern/Isys_JumpBeam.bmp", L"Isys_JumpBeam");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Pattern/Smoke/Smoke_FloorFrontTest3.bmp", L"Smoke_FloorFrontTest3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Pattern/Smoke/Smoke_Jump_FloorTest.bmp", L"Smoke_Jump_FloorTest");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Pattern/Smoke/Smoke_Up.bmp", L"Smoke_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Pattern/Smoke/SmokeMiddle.bmp", L"SmokeMiddle");

	// - Idle -
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_LIdle.bmp", L"Isys_LIdle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_RIdle.bmp", L"Isys_RIdle");

	// - Walk -
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_LWalk.bmp", L"Isys_LWalk");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_RWalk.bmp", L"Isys_RWalk");

	// - �⺻ ����1 : ���� �ֵθ��� -
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_LNormalAttack.bmp", L"Isys_LAttack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_RNormalAttack.bmp", L"Isys_RAttack");

	// - �⺻ ����2 : �߱��� �� �ֵθ��� -
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_LNormalAttack2.bmp", L"Isys_LAttack2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_RNormalAttack2.bmp", L"Isys_RAttack2");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Attack/Isys_AttackLeg.bmp", L"Isys_RAttack2_Effect");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Attack/Isys_AttackLegL.bmp", L"Isys_LAttack2_Effect");

	// - �⺻ ����3 : �÷��̾�� �����̵��� ����ġ��ġ -
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys6L.bmp", L"Isys6L");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys6.bmp", L"Isys6");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Attack/Isys_AttackGrabL.bmp", L"Isys_AttackGrabL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Attack/Isys_AttackGrab.bmp", L"Isys_AttackGrab");

	// - �⺻ ����4(2����� ����) : �ڷ� ������ �� ������ �߻�
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys8L.bmp", L"Isys8L");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys8.bmp", L"Isys8");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Attack/Isys_AttackLaiserL.bmp", L"Isys_LRazor");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Attack/Isys_AttackLaiser.bmp", L"Isys_RRazor");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Attack/LaiserStartEffect.bmp", L"LaiserStartEffect");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Attack/LaiserAfterEffect.bmp", L"LaiserAfterEffect");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Attack/LaiserAfterEffectL.bmp", L"LaiserAfterEffectL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Attack/Isys_LaiserStart.bmp", L"Isys_LaiserStart");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Attack/Isys_LaiserLineL.bmp", L"Isys_RazorLineL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Attack/Isys_LaiserLine.bmp", L"Isys_RazorLine");

	// - ������ �齺�� -
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_LBackStep.bmp", L"Isys_LBackStep");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_RBackStep.bmp", L"Isys_RBackStep");

	// - �ǰ� -
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_LAttacked.bmp", L"Isys_LAttacked");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_RAttacked.bmp", L"Isys_RAttacked");

	// - ������ -
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Flying.bmp", L"Isys_Flying");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Flyingg.bmp", L"Isys_Flyingg");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_HandUp1.bmp", L"Isys_HandUp1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_HandUp2.bmp", L"Isys_HandUp2");

	// ����, ���� ����Ʈ
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Attack/Feather.bmp", L"Isys_Feather");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Attack/Feather_Attack.bmp", L"Isys_FeatherAttack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Attack/FeatherAttackpos.bmp", L"Isys_FeatherAttackPos");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Attack/FeatherAttackposTest.bmp", L"Isys_FeatherAttackPos2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Attack/FeatherLineTest2.bmp", L"FeatherLineTest2");

	// ���� ����
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Attack/Isys_ChopFirstFloorTest.bmp", L"Isys_ChopFirstFloor");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Attack/Isys_ChopSecondFloorTest.bmp", L"Isys_ChopSecondFloor");

	// 2�� ����ȭ ȸ����
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Pattern/Smoke/Smoke_Up2.bmp", L"Smoke_Up2");

	// 3�� ����ȭ �齺��
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Pattern/Runestone/BlueRune.bmp", L"BlueRune");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Pattern/Runestone/RedRune.bmp", L"RedRune");

	// �����
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Pattern/Isys_Wave2.bmp", L"Isys_Wave");

	// ȸ����
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Pattern/Smoke/SmokeMiddle.bmp", L"SmokeMiddle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Pattern/Isys_Wind.bmp", L"Isys_Wind");

	// �����̵� ����
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Attack/Isys_LightningEffect1.bmp", L"Isys_LightningEffect1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Isys_Attack/Isys_LightningEffect2Test.bmp", L"Isys_LightningEffect2Test");

	CSoundMgr::Get_Instance()->PlayBGM(L"Isys_Bgm.mp3", g_fVolume);

	// ���� �ƽ�
	CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, CAbstractFactory<CTownCutsin>::Create_Obj(400.f, 300.f, 800.f, 600.f, 0.f, 2.f, L"Isys_EnterScene"));

	// ���� ���� �κ�
	AI* pBossAI = new AI;
	pBossAI->AddState(new CIsys_Idle);
	pBossAI->AddState(new CIsys_Trace);
	pBossAI->AddState(new CIsys_Attack1);
	pBossAI->AddState(new CIsys_Attack2);
	pBossAI->AddState(new CIsys_Attack3);
	pBossAI->AddState(new CIsys_Razor);
	pBossAI->AddState(new CIsys_BackStep);
	pBossAI->AddState(new CIsys_Appear);
	pBossAI->AddState(new CIsys_PrePattern);
	pBossAI->AddState(new CIsys_Pattern1);
	pBossAI->AddState(new CIsys_Pattern2);
	pBossAI->AddState(new CIsys_Pattern3);
	pBossAI->AddState(new CIsys_P3_Fail);
	pBossAI->AddState(new CIsys_NormalAttacked);
	pBossAI->AddState(new CIsys_ThrustAttacked);
	pBossAI->AddState(new CIsys_LevitateAttacked);
	pBossAI->AddState(new CIsys_Grogy);
	pBossAI->AddState(new CIsys_Dead);
	pBossAI->SetCurState(BOSS_IDLE);

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CIsys>::Create_Obj(NEST_SIZEX * 0.5f, 400.f, 371.f, 373.f, L"Isys_FlyingReady2"));
	dynamic_cast<CMonster*>(CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER).back())->Set_AI(pBossAI);
	dynamic_cast<CMonster*>(CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER).back())->SetMonInfo({ 300.f, 50.f });

	if (CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).empty())
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create_Obj());
	}
	CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Set_Pos(320.f , 640.f);
	dynamic_cast<CPlayer*> (CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front())->Set_PlayerState(CPlayer::PS_IDLE);
	CScrollMgr::Get_Instance()->ScrollX_Fix(494.f);
	CScrollMgr::Get_Instance()->ScrollY_Fix(-340.f);
	CTileMgr::Get_Instance()->Initialize();
	CTileMgr::Get_Instance()->Load_Tile(L"../Image/Tile/Nest_Tile.dat");
}

int CNest::Update()
{
	m_dwTime += CTimeMgr::Get_Instance()->GetfDT();
	m_TabTime += CTimeMgr::Get_Instance()->GetfDT();;

	if (3 < m_dwTime)
	{
		m_dwTime = 0;
		CScene::Reset_Combo();
	}

	CTileMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();

	Key_Input();
	Set_StoneImmune();

	return 0;
}

void CNest::Late_Update()
{
	CCollsionMgr::Collision_RectExTile(CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER), CTileMgr::Get_Instance()->GetTileNest());
	CCollsionMgr::Collision_AttackRectPM(CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER), CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_ATTACK));
	CCollsionMgr::Collision_WAttackRectPM(CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER), CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_WIDEATTACK));
	CCollsionMgr::Collision_AttackRectMP(CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER_ATTACK), CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER));
	CCollsionMgr::Collision_WAttackRectMP(CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER_WIDEATTACK), CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER));
	CCollsionMgr::Collision_WAttackRectMP2(CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER_WIDEATTACK), CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER));

	// ��Ϳ� �齺��� �浹ó��
	CCollsionMgr::Collision_AttackRectMP(CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER_ATTACK), CObjMgr::Get_Instance()->GetObjList(OBJ_RUNESTONE1));
	CCollsionMgr::Collision_AttackRectMP(CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER_ATTACK), CObjMgr::Get_Instance()->GetObjList(OBJ_RUNESTONE2));

	CTileMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
}

void CNest::Render(HDC hDC)
{
	float		fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Isys_DarkGround");

	if(DARK == m_eWeather)
		hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Isys_DarkGround");
	else
		hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Isys_LightGround");

	BitBlt(hDC, (int)fScrollX, (int)fScrollY, NEST_SIZEX, NEST_SIZEY, hGroundDC, 0, 0, SRCCOPY);

	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);

	Draw_ComboFont(m_iComboCount);
}

void CNest::Release()
{
	// �� ��ȯ�� ��, �÷��̾�, UI���� ���� ����
	for (size_t i = OBJ_PLAYER; i < OBJ_END; ++i)
	{
		if (OBJ_UI != i && OBJ_MAINUI != i && OBJ_PLAYER != i
			&& OBJ_MOUSE != i && OBJ_MOUSEPOINT != i
			&& OBJ_INVEN != i && OBJ_INVENITEM != i && OBJ_STORE != i && OBJ_STOREITEM != i && OBJ_MYINFO != i
			&& OBJ_SKILLICON != i && OBJ_EQUIPMENT != i && OBJ_RUNESTONE1 != i && OBJ_RUNESTONE2 != i)
			CObjMgr::Get_Instance()->Delete_ID((OBJ_ID)i);
	}
	CSoundMgr::Get_Instance()->StopAll();
}

void CNest::Set_StoneImmune()
{
	// �� �齺�� ����Ʈ
	list<CObj*> lstLightStone = CObjMgr::Get_Instance()->GetObjList(OBJ_RUNESTONE1);

	// �� �齺�� ����Ʈ
	list<CObj*> lstDarkStone = CObjMgr::Get_Instance()->GetObjList(OBJ_RUNESTONE2);

	// ���� ���̶�� �� �齺���� �������� �����, ������ ���� ����
	if (DARK == m_eWeather)
	{
		for (auto& stone : lstLightStone)
		{
			stone->Set_DrawOption(0);
			stone->Set_IsImmune(true);
		}
		for (auto& stone : lstDarkStone)
		{
			stone->Set_DrawOption(1);
			stone->Set_IsImmune(false);
		}
	}
	// ���� ���̶�� �� �齺���� �������� �����, ������ ���� ����
	else if (LIGHT == m_eWeather)
	{
		for (auto& stone : lstLightStone)
		{
			stone->Set_DrawOption(1);
			stone->Set_IsImmune(false);
		}
		for (auto& stone : lstDarkStone)
		{
			stone->Set_DrawOption(0);
			stone->Set_IsImmune(true);
		}
	}
}

void CNest::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_TAB) && 1 < m_TabTime)
	{
		m_TabTime = 0;
		if (DARK == m_eWeather)
			m_eWeather = LIGHT;
		else
			m_eWeather = DARK;
	}
}
