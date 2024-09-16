
#include "stdafx.h"
#include "MainGame.h"
#include "CollsionMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "TileMgr.h"
#include "TimeMgr.h"
#include "SoundMgr.h"
#include "UI_Base.h"
#include "UI_Hp.h"
#include "UI_Mp.h"

CMainGame::CMainGame()
	: m_dwTime(GetTickCount()), m_iFPS(0)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_DC = GetDC(g_hWnd);

	CSoundMgr::Get_Instance()->Initialize();
	CTimeMgr::Get_Instance()->Initialize();
	CSceneMgr::Get_Instance()->Scene_Change(SC_LOGO);

#pragma region �̹��� �ε�
	// ============================ < BackGround Image > =================================
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BackGround.bmp", L"Ground");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/SeriaRoom_Ground.bmp", L"SeriaRoom");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Hendon.bmp", L"Hendon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Alfhlyra.bmp", L"Alfhlyra");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/reshipon1.bmp", L"Reshipon1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/reshipon3.bmp", L"Reshipon2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/SkasaRair.bmp", L"SkasaRair");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Isys_WaitGround.bmp", L"Isys_WaitGround");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Isys_DarkGround.bmp", L"Isys_DarkGround");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Isys_LightGround.bmp", L"Isys_LightGround");

	// < ���� �ƽ� >
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/TownCutsin/Alfhlyra_Cutscene.bmp", L"Alfhlyra_Cutscene");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/TownCutsin/CutScene.bmp", L"CutScene");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/TownCutsin/Isys_EnterScene.bmp", L"Isys_EnterScene");
	// CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/TownCutsin/Stompassmap.bmp", L"Stompassmap");

	// < UI Image >
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/State.bmp", L"UIState");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/UIinven.bmp", L"UIinven");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/UIBase2.bmp", L"UIBase");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/UIstore_2.bmp", L"UIstore2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Hp.bmp", L"UIHp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Mp.bmp", L"UIMp");

	// < ���� ����Ʈ >
	// CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/��������Ʈ/HpPotion.bmp", L"HpPotion");
	// CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/��������Ʈ/ManaPotion.bmp", L"ManaPotion");

	// < ������ >
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Item_Back2.bmp", L"Item_Back2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Item_Back3.bmp", L"Item_Back3");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/����/Weapon4.bmp", L"Weapon4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/����/Weapon3.bmp", L"Weapon3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/����/Weapon2.bmp", L"Weapon2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/����/Weapon1.bmp", L"Weapon1");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Īȣ/Title1.bmp", L"Title1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Īȣ/541.bmp", L"Title2");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/����/Bracelet1.bmp", L"Bracelet1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/����/Bracelet2.bmp", L"Bracelet2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/����/Bracelet3.bmp", L"Bracelet3");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/�����/Neckless1.bmp", L"Neckless1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/�����/Neckless2.bmp", L"Neckless2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/�����/Neckless3.bmp", L"Neckless3");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/����/Ring1.bmp", L"Ring1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/����/Ring2.bmp", L"Ring2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/����/Ring3.bmp", L"Ring3");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/�������/SupportItem.bmp", L"SupportItem");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/������/MasicStone1.bmp", L"MasicStone1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/������/MasicStone2.bmp", L"MasicStone2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/������/MasicStone3.bmp", L"MasicStone3");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/����/Armor4.bmp", L"Armor4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/����/Armor5.bmp", L"Armor5");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/����/Armor6.bmp", L"Armor6");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/����/Pant4.bmp", L"Pant4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/����/Pant5.bmp", L"Pant5");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/����/Pant6.bmp", L"Pant6");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/��Ʈ/Belt4.bmp", L"Belt4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/��Ʈ/Belt5.bmp", L"Belt5");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/��Ʈ/Belt6.bmp", L"Belt6");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/���/Shoulder4.bmp", L"Shoulder4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/���/Shoulder5.bmp", L"Shoulder5");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/���/Shoulder6.bmp", L"Shoulder6");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/�Ź�/Shoes4.bmp", L"Shoes4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/�Ź�/Shoes5.bmp", L"Shoes5");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/�Ź�/Shoes6.bmp", L"Shoes6");

	// < ������ ��Ʈ >
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Font/HpNumber.bmp", L"MonsterHpNum");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Font/Damage.bmp", L"Damage");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Font/DamageNumber.bmp", L"DamageFont1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Font/ComboNumber_3.bmp", L"DamageFont2");

	// < �޺� ��Ʈ >
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Font/3]-horz.bmp", L"3]-horz");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Font/Combo_Bonus.bmp", L"Combo_Bonus");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Font/ComboNumber.bmp", L"ComboNumber");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Font/HitCombo.bmp", L"HitCombo");

	// < ���� HpBar >
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster_Hp/BossHp2.bmp", L"BossHp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster_Hp/MonsterBar.bmp", L"MonsterHp");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster_Hp/BossBar.bmp", L"BossBar");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster_Hp/MonsterHpBar.bmp", L"MonsterBar");

	// < ���� Ÿ�� >
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Human_Type.bmp", L"Human_Type");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Beast_Type.bmp", L"Beast_Type");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Complex_Type.bmp", L"Complex_Type");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Devil_Type.bmp", L"Devil_Type");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Undead_Type.bmp", L"Undead_Type");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Dragon_Type.bmp", L"Dragon_Type");

	// ============================ < Boss - Skasa > =============================================
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Skasa/��ī��/LSkasa.bmp", L"LSkasa");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Skasa/��ī��/RSkasa.bmp", L"RSkasa");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Skasa/��ī��/IceMagic.bmp", L"IceMagic");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Skasa/��ī��/SkasaIcon.bmp", L"SkasaIcon");

	// ============================ < Boss - Isys > =============================================

	// ============================ < Monster > =============================================
	// - ��� ���� -
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Expeller_L.bmp", L"Expeller_L");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Expeller_R.bmp", L"Expeller_R");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Expeller_Portrait.bmp", L"Expeller_Portrait");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/SunderBolt.bmp", L"Expeller_Sunder");

	// - ������ -
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Nudeogi/LNudeogi.bmp", L"LNudeogi");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Nudeogi/RNudeogi.bmp", L"RNudeogi");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Nudeogi/Nudeogi_Portrait.bmp", L"Nudeogi_Portrait");

	// - �峭�� -
	// CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Toy/LToy.bmp", L"LToy");
	// CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Toy/RToy.bmp", L"RToy");
	// CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Toy/Toy_Portrait.bmp", L"Toy_Portrait");

	// ============================ < Effect > =============================================
	// - �ǰ� ����Ʈ -
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/�ǰ�����Ʈ/LHitEffect.bmp", L"LHitEffect");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/�ǰ�����Ʈ/RHitEffect.bmp", L"RHitEffect");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/�ǰ�����Ʈ/MonsterHit.bmp", L"MonsterHit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/�ǰ�����Ʈ/PlayerHit.bmp", L"PlayerHit");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/�ǰ�����Ʈ/PlayerHit_Daegak.bmp", L"PlayerHit_Daegak");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/�ǰ�����Ʈ/PlayerHit_Normal.bmp", L"PlayerHit_Normal");

#pragma endregion �̹��� �ε�
}

void CMainGame::Update(void)
{
	CSceneMgr::Get_Instance()->Update();
	CTimeMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update(void)
{
	CSceneMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Scroll_Lock();
}

void CMainGame::Render(void)
{	
	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"������������ FPS : %d", m_iFPS);
		m_iFPS = 0;
		m_dwTime = GetTickCount();

		// SetWindowText : ������ Ÿ��Ʋ�� ����ϴ� �Լ�
		SetWindowText(g_hWnd, m_szFPS);
	}

	// �ܻ� ���Ÿ� ���� BackDC
	HDC		hBackDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");

	// ���� ���۸� : �̸� hBackDC�� �׸� ����, �ش� DC�� �ѹ��� m_DC�� �����Ͽ� �������� ���ش�.
	CSceneMgr::Get_Instance()->Render(hBackDC);

	// �̸� �׷����� ȭ���� hBackDC�� �״�� ������� �����Ͽ� m_DC�� �����Ѵ�
	BitBlt(m_DC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);
}

void CMainGame::Release(void)
{
	CSoundMgr::Destroy_Instance();
	CTimeMgr::Destroy_Instance();
	CScrollMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	CTileMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();
	CBmpMgr::Destroy_Instance();

	ReleaseDC(g_hWnd, m_DC);
}

