
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

#pragma region 이미지 로딩
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

	// < 마을 컷신 >
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

	// < 포션 이펙트 >
	// CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/포션이펙트/HpPotion.bmp", L"HpPotion");
	// CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/포션이펙트/ManaPotion.bmp", L"ManaPotion");

	// < 아이템 >
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Item_Back2.bmp", L"Item_Back2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Item_Back3.bmp", L"Item_Back3");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/무기/Weapon4.bmp", L"Weapon4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/무기/Weapon3.bmp", L"Weapon3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/무기/Weapon2.bmp", L"Weapon2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/무기/Weapon1.bmp", L"Weapon1");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/칭호/Title1.bmp", L"Title1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/칭호/541.bmp", L"Title2");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/팔찌/Bracelet1.bmp", L"Bracelet1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/팔찌/Bracelet2.bmp", L"Bracelet2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/팔찌/Bracelet3.bmp", L"Bracelet3");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/목걸이/Neckless1.bmp", L"Neckless1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/목걸이/Neckless2.bmp", L"Neckless2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/목걸이/Neckless3.bmp", L"Neckless3");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/반지/Ring1.bmp", L"Ring1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/반지/Ring2.bmp", L"Ring2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/반지/Ring3.bmp", L"Ring3");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/보조장비/SupportItem.bmp", L"SupportItem");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/마법석/MasicStone1.bmp", L"MasicStone1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/마법석/MasicStone2.bmp", L"MasicStone2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/마법석/MasicStone3.bmp", L"MasicStone3");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/상의/Armor4.bmp", L"Armor4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/상의/Armor5.bmp", L"Armor5");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/상의/Armor6.bmp", L"Armor6");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/하의/Pant4.bmp", L"Pant4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/하의/Pant5.bmp", L"Pant5");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/하의/Pant6.bmp", L"Pant6");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/벨트/Belt4.bmp", L"Belt4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/벨트/Belt5.bmp", L"Belt5");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/벨트/Belt6.bmp", L"Belt6");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/어깨/Shoulder4.bmp", L"Shoulder4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/어깨/Shoulder5.bmp", L"Shoulder5");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/어깨/Shoulder6.bmp", L"Shoulder6");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/신발/Shoes4.bmp", L"Shoes4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/신발/Shoes5.bmp", L"Shoes5");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/신발/Shoes6.bmp", L"Shoes6");

	// < 데미지 폰트 >
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Font/HpNumber.bmp", L"MonsterHpNum");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Font/Damage.bmp", L"Damage");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Font/DamageNumber.bmp", L"DamageFont1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Font/ComboNumber_3.bmp", L"DamageFont2");

	// < 콤보 폰트 >
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Font/3]-horz.bmp", L"3]-horz");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Font/Combo_Bonus.bmp", L"Combo_Bonus");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Font/ComboNumber.bmp", L"ComboNumber");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Font/HitCombo.bmp", L"HitCombo");

	// < 몬스터 HpBar >
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster_Hp/BossHp2.bmp", L"BossHp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster_Hp/MonsterBar.bmp", L"MonsterHp");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster_Hp/BossBar.bmp", L"BossBar");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster_Hp/MonsterHpBar.bmp", L"MonsterBar");

	// < 몬스터 타입 >
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Human_Type.bmp", L"Human_Type");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Beast_Type.bmp", L"Beast_Type");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Complex_Type.bmp", L"Complex_Type");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Devil_Type.bmp", L"Devil_Type");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Undead_Type.bmp", L"Undead_Type");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Dragon_Type.bmp", L"Dragon_Type");

	// ============================ < Boss - Skasa > =============================================
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Skasa/스카사/LSkasa.bmp", L"LSkasa");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Skasa/스카사/RSkasa.bmp", L"RSkasa");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Skasa/스카사/IceMagic.bmp", L"IceMagic");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Skasa/스카사/SkasaIcon.bmp", L"SkasaIcon");

	// ============================ < Boss - Isys > =============================================

	// ============================ < Monster > =============================================
	// - 기사 몬스터 -
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Expeller_L.bmp", L"Expeller_L");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Expeller_R.bmp", L"Expeller_R");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Expeller_Portrait.bmp", L"Expeller_Portrait");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/SunderBolt.bmp", L"Expeller_Sunder");

	// - 누더기 -
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Nudeogi/LNudeogi.bmp", L"LNudeogi");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Nudeogi/RNudeogi.bmp", L"RNudeogi");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Nudeogi/Nudeogi_Portrait.bmp", L"Nudeogi_Portrait");

	// - 장난감 -
	// CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Toy/LToy.bmp", L"LToy");
	// CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Toy/RToy.bmp", L"RToy");
	// CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Toy/Toy_Portrait.bmp", L"Toy_Portrait");

	// ============================ < Effect > =============================================
	// - 피격 이펙트 -
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/피격이펙트/LHitEffect.bmp", L"LHitEffect");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/피격이펙트/RHitEffect.bmp", L"RHitEffect");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/피격이펙트/MonsterHit.bmp", L"MonsterHit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/피격이펙트/PlayerHit.bmp", L"PlayerHit");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/피격이펙트/PlayerHit_Daegak.bmp", L"PlayerHit_Daegak");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/피격이펙트/PlayerHit_Normal.bmp", L"PlayerHit_Normal");

#pragma endregion 이미지 로딩
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
		swprintf_s(m_szFPS, L"던전앤파이터 FPS : %d", m_iFPS);
		m_iFPS = 0;
		m_dwTime = GetTickCount();

		// SetWindowText : 윈도우 타이틀에 출력하는 함수
		SetWindowText(g_hWnd, m_szFPS);
	}

	// 잔상 제거를 위한 BackDC
	HDC		hBackDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");

	// 더블 버퍼링 : 미리 hBackDC에 그린 다음, 해당 DC를 한번에 m_DC로 송출하여 깜빡임을 없앤다.
	CSceneMgr::Get_Instance()->Render(hBackDC);

	// 미리 그려놓은 화면인 hBackDC를 그대로 고속으로 복사하여 m_DC에 송출한다
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

