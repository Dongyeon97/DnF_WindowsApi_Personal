#include "stdafx.h"
#include "Player.h"

#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

#include "UI_Inven.h"
#include "UI_Shop.h"
#include "UI_Hp.h"
#include "UI_Mp.h"
#include "Bullet.h"
#include "PlayerAttack.h"
#include "UI_Base.h"
#include "Effect.h"
#include "Item.h"
#include "PlayerAttack2.h"
#include "UI_SkillIcon.h"
#include "UI_Alpha.h"
#include "NonAlpha.h"
#include "UI_SkillIcon_2.h"
#include "Satelite.h"
#include "Vertical.h"
#include "Vertical.h"
#include "UI_Info.h"

float g_fVolume = 0.1f;

CPlayer::CPlayer() : m_fDistance(0.f),
					m_fJumpSpeed(0.f),
					m_fJumpTime(0.f),
					m_lJumpEndTime(0),
					m_iJumpAttackCount(0),
					m_lJumpAttackTime(0),
					m_ePlayerPreState(PS_END),
					m_ePlayerState(PS_IDLE),
					m_fLRunReadyTime(0),
					m_fRRunReadyTime(0),
					m_lAtkFinalTime(0),
					m_lAtkEndTime(0),
					m_lSlideTime(0),
					m_fSlideSpeed(4.f),
					m_lWalkTime(0),
					m_iNormalFinalCount(0),
					m_iDNormalCount(0),
					m_iWindmillCount(0),
					m_iHeadShotCount(0),
					m_iMovingShotCount(0),
					m_iSpreeCount(0),
					m_iSateliteCount(0),
					m_iSeventhCount(0),
					m_HpCoolTime(0),
					m_MpCoolTime(0),
					m_bDBR(false),
					m_bGunGuard(false),
					m_DBRCool(COOL_DBR),
					m_ZacksCool(COOL_ZACKS),
					m_GunGuardCool(COOL_GUNGUARD),
					m_WindmillCool(COOL_WINDMILL),
					m_MahaCool(COOL_MAHA),
					m_HeadShotCool(COOL_HEADSHOT),
					m_MovingShotCool(COOL_MOVINGSHOT),
					m_SpreeCool(COOL_SPREE),
					m_SateliteCool(COOL_SATELITE),
					m_AwakeningCool(COOL_AWAKENING),
					m_bBuff(false)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	// 플레이어 스테이터스
	m_tInfo = { (SERIAROOM_SIZEX * 0.5f), (SERIAROOM_SIZEY * 0.5f), 271.f, 237.f };
	m_fSpeed = 5.f;
	m_fDistance = 100.f;
	m_fAngle = 0.f;

	m_fJumpSpeed = 16.5f;

	// Hp
	m_tInfo.fMaxHp = 70000.f;
	m_tInfo.fHp = 70000.f;
			
	// Mp
	m_tInfo.fMaxMp = 10000.f;
	m_tInfo.fMp = 7000.f;

	// 물공, 물방
	m_tInfo.fAtk = 358.f;
	m_tInfo.fDef = 38976.f;

	// 마공, 마방
	m_tInfo.fMAtk = 2462.f;
	m_tInfo.fMDef = 41711.f;

	// 힘, 공속
	m_tInfo.fStrength = 3736.f;
	m_tInfo.fAtkSpeed = 77.3214f;

	// 체력, 이속
	m_tInfo.fHealth = 2853.f;
	m_tInfo.fMoveSpeed = 67.2f;

	// 화, 수, 명, 암
	m_tInfo.fFire		= 31.f;
	m_tInfo.fWater		= 21.f;
	m_tInfo.fLightness	= 21.f;
	m_tInfo.fDarkness	= 21.f;

	// 항마력
	m_tInfo.fExorcism = 5821.f;

	// 타일충돌 Rect 크기
	m_fTileCollisionSizeX = 64.f;
	m_fTileCollisionSizeY = 64.f;

	// 피격 Rect 크기
	m_fCollisionSizeX = 54.f;
	m_fCollisionSizeY = 140.f;

	// 애니메이션
	m_eRender = GAMEOBJECT;
	m_ePlayerState = PS_IDLE;
	m_eMonType = PLAYER;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 0.2;
	m_tFrame.dwTime = 0;

	m_pFrameKey = L"Player_LEFT";
	m_eDir = DIR_LEFT;

	// 상하좌우 방향 상태 이미지 불러오기
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/LPlayer.bmp", L"Player_LEFT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/RPlayer.bmp", L"Player_RIGHT");

	// 플레이어 잔상
	// CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/LPlayer2.bmp", L"LPlayer_Black");
	// CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/RPlayer2.bmp", L"RPlayer_Black");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/각성기/L각성기/L각성2.bmp", L"LAwaken_Black");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/각성기/R각성기/R각성2.bmp", L"RAwaken_Black");

	// 플레이어 그림자
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Shadow.bmp", L"Shadow");

	// ============================ < Player Attack & Skill > ============================
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/일반공격/BulletLeft.bmp", L"LBullet");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/일반공격/BulletRight.bmp", L"RBullet");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/일반공격/BulletLowLeft.bmp", L"LBullet_Low");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/일반공격/BulletLowRight.bmp", L"RBullet_Low");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/기본 공격/LSFiringEffect.bmp", L"LSFiringEffect");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/기본 공격/RSFiringEffect.bmp", L"RSFiringEffect");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/기본 공격/LFiringEffect.bmp", L"LFiringEffect");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/기본 공격/RFiringEffect.bmp", L"RFiringEffect");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/잭스파이크/ZackSpikeLeft.bmp", L"LZacks");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/잭스파이크/ZackSpikeRight.bmp", L"RZacks");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/윈드밀/Windmill.bmp", L"Windmill");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/윈드밀/WindmillDust.bmp", L"WindmillDust");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/마하킥/LMaha.bmp", L"LMaha");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/마하킥/RMaha.bmp", L"RMaha");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/헤드샷/LSConflictEffect.bmp", L"LSConflictEffect");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/헤드샷/RSConflictEffect.bmp", L"RSConflictEffect");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/헤드샷/LHeadShot.bmp", L"LHeadShot");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/헤드샷/LHeadConflictEffect.bmp", L"LHeadConflictEffect");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/헤드샷/LHeadShootHit.bmp", L"LHeadShootHit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/헤드샷/LHeadShootNormal.bmp", L"LHeadShootNormal");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/헤드샷/RHeadShot.bmp", L"RHeadShot");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/헤드샷/RHeadConflictEffect.bmp", L"RHeadConflictEffect");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/헤드샷/RHeadShootHit.bmp", L"RHeadShootHit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/헤드샷/RHeadShootNormal.bmp", L"RHeadShootNormal");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/난사/L_Random_Fire3.bmp", L"LSpree");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/난사/R_Random_Fire2.bmp", L"RSpree");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/난사/LD_Random_Fire2.bmp", L"LDSpree");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/난사/RD_Random_Fire2.bmp", L"RDSpree");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/난사/LDD_Random_Fire2.bmp", L"LDDSpree");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/난사/RDD_Random_Fire2.bmp", L"RDDSpree");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/난사/LU_Random_Fire2.bmp", L"LUSpree");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/난사/RU_Random_Fire2.bmp", L"RUSpree");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/각성기/L각성기/L각성1.bmp", L"LAwakening");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/각성기/R각성기/R각성1.bmp", L"RAwakening");
	
	// 데스바이리볼버
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/데스바이리볼버/DeathByRevolver3.bmp", L"DeathByRevolver2");
	// 세틀라이트빔
	// CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/세틀라이트빔/Satelaser/CutIn_Buff2.bmp", L"CutIn_Buff");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/세틀라이트빔/Satelaser/Satelaser_Core3.bmp", L"Satelaser_Core");
	// CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/세틀라이트빔/Satelaser/Satelaser_CrashRemaster.bmp", L"Satelaser_CrashRemaster");
	// CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/세틀라이트빔/Satelaser/Satelaser_Sub.bmp", L"Satelaser_Sub");
	// CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/세틀라이트빔/Satelaser/Satelaser_Target.bmp", L"Satelaser_Target");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/각성기/L각성기/LSeventhFinal.bmp", L"LSeventhFinal");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/각성기/L각성기/LSeventhFinalBeforeThree3.bmp", L"LSeventhFinalBeforeThree3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/각성기/L각성기/LSeventhFinalBeforeThree4.bmp", L"LSeventhFinalBeforeThree4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/각성기/L각성기/LSeventhFinalBeforeThree5.bmp", L"LSeventhFinalBeforeThree5");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/각성기/L각성기/LSeventhNormal.bmp", L"LSeventhNormal");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/각성기/R각성기/RSeventhFinal.bmp", L"RSeventhFinal");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/각성기/R각성기/RSeventhFinalBeforeThree3.bmp", L"RSeventhFinalBeforeThree3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/각성기/R각성기/RSeventhFinalBeforeThree4.bmp", L"RSeventhFinalBeforeThree4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/각성기/R각성기/RSeventhFinalBeforeThree5.bmp", L"RSeventhFinalBeforeThree5");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/각성기/R각성기/RSeventhNormal.bmp", L"RSeventhNormal");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/각성기/SeventhDust.bmp", L"SeventhDust");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/각성기/SeventhDust1.bmp", L"SeventhDust1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/각성기/SeventhFeather1.bmp", L"SeventhFeather1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/각성기/SeventhFeather2.bmp", L"SeventhFeather2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/각성기/SeventhFeather3.bmp", L"SeventhFeather3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/각성기/SeventhFeather4.bmp", L"SeventhFeather4");

	// ============================ < 스킬 아이콘 > ============================
	// 회색 아이콘(쿨타임용)
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/각종 스킬 아이콘/BZack.bmp", L"BZack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/각종 스킬 아이콘/WindMill_Off.bmp", L"WindMill_Off");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/각종 스킬 아이콘/MahaKick_Off.bmp", L"MahaKick_Off");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/각종 스킬 아이콘/HeadShoot_Off.bmp", L"HeadShoot_Off");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/각종 스킬 아이콘/Moving_Shoot_Off.bmp", L"Moving_Shoot_Off");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/각종 스킬 아이콘/Random_Shoot_Off.bmp", L"Random_Shoot_Off");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/각종 스킬 아이콘/Seven'sFlow_Off.bmp", L"Seven'sFlow_Off");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/각종 스킬 아이콘/DBR.bmp", L"DBR");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/각종 스킬 아이콘/GunGuard.bmp", L"GunGuard");

	// 일반 아이콘
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/각종 스킬 아이콘/Zack2.bmp", L"Zack2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/각종 스킬 아이콘/Icon_Satelaser.bmp", L"Icon_Satelaser");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/각성기/Cutsin.bmp", L"Cutsin"); // 각성기 컷신
}

void CPlayer::Update_Rect()
{
	// 오브젝트 실제 크기 업데이트
	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));

	// 플레이어 충돌체 업데이트
	m_tRectCollision.left = LONG(m_tInfo.fX - (m_fCollisionSizeX * 0.5f));
	m_tRectCollision.top = LONG(m_tInfo.fY + (m_fCollisionSizeY * 0.5f) - m_fCollisionSizeY);
	m_tRectCollision.right = LONG(m_tInfo.fX + (m_fCollisionSizeX * 0.5f));
	m_tRectCollision.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));

	m_lRectCollisionCenter = { m_tRectCollision.left + LONG(m_fCollisionSizeX * 0.5f),
							m_tRectCollision.top + LONG(m_fCollisionSizeY * 0.5f) };

	// 플레이어 - 타일 충돌용 업데이트
	if ((m_ePlayerState != PS_JUMP && m_ePlayerState != PS_JUMPATTACK && m_ePlayerState != PS_LEVITATE_ATTACKED))
	{
		m_tTileCollision.left = LONG(m_tInfo.fX - (m_fTileCollisionSizeX * 0.5f));
		m_tTileCollision.top = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f) - m_fTileCollisionSizeY);
		m_tTileCollision.right = LONG(m_tInfo.fX + (m_fTileCollisionSizeX * 0.5f));
		m_tTileCollision.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));

		m_lTileCollisionCenter = { m_tTileCollision.left + LONG(m_fTileCollisionSizeX * 0.5f),
								m_tTileCollision.top + LONG(m_fTileCollisionSizeY * 0.5f) };
	}
}

void CPlayer::Move_Frame()
{
	// 시간에 흐름에 따라 프레임 변화
	if (m_tFrame.dwSpeed < m_tFrame.dwTime)
	{
		// 날아가는 피격모션은 마지막 모션 유지
		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd && m_ePlayerState == PS_LEVITATE_ATTACKED)
		{
			m_tFrame.iFrameStart = 4;
		}

		// if문에 한번 들어올 때마다 프레임 변화를 줌
		++m_tFrame.iFrameStart;

		// 계속해서 델타 타임 갱신
		m_tFrame.dwTime = 0;

		// 스프라이트 끝에 도달하면 첫 스프라이트로 돌아감
		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
	}
}

int CPlayer::Update()
{
	m_eRender = GAMEOBJECT;
	m_dwTime += CTimeMgr::Get_Instance()->GetfDT();
	m_tFrame.dwTime += CTimeMgr::Get_Instance()->GetfDT();

	// 회복물약 쿨타임
	m_HpCoolTime += CTimeMgr::Get_Instance()->GetfDT();
	m_MpCoolTime += CTimeMgr::Get_Instance()->GetfDT();

	if (0 >= m_tInfo.fHp && PS_DEAD != m_ePlayerState)
	{
		CSoundMgr::Get_Instance()->PlaySoundW(L"gn_death.wav", SOUND_EFFECT, g_fVolume);
		m_ePlayerState = PS_DEAD;
	}

	// 스킬 쿨타임 체크
	Cool_Check();
	DBR_Check();
	GunGuard_Check();

	// 그로기 버프 시간 체크
	if (m_bBuff)
		GrogyBuff_Check();

	Key_Input();
	Motion_Change();
	Update_Rect();

   return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
	// 피격시에만 피격충돌을 처리하도록 최적화
	if(PS_THRUST_ATTACKED == m_ePlayerState || PS_NORMAL_ATTACKED == m_ePlayerState || PS_LEVITATE_ATTACKED == m_ePlayerState)
	{
		OnKnockback(m_tHitInfo, m_tTileCollision.bottom);
	}
	Moving();
	Offset();
	if (!m_bStopMotion)
	{
		Move_Frame();
	}
}

void CPlayer::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	// 충돌 테스트용 렉트
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	// 렉트 체크용
	/*Rectangle(hDC, m_tRectCollision.left + fScrollX, m_tRectCollision.top + fScrollY,
		m_tRectCollision.right + fScrollX, m_tRectCollision.bottom + fScrollY);

	Rectangle(hDC, m_tRect.left + fScrollX, m_tRect.top + fScrollY,
		m_tRect.right + fScrollX, m_tRect.bottom + fScrollY);

	Rectangle(hDC, m_tTileCollision.left + fScrollX, m_tTileCollision.top + fScrollY,
		m_tTileCollision.right + fScrollX, m_tTileCollision.bottom + fScrollY);*/

	// 폰트
	HFONT font = CreateFont(18, 0, 0, 0, 850, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
		VARIABLE_PITCH | FF_ROMAN, L"맑은 고딕");
	HFONT oldfont = (HFONT)SelectObject(hDC, font);

	// 이동사격 발수 표시
	if (PS_MOVINGSHOT == m_ePlayerState)
	{
		SetTextColor(hDC, RGB(0, 0, 0));
		SetBkMode(hDC, TRANSPARENT); // 매개변수 DC의 글자배경을 투명하게 한다. 
		SetTextAlign(hDC, TA_LEFT);
		TextOut(hDC, m_tRectCollision.right + fScrollX - 10, m_tRectCollision.top + fScrollY, to_wstring(22 - m_iMovingShotCount).c_str(), (to_wstring(22 - m_iMovingShotCount)).size());
		SetBkMode(hDC, OPAQUE);
	}
	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkMode(hDC, TRANSPARENT); // 매개변수 DC의 글자배경을 투명하게 한다. 
	SetTextAlign(hDC, TA_CENTER);
	TextOut(hDC, m_tRectCollision.left + (Get_RectCollisionSizeX() * 0.5f) + fScrollX + 3, m_tRectCollision.top + fScrollY + 3,
		L"쥬신박동연", 6);
	SetBkMode(hDC, OPAQUE);

	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkMode(hDC, TRANSPARENT); // 매개변수 DC의 글자배경을 투명하게 한다. 
	SetTextAlign(hDC, TA_CENTER);
	TextOut(hDC, m_tRectCollision.left + (Get_RectCollisionSizeX() * 0.5f) + fScrollX + 2, m_tRectCollision.top + fScrollY + 2,
			L"쥬신박동연", 6);
	SetBkMode(hDC, OPAQUE);

	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkMode(hDC, TRANSPARENT); // 매개변수 DC의 글자배경을 투명하게 한다. 
	SetTextAlign(hDC, TA_LEFT);

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);

	// 알파 블렌딩 그림자
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 100;

	HDC	hMemDC2 = CBmpMgr::Get_Instance()->Find_Img(L"Shadow");

	GdiAlphaBlend(hDC,
		m_tTileCollision.left + (long)fScrollX,
		m_tTileCollision.top + (long)fScrollY + 30,
		60,
		28,
		hMemDC2,
		0,
		0,
		60,
		28,
		bf);
	

	// 플레이어 이미지 출력
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	GdiTransparentBlt(hDC,
					m_tRect.left + (long)fScrollX,
					m_tRect.top + (long)fScrollY,
					(int)m_tInfo.fCX,
					(int)m_tInfo.fCY,
					hMemDC,
					m_tFrame.iFrameStart * (int)m_tInfo.fCX,
					m_tFrame.iMotion * (int)m_tInfo.fCY,
					(int)m_tInfo.fCX,
					(int)m_tInfo.fCY,
					RGB(255, 255, 255));
}

void CPlayer::Release()
{
}

void CPlayer::DBR_Check()
{
	if (COOL_DBR < m_DBRCool && Get_DBR())
	{
		Set_DBR(false);
		m_tInfo.fAtk -= 300.f;
		m_fCriRatio -= 50.f;
	}
}

void CPlayer::GunGuard_Check()
{
	if (1.5 < m_GunGuardCool && Get_GunGuard())
	{
		Set_GunGuard(false);
		Set_IsImmune(false);
	}
}

void CPlayer::GrogyBuff_Check()
{
	if (m_GrogyBuffTime < 0)
	{
		m_bBuff = false;
		m_tInfo.fAtk -= 500;
		m_GrogyBuffTime = 0;
	}
	else
		m_GrogyBuffTime -= CTimeMgr::Get_Instance()->GetfDT();
}

void CPlayer::Key_Input(void)
{
	// 사운드 조절
	/*if (CKeyMgr::Get_Instance()->Key_Down(VK_F1))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"Success.wav", SOUND_EFFECT, g_fVolume);
		return;
	}

	else if (CKeyMgr::Get_Instance()->Key_Down(VK_F2))
	{
		g_fVolume -= 0.1f;

		if (0.f > g_fVolume)
			g_fVolume = 0.f;

		CSoundMgr::Get_Instance()->SetChannelVolume(SOUND_EFFECT, g_fVolume);
		return;
	}

	else if (CKeyMgr::Get_Instance()->Key_Down(VK_F3))
	{
		g_fVolume += 0.1f;

		if (1.f < g_fVolume)
			g_fVolume = 1.f;

		CSoundMgr::Get_Instance()->SetChannelVolume(SOUND_EFFECT, g_fVolume);
		return;
	}*/

	// ← 왼쪽 방향키
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)
		&& (m_ePlayerState != PS_NORMAL_ATTACKED && m_ePlayerState != PS_THRUST_ATTACKED && m_ePlayerState != PS_LEVITATE_ATTACKED))
	{
		if ((m_ePlayerState != PS_ATTACK1 && m_ePlayerState != PS_ATTACK2 && m_ePlayerState != PS_ATTACK3 && m_ePlayerState != PS_ATTACK4 && m_ePlayerState != PS_ATTACK5)
			&& (m_ePlayerState != PS_LSLIDE && m_ePlayerState != PS_RSLIDE)
			&& (m_ePlayerState != PS_DATTACK1 && m_ePlayerState != PS_DATTACK2 && m_ePlayerState != PS_DATTACK3 && m_ePlayerState != PS_DATTACK4 && m_ePlayerState != PS_DATTACK5)
			&& (m_ePlayerState != PS_JUMP && m_ePlayerState != PS_JUMPATTACK)
			&& (m_ePlayerState != PS_ZACKS && m_ePlayerState != PS_WINDMILL && m_ePlayerState != PS_MAHA)
			&& (m_ePlayerState != PS_DBR && m_ePlayerState != PS_GUNGUARD && m_ePlayerState != PS_HEADSHOT && m_ePlayerState != PS_MOVINGSHOT && m_ePlayerState != PS_SPREE)
			&& (m_ePlayerState != PS_AWAKEN && m_ePlayerState != PS_LAWAKENING && m_ePlayerState != PS_RAWAKENING)
			&& m_ePlayerState != PS_SATELITE && m_ePlayerState != PS_DEAD)
		{
			if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
				m_ePlayerState = PS_IDLE;
			DWORD currentTime = GetTickCount();
			if ((currentTime - m_fLRunReadyTime <= 300 || m_ePlayerState == PS_LRUN) && !(CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)))
			{
				m_pFrameKey = L"Player_LEFT";
				m_eDir = DIR_LEFT;
				m_ePlayerState = PS_LRUN;
			}
			else if (!(CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)))
			{
				m_lWalkTime = GetTickCount();
				m_pFrameKey = L"Player_LEFT";
				m_eDir = DIR_LEFT;
				m_ePlayerState = PS_LWALK;
			}
		}
		// 달리기 중에 X키를 누르면 슬라이딩
		if (m_ePlayerState == PS_LRUN && CKeyMgr::Get_Instance()->Key_Pressing('X'))
		{
			m_lSlideTime = GetTickCount();
			m_pFrameKey = L"Player_LEFT";
			m_eDir = DIR_LEFT;
			m_fSlideSpeed = 4.0f;
			m_ePlayerState = PS_LSLIDE;
			CSoundMgr::Get_Instance()->PlaySoundW(L"gn_sliding_03.wav", SOUND_EFFECT, g_fVolume);
		}

		// 왼쪽 방향키를 눌렀는데 점프중일때
		if (m_ePlayerState == PS_JUMP)
		{
			m_pFrameKey = L"Player_LEFT";
			m_eDir = DIR_LEFT;
			m_tInfo.fX -= 1.2f * m_fSpeed;
			m_tTileCollision.left -= LONG(1.2f * m_fSpeed);
			m_tTileCollision.right -= LONG(1.2f * m_fSpeed);
		}
		// 왼쪽 방향키를 눌렀는데 점공중일때
		else if (m_ePlayerState == PS_JUMPATTACK)
		{
		}
	}
	if (CKeyMgr::Get_Instance()->Key_Up(VK_LEFT) 
		&& (m_ePlayerState != PS_NORMAL_ATTACKED && m_ePlayerState != PS_THRUST_ATTACKED && m_ePlayerState != PS_LEVITATE_ATTACKED)
		&& (m_ePlayerState != PS_LSLIDE && m_ePlayerState != PS_RSLIDE)
		&& (m_ePlayerState != PS_JUMP && m_ePlayerState != PS_JUMPATTACK)
		&& (m_ePlayerState != PS_ZACKS && m_ePlayerState != PS_WINDMILL && m_ePlayerState != PS_MAHA) 
		&& (m_ePlayerState != PS_DBR && m_ePlayerState != PS_GUNGUARD && m_ePlayerState != PS_HEADSHOT && m_ePlayerState != PS_MOVINGSHOT && m_ePlayerState != PS_SPREE)
		&& (m_ePlayerState != PS_AWAKEN && m_ePlayerState != PS_LAWAKENING && m_ePlayerState != PS_RAWAKENING)
		&& m_ePlayerState != PS_SATELITE && m_ePlayerState != PS_DEAD)
	{
		// ← 을 누르다가 땠는데 달리던 중이였을 때 멈춤
		if (m_ePlayerState == PS_LRUN)
			m_ePlayerState = PS_IDLE;

		m_fLRunReadyTime = GetTickCount();
		m_pFrameKey = L"Player_LEFT";
		m_eDir = DIR_LEFT;
	}

	// → 오른쪽 방향키
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT) 
		&& (m_ePlayerState != PS_NORMAL_ATTACKED && m_ePlayerState != PS_THRUST_ATTACKED && m_ePlayerState != PS_LEVITATE_ATTACKED))
	{
		if ((m_ePlayerState != PS_ATTACK1 && m_ePlayerState != PS_ATTACK2 && m_ePlayerState != PS_ATTACK3 && m_ePlayerState != PS_ATTACK4 && m_ePlayerState != PS_ATTACK5)
			&& (m_ePlayerState != PS_DATTACK1 && m_ePlayerState != PS_DATTACK2 && m_ePlayerState != PS_DATTACK3 && m_ePlayerState != PS_DATTACK4 && m_ePlayerState != PS_DATTACK5)
			&& (m_ePlayerState != PS_LSLIDE && m_ePlayerState != PS_RSLIDE)
			&& (m_ePlayerState != PS_JUMP && m_ePlayerState != PS_JUMPATTACK)
			&& (m_ePlayerState != PS_ZACKS && m_ePlayerState != PS_WINDMILL && m_ePlayerState != PS_MAHA) 
			&& (m_ePlayerState != PS_DBR && m_ePlayerState != PS_GUNGUARD && m_ePlayerState != PS_HEADSHOT && m_ePlayerState != PS_MOVINGSHOT && m_ePlayerState != PS_SPREE)
			&& (m_ePlayerState != PS_AWAKEN && m_ePlayerState != PS_LAWAKENING && m_ePlayerState != PS_RAWAKENING)
			&& m_ePlayerState != PS_SATELITE && m_ePlayerState != PS_DEAD)
		{
			if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
				m_ePlayerState = PS_IDLE;
			DWORD currentTime = GetTickCount();
			if ((currentTime - m_fRRunReadyTime <= 300 || m_ePlayerState == PS_RRUN) && !(CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)))
			{
				m_pFrameKey = L"Player_RIGHT";
				m_eDir = DIR_RIGHT;
				m_ePlayerState = PS_RRUN;
			}
			else if (!(CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)))
			{
				m_lWalkTime = GetTickCount();
				m_pFrameKey = L"Player_RIGHT";
				m_eDir = DIR_RIGHT;
				m_ePlayerState = PS_RWALK;
			}
		}
		// 달리기 중에 X키를 누르면 슬라이딩
		if (m_ePlayerState == PS_RRUN && CKeyMgr::Get_Instance()->Key_Pressing('X'))
		{
			m_lSlideTime = GetTickCount();
			m_pFrameKey = L"Player_RIGHT";
			m_eDir = DIR_RIGHT;
			m_fSlideSpeed = 4.0f;
			m_ePlayerState = PS_RSLIDE;
			CSoundMgr::Get_Instance()->PlaySoundW(L"gn_sliding_03.wav", SOUND_EFFECT, g_fVolume);
		}

		// 오른쪽 방향키를 눌렀는데 점프중일때
		if (m_ePlayerState == PS_JUMP)
		{
			m_pFrameKey = L"Player_RIGHT";
			m_eDir = DIR_RIGHT;
			m_tInfo.fX += 1.2f * m_fSpeed;
			m_tTileCollision.left += LONG(1.2f * m_fSpeed);
			m_tTileCollision.right += LONG(1.2f * m_fSpeed);
		}
		else if (m_ePlayerState == PS_JUMPATTACK)
		{
		}
	}
	if (CKeyMgr::Get_Instance()->Key_Up(VK_RIGHT) 
		&& (m_ePlayerState != PS_NORMAL_ATTACKED && m_ePlayerState != PS_THRUST_ATTACKED && m_ePlayerState != PS_LEVITATE_ATTACKED)
		&& (m_ePlayerState != PS_LSLIDE && m_ePlayerState != PS_RSLIDE)
		&& (m_ePlayerState != PS_JUMP && m_ePlayerState != PS_JUMPATTACK)
		&& (m_ePlayerState != PS_ZACKS && m_ePlayerState != PS_WINDMILL && m_ePlayerState != PS_MAHA)
		&& (m_ePlayerState != PS_DBR && m_ePlayerState != PS_GUNGUARD && m_ePlayerState != PS_HEADSHOT && m_ePlayerState != PS_MOVINGSHOT && m_ePlayerState != PS_SPREE)
		&& (m_ePlayerState != PS_AWAKEN && m_ePlayerState != PS_LAWAKENING && m_ePlayerState != PS_RAWAKENING)
		&& m_ePlayerState != PS_SATELITE && m_ePlayerState != PS_DEAD)
	{
		// → 을 누르다가 땠는데 달리던 중이였을 때 멈춤
		if (m_ePlayerState == PS_RRUN)
			m_ePlayerState = PS_IDLE;

		m_fRRunReadyTime = GetTickCount();
		m_pFrameKey = L"Player_RIGHT";
		m_eDir = DIR_RIGHT;
	}

	// ↑ 위 방향키
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP)
		&& (m_ePlayerState != PS_NORMAL_ATTACKED && m_ePlayerState != PS_THRUST_ATTACKED && m_ePlayerState != PS_LEVITATE_ATTACKED))
	{
		// ↑ 를 눌렀는데 왼쪽으로 걷던 중일때
		if (m_ePlayerState == PS_LWALK)
		{
			m_tInfo.fY -= 0.7f * m_fSpeed;
		}
		// ↑ 를 눌렀는데 오른쪽으로 걷던 중일때
		else if (m_ePlayerState == PS_RWALK)
		{
			m_tInfo.fY -= 0.7f * m_fSpeed;
		}
		// ↑ 를 눌렀는데 왼쪽으로 뛰던 중일때
		else if (m_ePlayerState == PS_LRUN)
		{
			m_tInfo.fY -= 0.7f * m_fSpeed;
		}
		// ↑ 를 눌렀는데 오른쪽으로 뛰던 중일때
		else if (m_ePlayerState == PS_RRUN)
		{
			m_tInfo.fY -= 0.7f * m_fSpeed;
		}
		// ↑ 를 눌렀는데 점프 중일때
		else if (m_ePlayerState == PS_JUMP)
		{
			m_tInfo.fY -= 0.1f * m_fSpeed;
			m_tTileCollision.top -= 0.1f * m_fSpeed;
			m_tTileCollision.bottom -= 0.1f * m_fSpeed;
		}

		// 위의 상황들에 속하지 않으면서 공격, 슬라이딩, 스킬(추가예정)사용중이 아니고, 왼쪽을 바라보고 있었을 경우. 위로 그냥 걷기
		else if ((m_ePlayerState != PS_ATTACK1 && m_ePlayerState != PS_ATTACK2 && m_ePlayerState != PS_ATTACK3 && m_ePlayerState != PS_ATTACK4 && m_ePlayerState != PS_ATTACK5)
			&& (m_ePlayerState != PS_DATTACK1 && m_ePlayerState != PS_DATTACK2 && m_ePlayerState != PS_DATTACK3 && m_ePlayerState != PS_DATTACK4 && m_ePlayerState != PS_DATTACK5)
			&& (m_ePlayerState != PS_RSLIDE) && m_ePlayerState == PS_IDLE 
			&& (m_ePlayerState != PS_DATTACK1 && m_ePlayerState != PS_JUMP && m_ePlayerState != PS_JUMPATTACK)
			&& (m_ePlayerState != PS_ZACKS && m_ePlayerState != PS_WINDMILL && m_ePlayerState != PS_MAHA)
			&& (m_ePlayerState != PS_DBR && m_ePlayerState != PS_GUNGUARD && m_ePlayerState != PS_HEADSHOT && m_ePlayerState != PS_MOVINGSHOT && m_ePlayerState != PS_SPREE)
			&& (m_ePlayerState != PS_AWAKEN && m_ePlayerState != PS_LAWAKENING && m_ePlayerState != PS_RAWAKENING)
			&& m_ePlayerState != PS_SATELITE && m_ePlayerState != PS_DEAD)
		{
			m_ePlayerState = PS_JUSTWALKUP;
		}
	}
	if (CKeyMgr::Get_Instance()->Key_Up(VK_UP) 
		&& (m_ePlayerState != PS_NORMAL_ATTACKED && m_ePlayerState != PS_THRUST_ATTACKED && m_ePlayerState != PS_LEVITATE_ATTACKED)
		&& (m_ePlayerState != PS_LSLIDE && m_ePlayerState != PS_RSLIDE)
		&& (m_ePlayerState != PS_JUMP && m_ePlayerState != PS_JUMPATTACK)
		&& (m_ePlayerState != PS_ZACKS && m_ePlayerState != PS_WINDMILL && m_ePlayerState != PS_MAHA)
		&& (m_ePlayerState != PS_DBR && m_ePlayerState != PS_GUNGUARD && m_ePlayerState != PS_HEADSHOT && m_ePlayerState != PS_MOVINGSHOT && m_ePlayerState != PS_SPREE)
		&& (m_ePlayerState != PS_AWAKEN && m_ePlayerState != PS_LAWAKENING && m_ePlayerState != PS_RAWAKENING)
		&& m_ePlayerState != PS_SATELITE && m_ePlayerState != PS_DEAD)
	{
		if (m_ePlayerState == PS_JUSTWALKUP || m_ePlayerState == PS_JUSTWALKDOWN)
			m_ePlayerState = PS_IDLE;
	}

	// ↓ 아래 방향키
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN)
		&& (m_ePlayerState != PS_NORMAL_ATTACKED && m_ePlayerState != PS_THRUST_ATTACKED && m_ePlayerState != PS_LEVITATE_ATTACKED))
	{
		// ↓ 를 눌렀는데 왼쪽으로 걷던 중일때
		if (m_ePlayerState == PS_LWALK)
		{
			m_tInfo.fY += 0.7f * m_fSpeed;
		}
		// ↓ 를 눌렀는데 오른쪽으로 걷던 중일때
		else if (m_ePlayerState == PS_RWALK)
		{
			m_tInfo.fY += 0.7f * m_fSpeed;
		}
		// ↓ 를 눌렀는데 왼쪽으로 뛰던 중일때
		else if (m_ePlayerState == PS_LRUN)
		{
			m_tInfo.fY += 0.7f * m_fSpeed;
		}
		// ↓ 를 눌렀는데 오른쪽으로 뛰던 중일때
		else if (m_ePlayerState == PS_RRUN)
		{
			m_tInfo.fY += 0.7f * m_fSpeed;
		}
		// ↓ 를 눌렀는데 점프 중일때
		else if (m_ePlayerState == PS_JUMP)
		{
			m_tInfo.fY += 0.1f * m_fSpeed;
			m_tTileCollision.top += 0.2f * m_fSpeed;
			m_tTileCollision.bottom += 0.2f * m_fSpeed;
		}

		// 위의 상황들에 속하지 않으면서 공격, 슬라이딩, 스킬(추가예정)사용중이 아닐 때, 아래로 그냥 걷기
		else if ((m_ePlayerState != PS_ATTACK1 && m_ePlayerState != PS_ATTACK2 && m_ePlayerState != PS_ATTACK3 && m_ePlayerState != PS_ATTACK4 && m_ePlayerState != PS_ATTACK5)
			&& (m_ePlayerState != PS_LSLIDE && m_ePlayerState != PS_RSLIDE)
			&& (m_ePlayerState != PS_DATTACK1 && m_ePlayerState != PS_DATTACK2 && m_ePlayerState != PS_DATTACK3 && m_ePlayerState != PS_DATTACK4 && m_ePlayerState != PS_DATTACK5)
			&& (m_ePlayerState != PS_JUMP && m_ePlayerState != PS_JUMPATTACK)
			&& (m_ePlayerState != PS_ZACKS && m_ePlayerState != PS_WINDMILL && m_ePlayerState != PS_MAHA)
			&& (m_ePlayerState != PS_DBR && m_ePlayerState != PS_GUNGUARD && m_ePlayerState != PS_HEADSHOT && m_ePlayerState != PS_MOVINGSHOT && m_ePlayerState != PS_SPREE)
			&& (m_ePlayerState != PS_AWAKEN && m_ePlayerState != PS_LAWAKENING && m_ePlayerState != PS_RAWAKENING)
			&& m_ePlayerState != PS_SATELITE && m_ePlayerState != PS_DEAD)
		{
			m_ePlayerState = PS_JUSTWALKDOWN;
		}
	}
	if (CKeyMgr::Get_Instance()->Key_Up(VK_DOWN)
		&& (m_ePlayerState != PS_NORMAL_ATTACKED && m_ePlayerState != PS_THRUST_ATTACKED && m_ePlayerState != PS_LEVITATE_ATTACKED)
		&& (m_ePlayerState != PS_LSLIDE && m_ePlayerState != PS_RSLIDE)
		&& (m_ePlayerState != PS_JUMP && m_ePlayerState != PS_JUMPATTACK)
		&& (m_ePlayerState != PS_ZACKS && m_ePlayerState != PS_WINDMILL && m_ePlayerState != PS_MAHA)
		&& (m_ePlayerState != PS_DBR && m_ePlayerState != PS_GUNGUARD && m_ePlayerState != PS_HEADSHOT && m_ePlayerState != PS_MOVINGSHOT && m_ePlayerState != PS_SPREE)
		&& (m_ePlayerState != PS_AWAKEN && m_ePlayerState != PS_LAWAKENING && m_ePlayerState != PS_RAWAKENING)
		&& m_ePlayerState != PS_SATELITE && m_ePlayerState != PS_DEAD)
	{
		if (m_ePlayerState == PS_JUSTWALKUP || m_ePlayerState == PS_JUSTWALKDOWN)
			m_ePlayerState = PS_IDLE;
	}

	// BackSpace 메뉴로 나가기
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_BACK))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_LOGO);
		return;
	}

	// C 점프키
	if (CKeyMgr::Get_Instance()->Key_Pressing('C') 
		&& (m_ePlayerState != PS_NORMAL_ATTACKED && m_ePlayerState != PS_THRUST_ATTACKED && m_ePlayerState != PS_LEVITATE_ATTACKED)
		&& (m_ePlayerState != PS_LSLIDE && m_ePlayerState != PS_RSLIDE)
		&& (m_ePlayerState != PS_ATTACK1 && m_ePlayerState != PS_ATTACK2 && m_ePlayerState != PS_ATTACK3 && m_ePlayerState != PS_ATTACK4 && m_ePlayerState != PS_ATTACK5)
		&& (m_ePlayerState != PS_DATTACK1 && m_ePlayerState != PS_JUMP && m_ePlayerState != PS_JUMPATTACK)
		&& (m_ePlayerState != PS_ZACKS && m_ePlayerState != PS_WINDMILL && m_ePlayerState != PS_MAHA)
		&& (m_ePlayerState != PS_DBR && m_ePlayerState != PS_GUNGUARD && m_ePlayerState != PS_HEADSHOT && m_ePlayerState != PS_MOVINGSHOT && m_ePlayerState != PS_SPREE)
		&& (m_ePlayerState != PS_AWAKEN && m_ePlayerState != PS_LAWAKENING && m_ePlayerState != PS_RAWAKENING)
		&& m_ePlayerState != PS_SATELITE && m_ePlayerState != PS_DEAD)
	{
		m_ePlayerState = PS_JUMP;
		m_lJumpEndTime = GetTickCount();
		m_fJumpTime = 0.f;
		CSoundMgr::Get_Instance()->PlaySoundW(L"gn_jump.wav", SOUND_EFFECT, g_fVolume);
	}

	// X 공격키
	if (CKeyMgr::Get_Instance()->Key_Pressing('X') && (m_ePlayerState != PS_LSLIDE && m_ePlayerState != PS_RSLIDE && m_ePlayerState != PS_ATTACK5)
		&& (m_ePlayerState != PS_NORMAL_ATTACKED && m_ePlayerState != PS_THRUST_ATTACKED && m_ePlayerState != PS_LEVITATE_ATTACKED)
		&& (m_ePlayerState != PS_ZACKS && m_ePlayerState != PS_WINDMILL && m_ePlayerState != PS_MAHA)
		&& (m_ePlayerState != PS_DBR && m_ePlayerState != PS_GUNGUARD && m_ePlayerState != PS_HEADSHOT && m_ePlayerState != PS_MOVINGSHOT && m_ePlayerState != PS_SPREE)
		&& (m_ePlayerState != PS_AWAKEN && m_ePlayerState != PS_LAWAKENING && m_ePlayerState != PS_RAWAKENING)
		&& m_ePlayerState != PS_SATELITE && m_ePlayerState != PS_DEAD)
	{
		// 1타
		if ((m_ePlayerState == PS_IDLE || m_ePlayerState == PS_LWALK || m_ePlayerState == PS_RWALK) && (m_ePlayerState != PS_LRUN || m_ePlayerState != PS_RRUN))
		{
			// 아래 평타
			if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
			{
				if (m_pFrameKey == L"Player_LEFT")
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
						Create_Obj(ATT_NORMAL, true, m_tInfo.fX - 80.f, m_tInfo.fY, 30.f, 20.f, 11.5f, 210.f, 0.f, m_tTileCollision.bottom - 10.f, 0.8f, 30.f, 20.f, float(Get_TileCollision().bottom),
							m_tInfo.fAtk, 100.f, 5.f, 2.f, 5.f, 90.f, 0.f, 0.2f, L"LBullet_Low", { 255, 0, 255 }));
				}
				else
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
						Create_Obj(ATT_NORMAL, true, m_tInfo.fX + 80.f, m_tInfo.fY, 30.f, 20.f, 11.5f, 330.f, 0.f, m_tTileCollision.bottom - 10.f, 0.8f, 30.f, 20.f, float(Get_TileCollision().bottom),
							m_tInfo.fAtk, 100.f, 5.f, 2.f, 5.f, 90.f, 0.f, 0.2f, L"RBullet_Low", { 255, 0, 255 }));
				}
				m_ePlayerState = PS_DATTACK1;
			}
			else
			{
				if (m_pFrameKey == L"Player_LEFT")
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
						Create_Obj(ATT_NORMAL, true, m_tInfo.fX - 65.f, m_tInfo.fY - 24.f, 30.f, 20.f, 11.5f, 180.f, 0.f, 0.f, 0.8f, 30.f, 20.f, float(Get_TileCollision().bottom),
							m_tInfo.fAtk, 100.f, 5.f, 2.f, 5.f, 90.f, 0.f, 0.2f, L"LBullet", { 255, 0, 255 }));
				}
				else
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
						Create_Obj(ATT_NORMAL, true, m_tInfo.fX + 65.f, m_tInfo.fY - 24.f, 30.f, 20.f, 11.5f, 0.f, 0.f, 0.f, 0.8f, 30.f, 20.f, float(Get_TileCollision().bottom),
							m_tInfo.fAtk, 100.f, 5.f, 2.f, 5.f, 90.f, 0.f, 0.2f, L"RBullet", { 255, 0, 255 }));
				}
				m_ePlayerState = PS_ATTACK1;
			}
			CSoundMgr::Get_Instance()->PlaySoundW(L"RdShotBullet.wav", SOUND_EFFECT, g_fVolume);
			m_dwTime = 0;
			m_lAtkEndTime = GetTickCount();
		}
		// 2타
		else if ((m_ePlayerState == PS_ATTACK1 && m_dwTime > 0.245)  
				|| (m_ePlayerState == PS_DATTACK1 && m_dwTime > 0.21))
		{
			// 아래 평타
			if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
			{
				if (m_pFrameKey == L"Player_LEFT")
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
						Create_Obj(ATT_NORMAL, true, m_tInfo.fX - 80.f, m_tInfo.fY, 30.f, 20.f, 11.5f, 210.f, 0.f, m_tTileCollision.bottom - 10.f, 0.8f, 30.f, 20.f, float(Get_TileCollision().bottom),
							m_tInfo.fAtk, 100.f, 5.f, 2.f, 5.f, 90.f, 0.f, 0.2f, L"LBullet_Low", { 255, 0, 255 }));
				}
				else
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
						Create_Obj(ATT_NORMAL, true, m_tInfo.fX + 80.f, m_tInfo.fY, 30.f, 20.f, 11.5f, 330.f, 0.f, m_tTileCollision.bottom - 10.f, 0.8f, 30.f, 20.f, float(Get_TileCollision().bottom),
							m_tInfo.fAtk, 100.f, 5.f, 2.f, 5.f, 90.f, 0.f, 0.2f, L"RBullet_Low", { 255, 0, 255 }));
				}
				m_ePlayerState = PS_DATTACK2;
			}
			else
			{
				if (m_pFrameKey == L"Player_LEFT")
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
						Create_Obj(ATT_NORMAL, true, m_tInfo.fX - 65.f, m_tInfo.fY - 24.f, 30.f, 20.f, 11.5f, 180.f, 0.f, 0.f, 0.8f, 30.f, 20.f, float(Get_TileCollision().bottom),
							m_tInfo.fAtk, 100.f, 5.f, 2.f, 5.f, 90.f, 0.f, 0.2f, L"LBullet", { 255, 0, 255 }));
				}
				else
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
						Create_Obj(ATT_NORMAL, true, m_tInfo.fX + 65.f, m_tInfo.fY - 24.f, 30.f, 20.f, 11.5f, 0.f, 0.f, 0.f, 0.8f, 30.f, 20.f, float(Get_TileCollision().bottom),
							m_tInfo.fAtk, 100.f, 5.f, 2.f, 5.f, 90.f, 0.f, 0.2f, L"RBullet", { 255, 0, 255 }));
				}
				m_ePlayerState = PS_ATTACK2;
			}
			CSoundMgr::Get_Instance()->PlaySoundW(L"RdShotBullet.wav", SOUND_EFFECT, g_fVolume);
			m_dwTime = 0;
			m_lAtkEndTime = GetTickCount();
		}
		// 3타
		else if ((m_ePlayerState == PS_ATTACK2 && m_dwTime > 0.245) 
				|| (m_ePlayerState == PS_DATTACK2 && m_dwTime > 0.21))
		{
			// 아래 평타
			if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
			{
				if (m_pFrameKey == L"Player_LEFT")
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
						Create_Obj(ATT_NORMAL, true, m_tInfo.fX - 80.f, m_tInfo.fY, 30.f, 20.f, 11.5f, 210.f, 0.f, m_tTileCollision.bottom - 10.f, 0.8f, 30.f, 20.f, float(Get_TileCollision().bottom),
							m_tInfo.fAtk, 100.f, 5.f, 2.f, 5.f, 90.f, 0.f, 0.2f, L"LBullet_Low", { 255, 0, 255 }));
				}
				else
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
						Create_Obj(ATT_NORMAL, true, m_tInfo.fX + 80.f, m_tInfo.fY, 30.f, 20.f, 11.5f, 330.f, 0.f, m_tTileCollision.bottom - 10.f, 0.8f, 30.f, 20.f, float(Get_TileCollision().bottom),
							m_tInfo.fAtk, 100.f, 5.f, 2.f, 5.f, 90.f, 0.f, 0.2f, L"RBullet_Low", { 255, 0, 255 }));
				}
				m_ePlayerState = PS_DATTACK3;
			}
			else
			{
				if (m_pFrameKey == L"Player_LEFT")
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
						Create_Obj(ATT_NORMAL, true, m_tInfo.fX - 65.f, m_tInfo.fY - 24.f, 30.f, 20.f, 11.5f, 180.f, 0.f, 0.f, 0.8f, 30.f, 20.f, float(Get_TileCollision().bottom),
							m_tInfo.fAtk, 100.f, 5.f, 2.f, 5.f, 90.f, 0.f, 0.2f, L"LBullet", { 255, 0, 255 }));
				}
				else
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
						Create_Obj(ATT_NORMAL, true, m_tInfo.fX + 65.f, m_tInfo.fY - 24.f, 30.f, 20.f, 11.5f, 0.f, 0.f, 0.f, 0.8f, 30.f, 20.f, float(Get_TileCollision().bottom),
							m_tInfo.fAtk, 100.f, 5.f, 2.f, 5.f, 90.f, 0.f, 0.2f, L"RBullet", { 255, 0, 255 }));
				}
				m_ePlayerState = PS_ATTACK3;
			}
			CSoundMgr::Get_Instance()->PlaySoundW(L"RdShotBullet.wav", SOUND_EFFECT, g_fVolume);
			m_dwTime = 0;
			m_lAtkEndTime = GetTickCount64();
		}
		// 4타
		else if ((m_ePlayerState == PS_ATTACK3 && m_dwTime > 0.245) 
			|| (m_ePlayerState == PS_DATTACK3 && m_dwTime > 0.21))
		{
			// 아래 평타
			if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
			{
				if (m_pFrameKey == L"Player_LEFT")
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
						Create_Obj(ATT_NORMAL, true, m_tInfo.fX - 80.f, m_tInfo.fY, 30.f, 20.f, 11.5f, 210.f, 0.f, m_tTileCollision.bottom - 10.f, 0.8f, 30.f, 20.f, float(Get_TileCollision().bottom),
							m_tInfo.fAtk, 100.f, 5.f, 2.f, 5.f, 90.f, 0.f, 0.2f, L"LBullet_Low", { 255, 0, 255 }));
				}
				else
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
						Create_Obj(ATT_NORMAL, true, m_tInfo.fX + 80.f, m_tInfo.fY, 30.f, 20.f, 11.5f, 330.f, 0.f, m_tTileCollision.bottom - 10.f, 0.8f, 30.f, 20.f, float(Get_TileCollision().bottom),
							m_tInfo.fAtk, 100.f, 5.f, 2.f, 5.f, 90.f, 0.f, 0.2f, L"RBullet_Low", { 255, 0, 255 }));
				}
				m_ePlayerState = PS_DATTACK4;
			}
			else
			{
				if (m_pFrameKey == L"Player_LEFT")
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
						Create_Obj(ATT_NORMAL, true, m_tInfo.fX - 65.f, m_tInfo.fY - 24.f, 30.f, 20.f, 11.5f, 180.f, 0.f, 0.f, 0.8f, 30.f, 20.f, float(Get_TileCollision().bottom),
							m_tInfo.fAtk, 100.f, 5.f, 2.f, 5.f, 90.f, 0.f, 0.2f, L"LBullet", { 255, 0, 255 }));
				}
				else
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
						Create_Obj(ATT_NORMAL, true, m_tInfo.fX + 65.f, m_tInfo.fY - 24.f, 30.f, 20.f, 11.5f, 0.f, 0.f, 0.f, 0.8f, 30.f, 20.f, float(Get_TileCollision().bottom),
							m_tInfo.fAtk, 100.f, 5.f, 2.f, 5.f, 90.f, 0.f, 0.2f, L"RBullet", { 255, 0, 255 }));
				}
				m_ePlayerState = PS_ATTACK4;
			}
			CSoundMgr::Get_Instance()->PlaySoundW(L"RdShotBullet.wav", SOUND_EFFECT, g_fVolume);
			m_dwTime = 0;
			m_lAtkEndTime = GetTickCount64();
		}
		// 5타
		else if ((m_ePlayerState == PS_ATTACK4 && m_dwTime > 0.300) 
				|| (m_ePlayerState == PS_DATTACK4 && m_dwTime > 0.300))
		{
			// 아래 평타
			if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
			{
				m_ePlayerState = PS_DATTACK5;
			}
			else
			{
				m_ePlayerState = PS_ATTACK5;
			}
			m_dwTime = 0;
			m_lAtkFinalTime = GetTickCount64();
		}
		// 점공
		else if ((m_ePlayerState == PS_JUMP || m_ePlayerState == PS_JUMPATTACK) && (m_iJumpAttackCount < 4) && (m_dwTime > 0.3))
		{
			if (m_pFrameKey == L"Player_LEFT")
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
					Create_Obj(ATT_NORMAL, true, m_tInfo.fX - 40.f, m_tInfo.fY - 24.f, 30.f, 20.f, 11.5f, 225.f, 0.f, m_tTileCollision.bottom - 10.f, 0.8f, 30.f, 20.f, float(Get_TileCollision().bottom),
								m_tInfo.fAtk, 120.f, 5.f, 2.f, 5.f, 90.f, 0.f, 0.2f, L"LBullet_Low", { 255, 0, 255 }));
			}
			else
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
					Create_Obj(ATT_NORMAL, true, m_tInfo.fX + 40.f, m_tInfo.fY - 24.f, 30.f, 20.f, 11.5f, 315.f, 0.f, m_tTileCollision.bottom - 10.f, 0.8f, 30.f, 20.f, float(Get_TileCollision().bottom),
								m_tInfo.fAtk, 120.f, 5.f, 2.f, 5.f, 90.f, 0.f, 0.2f, L"RBullet_Low", { 255, 0, 255 }));
			}
			CSoundMgr::Get_Instance()->PlaySoundW(L"RdShotBullet.wav", SOUND_EFFECT, g_fVolume);
			m_dwTime = 0;
			++m_iJumpAttackCount;
			m_ePlayerState = PS_JUMPATTACK;
			m_lJumpAttackTime = GetTickCount();
		}
	}
	if (CKeyMgr::Get_Instance()->Key_Up('X'))
	{
		
	}

	// SPACE 데스 바이 리볼버
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE) && MANA_DBR < m_tInfo.fMp && COOL_DBR < m_DBRCool
		&& (m_ePlayerState != PS_NORMAL_ATTACKED && m_ePlayerState != PS_THRUST_ATTACKED && m_ePlayerState != PS_LEVITATE_ATTACKED)
		&& (m_ePlayerState != PS_LSLIDE && m_ePlayerState != PS_RSLIDE)
		&& (m_ePlayerState != PS_JUMP && m_ePlayerState != PS_JUMPATTACK)
		&& (m_ePlayerState != PS_ZACKS && m_ePlayerState != PS_WINDMILL && m_ePlayerState != PS_MAHA)
		&& (m_ePlayerState != PS_GUNGUARD && m_ePlayerState != PS_DBR && m_ePlayerState != PS_HEADSHOT && m_ePlayerState != PS_MOVINGSHOT && m_ePlayerState != PS_SPREE)
		&& (m_ePlayerState != PS_AWAKEN && m_ePlayerState != PS_LAWAKENING && m_ePlayerState != PS_RAWAKENING)
		&& m_ePlayerState != PS_SATELITE && m_ePlayerState != PS_DEAD)
	{
		// 데바리 효과 : 공격력 + 300, 크리확률 + 50%
		Set_DBR(true);
		m_tInfo.fAtk += 300;
		Set_CriRatio(50);

		// 데바리 아이콘
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CUI_SkillIcon_2>::
			Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX - 120.f, m_tInfo.fY - 200.f, 28.f, 28.f, 0.f, 0.f, 0.f, 0.f, 1.5f, 28.f, 28.f, float(Get_TileCollision().bottom),
				m_tInfo.fAtk, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, L"DBR", { 255, 255, 255 }));

		CSoundMgr::Get_Instance()->PlaySoundW(L"revolver.wav", SOUND_EFFECT, g_fVolume);
		m_ePlayerState = PS_DBR;
		Take_Mana(MANA_DBR);
		SkillCool_Making(582.f, 532.f, (float)COOL_DBR, L"DBR");
		m_DBRCool = 0;
		m_dwTime = 0;
	}

	// E 건가드
	if (CKeyMgr::Get_Instance()->Key_Pressing('E') && MANA_GUNGUARD < m_tInfo.fMp && COOL_GUNGUARD < m_GunGuardCool
		&& (m_ePlayerState != PS_NORMAL_ATTACKED && m_ePlayerState != PS_THRUST_ATTACKED && m_ePlayerState != PS_LEVITATE_ATTACKED)
		&& (m_ePlayerState != PS_LSLIDE && m_ePlayerState != PS_RSLIDE)
		&& (m_ePlayerState != PS_JUMP && m_ePlayerState != PS_JUMPATTACK)
		&& (m_ePlayerState != PS_ZACKS && m_ePlayerState != PS_WINDMILL && m_ePlayerState != PS_MAHA)
		&& (m_ePlayerState != PS_GUNGUARD && m_ePlayerState != PS_DBR && m_ePlayerState != PS_HEADSHOT && m_ePlayerState != PS_MOVINGSHOT && m_ePlayerState != PS_SPREE)
		&& (m_ePlayerState != PS_AWAKEN && m_ePlayerState != PS_LAWAKENING && m_ePlayerState != PS_RAWAKENING)
		&& m_ePlayerState != PS_SATELITE && m_ePlayerState != PS_DEAD)
	{
		// 건가드 효과 : 1초간 무적
		Set_GunGuard(true);
		Set_IsImmune(true);

		// CSoundMgr::Get_Instance()->PlaySoundW(L"revolver.wav", SOUND_EFFECT, g_fVolume);
		m_ePlayerState = PS_GUNGUARD;
		Take_Mana(MANA_GUNGUARD);
		SkillCool_Making(612.f, 532.f, (float)COOL_GUNGUARD, L"GunGuard");
		m_GunGuardCool = 0;
		m_dwTime = 0;
	}

	// Z 잭스파이크
	if (CKeyMgr::Get_Instance()->Key_Pressing('Z') && MANA_ZACKS < m_tInfo.fMp && COOL_ZACKS < m_ZacksCool
		&& (m_ePlayerState != PS_NORMAL_ATTACKED && m_ePlayerState != PS_THRUST_ATTACKED && m_ePlayerState != PS_LEVITATE_ATTACKED)
		&& (m_ePlayerState != PS_LSLIDE && m_ePlayerState != PS_RSLIDE)
		&& (m_ePlayerState != PS_JUMP && m_ePlayerState != PS_JUMPATTACK)
		&& (m_ePlayerState != PS_ZACKS && m_ePlayerState != PS_MAHA)
		&& (m_ePlayerState != PS_DBR && m_ePlayerState != PS_GUNGUARD && m_ePlayerState != PS_HEADSHOT && m_ePlayerState != PS_MOVINGSHOT && m_ePlayerState != PS_SPREE)
		&& (m_ePlayerState != PS_AWAKEN && m_ePlayerState != PS_LAWAKENING && m_ePlayerState != PS_RAWAKENING)
		&& m_ePlayerState != PS_SATELITE && m_ePlayerState != PS_DEAD)
	{
		// 잔상 - 평타나 스타일리쉬 스킬들 시전도중 잭스파이크 시전시
		if (((m_ePlayerState == PS_ATTACK1 || m_ePlayerState == PS_ATTACK2 || m_ePlayerState == PS_ATTACK3 || m_ePlayerState == PS_ATTACK4 || m_ePlayerState == PS_ATTACK5)
			|| (m_ePlayerState == PS_DATTACK1 || m_ePlayerState == PS_DATTACK2 || m_ePlayerState == PS_DATTACK3 || m_ePlayerState == PS_DATTACK4 || m_ePlayerState == PS_DATTACK5)
			&& 0.245 > m_dwTime)
			|| (m_ePlayerState == PS_WINDMILL || m_ePlayerState == PS_MAHA || m_ePlayerState == PS_HEADSHOT))
		{
			CObjMgr::Get_Instance()->Delete_ID(OBJ_EFFECT);

			// 잔상 남기기
			if (L"Player_LEFT" == Get_FrameKey())
			{
				Making_Shadow(L"Player_LEFT", 0.4f);
			}
			else
			{
				Making_Shadow(L"Player_RIGHT", 0.4f);
			}
		}

		if (L"Player_LEFT" == Get_FrameKey())
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
				Create_Obj(ATT_LEVITATE, false, m_tInfo.fX - 45.f, m_tInfo.fY + 27.f, 92.f, 125.f, 0.f, 0.f, 0.f, 0.f, 0.2f, 92.f, 125.f, float(Get_TileCollision().bottom),
					m_tInfo.fAtk, 250.f, 1.f, 1.f, 10.f, 90.f, 180.f, 1.5f, L"LZacks", {0, 0, 0}));
			CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER_ATTACK).back()->Set_Frame(tagFrame{ 0, 2, 0, 0.06667, 0. });
		}
		else
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
				Create_Obj(ATT_LEVITATE, false, m_tInfo.fX + 45.f, m_tInfo.fY + 27.f, 92.f, 125.f, 0.f , 0.f, 0.f, 0.f, 0.2f, 92.f, 125.f, float(Get_TileCollision().bottom),
					m_tInfo.fAtk, 250.f, 1.f, 1.f, 10.f, 90.f, 0.f, 1.5f, L"RZacks", { 0, 0, 0 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER_ATTACK).back()->Set_Frame(tagFrame{ 0, 2, 0, 0.06667, 0. });
		}
		switch (rand() % 2)
		{
		case 0:
			CSoundMgr::Get_Instance()->PlaySoundW(L"gn_jspike_01.wav", SOUND_EFFECT, g_fVolume);
			break;

		case 1:
			CSoundMgr::Get_Instance()->PlaySoundW(L"gn_jspike_02.wav", SOUND_EFFECT, g_fVolume);
			break;
		}
		m_ePlayerState = PS_ZACKS;
		Take_Mana(MANA_ZACKS);
		SkillCool_Making(552.f, 532.f, (float)COOL_ZACKS, L"Zack2");
		m_ZacksCool = 0;
		m_dwTime = 0;
	}

	// S 윈드밀
	if (CKeyMgr::Get_Instance()->Key_Pressing('S') && MANA_WINDMILL < m_tInfo.fMp && COOL_WINDMILL < m_WindmillCool
		&& (m_ePlayerState != PS_NORMAL_ATTACKED && m_ePlayerState != PS_THRUST_ATTACKED && m_ePlayerState != PS_LEVITATE_ATTACKED)
		&& (m_ePlayerState != PS_LSLIDE && m_ePlayerState != PS_RSLIDE)
		&& (m_ePlayerState != PS_JUMP && m_ePlayerState != PS_JUMPATTACK)
		&& (m_ePlayerState != PS_DBR && m_ePlayerState != PS_GUNGUARD && m_ePlayerState != PS_WINDMILL)
		&& (m_ePlayerState != PS_MOVINGSHOT && m_ePlayerState != PS_SPREE)
		&& (m_ePlayerState != PS_AWAKEN && m_ePlayerState != PS_LAWAKENING && m_ePlayerState != PS_RAWAKENING)
		&& m_ePlayerState != PS_SATELITE && m_ePlayerState != PS_DEAD)
	{
		// 트리플 클러치 - 평타 사용중에 윈드밀 사용시
		// 잔상 - 평타나 스타일리쉬 스킬들 시전도중 난사 시전시
		if (((m_ePlayerState == PS_ATTACK1 || m_ePlayerState == PS_ATTACK2 || m_ePlayerState == PS_ATTACK3 || m_ePlayerState == PS_ATTACK4 || m_ePlayerState == PS_ATTACK5)
			|| (m_ePlayerState == PS_DATTACK1 || m_ePlayerState == PS_DATTACK2 || m_ePlayerState == PS_DATTACK3 || m_ePlayerState == PS_DATTACK4 || m_ePlayerState == PS_DATTACK5)
			&& 0.245 > m_dwTime)
			|| (m_ePlayerState == PS_ZACKS || m_ePlayerState == PS_MAHA || m_ePlayerState == PS_HEADSHOT))
		{
			CObjMgr::Get_Instance()->Delete_ID(OBJ_EFFECT);

			// 잔상 남기기
			if (L"Player_LEFT" == Get_FrameKey())
			{
				Making_Shadow(L"Player_LEFT", 0.4f);
			}
			else
			{
				Making_Shadow(L"Player_RIGHT", 0.4f);
			}
		}

		if (L"Player_LEFT" == Get_FrameKey())
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
				Create_Obj(ATT_THRUST, false, m_tInfo.fX, m_tInfo.fY + 20.f, 213.f, 117.f, 0.f, 0.f, 0.f, 0.f, 1.f, 200.f, 100.f, float(Get_TileCollision().bottom),
					m_tInfo.fAtk, 350.f, 5.f, 1.5f, 5.f, 0.f, 180.f, 0.4f, L"WindmillAtk", { 0, 0, 0 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER_ATTACK).back()->Set_Frame(tagFrame{ 0, 4, 0, 0.16666, 0. });

			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
				Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX, m_tInfo.fY + 60.f, 196.f, 59.f, 0.f, 0.f, 0.f, 0.f, 1.f, 196.f, 59.f, float(Get_TileCollision().bottom),
					m_tInfo.fAtk, 50.f, 0.f, 0.f, 5.f, 90.f, 0.f, 0.8f, L"WindmillDust", { 0, 0, 0 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 3, 0, 0.16666, 0. });
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_RenderID(BACKGROUNDEFFECT);

			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
				Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX, m_tInfo.fY + 20.f, 213.f, 117.f, 0.f, 0.f, 0.f, 0.f, 1.f, 213.f, 117.f, float(Get_TileCollision().bottom),
					m_tInfo.fAtk, 50.f, 0.f, 0.f, 5.f, 0.f, 0.f, 0.8f, L"Windmill", { 0, 0, 0 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 4, 0, 0.16666, 0. });
		}
		else
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
				Create_Obj(ATT_THRUST, false, m_tInfo.fX, m_tInfo.fY + 20.f, 213.f, 117.f, 0.f, 0.f, 0.f, 0.f, 1.f, 200.f, 100.f, float(Get_TileCollision().bottom),
					m_tInfo.fAtk, 350.f, 5.f, 1.5f, 5.f, 0.f, 0.f, 0.4f, L"WindmilAtk", { 0, 0, 0 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER_ATTACK).back()->Set_Frame(tagFrame{ 0, 4, 0, 0.16666, 0. });

			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
				Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX, m_tInfo.fY + 60.f, 196.f, 59.f, 0.f, 0.f, 0.f, 0.f, 1.f, 196.f, 59.f, float(Get_TileCollision().bottom),
					m_tInfo.fAtk, 50.f, 0.f, 0.f, 5.f, 90.f, 0.f, 0.8f, L"WindmillDust", { 0, 0, 0 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 3, 0, 0.16666, 0. });
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_RenderID(BACKGROUNDEFFECT);

			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
				Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX, m_tInfo.fY + 20.f, 213.f, 117.f, 0.f, 0.f, 0.f, 0.f, 1.f, 213.f, 117.f, float(Get_TileCollision().bottom),
					m_tInfo.fAtk, 50.f, 0.f, 0.f, 5.f, 0.f, 0.f, 0.8f, L"Windmill", { 0, 0, 0 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 4, 0, 0.16666, 0. });
		}

		CSoundMgr::Get_Instance()->PlaySoundW(L"gn_windmill_02.wav", SOUND_EFFECT, g_fVolume);
		CSoundMgr::Get_Instance()->PlaySoundW(L"windmill_hit.ogg", SOUND_EFFECT2, g_fVolume);
		m_ePlayerState = PS_WINDMILL;
		Take_Mana(MANA_WINDMILL);
		SkillCool_Making(582.f, 572.f, (float)COOL_WINDMILL, L"WindMill_Off");
		m_WindmillCool = 0;
		m_dwTime = 0;
	}

	// D 마하킥
	if (CKeyMgr::Get_Instance()->Key_Pressing('D') && MANA_MAHA < m_tInfo.fMp && COOL_MAHA < m_MahaCool
		&& (m_ePlayerState != PS_NORMAL_ATTACKED && m_ePlayerState != PS_THRUST_ATTACKED && m_ePlayerState != PS_LEVITATE_ATTACKED)
		&& (m_ePlayerState != PS_LSLIDE && m_ePlayerState != PS_RSLIDE)
		&& (m_ePlayerState != PS_JUMP && m_ePlayerState != PS_JUMPATTACK)
		&& (m_ePlayerState != PS_DBR && m_ePlayerState != PS_GUNGUARD && m_ePlayerState != PS_MAHA)
		&& (m_ePlayerState != PS_MOVINGSHOT && m_ePlayerState != PS_SPREE)
		&& (m_ePlayerState != PS_AWAKEN && m_ePlayerState != PS_LAWAKENING && m_ePlayerState != PS_RAWAKENING)
		&& m_ePlayerState != PS_SATELITE && m_ePlayerState != PS_DEAD)
	{
		// 트리플 클러치 - 윈드밀이나 평타 사용중에 마하킥 사용시
		// 잔상 - 평타나 스타일리쉬 스킬들 시전도중 난사 시전시
		if (((m_ePlayerState == PS_ATTACK1 || m_ePlayerState == PS_ATTACK2 || m_ePlayerState == PS_ATTACK3 || m_ePlayerState == PS_ATTACK4 || m_ePlayerState == PS_ATTACK5)
			|| (m_ePlayerState == PS_DATTACK1 || m_ePlayerState == PS_DATTACK2 || m_ePlayerState == PS_DATTACK3 || m_ePlayerState == PS_DATTACK4 || m_ePlayerState == PS_DATTACK5)
			&& 0.245 > m_dwTime)
			|| (m_ePlayerState == PS_ZACKS || m_ePlayerState == PS_WINDMILL || m_ePlayerState == PS_HEADSHOT))
		{
			// 맨 뒤의 두개의 이펙트를 지운다(윈드밀 이펙트)
			CObjMgr::Get_Instance()->Delete_ID(OBJ_EFFECT);
			
			// 잔상 남기기
			if (L"Player_LEFT" == Get_FrameKey())
			{
				Making_Shadow(L"Player_LEFT", 0.4f);
			}
			else
			{
				Making_Shadow(L"Player_RIGHT", 0.4f);
			}
		}

		if (L"Player_LEFT" == Get_FrameKey())
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
				Create_Obj(ATT_THRUST, false, m_tInfo.fX - 60.f, m_tInfo.fY + 45.f, 150.f, 100.f, 0.f, 0.f, 0.f, 0.f, 0.3f, 150.f, 80.f, float(Get_TileCollision().bottom),
					m_tInfo.fAtk, 800.f, 40.f, 10.f, 2.f, 90.f, 180.f, 0.35f, L"LMahaAttack", { 0, 0, 0 }));

			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
				Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX - 60.f, m_tInfo.fY + 60.f, 166.f, 72.f, 0.f, 0.f, 0.f, 0.f, 0.3f, 166.f, 72.f, float(Get_TileCollision().bottom),
					m_tInfo.fAtk, 50.f, 0.f, 0.f, 5.f, 90.f, 0.f, 0.8f, L"LMaha", { 0, 0, 0 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 3, 0, 0.1, 0. });
		}
		else
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
				Create_Obj(ATT_THRUST, false, m_tInfo.fX + 60.f, m_tInfo.fY + 45.f, 150.f, 100.f, 0.f, 0.f, 0.f, 0.f, 0.3f, 150.f, 80.f, float(Get_TileCollision().bottom),
					m_tInfo.fAtk, 800.f, 40.f, 10.f, 2.f, 90.f, 0.f, 0.35f, L"RMahaAttack", { 0, 0, 0 }));

			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
				Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX + 60.f, m_tInfo.fY + 60.f, 166.f, 72.f, 0.f, 0.f, 0.f, 0.f, 0.3f, 166.f, 72.f, float(Get_TileCollision().bottom),
					m_tInfo.fAtk, 50.f, 0.f, 0.f, 5.f, 90.f, 0.f, 0.8f, L"RMaha", { 0, 0, 0 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 3, 0, 0.1, 0. });
		}

		CSoundMgr::Get_Instance()->PlaySoundW(L"mahakick.wav", SOUND_EFFECT, g_fVolume);
		m_ePlayerState = PS_MAHA;
		Take_Mana(MANA_MAHA);
		SkillCool_Making(612.f, 572.f, (float)COOL_MAHA, L"MahaKick_Off");
		m_MahaCool = 0;
		m_dwTime = 0;
	}

	// A 헤드샷
	if (CKeyMgr::Get_Instance()->Key_Pressing('A') && MANA_HEADSHOT < m_tInfo.fMp && COOL_HEADSHOT < m_HeadShotCool
		&& (m_ePlayerState != PS_NORMAL_ATTACKED && m_ePlayerState != PS_THRUST_ATTACKED && m_ePlayerState != PS_LEVITATE_ATTACKED)
		&& (m_ePlayerState != PS_LSLIDE && m_ePlayerState != PS_RSLIDE)
		&& (m_ePlayerState != PS_JUMP && m_ePlayerState != PS_JUMPATTACK)
		&& (m_ePlayerState != PS_DBR && m_ePlayerState != PS_GUNGUARD && m_ePlayerState != PS_HEADSHOT && m_ePlayerState != PS_MOVINGSHOT && m_ePlayerState != PS_SPREE)
		&& (m_ePlayerState != PS_AWAKEN && m_ePlayerState != PS_LAWAKENING && m_ePlayerState != PS_RAWAKENING)
		&& m_ePlayerState != PS_SATELITE && m_ePlayerState != PS_DEAD)
	{
		// 트리플 클러치 - 마하킥이나 평타 시전중에 헤드샷 시전시
		// 잔상 - 평타나 스타일리쉬 스킬들 시전도중 난사 시전시
		if (((m_ePlayerState == PS_ATTACK1 || m_ePlayerState == PS_ATTACK2 || m_ePlayerState == PS_ATTACK3 || m_ePlayerState == PS_ATTACK4 || m_ePlayerState == PS_ATTACK5)
			|| (m_ePlayerState == PS_DATTACK1 || m_ePlayerState == PS_DATTACK2 || m_ePlayerState == PS_DATTACK3 || m_ePlayerState == PS_DATTACK4 || m_ePlayerState == PS_DATTACK5)
			&& 0.245 > m_dwTime)
			|| (m_ePlayerState == PS_ZACKS || m_ePlayerState == PS_WINDMILL || m_ePlayerState == PS_MAHA))
		{
			// 맨 뒤의 두개의 이펙트를 지운다(마하킥 이펙트)
			CObjMgr::Get_Instance()->Delete_ID(OBJ_EFFECT);

			// 잔상 남기기
			if (L"Player_LEFT" == Get_FrameKey())
			{
				Making_Shadow(L"Player_LEFT", 0.4f);
			}
			else
			{
				Making_Shadow(L"Player_RIGHT", 0.4f);
			}
		}

		m_ePlayerState = PS_HEADSHOT;
		Take_Mana(MANA_HEADSHOT);
		SkillCool_Making(552.f, 572.f, (float)COOL_HEADSHOT, L"HeadShoot_Off");
		m_HeadShotCool = 0;
		m_dwTime = 0;
	}

	// R 이동사격
	if (CKeyMgr::Get_Instance()->Key_Pressing('R') && MANA_MOVINGSHOT < m_tInfo.fMp && COOL_MOVINGSHOT < m_MovingShotCool
		&& (m_ePlayerState != PS_NORMAL_ATTACKED && m_ePlayerState != PS_THRUST_ATTACKED && m_ePlayerState != PS_LEVITATE_ATTACKED)
		&& (m_ePlayerState != PS_LSLIDE && m_ePlayerState != PS_RSLIDE)
		&& (m_ePlayerState != PS_JUMP && m_ePlayerState != PS_JUMPATTACK)
		&& (m_ePlayerState != PS_DBR && m_ePlayerState != PS_GUNGUARD && m_ePlayerState != PS_MOVINGSHOT && m_ePlayerState != PS_SPREE)
		&& (m_ePlayerState != PS_AWAKEN && m_ePlayerState != PS_LAWAKENING && m_ePlayerState != PS_RAWAKENING)
		&& m_ePlayerState != PS_SATELITE && m_ePlayerState != PS_DEAD)
	{
		// 잔상 - 평타나 스타일리쉬 시전도중 이동사격 시전시
		// 잔상 - 평타나 스타일리쉬 스킬들 시전도중 난사 시전시
		if (((m_ePlayerState == PS_ATTACK1 || m_ePlayerState == PS_ATTACK2 || m_ePlayerState == PS_ATTACK3 || m_ePlayerState == PS_ATTACK4 || m_ePlayerState == PS_ATTACK5)
			|| (m_ePlayerState == PS_DATTACK1 || m_ePlayerState == PS_DATTACK2 || m_ePlayerState == PS_DATTACK3 || m_ePlayerState == PS_DATTACK4 || m_ePlayerState == PS_DATTACK5)
			&& 0.245 > m_dwTime)
			|| (m_ePlayerState == PS_ZACKS || m_ePlayerState == PS_WINDMILL || m_ePlayerState == PS_MAHA || m_ePlayerState == PS_HEADSHOT))
		{
			// 맨 뒤의 두개의 이펙트를 지운다(윈드밀 이펙트)
			CObjMgr::Get_Instance()->Delete_ID(OBJ_EFFECT);

			// 잔상 남기기
			if (L"Player_LEFT" == Get_FrameKey())
			{
				Making_Shadow(L"Player_LEFT", 0.4f);
			}
			else
			{
				Making_Shadow(L"Player_RIGHT", 0.4f);
			}
		}
		m_ePlayerState = PS_MOVINGSHOT;
		Take_Mana(MANA_MOVINGSHOT);
		SkillCool_Making(642.f, 572.f, (float)COOL_MOVINGSHOT, L"Moving_Shoot_Off");
		m_MovingShotCool = 0;
		m_dwTime = 0;
	}

	// F 난사
	if (CKeyMgr::Get_Instance()->Key_Pressing('F') && MANA_SPREE < m_tInfo.fMp && COOL_SPREE < m_SpreeCool
		&& (m_ePlayerState != PS_NORMAL_ATTACKED && m_ePlayerState != PS_THRUST_ATTACKED && m_ePlayerState != PS_LEVITATE_ATTACKED)
		&& (m_ePlayerState != PS_LSLIDE && m_ePlayerState != PS_RSLIDE)
		&& (m_ePlayerState != PS_JUMP && m_ePlayerState != PS_JUMPATTACK)
		&& (m_ePlayerState != PS_DBR && m_ePlayerState != PS_GUNGUARD && m_ePlayerState != PS_MOVINGSHOT && m_ePlayerState != PS_SPREE)
		&& (m_ePlayerState != PS_AWAKEN && m_ePlayerState != PS_LAWAKENING && m_ePlayerState != PS_RAWAKENING)
		&& m_ePlayerState != PS_SATELITE && m_ePlayerState != PS_DEAD)
	{
		// 잔상 - 평타나 스타일리쉬 스킬들 시전도중 난사 시전시
		if (((m_ePlayerState == PS_ATTACK1 || m_ePlayerState == PS_ATTACK2 || m_ePlayerState == PS_ATTACK3 || m_ePlayerState == PS_ATTACK4 || m_ePlayerState == PS_ATTACK5)
			|| (m_ePlayerState == PS_DATTACK1 || m_ePlayerState == PS_DATTACK2 || m_ePlayerState == PS_DATTACK3 || m_ePlayerState == PS_DATTACK4 || m_ePlayerState == PS_DATTACK5)
			&& 0.245 > m_dwTime)
			|| (m_ePlayerState == PS_ZACKS || m_ePlayerState == PS_WINDMILL || m_ePlayerState == PS_MAHA || m_ePlayerState == PS_HEADSHOT))
		{
			// 맨 뒤의 두개의 이펙트를 지운다
			CObjMgr::Get_Instance()->Delete_ID(OBJ_EFFECT);

			// 잔상 남기기
			if (L"Player_LEFT" == Get_FrameKey())
			{
				Making_Shadow(L"Player_LEFT", 0.4f);
			}
			else
			{
				Making_Shadow(L"Player_RIGHT", 0.4f);
			}
		}

		CSoundMgr::Get_Instance()->PlaySoundW(L"RdShotStart.wav", SOUND_EFFECT, g_fVolume);
		m_ePlayerState = PS_SPREE;
		Take_Mana(MANA_SPREE);
		SkillCool_Making(672.f, 572.f, (float)COOL_SPREE, L"Random_Shoot_Off");
		m_SpreeCool = 0;
		m_dwTime = 0;
	}

	// G 세틀라이트빔
	if (CKeyMgr::Get_Instance()->Key_Pressing('G') && MANA_SATELITE < m_tInfo.fMp && COOL_SATELITE < m_SateliteCool
		&& (m_ePlayerState != PS_NORMAL_ATTACKED && m_ePlayerState != PS_THRUST_ATTACKED && m_ePlayerState != PS_LEVITATE_ATTACKED)
		&& (m_ePlayerState != PS_LSLIDE && m_ePlayerState != PS_RSLIDE)
		&& (m_ePlayerState != PS_JUMP && m_ePlayerState != PS_JUMPATTACK)
		&& (m_ePlayerState != PS_DBR && m_ePlayerState != PS_GUNGUARD && m_ePlayerState != PS_MOVINGSHOT && m_ePlayerState != PS_SPREE)
		&& (m_ePlayerState != PS_AWAKEN && m_ePlayerState != PS_LAWAKENING && m_ePlayerState != PS_RAWAKENING)
		&& m_ePlayerState != PS_SATELITE && m_ePlayerState != PS_DEAD)
	{
		// 세틀라이트빔 시전 사운드
		CSoundMgr::Get_Instance()->PlaySoundW(L"satellitebeam_call.ogg", SOUND_EFFECT, g_fVolume);
		m_ePlayerState = PS_SATELITE;
		Take_Mana(MANA_SATELITE);
		SkillCool_Making(642.f, 532.f, (float)COOL_SATELITE, L"Icon_Satelaser");
		m_SateliteCool = 0;
		m_dwTime = 0;
	}

	// Y 각성기
	if (CKeyMgr::Get_Instance()->Key_Pressing('Y') && MANA_AWAKENING < m_tInfo.fMp && COOL_AWAKENING < m_AwakeningCool
		&& (m_ePlayerState != PS_NORMAL_ATTACKED && m_ePlayerState != PS_THRUST_ATTACKED && m_ePlayerState != PS_LEVITATE_ATTACKED)
		&& (m_ePlayerState != PS_LSLIDE && m_ePlayerState != PS_RSLIDE)
		&& (m_ePlayerState != PS_JUMP && m_ePlayerState != PS_JUMPATTACK)
		&& (m_ePlayerState != PS_DBR && m_ePlayerState != PS_GUNGUARD && m_ePlayerState != PS_MOVINGSHOT && m_ePlayerState != PS_SPREE)
		&& (m_ePlayerState != PS_AWAKEN && m_ePlayerState != PS_LAWAKENING && m_ePlayerState != PS_RAWAKENING)
		&& m_ePlayerState != PS_SATELITE && m_ePlayerState != PS_DEAD)
	{
		// 잔상 - 평타나 스타일리쉬 스킬들 시전도중 각성기 시전시
		if (((m_ePlayerState == PS_ATTACK1 || m_ePlayerState == PS_ATTACK2 || m_ePlayerState == PS_ATTACK3 || m_ePlayerState == PS_ATTACK4 || m_ePlayerState == PS_ATTACK5)
			|| (m_ePlayerState == PS_DATTACK1 || m_ePlayerState == PS_DATTACK2 || m_ePlayerState == PS_DATTACK3 || m_ePlayerState == PS_DATTACK4 || m_ePlayerState == PS_DATTACK5)
			&& 0.245 > m_dwTime)
			|| (m_ePlayerState == PS_ZACKS || m_ePlayerState == PS_WINDMILL || m_ePlayerState == PS_MAHA || m_ePlayerState == PS_HEADSHOT))
		{
			CObjMgr::Get_Instance()->Delete_ID(OBJ_EFFECT);

			// 잔상 남기기
			if (L"Player_LEFT" == Get_FrameKey())
				Making_Shadow(L"Player_LEFT", 0.5f);
			else
				Making_Shadow(L"Player_RIGHT", 0.5f);
		}
		// CSoundMgr::Get_Instance()->PlaySoundW(L"RdShotStart.wav", SOUND_EFFECT, g_fVolume);
		Set_IsImmune(true);		// 각성기 상태일때 무적 활성화
		m_ePlayerState = PS_AWAKEN;
		Take_Mana(MANA_AWAKENING);
		SkillCool_Making(702.f, 572.f, (float)COOL_AWAKENING, L"Seven'sFlow_Off");
		m_AwakeningCool = 0;
		m_dwTime = 0;
	}

	// 인벤토리 I
	if (CKeyMgr::Get_Instance()->Key_Pressing('I'))
	{
		if (!(dynamic_cast<CUI_Inven*>((CObjMgr::Get_Instance()->GetObjList(OBJ_INVEN)).front())->Get_Render()) && 0.2 < m_dwTime)
		{
			dynamic_cast<CUI_Inven*>((CObjMgr::Get_Instance()->GetObjList(OBJ_INVEN)).front())->Set_Render(true);
			CSoundMgr::Get_Instance()->PlaySoundW(L"InvenOn.wav", SOUND_EFFECT, g_fVolume);
			m_dwTime = 0;
		}
		else if (dynamic_cast<CUI_Inven*>((CObjMgr::Get_Instance()->GetObjList(OBJ_INVEN)).front())->Get_Render() && 0.2 < m_dwTime)
		{
			dynamic_cast<CUI_Inven*>((CObjMgr::Get_Instance()->GetObjList(OBJ_INVEN)).front())->Set_Render(false);
			CSoundMgr::Get_Instance()->PlaySoundW(L"InvenOn.wav", SOUND_EFFECT, g_fVolume);
			m_dwTime = 0;
		}
	}
	
	// 상점 U
	if (CKeyMgr::Get_Instance()->Key_Pressing('U'))
	{
		if (!(dynamic_cast<CUI_Store*>((CObjMgr::Get_Instance()->GetObjList(OBJ_STORE)).front())->Get_Render()) && 0.2 < m_dwTime)
		{
			dynamic_cast<CUI_Store*>((CObjMgr::Get_Instance()->GetObjList(OBJ_STORE)).front())->Set_Render(true);
			CSoundMgr::Get_Instance()->PlaySoundW(L"InvenOn.wav", SOUND_EFFECT, g_fVolume);
			m_dwTime = 0;
		}
		else if (dynamic_cast<CUI_Store*>((CObjMgr::Get_Instance()->GetObjList(OBJ_STORE)).front())->Get_Render() && 0.2 < m_dwTime)
		{
			dynamic_cast<CUI_Store*>((CObjMgr::Get_Instance()->GetObjList(OBJ_STORE)).front())->Set_Render(false);
			CSoundMgr::Get_Instance()->PlaySoundW(L"InvenOn.wav", SOUND_EFFECT, g_fVolume);
			m_dwTime = 0;
		}
	}

	// 내정보 M
	if (CKeyMgr::Get_Instance()->Key_Pressing('M'))
	{
		if (!(dynamic_cast<CUI_Info*>((CObjMgr::Get_Instance()->GetObjList(OBJ_MYINFO)).front())->Get_Render()) && 0.2 < m_dwTime)
		{
			dynamic_cast<CUI_Info*>((CObjMgr::Get_Instance()->GetObjList(OBJ_MYINFO)).front())->Set_Render(true);
			CSoundMgr::Get_Instance()->PlaySoundW(L"InvenOn.wav", SOUND_EFFECT, g_fVolume);
			m_dwTime = 0;
		}
		else if (dynamic_cast<CUI_Info*>((CObjMgr::Get_Instance()->GetObjList(OBJ_MYINFO)).front())->Get_Render() && 0.2 < m_dwTime)
		{
			dynamic_cast<CUI_Info*>((CObjMgr::Get_Instance()->GetObjList(OBJ_MYINFO)).front())->Set_Render(false);
			CSoundMgr::Get_Instance()->PlaySoundW(L"InvenOn.wav", SOUND_EFFECT, g_fVolume);
			m_dwTime = 0;
		}
	}

	// Hp물약 1
	if (CKeyMgr::Get_Instance()->Key_Pressing('1') && 0.5 < m_HpCoolTime)
	{
		CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Set_Hp(CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Hp() + 20000);
		if (m_tInfo.fHp > m_tInfo.fMaxHp)
			m_tInfo.fHp = m_tInfo.fMaxHp;

		CSoundMgr::Get_Instance()->PlaySoundW(L"Hp_recover.ogg", SOUND_EFFECT, g_fVolume);
		m_HpCoolTime = 0;
	}

	// Mp물약 2
	if (CKeyMgr::Get_Instance()->Key_Pressing('2') && 0.5 < m_MpCoolTime)
	{
		CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Set_Mp(CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Mp() + 3000);
		if (m_tInfo.fMp > m_tInfo.fMaxMp)
			m_tInfo.fMp = m_tInfo.fMaxMp;

		CSoundMgr::Get_Instance()->PlaySoundW(L"Hp_recover.ogg", SOUND_EFFECT, g_fVolume);
		m_MpCoolTime = 0;
	}
}

void CPlayer::Moving(void)
{
	DWORD currentTime = GetTickCount64();
	switch (m_ePlayerState)
	{
	// 아이돌
	case PS_IDLE:
		Set_StopMotion(false);
		m_iNormalFinalCount = 0;
		m_iDNormalCount = 0;
		m_iJumpAttackCount = 0;
		m_iSateliteCount = 0;
		break;

	// 그냥 위로 걷기
	case PS_JUSTWALKUP:
		m_tInfo.fY -= m_fSpeed * 0.7f;
		break;

	// 그냥 아래로 걷기
	case PS_JUSTWALKDOWN:
		m_tInfo.fY += m_fSpeed * 0.7f;
		break;

	// 왼쪽으로 걷기
	case PS_LWALK:
		if (currentTime - m_lWalkTime > 20)
			m_ePlayerState = PS_IDLE;
		m_tInfo.fX -= m_fSpeed;
		break;

	// 오른쪽으로 걷기
	case PS_RWALK:
		if (currentTime - m_lWalkTime > 20)
			m_ePlayerState = PS_IDLE;
		m_tInfo.fX += m_fSpeed;
		break;

	// 왼쪽 달리기
	case PS_LRUN:
		if (m_dwTime > 0.4)
		{
			CSoundMgr::Get_Instance()->PlaySoundW(L"run_floor_01.ogg", SOUND_EFFECT, g_fVolume - 0.05);
			m_dwTime = 0;
		}
		m_tInfo.fX -= 1.5f * m_fSpeed;
		break;

	// 오른쪽 달리기
	case PS_RRUN:
		if (m_dwTime > 0.4)
		{
			CSoundMgr::Get_Instance()->PlaySoundW(L"run_floor_01.ogg", SOUND_EFFECT, g_fVolume - 0.05);
			m_dwTime = 0;
		}
		m_tInfo.fX += 1.5f * m_fSpeed;
		break;

	// 왼쪽 슬라이딩
	case PS_LSLIDE:
		if (currentTime - m_lSlideTime > 700)
		{
			m_ePlayerState = PS_IDLE;
			m_fSlideSpeed = 3.5f;
			break;
		}
		if (m_fSlideSpeed * m_fSpeed > 0)
			m_tInfo.fX -= m_fSlideSpeed * m_fSpeed;
		m_fSlideSpeed -= 0.08f;
		break;

	// 오른쪽 슬라이딩
	case PS_RSLIDE:
		if (currentTime - m_lSlideTime > 700)
		{
			m_ePlayerState = PS_IDLE;
			m_fSlideSpeed = 3.5f;
			break;
		}
		if(m_fSlideSpeed * m_fSpeed > 0)
			m_tInfo.fX += m_fSlideSpeed * m_fSpeed;
		m_fSlideSpeed -= 0.08f;
		break;

	// 점프
	case PS_JUMP:
	{
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			Set_StopMotion(true);

		if ((m_tRect.bottom < m_tTileCollision.bottom + 30.f && m_tRect.bottom > m_tTileCollision.bottom - 30.f)
			&& (currentTime - m_lJumpEndTime > 700))
		{
			m_tInfo.fY = m_tTileCollision.bottom - (0.5f * m_tInfo.fCY);
			m_fJumpTime = 0.f;
			m_lJumpAttackTime = 0;
			m_ePlayerState = PS_IDLE;
			break;
		}
		
		float m_fJumptDistance = -1.f * (m_fJumpSpeed * m_fJumpTime);
		float m_fFallDistance = (5.12f * powf(m_fJumpTime, 2.f));

		if (9.8f * m_fJumpTime < 2.15f * m_fJumpSpeed)
		{
			m_fJumpTime += 0.095f;
			m_fFallSpeed = 9.8f * m_fJumpTime;
		}

		// 점프로 올라가려는 힘과 중력으로 인해 내려가려는 힘이 동일해지는 시기(최고점)
		// if (-m_fJumptDistance < m_fFallDistance)
			// int a = 0;

		m_tInfo.fY += m_fJumptDistance + m_fFallDistance;
		break;
	}
	break;

	// 점프 공격
	case PS_JUMPATTACK:
	{
		if (((m_tRect.bottom < m_tTileCollision.bottom + 30.f && m_tRect.bottom > m_tTileCollision.bottom - 30.f)
			&& (currentTime - m_lJumpEndTime > 700)) || (currentTime - m_lJumpAttackTime > 420))
		{
			m_ePlayerState = PS_JUMP;
			break;
		}

		if (9.8f * m_fJumpTime < 2.15f * m_fJumpSpeed)
			m_fJumpTime += 0.095f;
		
		break;
	}
	break;

	// 평타1
	case PS_ATTACK1:

		if (m_dwTime > 0.245)
		{
			m_dwTime = 0;
			m_ePlayerState = PS_IDLE;
		}
		break;

	// 평타2
	case PS_ATTACK2:
		if (m_dwTime > 0.245)
		{
			m_dwTime = 0;
			m_ePlayerState = PS_IDLE;
		}
		break;

	// 평타3
	case PS_ATTACK3:
		if (m_dwTime > 0.245)
		{
			m_dwTime = 0;
			m_ePlayerState = PS_IDLE;
		}
		break;

	// 평타4
	case PS_ATTACK4:
		if (m_dwTime > 0.350)
		{
			m_dwTime = 0;
			m_ePlayerState = PS_IDLE;
		}
		break;

	// 평타5
	case PS_ATTACK5:
		if (m_dwTime > 0.250 && m_iNormalFinalCount < 1)
		{
			++m_iNormalFinalCount;
			if (m_pFrameKey == L"Player_LEFT")
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
					Create_Obj(ATT_NORMAL, true, m_tInfo.fX - 65.f, m_tInfo.fY - 24.f, 30.f, 20.f, 11.5f, 180.f, 0.f, 0.f, 0.8f, 30.f, 20.f, float(Get_TileCollision().bottom),
						m_tInfo.fAtk, 150.f, 5.f, 2.f, 5.f, 90.f, 0.f, 0.2f, L"LBullet", { 255, 0, 255 }));
			}
			else
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
					Create_Obj(ATT_NORMAL, true, m_tInfo.fX + 65.f, m_tInfo.fY - 24.f, 30.f, 20.f, 11.5f, 0.f, 0.f, 0.f, 0.8f, 30.f, 20.f, float(Get_TileCollision().bottom),
						m_tInfo.fAtk, 150.f, 5.f, 2.f, 5.f, 90.f, 0.f, 0.2f, L"RBullet", { 255, 0, 255 }));
			}
			CSoundMgr::Get_Instance()->PlaySoundW(L"RdShotBullet.wav", SOUND_EFFECT, g_fVolume);
		}

		if (m_dwTime > 0.405)
		{
			CSoundMgr::Get_Instance()->PlaySoundW(L"paning_01.ogg", SOUND_EFFECT2, g_fVolume);
			m_iNormalFinalCount = 0;
			m_iDNormalCount = 0;
			m_dwTime = 0;
			m_ePlayerState = PS_IDLE;
		}
		break;

		// 아래평타1
	case PS_DATTACK1:
		if (m_dwTime > 0.21)
		{
			m_dwTime = 0;
			m_ePlayerState = PS_IDLE;
		}
		break;

		// 아래평타2
	case PS_DATTACK2:
		if (m_dwTime > 0.21)
		{
			m_dwTime = 0;
			m_ePlayerState = PS_IDLE;
		}
		break;

		// 아래평타3
	case PS_DATTACK3:
		if (m_dwTime > 0.21)
		{
			m_dwTime = 0;
			m_ePlayerState = PS_IDLE;
		}
		break;

		// 아래평타4
	case PS_DATTACK4:
		if (m_dwTime > 0.315)
		{
			m_dwTime = 0;
			m_ePlayerState = PS_IDLE;
		}
		break;

	// 아래평타5
	case PS_DATTACK5:
		if (m_dwTime > 0.245 && m_iDNormalCount < 1)
		{
			++m_iDNormalCount;
			if (m_pFrameKey == L"Player_LEFT")
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
					Create_Obj(ATT_NORMAL, true, m_tInfo.fX - 65.f, m_tInfo.fY - 24.f, 30.f, 20.f, 11.5f, 210.f, 0.f, m_tTileCollision.bottom - 10.f, 0.8f, 30.f, 20.f, float(Get_TileCollision().bottom),
						m_tInfo.fAtk, 150.f, 5.f, 2.f, 5.f, 90.f, 0.f, 0.2f, L"LBullet_Low", { 255, 0, 255 }));
			}
			else
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
					Create_Obj(ATT_NORMAL, true, m_tInfo.fX + 65.f, m_tInfo.fY - 24.f, 30.f, 20.f, 11.5f, 330.f, 0.f, m_tTileCollision.bottom - 10.f, 0.8f, 30.f, 20.f, float(Get_TileCollision().bottom),
						m_tInfo.fAtk, 150.f, 5.f, 2.f, 5.f, 90.f, 0.f, 0.2f, L"RBullet_Low", { 255, 0, 255 }));
			}
			CSoundMgr::Get_Instance()->PlaySoundW(L"RdShotBullet.wav", SOUND_EFFECT, g_fVolume);
		}

		if (m_dwTime > 0.350)
		{
			CSoundMgr::Get_Instance()->PlaySoundW(L"paning_01.ogg", SOUND_EFFECT2, g_fVolume);
			m_iNormalFinalCount = 0;
			m_iDNormalCount = 0;
			m_dwTime = 0;
			m_ePlayerState = PS_IDLE;
		}
		break;

	// SPACE 데스 바이 리볼버
	case PS_DBR:
		if (m_dwTime > 0.6)
		{
			m_dwTime = 0;
			m_ePlayerState = PS_IDLE;
		}
		break;

	// Z 잭스파이크
	case PS_ZACKS:
		if (m_dwTime > 0.4)
		{
			m_dwTime = 0;
			m_ePlayerState = PS_IDLE;
		}
		break;

	// E 건가드
	case PS_GUNGUARD:
		if (m_dwTime > 1)
		{
			m_dwTime = 0;
			m_ePlayerState = PS_IDLE;
		}
		break;

	// S 윈드밀
	case PS_WINDMILL:
		if (m_dwTime > 0.5 && 0 == m_iWindmillCount)
		{
			++m_iWindmillCount;
			CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
				Create_Obj(ATT_THRUST, false, m_tInfo.fX, m_tInfo.fY + 20.f, 347.f, 117.f, 0.f, 0.f, 0.f, 0.f, 1.f, 200.f, 100.f, float(Get_TileCollision().bottom),
					m_tInfo.fAtk, 350.f, 5.f, 1.5f, 5.f, 0.f, 0.f, 0.4f, L"Windmill2", { 0, 0, 0 }));
		}
		if (m_dwTime > 1)
		{
			m_dwTime = 0;
			m_iWindmillCount = 0;
			m_ePlayerState = PS_IDLE;
		}
		break;

		// D 마하킥
	case PS_MAHA:
		if (m_dwTime > 0.3)
		{
			m_dwTime = 0;
			m_iWindmillCount = 0;
			m_ePlayerState = PS_IDLE;
		}
		break;

		// A 헤드샷
	case PS_HEADSHOT:
		if (m_dwTime > 0.175 && m_iHeadShotCount < 1)
		{
			++m_iHeadShotCount;
			if (m_pFrameKey == L"Player_LEFT")
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
					Create_Obj(ATT_NORMAL, true, m_tInfo.fX - 65.f, m_tInfo.fY - 24.f, 40.f, 20.f, 16.5f, 180.f, 0.f, 0.f, 0.8f, 40.f, 20.f, float(Get_TileCollision().bottom),
						m_tInfo.fAtk, 1200.f, 5.f, 2.f, 5.f, 90.f, 0.f, 0.2f, L"LHeadShot", { 0, 0, 0 }));
			}
			else
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
					Create_Obj(ATT_NORMAL, true, m_tInfo.fX + 65.f, m_tInfo.fY - 24.f, 40.f, 20.f, 16.5f, 0.f, 0.f, 0.f, 0.8f, 40.f, 20.f, float(Get_TileCollision().bottom),
						m_tInfo.fAtk, 1200.f, 5.f, 2.f, 5.f, 90.f, 0.f, 0.2f, L"RHeadShot", { 0, 0, 0 }));
			}
			CSoundMgr::Get_Instance()->PlaySoundW(L"gn_hshot_03.wav", SOUND_EFFECT, g_fVolume);
		}
		if (m_dwTime > 0.315)
		{
			m_dwTime = 0;
			m_iHeadShotCount = 0;
			m_ePlayerState = PS_IDLE;
		}
		break;

		// R 이동사격
	case PS_MOVINGSHOT:
		// 이동사격중 V 누를시 취소
		if (CKeyMgr::Get_Instance()->Key_Pressing('V'))
		{
			m_dwTime = 0;
			m_iMovingShotCount = 0;
			m_ePlayerState = PS_IDLE;
			break;
		}

		// 이동사격중 Z 누를시 방향전환
		if (CKeyMgr::Get_Instance()->Key_Pressing('Z') && 0.2 < m_dwTime)
		{
			m_dwTime = 0;
			if (L"Player_LEFT" == Get_FrameKey())
				Set_FrameKey(L"Player_RIGHT");
			else
				Set_FrameKey(L"Player_LEFT");
		}

		// 이동사격중 방향키로 이동가능
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		{
			m_tInfo.fX -= m_fSpeed;
		}

		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		{
			m_tInfo.fX += m_fSpeed;
		}

		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		{
			m_tInfo.fY -= m_fSpeed;
		}

		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		{
			m_tInfo.fY += m_fSpeed;
		}

		if (CKeyMgr::Get_Instance()->Key_Pressing('X') && 0.08 < m_dwTime)
		{
			m_dwTime = 0;
			++m_iMovingShotCount;
			Making_MovingShot();
		}

		if (m_iMovingShotCount > 21 || CKeyMgr::Get_Instance()->Key_Pressing('V'))
		{
			m_dwTime = 0;
			m_iMovingShotCount = 0;
			m_ePlayerState = PS_IDLE;
		}
		break;
		
		// F 난사
	case PS_SPREE:
		// 난사중 V 누를시 취소
		if(CKeyMgr::Get_Instance()->Key_Pressing('V'))
		{
			m_dwTime = 0;
			m_iSpreeCount = 0;
			m_ePlayerState = PS_IDLE;
			break;
		}
		if (m_dwTime > 0 && 0 == m_iSpreeCount)
		{
			++m_iSpreeCount;
			Making_Spree();
		}
		if (m_dwTime > 0.05 && 1 == m_iSpreeCount)
		{
			++m_iSpreeCount;
			Making_Spree();
		}
		if (m_dwTime > 0.1 && 2 == m_iSpreeCount)
		{
			++m_iSpreeCount;
			Making_Spree();
		}
		if (m_dwTime > 0.15 && 3 == m_iSpreeCount)
		{
			++m_iSpreeCount;
			Making_Spree();
		}
		if (m_dwTime > 0.2 && 4 == m_iSpreeCount)
		{
			++m_iSpreeCount;
			Making_Spree();
		}
		if (m_dwTime > 0.25 && 5 == m_iSpreeCount)
		{
			++m_iSpreeCount;
			Making_Spree();
		}
		if (m_dwTime > 0.3 && 6 == m_iSpreeCount)
		{
			++m_iSpreeCount;
			Making_Spree();
		}
		if (m_dwTime > 0.35 && 7 == m_iSpreeCount)
		{
			++m_iSpreeCount;
			Making_Spree();
		}
		if (m_dwTime > 0.4 && 8 == m_iSpreeCount)
		{
			++m_iSpreeCount;
			Making_Spree();
		}
		if (m_dwTime > 0.45 && 9 == m_iSpreeCount)
		{
			++m_iSpreeCount;
			Making_Spree();
		}

		if (m_dwTime > 0.5 && 10 == m_iSpreeCount)
		{
			++m_iSpreeCount;
			Making_Spree();
		}
		if (m_dwTime > 0.55 && 11 == m_iSpreeCount)
		{
			++m_iSpreeCount;
			Making_Spree();
		}
		if (m_dwTime > 0.6 && 12 == m_iSpreeCount)
		{
			++m_iSpreeCount;
			Making_Spree();
		}
		if (m_dwTime > 0.65 && 13 == m_iSpreeCount)
		{
			++m_iSpreeCount;
			Making_Spree();
		}
		if (m_dwTime > 0.7 && 14 == m_iSpreeCount)
		{
			++m_iSpreeCount;
			Making_Spree();
		}
		if (m_dwTime > 0.75 && 15 == m_iSpreeCount)
		{
			++m_iSpreeCount;
			Making_Spree();
		}
		if (m_dwTime > 0.8 && 16 == m_iSpreeCount)
		{
			++m_iSpreeCount;
			Making_Spree();
		}
		if (m_dwTime > 0.85 && 17 == m_iSpreeCount)
		{
			++m_iSpreeCount;
			Making_Spree();
		}
		if (m_dwTime > 0.9 && 18 == m_iSpreeCount)
		{
			++m_iSpreeCount;
			Making_Spree();
		}
		if (m_dwTime > 0.95 && 19 == m_iSpreeCount)
		{
			++m_iSpreeCount;
			Making_Spree();
		}
		if (m_dwTime > 1 && 20 == m_iSpreeCount)
		{
			++m_iSpreeCount;
			Making_Spree();
		}

		if (m_dwTime > 1.05 && 21 == m_iSpreeCount)
		{
			++m_iSpreeCount;
			Making_Spree();
		}
		if (m_dwTime > 1.1 && 22 == m_iSpreeCount)
		{
			++m_iSpreeCount;
			Making_Spree();
		}
		if (m_dwTime > 1.15 && 23 == m_iSpreeCount)
		{
			++m_iSpreeCount;
			Making_Spree();
		}
		if (m_dwTime > 1.2 && 24 == m_iSpreeCount)
		{
			++m_iSpreeCount;
			Making_Spree();
		}
		if (m_dwTime > 1.25 && 25 == m_iSpreeCount)
		{
			++m_iSpreeCount;
			Making_Spree();
		}

		if (m_dwTime > 1.5)
		{
			m_dwTime = 0;
			m_iSpreeCount = 0;
			m_ePlayerState = PS_IDLE;
		}
		break;

		// G 세틀라이트빔
	case PS_SATELITE:
		if (0 < m_dwTime && 0 == m_iSateliteCount)
		{
			Set_IsImmune(true);
			++m_iSateliteCount;
			// 컷신
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CVertical>::
				Create_Obj(ATT_JUSTEFFECT, false, 480.f, 334.f, 720.f, 668.f, 0.f, 0.f, 0.f, 0.f, 1.f, 720.f, 668.f, float(Get_TileCollision().bottom),
					0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, L"CutIn_Buff", { 255, 255, 255 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 18, 0, 0.053, 0. });
		}
		if (1 < m_dwTime && 1 == m_iSateliteCount)
		{
			++m_iSateliteCount;
			if (L"Player_LEFT" == Get_FrameKey())
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_WIDEATTACK, CAbstractFactory<CSatelite>::
					Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX - 150.f, m_tInfo.fY - 150.f, 578.f, 600.f, 5.f, 0.f, 0.f, 0.f, 15.f, 350.f, 500.f, float(Get_TileCollision().bottom),
						m_tInfo.fAtk, 50.f, 0.f, 0.f, 5.f, 0.f, 0.f, 0.5f, L"Satelaser_Core", { 0, 0, 0 }));
				CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER_WIDEATTACK).back()->Set_Frame(tagFrame{ 0, 15, 0, 0.1, 0. });
			}
			else
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_WIDEATTACK, CAbstractFactory<CSatelite>::
					Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX + 150.f, m_tInfo.fY - 150.f, 578.f, 600.f, 5.f, 0.f, 0.f, 0.f, 15.f, 350.f, 500.f, float(Get_TileCollision().bottom),
						m_tInfo.fAtk, 50.f, 0.f, 0.f, 5.f, 0.f, 0.f, 0.5f, L"Satelaser_Core", { 0, 0, 0 }));
				CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER_WIDEATTACK).back()->Set_Frame(tagFrame{ 0, 15, 0, 0.1, 0. });
			}
		}
		if (1.5 < m_dwTime)
		{
			Set_IsImmune(false);
			m_dwTime = 0;
			m_iSateliteCount = 0;
			m_ePlayerState = PS_IDLE;
		}
		break;

		// Y 각성기
	case PS_AWAKEN:
		if (L"Player_LEFT" == Get_FrameKey())
			m_ePlayerState = PS_LAWAKENING;
		else if (L"Player_RIGHT" == Get_FrameKey())
			m_ePlayerState = PS_RAWAKENING;

		break;

	case PS_LAWAKENING:
		DoSeventhL();
		if (3.7 < m_dwTime && 10 < m_iSeventhCount)
		{
			Set_IsImmune(false);	// 무적 해제
			m_dwTime = 0;
			m_iSeventhCount = 0;
			if (L"LAwakening" == Get_FrameKey())
				Set_FrameKey(L"Player_LEFT");
			if (L"RAwakening" == Get_FrameKey())
				Set_FrameKey(L"Player_RIGHT");
			m_ePlayerState = PS_IDLE;
		}
		break;

	case PS_RAWAKENING:
		DoSeventhR();
		if (3.7 < m_dwTime && 10 < m_iSeventhCount)
		{
			Set_IsImmune(false);	// 무적 해제
			m_dwTime = 0;
			m_iSeventhCount = 0;
			if (L"LAwakening" == Get_FrameKey())
				Set_FrameKey(L"Player_LEFT");
			if (L"RAwakening" == Get_FrameKey())
				Set_FrameKey(L"Player_RIGHT");
			m_ePlayerState = PS_IDLE;
		}
		break;

	// 일반 피격(제자리)
	case PS_NORMAL_ATTACKED:
		if (!m_bKnockback)
		{
			m_dwTime = 0;
			m_iSpreeCount = 0;
			m_ePlayerState = PS_IDLE;
		}
		break;

	// 넉백 피격(밀려남)
	case PS_THRUST_ATTACKED:
		if (!m_bKnockback)
		{
			m_dwTime = 0;
			m_iSpreeCount = 0;
			m_ePlayerState = PS_IDLE;
		}

		break;

	// 띄움 피격(띄워짐)
	case PS_LEVITATE_ATTACKED:
		if (!m_bKnockback)
		{
			m_dwTime = 0;
			m_iSpreeCount = 0;
			// m_tInfo.fY = m_tTileCollision.bottom - (0.5f * m_tInfo.fCY);
			m_ePlayerState = PS_IDLE;
		}
		break;

	// 사망
	case PS_DEAD:
		Set_IsImmune(true);
		if (Get_Frame().iFrameStart == Get_Frame().iFrameEnd)
			Set_StopMotion(true);
		
		if (2.5 < m_dwTime)
		{
			m_dwTime = 0;
			m_iSpreeCount = 0;
			Set_StopMotion(false);
			Set_IsImmune(false);
			m_tInfo.fHp = m_tInfo.fMaxHp;
			m_ePlayerState = PS_IDLE;
		}
		break;
	}
}

void CPlayer::Offset(void)
{
	// 스크롤이 동작하기 위한 화면상의 최소, 최대 위치
	float		fOffSetMinX = 350.f;
	float		fOffSetMaxX = 450.f;

	float		fOffSetMinY = 250.f;
	float		fOffSetMaxY = 350.f;

	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	if (m_ePlayerState == PS_LWALK || m_ePlayerState == PS_RWALK ||
		m_ePlayerState == PS_JUSTWALKUP || m_ePlayerState == PS_JUSTWALKDOWN || m_ePlayerState == PS_MOVINGSHOT)
	{
		if (fOffSetMinX > m_tInfo.fX + fScrollX)
			CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

		if (fOffSetMaxX < m_tInfo.fX + fScrollX)
			CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);

		if (fOffSetMinY > m_tInfo.fY + fScrollY)
			CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);

		if (fOffSetMaxY < m_tInfo.fY + fScrollY)
			CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);
	}
	else if(m_ePlayerState == PS_LRUN || m_ePlayerState == PS_RRUN)
	{
		if (fOffSetMinX > m_tInfo.fX + fScrollX)
			CScrollMgr::Get_Instance()->Set_ScrollX(1.5f * m_fSpeed);

		if (fOffSetMaxX < m_tInfo.fX + fScrollX)
			CScrollMgr::Get_Instance()->Set_ScrollX(1.5f * -m_fSpeed);

		if (fOffSetMinY > m_tInfo.fY + fScrollY)
			CScrollMgr::Get_Instance()->Set_ScrollY(1.5f * m_fSpeed);

		if (fOffSetMaxY < m_tInfo.fY + fScrollY)
			CScrollMgr::Get_Instance()->Set_ScrollY(1.5f * -m_fSpeed);
	}
	else if (m_ePlayerState == PS_LSLIDE || m_ePlayerState == PS_RSLIDE)
	{
		if (fOffSetMinX > m_tInfo.fX + fScrollX)
			CScrollMgr::Get_Instance()->Set_ScrollX(3.5f * m_fSpeed);

		if (fOffSetMaxX < m_tInfo.fX + fScrollX)
			CScrollMgr::Get_Instance()->Set_ScrollX(-3.5f * m_fSpeed);

		if (fOffSetMinY > m_tInfo.fY + fScrollY)
			CScrollMgr::Get_Instance()->Set_ScrollY(3.5f * m_fSpeed);

		if (fOffSetMaxY < m_tInfo.fY + fScrollY)
			CScrollMgr::Get_Instance()->Set_ScrollY(-3.5f * m_fSpeed);
	}
	else if (m_ePlayerState == PS_JUMP || m_ePlayerState == PS_JUMPATTACK
			|| m_ePlayerState == PS_NORMAL_ATTACKED || m_ePlayerState == PS_THRUST_ATTACKED || m_ePlayerState == PS_LEVITATE_ATTACKED)
	{
		if (fOffSetMinX > m_tInfo.fX + fScrollX)
			CScrollMgr::Get_Instance()->Set_ScrollX(1.5f * m_fSpeed);

		if (fOffSetMaxX < m_tInfo.fX + fScrollX)
			CScrollMgr::Get_Instance()->Set_ScrollX(-1.5 * m_fSpeed);
	}
	else
	{
		if (fOffSetMinX > m_tInfo.fX + fScrollX)
			CScrollMgr::Get_Instance()->Set_ScrollX(1.5f * m_fSpeed);

		if (fOffSetMaxX < m_tInfo.fX + fScrollX)
			CScrollMgr::Get_Instance()->Set_ScrollX(-1.5 * m_fSpeed);
	}
}

// 모션 상태를 변화시켜주는 함수(유한 상태 머신)
void CPlayer::Motion_Change()
{
	// 현재 상태와 외부 요인에 의해(ex.방향키, 스킬키 등...) 새롭게 바뀐 상태가 동일하지 않을 때,
	if (m_ePlayerPreState != m_ePlayerState)
	{
		// 만약 현재 상태가 ...라면
		switch (m_ePlayerState)
		{
			// 해당 상태에 맞게 프레임 구조체의 값들을 변경해준다.

		// 아이들
		case PS_IDLE:
			Set_StopMotion(false);
			m_tFrame.iFrameStart = 0; 
			m_tFrame.iFrameEnd	 = 12;
			m_tFrame.iMotion	 = 0;
			m_tFrame.dwSpeed	 = 0.3;
			break;

		// 제자리 위로 걷기
		case PS_JUSTWALKUP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 6;
			m_tFrame.dwSpeed = 0.15;
			break;

		// 제자리 아래로 걷기
		case PS_JUSTWALKDOWN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 6;
			m_tFrame.dwSpeed = 0.15;
			break;

		// 왼쪽 걷기
		case PS_LWALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 6;
			m_tFrame.dwSpeed = 0.15;
			break;

		// 오른쪽 걷기
		case PS_RWALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 6;
			m_tFrame.dwSpeed = 0.15;
			break;

		// 왼쪽 달리기
		case PS_LRUN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 12;
			m_tFrame.dwSpeed = 0.10;
			break;

		// 오른쪽 달리기
		case PS_RRUN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 12;
			m_tFrame.dwSpeed = 0.10;
			break;

		// X 왼쪽 슬라이딩
		case PS_LSLIDE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 13;
			m_tFrame.dwSpeed = 0.15;
			break;

		// X 오른쪽 슬라이딩
		case PS_RSLIDE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 13;
			m_tFrame.dwSpeed = 0.15;
			break;

		// C 점프
		case PS_JUMP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 7;
			m_tFrame.dwSpeed = 0.25;
			break;

		// X 점프 공격
		case PS_JUMPATTACK:
			m_tFrame.iFrameStart = 1;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 8;
			m_tFrame.dwSpeed = 0.06;
			break;

		// X 평타1
		case PS_ATTACK1:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 0.035;
			break;

		// X 평타2
		case PS_ATTACK2:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 0.035;
			break;

		// X 평타3
		case PS_ATTACK3:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 0.035;
			break;

		// X 평타4
		case PS_ATTACK4:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 0.035;
			break;

		// X 평타5
		case PS_ATTACK5:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 0.045;
			break;

		// X 아래평타1
		case PS_DATTACK1:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 0.04;
			break;

		// X 아래평타2
		case PS_DATTACK2:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 0.04;
			break;

		// X 아래평타3
		case PS_DATTACK3:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 0.04;
			break;

		// X 아래평타4
		case PS_DATTACK4:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 0.05;
			break;

		// X 아래평타5
		case PS_DATTACK5:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 5;
			m_tFrame.dwSpeed = 0.035;
			break;

		// SPACE 데스바이리볼버
		case PS_DBR:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 27;
			m_tFrame.dwSpeed = 0.15;
			break;

		// Z 잭스파이크
		case PS_ZACKS:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 22;
			m_tFrame.dwSpeed = 0.1;
			break;

		// E 건가드
		case PS_GUNGUARD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 26;
			m_tFrame.dwSpeed = 0.75;
			break;

		// S 윈드밀
		case PS_WINDMILL:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 14;
			m_tFrame.dwSpeed = 0.18;
			break;

		// D 마하킥
		case PS_MAHA:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 23;
			m_tFrame.dwSpeed = 0.05;
			break;

		// A 헤드샷
		case PS_HEADSHOT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 0.035;
			break;

		// R 이동사격
		case PS_MOVINGSHOT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 12;
			m_tFrame.iMotion = 10;
			m_tFrame.dwSpeed = 0.1;
			break;

		// F 난사
		case PS_SPREE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 12;
			m_tFrame.iMotion = 25;
			m_tFrame.dwSpeed = 0.05;
			break;

		// Y 세틀라이트빔
		case PS_SATELITE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 27;
			m_tFrame.dwSpeed = 0.25;
			break;

		// Y 각성기
		case PS_AWAKEN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 10;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 0.05;
			break;

		// 일반 피격 모션
		case PS_NORMAL_ATTACKED:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 15;
			m_tFrame.dwSpeed = 0.4;
			break;

		// 밀쳐지는 피격 모션
		case PS_THRUST_ATTACKED:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 15;
			m_tFrame.dwSpeed = 0.4;
			break;

		// 날아가는 피격 모션
		case PS_LEVITATE_ATTACKED:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 16;
			m_tFrame.dwSpeed = 0.2;
			break;

		// 사망
		case PS_DEAD:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 16;
			m_tFrame.dwSpeed = 0.3;
			break;
		}

		// 새롭게 변경된 상태를 m_ePreState에 저장한다.
		m_ePlayerPreState = m_ePlayerState;
	}
}

void CPlayer::Cool_Check()
{
	m_DBRCool += CTimeMgr::Get_Instance()->GetfDT();
	m_ZacksCool += CTimeMgr::Get_Instance()->GetfDT();
	m_GunGuardCool += CTimeMgr::Get_Instance()->GetfDT();
	m_WindmillCool += CTimeMgr::Get_Instance()->GetfDT();
	m_MahaCool += CTimeMgr::Get_Instance()->GetfDT();
	m_HeadShotCool += CTimeMgr::Get_Instance()->GetfDT();
	m_MovingShotCool += CTimeMgr::Get_Instance()->GetfDT();
	m_SpreeCool += CTimeMgr::Get_Instance()->GetfDT();

	m_SateliteCool += CTimeMgr::Get_Instance()->GetfDT();
	m_AwakeningCool += CTimeMgr::Get_Instance()->GetfDT();
}

void CPlayer::SkillCool_Making(float _fX, float _fY, float _fLifeTime, TCHAR* _pKey)
{
	// 아이콘이 생성될 위치, 쿨타임, 이미지 키
	CObjMgr::Get_Instance()->Add_Object(OBJ_SKILLICON, CAbstractFactory<CUI_SkillIcon>::Create_Obj(_fX, _fY, _fLifeTime, _pKey));
}

// 플레이어 잔상 제작용 함수
void CPlayer::Making_Shadow(TCHAR* _pKey, float _fLifeTime)
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
		Create_Obj(ATT_JUSTEFFECT, m_tInfo.fX, m_tInfo.fY, 271.f, 237.f, _fLifeTime, _pKey));
	CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER_ATTACK).back()->Set_RGB(tagColor{255, 255, 255});
	CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER_ATTACK).back()->Set_Frame(tagFrame{ m_tFrame.iFrameStart, m_tFrame.iFrameEnd, m_tFrame.iMotion, m_tFrame.dwSpeed, m_tFrame.dwTime });
	CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER_ATTACK).back()->Set_AlphaValue(150);
	CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER_ATTACK).back()->Set_StopMotion(true);
	CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER_ATTACK).back()->Set_RenderID(BACKGROUNDEFFECT);
}

// 이동사격 탄환 제작용 함수
void CPlayer::Making_MovingShot()
{
	CSoundMgr::Get_Instance()->PlaySoundW(L"RdShotBullet.wav", SOUND_EFFECT, g_fVolume);

	int iRand = rand();
	float fAngle = float(iRand % 5);

	switch (iRand % 2)
	{
	case 0:
		if (m_pFrameKey == L"Player_LEFT")
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
				Create_Obj(ATT_NORMAL, true, m_tInfo.fX - 65.f, m_tInfo.fY - 24.f, 30.f, 20.f, 15.5f, 180.f + fAngle, 0.f, 0.f, 0.8f, 40.f, 20.f, float(Get_TileCollision().bottom),
					m_tInfo.fAtk, 250.f, 5.f, 2.f, 5.f, 90.f, 0.f, 0.2f, L"LBullet", { 255, 0, 255 }));
		}
		else
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
				Create_Obj(ATT_NORMAL, true, m_tInfo.fX + 65.f, m_tInfo.fY - 24.f, 30.f, 20.f, 15.5f, 0.f + fAngle, 0.f, 0.f, 0.8f, 40.f, 20.f, float(Get_TileCollision().bottom),
					m_tInfo.fAtk, 250.f, 5.f, 2.f, 5.f, 90.f, 0.f, 0.2f, L"RBullet", { 255, 0, 255 }));
		}
		break;

	case 1:
		if (m_pFrameKey == L"Player_LEFT")
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
				Create_Obj(ATT_NORMAL, true, m_tInfo.fX - 65.f, m_tInfo.fY - 24.f, 30.f, 20.f, 15.5f, 180.f + fAngle, 0.f, 0.f, 0.8f, 40.f, 20.f, float(Get_TileCollision().bottom),
					m_tInfo.fAtk, 250.f, 5.f, 2.f, 5.f, 90.f, 0.f, 0.2f, L"LBullet", { 255, 0, 255 }));
		}
		else
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
				Create_Obj(ATT_NORMAL, true, m_tInfo.fX + 65.f, m_tInfo.fY - 24.f, 30.f, 20.f, 15.5f, 0.f + fAngle, 0.f, 0.f, 0.8f, 40.f, 20.f, float(Get_TileCollision().bottom),
					m_tInfo.fAtk, 250.f, 5.f, 2.f, 5.f, 90.f, 0.f, 0.2f, L"RBullet", { 255, 0, 255 }));
		}
		break;
	}

	
}

// 난사 이펙트 제작용 함수
void CPlayer::Making_Spree()
{
	if(0 == m_iSpreeCount % 2)
		CSoundMgr::Get_Instance()->PlaySoundW(L"RdShotBullet.wav", SOUND_EFFECT, g_fVolume);

	int iRand = rand();

	switch (iRand % 8)
	{
		// 좌 상단
	case 0:
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
			Create_Obj(ATT_LEVITATE, false, m_tInfo.fX - 130.f, m_tInfo.fY - 40.f, 250.f, 259.f, 0.f, 0.f, 0.f, 0.f, 0.3f, 150.f, 150.f, float(Get_TileCollision().bottom),
				m_tInfo.fAtk, 400.f, 3.f, 0.f, 9.5f, 90.f, 180.f, 0.4f, L"LU", { 255, 255, 255 }));

		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
			Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX - 130.f, m_tInfo.fY - 40.f, 250.f, 259.f, 0.f, 0.f, 0.f, 0.f, 0.3f, 150.f, 150.f, float(Get_TileCollision().bottom),
				m_tInfo.fAtk, 400.f, 1.5f, 0.f, 0.f, 90.f, 0.f, 0.4f, L"LUSpree", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 5, 0, 0.05, 0. });
		break;

		// 좌 중단
	case 1:
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
			Create_Obj(ATT_LEVITATE, false, m_tInfo.fX - 130.f, m_tInfo.fY - 20.f, 250.f, 259.f, 0.f, 0.f, 0.f, 0.f, 0.3f, 150.f, 150.f, float(Get_TileCollision().bottom),
				m_tInfo.fAtk, 400.f, 3.f, 0.f, 9.5f, 90.f, 180.f, 0.4f, L"L", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER_ATTACK).back()->Set_Frame(tagFrame{ 0, 5, 0, 0.05, 0. });

		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
			Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX - 130.f, m_tInfo.fY - 20.f, 250.f, 259.f, 0.f, 0.f, 0.f, 0.f, 0.3f, 150.f, 150.f, float(Get_TileCollision().bottom),
				m_tInfo.fAtk, 400.f, 1.5f, 0.f, 0.f, 90.f, 0.f, 0.4f, L"LSpree", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 5, 0, 0.05, 0. });
		break;

		// 좌 중하단
	case 2:
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
			Create_Obj(ATT_LEVITATE, false, m_tInfo.fX - 130.f, m_tInfo.fY + 25.f, 250.f, 259.f, 0.f, 0.f, 0.f, 0.f, 0.3f, 150.f, 150.f, float(Get_TileCollision().bottom),
				m_tInfo.fAtk, 400.f, 3.f, 0.f, 9.5f, 90.f, 180.f, 0.4f, L"LD", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER_ATTACK).back()->Set_Frame(tagFrame{ 0, 5, 0, 0.05, 0. });

		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
			Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX - 130.f, m_tInfo.fY + 25.f, 250.f, 259.f, 0.f, 0.f, 0.f, 0.f, 0.3f, 150.f, 150.f, float(Get_TileCollision().bottom),
				m_tInfo.fAtk, 400.f, 1.5f, 0.f, 0.f, 90.f, 0.f, 0.4f, L"LDSpree", { 0, 0, 0 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 5, 0, 0.05, 0. });
		break;

		// 좌 하단
	case 3:
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
			Create_Obj(ATT_LEVITATE, false, m_tInfo.fX - 115.f, m_tInfo.fY + 75.f, 250.f, 259.f, 0.f, 0.f, 0.f, 0.f, 0.3f, 150.f, 150.f, float(Get_TileCollision().bottom),
				m_tInfo.fAtk, 400.f, 3.f, 0.f, 9.5f, 90.f, 180.f, 0.4f, L"LDD", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER_ATTACK).back()->Set_Frame(tagFrame{ 0, 5, 0, 0.05, 0. });

		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
			Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX - 115.f, m_tInfo.fY + 75.f, 250.f, 259.f, 0.f, 0.f, 0.f, 0.f, 0.3f, 150.f, 150.f, float(Get_TileCollision().bottom),
				m_tInfo.fAtk, 400.f, 1.5f, 0.f, 0.f, 90.f, 0.f, 0.4f, L"LDDSpree", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 5, 0, 0.05, 0. });
		break;
		// 우 상단
	case 4:
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
			Create_Obj(ATT_LEVITATE, false, m_tInfo.fX + 130.f, m_tInfo.fY - 40.f, 250.f, 259.f, 0.f, 0.f, 0.f, 0.f, 0.3f, 150.f, 150.f, float(Get_TileCollision().bottom),
				m_tInfo.fAtk, 400.f, 3.f, 0.f, 9.5f, 90.f, 0.f, 0.4f, L"RU", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER_ATTACK).back()->Set_Frame(tagFrame{ 0, 5, 0, 0.05, 0. });

		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
			Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX + 130.f, m_tInfo.fY - 40.f, 250.f, 259.f, 0.f, 0.f, 0.f, 0.f, 0.3f, 150.f, 150.f, float(Get_TileCollision().bottom),
				m_tInfo.fAtk, 400.f, 1.5f, 0.f, 0.f, 90.f, 0.f, 0.4f, L"RUSpree", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 5, 0, 0.05, 0. });
		break;

		// 우 중단
	case 5:
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
			Create_Obj(ATT_LEVITATE, false, m_tInfo.fX + 130.f, m_tInfo.fY - 20, 250.f, 259.f, 0.f, 0.f, 0.f, 0.f, 0.3f, 150.f, 150.f, float(Get_TileCollision().bottom),
				m_tInfo.fAtk, 400.f, 3.f, 0.f, 9.5f, 90.f, 0.f, 0.4f, L"R", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER_ATTACK).back()->Set_Frame(tagFrame{ 0, 5, 0, 0.05, 0. });

		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
			Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX + 130.f, m_tInfo.fY - 20, 250.f, 259.f, 0.f, 0.f, 0.f, 0.f, 0.3f, 150.f, 150.f, float(Get_TileCollision().bottom),
				m_tInfo.fAtk, 400.f, 1.5f, 0.f, 0.f, 90.f, 0.f, 0.4f, L"RSpree", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 5, 0, 0.05, 0. });
		break;

		// 우 중하단
	case 6:
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
			Create_Obj(ATT_LEVITATE, false, m_tInfo.fX + 130.f, m_tInfo.fY + 25.f, 250.f, 259.f, 0.f, 0.f, 0.f, 0.f, 0.3f, 150.f, 150.f, float(Get_TileCollision().bottom),
				m_tInfo.fAtk, 400.f, 3.f, 0.f, 9.5f, 90.f, 0.f, 0.4f, L"RD", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER_ATTACK).back()->Set_Frame(tagFrame{ 0, 5, 0, 0.05, 0. });

		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
			Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX + 130.f, m_tInfo.fY + 25.f, 250.f, 259.f, 0.f, 0.f, 0.f, 0.f, 0.3f, 150.f, 150.f, float(Get_TileCollision().bottom),
				m_tInfo.fAtk, 400.f, 1.5f, 0.f, 0.f, 90.f, 0.f, 0.4f, L"RDSpree", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 5, 0, 0.05, 0. });
		break;

		// 우 하단
	case 7:
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
			Create_Obj(ATT_LEVITATE, false, m_tInfo.fX + 115.f, m_tInfo.fY + 75.f, 250.f, 259.f, 0.f, 0.f, 0.f, 0.f, 0.3f, 150.f, 150.f, float(Get_TileCollision().bottom),
				m_tInfo.fAtk, 400.f, 3.f, 0.f, 9.5f, 90.f, 0.f, 0.4f, L"RDD", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER_ATTACK).back()->Set_Frame(tagFrame{ 0, 5, 0, 0.05, 0. });

		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
			Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX + 115.f, m_tInfo.fY + 75.f, 250.f, 259.f, 0.f, 0.f, 0.f, 0.f, 0.3f, 150.f, 150.f, float(Get_TileCollision().bottom),
				m_tInfo.fAtk, 400.f, 1.5f, 0.f, 0.f, 90.f, 0.f, 0.4f, L"RDDSpree", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 5, 0, 0.05, 0. });
		break;
	}
}

// 각성기 제작용 함수
void CPlayer::Making_Awakening(float _fX, float _fY, float _fCX, float _fCY, float _fECX, float _fECY, TCHAR* _pKey, TCHAR* _pEKey
	, int _Start, int _End, float _FrameSpeed, float _LifeTime, int _EStart, int _EEnd, float _EFrameSpeed, float _ELifeTime)
{
	// 히트 박스
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_WIDEATTACK, CAbstractFactory<CPlayerAttack>::
		Create_Obj(ATT_THRUST, false, _fX, _fY, 500.f, 400.f, 0.f, 0.f, 0.f, 0.f, 0.2f, 700.f, 400.f, float(Get_TileCollision().bottom),
			m_tInfo.fAtk, 2500.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.2f, L"SeventhAttack", { 255, 0, 255 }));
	// 포격 이펙트
	CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
		Create_Obj(ATT_JUSTEFFECT, false, _fX, _fY, _fCX, _fCY, 0.f, 0.f, 0.f, 0.f, _LifeTime, _fCX, _fCY, float(Get_TileCollision().bottom),
			m_tInfo.fAtk, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, _pKey, { 255, 0, 255 }));
	CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ _Start, _End, 0, _FrameSpeed, 0. });
	// 깃털 이펙트
	CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
		Create_Obj(ATT_JUSTEFFECT, false, _fX, _fY, _fECX, _fECY, 0.f, 0.f, 0.f, 0.f, _ELifeTime, _fECX, _fECY, float(Get_TileCollision().bottom),
			m_tInfo.fAtk, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, _pEKey, { 255, 0, 255 }));
	CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ _EStart, _EEnd, 0, _EFrameSpeed, 0. });

}

// 각성기 이펙트 제작용 함수
void CPlayer::Making_AwakeningE(float _fX, float _fY, float _fECX, float _fECY, TCHAR* _pEKey
	, int _EStart, int _EEnd, float _EFrameSpeed, float _ELifeTime)
{
	// 깃털 이펙트
	CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
		Create_Obj(ATT_JUSTEFFECT, false, _fX, _fY, _fECX, _fECY, 0.f, 0.f, 0.f, 0.f, _ELifeTime, _fECX, _fECY, float(Get_TileCollision().bottom),
			m_tInfo.fAtk, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, _pEKey, { 255, 0, 255 }));
	CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ _EStart, _EEnd, 0, _EFrameSpeed, 0. });

}

// 방향에 따른 각성기
void CPlayer::DoSeventhL()
{
	if (m_dwTime > 0 && 0 == m_iSeventhCount)
	{
		++m_iSeventhCount;

		// 컷신
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CNonAlpha>::
			Create_Obj(ATT_JUSTEFFECT, false, 400.f, 440.f, 800.f, 260.f, 0.f, 0.f, 0.f, 0.f, 0.8f, 800.f, 260.f, float(Get_TileCollision().bottom),
				0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, L"Cutsin", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 15, 0, 0.05, 0. });

		Set_FrameKey(L"LAwakening");
		Set_Frame(tagFrame{ 0, 9, 0, 0.05, 0. });
		// 잔상 남기기
		if (L"LAwakening" == Get_FrameKey())
			Making_Shadow(L"LAwaken_Black", 1.0f);
		else
			Making_Shadow(L"RAwaken_Black", 1.0f);
		Set_PosX(-20.f);

	}
	// 1타
	if (m_dwTime > 0.5 && 1 == m_iSeventhCount)
	{
		++m_iSeventhCount;

		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			368.f, 400.f,
			L"SeventhFeather3",
			0, 10, 0.07, 0.77);
		Set_Frame(tagFrame{ 0, 3, 1, 0.075, 0. });
		// 잔상 남기기
		if (L"LAwakening" == Get_FrameKey())
			Making_Shadow(L"LAwaken_Black", 1.0f);
		else
			Making_Shadow(L"RAwaken_Black", 1.0f);
		Set_PosX(-75.f);
		Set_PosY(-110.f);
		// 왼쪽
		Making_Awakening(m_tInfo.fX - 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 369.f, 400.f,
			L"LSeventhNormal", L"SeventhFeather5",
			0, 5, 0.03, 0.18, 0, 6, 0.07, 0.49);
		// 오른쪽
		Making_Awakening(m_tInfo.fX + 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 167.f, 194.f,
			L"LSeventhNormal", L"SeventhFeather1",
			0, 5, 0.03, 0.18, 0, 8, 0.07, 0.63);
	}
	// 2타
	if (m_dwTime > 0.8 && 2 == m_iSeventhCount)
	{

		++m_iSeventhCount;

		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			368.f, 400.f,
			L"SeventhFeather3",
			0, 10, 0.07, 0.77);
		Set_Frame(tagFrame{ 0, 3, 2, 0.075, 0. });
		// 잔상 남기기
		if (L"LAwakening" == Get_FrameKey())
			Making_Shadow(L"LAwaken_Black", 1.0f);
		else
			Making_Shadow(L"RAwaken_Black", 1.0f);
		Set_PosX(-75.f);
		Set_PosY(+220.f);
		// 왼쪽
		Making_Awakening(m_tInfo.fX - 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 167.f, 194.f,
			L"LSeventhNormal", L"SeventhFeather1",
			0, 5, 0.03, 0.18, 0, 8, 0.07, 0.63);
		// 오른쪽
		Making_Awakening(m_tInfo.fX + 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 167.f, 194.f,
			L"LSeventhNormal", L"SeventhFeather1",
			0, 5, 0.03, 0.18, 0, 8, 0.07, 0.63);
	}
	// 3타
	if (m_dwTime > 1.1 && 3 == m_iSeventhCount)
	{
		++m_iSeventhCount;

		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			368.f, 400.f,
			L"SeventhFeather3",
			0, 10, 0.1, 1.1);
		Set_Frame(tagFrame{ 0, 9, 3, 0.03, 0. });
		// 잔상 남기기
		if (L"LAwakening" == Get_FrameKey())
			Making_Shadow(L"LAwaken_Black", 1.0f);
		else
			Making_Shadow(L"RAwaken_Black", 1.0f);
		Set_PosX(-75.f);
		Set_PosY(-240.f);
		// 왼쪽
		Making_Awakening(m_tInfo.fX + 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 0.f, 0.f,
			L"LSeventhNormal", L"-",
			0, 5, 0.03, 0.18, 0, 0, 0, 0);

		// 오른쪽
		Making_Awakening(m_tInfo.fX + 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 0.f, 0.f,
			L"LSeventhNormal", L"-",
			0, 5, 0.03, 0.18, 0, 0, 0, 0);
		Making_AwakeningE(m_tInfo.fX + 100.f, m_tInfo.fY + 50.f,
			100.f, 55.f,
			L"SeventhDust1",
			0, 5, 0.07, 0.42);
	}
	// 4타
	if (m_dwTime > 1.4 && 4 == m_iSeventhCount)
	{
		++m_iSeventhCount;

		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			368.f, 400.f,
			L"SeventhFeather3",
			0, 10, 0.1, 1.1);
		Set_Frame(tagFrame{ 0, 3, 4, 0.075, 0. });
		// 잔상 남기기
		if (L"LAwakening" == Get_FrameKey())
			Making_Shadow(L"LAwaken_Black", 1.0f);
		else
			Making_Shadow(L"RAwaken_Black", 1.0f);
		Set_PosX(-75.f);
		Set_PosY(+180.f);

		// 왼쪽
		Making_Awakening(m_tInfo.fX - 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 0.f, 0.f,
			L"LSeventhNormal", L"-",
			0, 5, 0.03, 0.18, 0, 0, 0, 0);
		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			167.f, 194.f,
			L"SeventhFeather1",
			0, 8, 0.07, 0.63);
		// 오른쪽
		Making_Awakening(m_tInfo.fX + 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 0.f, 0.f,
			L"LSeventhNormal", L"-",
			0, 5, 0.03, 0.18, 0, 0, 0, 0);
		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			167.f, 194.f,
			L"SeventhFeather1",
			0, 8, 0.07, 0.63);
		// 위쪽
		Making_Awakening(m_tInfo.fX, m_tInfo.fY - 120.f,
			316.f, 274.f, 0.f, 0.f,
			L"LSeventhNormal", L"-",
			0, 5, 0.03, 0.18, 0, 0, 0, 0);
	}
	// 5타
	if (m_dwTime > 1.7 && 5 == m_iSeventhCount)
	{
		++m_iSeventhCount;

		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			368.f, 400.f,
			L"SeventhFeather3",
			0, 10, 0.1, 1.1);
		Set_Frame(tagFrame{ 0, 3, 5, 0.075, 0. });
		// 잔상 남기기
		if (L"LAwakening" == Get_FrameKey())
			Making_Shadow(L"LAwaken_Black", 1.0f);
		else
			Making_Shadow(L"RAwaken_Black", 1.0f);
		Set_PosX(-75.f);
		Set_PosY(-200.f);

		// 왼쪽
		Making_AwakeningE(m_tInfo.fX - 100.f, m_tInfo.fY,
			369.f, 400.f,
			L"SeventhFeather5",
			0, 6, 0.07, 0.49);
		// 오른쪽
		Making_Awakening(m_tInfo.fX + 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 0.f, 0.f,
			L"LSeventhNormal", L"-",
			0, 5, 0.03, 0.18, 0, 0, 0, 0);
	}
	if (m_dwTime > 2.0 && 6 == m_iSeventhCount)
	{
		++m_iSeventhCount;

		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			368.f, 400.f,
			L"SeventhFeather3",
			0, 10, 0.1, 1.1);
		Set_FrameKey(L"Player_LEFT");
		Set_Frame(tagFrame{ 0, 5, 14, 0.075, 0. });
		// 잔상 남기기
		if (L"Player_LEFT" == Get_FrameKey())
			Making_Shadow(L"Player_LEFT", 1.0f);
		else
			Making_Shadow(L"Player_RIGHT", 1.0f);
		Set_PosY(120.f);
	}
	if (m_dwTime > 2.45 && 7 == m_iSeventhCount)
	{
		++m_iSeventhCount;

		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			368.f, 400.f,
			L"SeventhFeather3",
			0, 10, 0.1, 1.1);
		Set_FrameKey(L"Player_RIGHT");
		Set_Frame(tagFrame{ 1, 4, 8, 0.05, 0. });
		if (L"Player_LEFT" == Get_FrameKey())
			Making_Shadow(L"Player_LEFT", 1.0f);
		else
			Making_Shadow(L"Player_RIGHT", 1.0f);
		Set_PosY(-50.f);
		Set_PosX(-50.f);

		// 오른쪽
		Making_Awakening(m_tInfo.fX + 155.f, m_tInfo.fY + 60.f,
			337.f, 407.f, 0.f, 0.f,
			L"RSeventhFinalBeforeThree5", L"-",
			0, 6, 0.07, 0.49, 0, 0, 0, 0);
		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			345.f, 304.f,
			L"SeventhFeather2",
			0, 6, 0.07, 0.49);
	}
	if (m_dwTime > 2.65 && 8 == m_iSeventhCount)
	{
		++m_iSeventhCount;

		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			368.f, 400.f,
			L"SeventhFeather3",
			0, 10, 0.1, 1.1);
		Set_PosY(30.f);
		Set_PosX(-10.f);

		// 오른쪽
		Making_Awakening(m_tInfo.fX + 155.f, m_tInfo.fY + 60.f,
			337.f, 407.f, 0.f, 0.f,
			L"RSeventhFinalBeforeThree4", L"-",
			0, 6, 0.07, 0.49, 0, 0, 0, 0);
		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			345.f, 304.f,
			L"SeventhFeather2",
			0, 6, 0.07, 0.49);
	}
	if (m_dwTime > 2.85 && 9 == m_iSeventhCount)
	{
		++m_iSeventhCount;

		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			368.f, 400.f,
			L"SeventhFeather3",
			0, 10, 0.1, 1.1);
		Set_PosY(30.f);
		Set_PosX(-10.f);

		// 오른쪽
		Making_Awakening(m_tInfo.fX + 155.f, m_tInfo.fY + 80.f,
			337.f, 407.f, 0.f, 0.f,
			L"RSeventhFinalBeforeThree3", L"-",
			0, 6, 0.07, 0.49, 0, 0, 0, 0);
		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			345.f, 304.f,
			L"SeventhFeather2",
			0, 6, 0.07, 0.49);
	}
	// 7타(막타)
	if (m_dwTime > 3.05 && 10 == m_iSeventhCount)
	{
		++m_iSeventhCount;
		Set_FrameKey(L"RAwakening");
		Set_Frame(tagFrame{ 0, 11, 0, 0.05, 0. });
		if (L"LAwakening" == Get_FrameKey())
			Making_Shadow(L"LAwaken_Black", 1.0f);
		else
			Making_Shadow(L"RAwaken_Black", 1.0f);
		Set_PosY(10.f);
	}
	if (m_dwTime > 3.65 && 11 == m_iSeventhCount)
	{
		Making_Awakening(m_tInfo.fX + 280.f, m_tInfo.fY,
			547.f, 474.f, 0.f, 0.f,
			L"RSeventhFinal", L"-",
			0, 6, 0.07, 0.49, 0, 0, 0, 0);
		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY - 30.f,
			580.f, 250.f,
			L"SeventhFeather4",
			0, 9, 0.07, 0.7);
		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			368.f, 400.f,
			L"SeventhFeather3",
			0, 10, 0.1, 1.1);
	}
}
void CPlayer::DoSeventhR()
{
	if (m_dwTime > 0 && 0 == m_iSeventhCount)
	{
		++m_iSeventhCount;

		// 컷신
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CNonAlpha>::
			Create_Obj(ATT_JUSTEFFECT, false, 400.f, 440.f, 800.f, 260.f, 0.f, 0.f, 0.f, 0.f, 0.8f, 800.f, 260.f, float(Get_TileCollision().bottom),
				0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, L"Cutsin", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 15, 0, 0.05, 0. });


		Set_FrameKey(L"RAwakening");
		Set_Frame(tagFrame{ 0, 9, 0, 0.05, 0. });
		// 잔상 남기기
		if (L"LAwakening" == Get_FrameKey())
			Making_Shadow(L"LAwaken_Black", 1.0f);
		else
			Making_Shadow(L"RAwaken_Black", 1.0f);
		Set_PosX(-20.f);
	}
	// 1타
	if (m_dwTime > 0.5 && 1 == m_iSeventhCount)
	{
		++m_iSeventhCount;

		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			368.f, 400.f,
			L"SeventhFeather3",
			0, 10, 0.07, 0.77);
		Set_Frame(tagFrame{ 0, 3, 1, 0.075, 0. });
		// 잔상 남기기
		if (L"LAwakening" == Get_FrameKey())
			Making_Shadow(L"LAwaken_Black", 1.0f);
		else
			Making_Shadow(L"RAwaken_Black", 1.0f);
		Set_PosX(75.f);
		Set_PosY(-110.f);
		// 왼쪽
		Making_Awakening(m_tInfo.fX + 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 369.f, 400.f,
			L"RSeventhNormal", L"SeventhFeather5",
			0, 5, 0.03, 0.18, 0, 6, 0.07, 0.49);
		// 오른쪽
		Making_Awakening(m_tInfo.fX - 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 167.f, 194.f,
			L"RSeventhNormal", L"SeventhFeather1",
			0, 5, 0.03, 0.18, 0, 8, 0.07, 0.63);
	}
	// 2타
	if (m_dwTime > 0.8 && 2 == m_iSeventhCount)
	{

		++m_iSeventhCount;

		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			368.f, 400.f,
			L"SeventhFeather3",
			0, 10, 0.07, 0.77);
		Set_Frame(tagFrame{ 0, 3, 2, 0.075, 0. });
		// 잔상 남기기
		if (L"LAwakening" == Get_FrameKey())
			Making_Shadow(L"LAwaken_Black", 1.0f);
		else
			Making_Shadow(L"RAwaken_Black", 1.0f);
		Set_PosX(75.f);
		Set_PosY(+220.f);
		// 왼쪽
		Making_Awakening(m_tInfo.fX + 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 167.f, 194.f,
			L"RSeventhNormal", L"SeventhFeather1",
			0, 5, 0.03, 0.18, 0, 8, 0.07, 0.63);
		// 오른쪽
		Making_Awakening(m_tInfo.fX - 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 167.f, 194.f,
			L"RSeventhNormal", L"SeventhFeather1",
			0, 5, 0.03, 0.18, 0, 8, 0.07, 0.63);
	}
	// 3타
	if (m_dwTime > 1.1 && 3 == m_iSeventhCount)
	{
		++m_iSeventhCount;

		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			368.f, 400.f,
			L"SeventhFeather3",
			0, 10, 0.1, 1.1);
		Set_Frame(tagFrame{ 0, 9, 3, 0.03, 0. });
		// 잔상 남기기
		if (L"LAwakening" == Get_FrameKey())
			Making_Shadow(L"LAwaken_Black", 1.0f);
		else
			Making_Shadow(L"RAwaken_Black", 1.0f);
		Set_PosX(75.f);
		Set_PosY(-240.f);
		// 왼쪽
		Making_Awakening(m_tInfo.fX - 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 0.f, 0.f,
			L"RSeventhNormal", L"-",
			0, 5, 0.03, 0.18, 0, 0, 0, 0);

		// 오른쪽
		Making_Awakening(m_tInfo.fX - 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 0.f, 0.f,
			L"RSeventhNormal", L"-",
			0, 5, 0.03, 0.18, 0, 0, 0, 0);
		Making_AwakeningE(m_tInfo.fX - 100.f, m_tInfo.fY + 50.f,
			100.f, 55.f,
			L"SeventhDust1",
			0, 5, 0.07, 0.42);
	}
	// 4타
	if (m_dwTime > 1.4 && 4 == m_iSeventhCount)
	{
		++m_iSeventhCount;

		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			368.f, 400.f,
			L"SeventhFeather3",
			0, 10, 0.1, 1.1);
		Set_Frame(tagFrame{ 0, 3, 4, 0.075, 0. });
		// 잔상 남기기
		if (L"LAwakening" == Get_FrameKey())
			Making_Shadow(L"LAwaken_Black", 1.0f);
		else
			Making_Shadow(L"RAwaken_Black", 1.0f);
		Set_PosX(75.f);
		Set_PosY(+180.f);

		// 왼쪽
		Making_Awakening(m_tInfo.fX + 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 0.f, 0.f,
			L"RSeventhNormal", L"-",
			0, 5, 0.03, 0.18, 0, 0, 0, 0);
		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			167.f, 194.f,
			L"SeventhFeather1",
			0, 8, 0.07, 0.63);
		// 오른쪽
		Making_Awakening(m_tInfo.fX - 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 0.f, 0.f,
			L"RSeventhNormal", L"-",
			0, 5, 0.03, 0.18, 0, 0, 0, 0);
		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			167.f, 194.f,
			L"SeventhFeather1",
			0, 8, 0.07, 0.63);
		// 위쪽
		Making_Awakening(m_tInfo.fX, m_tInfo.fY - 120.f,
			316.f, 274.f, 0.f, 0.f,
			L"RSeventhNormal", L"-",
			0, 5, 0.03, 0.18, 0, 0, 0, 0);
	}
	// 5타
	if (m_dwTime > 1.7 && 5 == m_iSeventhCount)
	{
		++m_iSeventhCount;

		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			368.f, 400.f,
			L"SeventhFeather3",
			0, 10, 0.1, 1.1);
		Set_Frame(tagFrame{ 0, 3, 5, 0.075, 0. });
		// 잔상 남기기
		if (L"LAwakening" == Get_FrameKey())
			Making_Shadow(L"LAwaken_Black", 1.0f);
		else
			Making_Shadow(L"RAwaken_Black", 1.0f);
		Set_PosX(75.f);
		Set_PosY(-200.f);

		// 왼쪽
		Making_AwakeningE(m_tInfo.fX + 100.f, m_tInfo.fY,
			369.f, 400.f,
			L"SeventhFeather5",
			0, 6, 0.07, 0.49);
		// 오른쪽
		Making_Awakening(m_tInfo.fX - 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 0.f, 0.f,
			L"RSeventhNormal", L"-",
			0, 5, 0.03, 0.18, 0, 0, 0, 0);
	}
	if (m_dwTime > 2.0 && 6 == m_iSeventhCount)
	{
		++m_iSeventhCount;

		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			368.f, 400.f,
			L"SeventhFeather3",
			0, 10, 0.1, 1.1);
		Set_FrameKey(L"Player_RIGHT");
		Set_Frame(tagFrame{ 0, 5, 14, 0.075, 0. });
		// 잔상 남기기
		if (L"Player_RIGHT" == Get_FrameKey())
			Making_Shadow(L"Player_RIGHT", 1.0f);
		else
			Making_Shadow(L"Player_LEFT", 1.0f);
		Set_PosY(120.f);
	}
	if (m_dwTime > 2.45 && 7 == m_iSeventhCount)
	{
		++m_iSeventhCount;

		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			368.f, 400.f,
			L"SeventhFeather3",
			0, 10, 0.1, 1.1);
		Set_FrameKey(L"Player_LEFT");
		Set_Frame(tagFrame{ 1, 4, 8, 0.05, 0. });
		// 잔상 남기기
		if (L"Player_RIGHT" == Get_FrameKey())
			Making_Shadow(L"Player_RIGHT", 1.0f);
		else
			Making_Shadow(L"Player_LEFT", 1.0f);
		Set_PosY(-50.f);
		Set_PosX(50.f);

		// 오른쪽
		Making_Awakening(m_tInfo.fX - 155.f, m_tInfo.fY + 60.f,
			337.f, 407.f, 0.f, 0.f,
			L"LSeventhFinalBeforeThree5", L"-",
			0, 6, 0.07, 0.49, 0, 0, 0, 0);
		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			345.f, 304.f,
			L"SeventhFeather2",
			0, 6, 0.07, 0.49);
	}
	if (m_dwTime > 2.65 && 8 == m_iSeventhCount)
	{
		++m_iSeventhCount;

		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			368.f, 400.f,
			L"SeventhFeather3",
			0, 10, 0.1, 1.1);
		Set_PosY(30.f);
		Set_PosX(10.f);

		// 오른쪽
		Making_Awakening(m_tInfo.fX - 155.f, m_tInfo.fY + 60.f,
			337.f, 407.f, 0.f, 0.f,
			L"LSeventhFinalBeforeThree4", L"-",
			0, 6, 0.07, 0.49, 0, 0, 0, 0);
		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			345.f, 304.f,
			L"SeventhFeather2",
			0, 6, 0.07, 0.49);
	}
	if (m_dwTime > 2.85 && 9 == m_iSeventhCount)
	{
		++m_iSeventhCount;

		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			368.f, 400.f,
			L"SeventhFeather3",
			0, 10, 0.1, 1.1);
		Set_PosY(30.f);
		Set_PosX(10.f);

		// 오른쪽
		Making_Awakening(m_tInfo.fX - 155.f, m_tInfo.fY + 80.f,
			337.f, 407.f, 0.f, 0.f,
			L"LSeventhFinalBeforeThree3", L"-",
			0, 6, 0.07, 0.49, 0, 0, 0, 0);
		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			345.f, 304.f,
			L"SeventhFeather2",
			0, 6, 0.07, 0.49);
	}
	// 7타(막타)
	if (m_dwTime > 3.05 && 10 == m_iSeventhCount)
	{
		++m_iSeventhCount;
		Set_FrameKey(L"LAwakening");
		Set_Frame(tagFrame{ 0, 11, 0, 0.05, 0. });
		// 잔상 남기기
		if (L"LAwakening" == Get_FrameKey())
			Making_Shadow(L"LAwaken_Black", 1.0f);
		else
			Making_Shadow(L"RAwaken_Black", 1.0f);
		Set_PosY(10.f);
		
	}
	if (m_dwTime > 3.65 && 11 == m_iSeventhCount)
	{
		Making_Awakening(m_tInfo.fX - 280.f, m_tInfo.fY,
			547.f, 474.f, 0.f, 0.f,
			L"LSeventhFinal", L"-",
			0, 6, 0.07, 0.49, 0, 0, 0, 0);
		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY - 30.f,
			580.f, 250.f,
			L"SeventhFeather4",
			0, 9, 0.07, 0.7);
		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			368.f, 400.f,
			L"SeventhFeather3",
			0, 10, 0.1, 1.1);
	}
}
