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
	// �÷��̾� �������ͽ�
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

	// ����, ����
	m_tInfo.fAtk = 358.f;
	m_tInfo.fDef = 38976.f;

	// ����, ����
	m_tInfo.fMAtk = 2462.f;
	m_tInfo.fMDef = 41711.f;

	// ��, ����
	m_tInfo.fStrength = 3736.f;
	m_tInfo.fAtkSpeed = 77.3214f;

	// ü��, �̼�
	m_tInfo.fHealth = 2853.f;
	m_tInfo.fMoveSpeed = 67.2f;

	// ȭ, ��, ��, ��
	m_tInfo.fFire		= 31.f;
	m_tInfo.fWater		= 21.f;
	m_tInfo.fLightness	= 21.f;
	m_tInfo.fDarkness	= 21.f;

	// �׸���
	m_tInfo.fExorcism = 5821.f;

	// Ÿ���浹 Rect ũ��
	m_fTileCollisionSizeX = 64.f;
	m_fTileCollisionSizeY = 64.f;

	// �ǰ� Rect ũ��
	m_fCollisionSizeX = 54.f;
	m_fCollisionSizeY = 140.f;

	// �ִϸ��̼�
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

	// �����¿� ���� ���� �̹��� �ҷ�����
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/LPlayer.bmp", L"Player_LEFT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/RPlayer.bmp", L"Player_RIGHT");

	// �÷��̾� �ܻ�
	// CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/LPlayer2.bmp", L"LPlayer_Black");
	// CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/RPlayer2.bmp", L"RPlayer_Black");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/������/L������/L����2.bmp", L"LAwaken_Black");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/������/R������/R����2.bmp", L"RAwaken_Black");

	// �÷��̾� �׸���
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Shadow.bmp", L"Shadow");

	// ============================ < Player Attack & Skill > ============================
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/�Ϲݰ���/BulletLeft.bmp", L"LBullet");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/�Ϲݰ���/BulletRight.bmp", L"RBullet");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/�Ϲݰ���/BulletLowLeft.bmp", L"LBullet_Low");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/�Ϲݰ���/BulletLowRight.bmp", L"RBullet_Low");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/�⺻ ����/LSFiringEffect.bmp", L"LSFiringEffect");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/�⺻ ����/RSFiringEffect.bmp", L"RSFiringEffect");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/�⺻ ����/LFiringEffect.bmp", L"LFiringEffect");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/�⺻ ����/RFiringEffect.bmp", L"RFiringEffect");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/�轺����ũ/ZackSpikeLeft.bmp", L"LZacks");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/�轺����ũ/ZackSpikeRight.bmp", L"RZacks");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/�����/Windmill.bmp", L"Windmill");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/�����/WindmillDust.bmp", L"WindmillDust");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/����ű/LMaha.bmp", L"LMaha");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/����ű/RMaha.bmp", L"RMaha");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/��弦/LSConflictEffect.bmp", L"LSConflictEffect");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/��弦/RSConflictEffect.bmp", L"RSConflictEffect");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/��弦/LHeadShot.bmp", L"LHeadShot");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/��弦/LHeadConflictEffect.bmp", L"LHeadConflictEffect");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/��弦/LHeadShootHit.bmp", L"LHeadShootHit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/��弦/LHeadShootNormal.bmp", L"LHeadShootNormal");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/��弦/RHeadShot.bmp", L"RHeadShot");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/��弦/RHeadConflictEffect.bmp", L"RHeadConflictEffect");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/��弦/RHeadShootHit.bmp", L"RHeadShootHit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/��弦/RHeadShootNormal.bmp", L"RHeadShootNormal");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/����/L_Random_Fire3.bmp", L"LSpree");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/����/R_Random_Fire2.bmp", L"RSpree");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/����/LD_Random_Fire2.bmp", L"LDSpree");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/����/RD_Random_Fire2.bmp", L"RDSpree");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/����/LDD_Random_Fire2.bmp", L"LDDSpree");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/����/RDD_Random_Fire2.bmp", L"RDDSpree");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/����/LU_Random_Fire2.bmp", L"LUSpree");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/����/RU_Random_Fire2.bmp", L"RUSpree");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/������/L������/L����1.bmp", L"LAwakening");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/������/R������/R����1.bmp", L"RAwakening");
	
	// �������̸�����
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/�������̸�����/DeathByRevolver3.bmp", L"DeathByRevolver2");
	// ��Ʋ����Ʈ��
	// CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/��Ʋ����Ʈ��/Satelaser/CutIn_Buff2.bmp", L"CutIn_Buff");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/��Ʋ����Ʈ��/Satelaser/Satelaser_Core3.bmp", L"Satelaser_Core");
	// CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/��Ʋ����Ʈ��/Satelaser/Satelaser_CrashRemaster.bmp", L"Satelaser_CrashRemaster");
	// CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/��Ʋ����Ʈ��/Satelaser/Satelaser_Sub.bmp", L"Satelaser_Sub");
	// CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/��Ʋ����Ʈ��/Satelaser/Satelaser_Target.bmp", L"Satelaser_Target");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/������/L������/LSeventhFinal.bmp", L"LSeventhFinal");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/������/L������/LSeventhFinalBeforeThree3.bmp", L"LSeventhFinalBeforeThree3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/������/L������/LSeventhFinalBeforeThree4.bmp", L"LSeventhFinalBeforeThree4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/������/L������/LSeventhFinalBeforeThree5.bmp", L"LSeventhFinalBeforeThree5");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/������/L������/LSeventhNormal.bmp", L"LSeventhNormal");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/������/R������/RSeventhFinal.bmp", L"RSeventhFinal");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/������/R������/RSeventhFinalBeforeThree3.bmp", L"RSeventhFinalBeforeThree3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/������/R������/RSeventhFinalBeforeThree4.bmp", L"RSeventhFinalBeforeThree4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/������/R������/RSeventhFinalBeforeThree5.bmp", L"RSeventhFinalBeforeThree5");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/������/R������/RSeventhNormal.bmp", L"RSeventhNormal");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/������/SeventhDust.bmp", L"SeventhDust");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/������/SeventhDust1.bmp", L"SeventhDust1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/������/SeventhFeather1.bmp", L"SeventhFeather1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/������/SeventhFeather2.bmp", L"SeventhFeather2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/������/SeventhFeather3.bmp", L"SeventhFeather3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/������/SeventhFeather4.bmp", L"SeventhFeather4");

	// ============================ < ��ų ������ > ============================
	// ȸ�� ������(��Ÿ�ӿ�)
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/���� ��ų ������/BZack.bmp", L"BZack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/���� ��ų ������/WindMill_Off.bmp", L"WindMill_Off");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/���� ��ų ������/MahaKick_Off.bmp", L"MahaKick_Off");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/���� ��ų ������/HeadShoot_Off.bmp", L"HeadShoot_Off");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/���� ��ų ������/Moving_Shoot_Off.bmp", L"Moving_Shoot_Off");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/���� ��ų ������/Random_Shoot_Off.bmp", L"Random_Shoot_Off");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/���� ��ų ������/Seven'sFlow_Off.bmp", L"Seven'sFlow_Off");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/���� ��ų ������/DBR.bmp", L"DBR");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/���� ��ų ������/GunGuard.bmp", L"GunGuard");

	// �Ϲ� ������
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/���� ��ų ������/Zack2.bmp", L"Zack2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/���� ��ų ������/Icon_Satelaser.bmp", L"Icon_Satelaser");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/������/Cutsin.bmp", L"Cutsin"); // ������ �ƽ�
}

void CPlayer::Update_Rect()
{
	// ������Ʈ ���� ũ�� ������Ʈ
	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));

	// �÷��̾� �浹ü ������Ʈ
	m_tRectCollision.left = LONG(m_tInfo.fX - (m_fCollisionSizeX * 0.5f));
	m_tRectCollision.top = LONG(m_tInfo.fY + (m_fCollisionSizeY * 0.5f) - m_fCollisionSizeY);
	m_tRectCollision.right = LONG(m_tInfo.fX + (m_fCollisionSizeX * 0.5f));
	m_tRectCollision.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));

	m_lRectCollisionCenter = { m_tRectCollision.left + LONG(m_fCollisionSizeX * 0.5f),
							m_tRectCollision.top + LONG(m_fCollisionSizeY * 0.5f) };

	// �÷��̾� - Ÿ�� �浹�� ������Ʈ
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
	// �ð��� �帧�� ���� ������ ��ȭ
	if (m_tFrame.dwSpeed < m_tFrame.dwTime)
	{
		// ���ư��� �ǰݸ���� ������ ��� ����
		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd && m_ePlayerState == PS_LEVITATE_ATTACKED)
		{
			m_tFrame.iFrameStart = 4;
		}

		// if���� �ѹ� ���� ������ ������ ��ȭ�� ��
		++m_tFrame.iFrameStart;

		// ����ؼ� ��Ÿ Ÿ�� ����
		m_tFrame.dwTime = 0;

		// ��������Ʈ ���� �����ϸ� ù ��������Ʈ�� ���ư�
		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
	}
}

int CPlayer::Update()
{
	m_eRender = GAMEOBJECT;
	m_dwTime += CTimeMgr::Get_Instance()->GetfDT();
	m_tFrame.dwTime += CTimeMgr::Get_Instance()->GetfDT();

	// ȸ������ ��Ÿ��
	m_HpCoolTime += CTimeMgr::Get_Instance()->GetfDT();
	m_MpCoolTime += CTimeMgr::Get_Instance()->GetfDT();

	if (0 >= m_tInfo.fHp && PS_DEAD != m_ePlayerState)
	{
		CSoundMgr::Get_Instance()->PlaySoundW(L"gn_death.wav", SOUND_EFFECT, g_fVolume);
		m_ePlayerState = PS_DEAD;
	}

	// ��ų ��Ÿ�� üũ
	Cool_Check();
	DBR_Check();
	GunGuard_Check();

	// �׷α� ���� �ð� üũ
	if (m_bBuff)
		GrogyBuff_Check();

	Key_Input();
	Motion_Change();
	Update_Rect();

   return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
	// �ǰݽÿ��� �ǰ��浹�� ó���ϵ��� ����ȭ
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

	// �浹 �׽�Ʈ�� ��Ʈ
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	// ��Ʈ üũ��
	/*Rectangle(hDC, m_tRectCollision.left + fScrollX, m_tRectCollision.top + fScrollY,
		m_tRectCollision.right + fScrollX, m_tRectCollision.bottom + fScrollY);

	Rectangle(hDC, m_tRect.left + fScrollX, m_tRect.top + fScrollY,
		m_tRect.right + fScrollX, m_tRect.bottom + fScrollY);

	Rectangle(hDC, m_tTileCollision.left + fScrollX, m_tTileCollision.top + fScrollY,
		m_tTileCollision.right + fScrollX, m_tTileCollision.bottom + fScrollY);*/

	// ��Ʈ
	HFONT font = CreateFont(18, 0, 0, 0, 850, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
		VARIABLE_PITCH | FF_ROMAN, L"���� ���");
	HFONT oldfont = (HFONT)SelectObject(hDC, font);

	// �̵���� �߼� ǥ��
	if (PS_MOVINGSHOT == m_ePlayerState)
	{
		SetTextColor(hDC, RGB(0, 0, 0));
		SetBkMode(hDC, TRANSPARENT); // �Ű����� DC�� ���ڹ���� �����ϰ� �Ѵ�. 
		SetTextAlign(hDC, TA_LEFT);
		TextOut(hDC, m_tRectCollision.right + fScrollX - 10, m_tRectCollision.top + fScrollY, to_wstring(22 - m_iMovingShotCount).c_str(), (to_wstring(22 - m_iMovingShotCount)).size());
		SetBkMode(hDC, OPAQUE);
	}
	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkMode(hDC, TRANSPARENT); // �Ű����� DC�� ���ڹ���� �����ϰ� �Ѵ�. 
	SetTextAlign(hDC, TA_CENTER);
	TextOut(hDC, m_tRectCollision.left + (Get_RectCollisionSizeX() * 0.5f) + fScrollX + 3, m_tRectCollision.top + fScrollY + 3,
		L"��Źڵ���", 6);
	SetBkMode(hDC, OPAQUE);

	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkMode(hDC, TRANSPARENT); // �Ű����� DC�� ���ڹ���� �����ϰ� �Ѵ�. 
	SetTextAlign(hDC, TA_CENTER);
	TextOut(hDC, m_tRectCollision.left + (Get_RectCollisionSizeX() * 0.5f) + fScrollX + 2, m_tRectCollision.top + fScrollY + 2,
			L"��Źڵ���", 6);
	SetBkMode(hDC, OPAQUE);

	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkMode(hDC, TRANSPARENT); // �Ű����� DC�� ���ڹ���� �����ϰ� �Ѵ�. 
	SetTextAlign(hDC, TA_LEFT);

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);

	// ���� ���� �׸���
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
	

	// �÷��̾� �̹��� ���
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
	// ���� ����
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

	// �� ���� ����Ű
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
		// �޸��� �߿� XŰ�� ������ �����̵�
		if (m_ePlayerState == PS_LRUN && CKeyMgr::Get_Instance()->Key_Pressing('X'))
		{
			m_lSlideTime = GetTickCount();
			m_pFrameKey = L"Player_LEFT";
			m_eDir = DIR_LEFT;
			m_fSlideSpeed = 4.0f;
			m_ePlayerState = PS_LSLIDE;
			CSoundMgr::Get_Instance()->PlaySoundW(L"gn_sliding_03.wav", SOUND_EFFECT, g_fVolume);
		}

		// ���� ����Ű�� �����µ� �������϶�
		if (m_ePlayerState == PS_JUMP)
		{
			m_pFrameKey = L"Player_LEFT";
			m_eDir = DIR_LEFT;
			m_tInfo.fX -= 1.2f * m_fSpeed;
			m_tTileCollision.left -= LONG(1.2f * m_fSpeed);
			m_tTileCollision.right -= LONG(1.2f * m_fSpeed);
		}
		// ���� ����Ű�� �����µ� �������϶�
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
		// �� �� �����ٰ� ���µ� �޸��� ���̿��� �� ����
		if (m_ePlayerState == PS_LRUN)
			m_ePlayerState = PS_IDLE;

		m_fLRunReadyTime = GetTickCount();
		m_pFrameKey = L"Player_LEFT";
		m_eDir = DIR_LEFT;
	}

	// �� ������ ����Ű
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
		// �޸��� �߿� XŰ�� ������ �����̵�
		if (m_ePlayerState == PS_RRUN && CKeyMgr::Get_Instance()->Key_Pressing('X'))
		{
			m_lSlideTime = GetTickCount();
			m_pFrameKey = L"Player_RIGHT";
			m_eDir = DIR_RIGHT;
			m_fSlideSpeed = 4.0f;
			m_ePlayerState = PS_RSLIDE;
			CSoundMgr::Get_Instance()->PlaySoundW(L"gn_sliding_03.wav", SOUND_EFFECT, g_fVolume);
		}

		// ������ ����Ű�� �����µ� �������϶�
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
		// �� �� �����ٰ� ���µ� �޸��� ���̿��� �� ����
		if (m_ePlayerState == PS_RRUN)
			m_ePlayerState = PS_IDLE;

		m_fRRunReadyTime = GetTickCount();
		m_pFrameKey = L"Player_RIGHT";
		m_eDir = DIR_RIGHT;
	}

	// �� �� ����Ű
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP)
		&& (m_ePlayerState != PS_NORMAL_ATTACKED && m_ePlayerState != PS_THRUST_ATTACKED && m_ePlayerState != PS_LEVITATE_ATTACKED))
	{
		// �� �� �����µ� �������� �ȴ� ���϶�
		if (m_ePlayerState == PS_LWALK)
		{
			m_tInfo.fY -= 0.7f * m_fSpeed;
		}
		// �� �� �����µ� ���������� �ȴ� ���϶�
		else if (m_ePlayerState == PS_RWALK)
		{
			m_tInfo.fY -= 0.7f * m_fSpeed;
		}
		// �� �� �����µ� �������� �ٴ� ���϶�
		else if (m_ePlayerState == PS_LRUN)
		{
			m_tInfo.fY -= 0.7f * m_fSpeed;
		}
		// �� �� �����µ� ���������� �ٴ� ���϶�
		else if (m_ePlayerState == PS_RRUN)
		{
			m_tInfo.fY -= 0.7f * m_fSpeed;
		}
		// �� �� �����µ� ���� ���϶�
		else if (m_ePlayerState == PS_JUMP)
		{
			m_tInfo.fY -= 0.1f * m_fSpeed;
			m_tTileCollision.top -= 0.1f * m_fSpeed;
			m_tTileCollision.bottom -= 0.1f * m_fSpeed;
		}

		// ���� ��Ȳ�鿡 ������ �����鼭 ����, �����̵�, ��ų(�߰�����)������� �ƴϰ�, ������ �ٶ󺸰� �־��� ���. ���� �׳� �ȱ�
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

	// �� �Ʒ� ����Ű
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN)
		&& (m_ePlayerState != PS_NORMAL_ATTACKED && m_ePlayerState != PS_THRUST_ATTACKED && m_ePlayerState != PS_LEVITATE_ATTACKED))
	{
		// �� �� �����µ� �������� �ȴ� ���϶�
		if (m_ePlayerState == PS_LWALK)
		{
			m_tInfo.fY += 0.7f * m_fSpeed;
		}
		// �� �� �����µ� ���������� �ȴ� ���϶�
		else if (m_ePlayerState == PS_RWALK)
		{
			m_tInfo.fY += 0.7f * m_fSpeed;
		}
		// �� �� �����µ� �������� �ٴ� ���϶�
		else if (m_ePlayerState == PS_LRUN)
		{
			m_tInfo.fY += 0.7f * m_fSpeed;
		}
		// �� �� �����µ� ���������� �ٴ� ���϶�
		else if (m_ePlayerState == PS_RRUN)
		{
			m_tInfo.fY += 0.7f * m_fSpeed;
		}
		// �� �� �����µ� ���� ���϶�
		else if (m_ePlayerState == PS_JUMP)
		{
			m_tInfo.fY += 0.1f * m_fSpeed;
			m_tTileCollision.top += 0.2f * m_fSpeed;
			m_tTileCollision.bottom += 0.2f * m_fSpeed;
		}

		// ���� ��Ȳ�鿡 ������ �����鼭 ����, �����̵�, ��ų(�߰�����)������� �ƴ� ��, �Ʒ��� �׳� �ȱ�
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

	// BackSpace �޴��� ������
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_BACK))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_LOGO);
		return;
	}

	// C ����Ű
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

	// X ����Ű
	if (CKeyMgr::Get_Instance()->Key_Pressing('X') && (m_ePlayerState != PS_LSLIDE && m_ePlayerState != PS_RSLIDE && m_ePlayerState != PS_ATTACK5)
		&& (m_ePlayerState != PS_NORMAL_ATTACKED && m_ePlayerState != PS_THRUST_ATTACKED && m_ePlayerState != PS_LEVITATE_ATTACKED)
		&& (m_ePlayerState != PS_ZACKS && m_ePlayerState != PS_WINDMILL && m_ePlayerState != PS_MAHA)
		&& (m_ePlayerState != PS_DBR && m_ePlayerState != PS_GUNGUARD && m_ePlayerState != PS_HEADSHOT && m_ePlayerState != PS_MOVINGSHOT && m_ePlayerState != PS_SPREE)
		&& (m_ePlayerState != PS_AWAKEN && m_ePlayerState != PS_LAWAKENING && m_ePlayerState != PS_RAWAKENING)
		&& m_ePlayerState != PS_SATELITE && m_ePlayerState != PS_DEAD)
	{
		// 1Ÿ
		if ((m_ePlayerState == PS_IDLE || m_ePlayerState == PS_LWALK || m_ePlayerState == PS_RWALK) && (m_ePlayerState != PS_LRUN || m_ePlayerState != PS_RRUN))
		{
			// �Ʒ� ��Ÿ
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
		// 2Ÿ
		else if ((m_ePlayerState == PS_ATTACK1 && m_dwTime > 0.245)  
				|| (m_ePlayerState == PS_DATTACK1 && m_dwTime > 0.21))
		{
			// �Ʒ� ��Ÿ
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
		// 3Ÿ
		else if ((m_ePlayerState == PS_ATTACK2 && m_dwTime > 0.245) 
				|| (m_ePlayerState == PS_DATTACK2 && m_dwTime > 0.21))
		{
			// �Ʒ� ��Ÿ
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
		// 4Ÿ
		else if ((m_ePlayerState == PS_ATTACK3 && m_dwTime > 0.245) 
			|| (m_ePlayerState == PS_DATTACK3 && m_dwTime > 0.21))
		{
			// �Ʒ� ��Ÿ
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
		// 5Ÿ
		else if ((m_ePlayerState == PS_ATTACK4 && m_dwTime > 0.300) 
				|| (m_ePlayerState == PS_DATTACK4 && m_dwTime > 0.300))
		{
			// �Ʒ� ��Ÿ
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
		// ����
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

	// SPACE ���� ���� ������
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE) && MANA_DBR < m_tInfo.fMp && COOL_DBR < m_DBRCool
		&& (m_ePlayerState != PS_NORMAL_ATTACKED && m_ePlayerState != PS_THRUST_ATTACKED && m_ePlayerState != PS_LEVITATE_ATTACKED)
		&& (m_ePlayerState != PS_LSLIDE && m_ePlayerState != PS_RSLIDE)
		&& (m_ePlayerState != PS_JUMP && m_ePlayerState != PS_JUMPATTACK)
		&& (m_ePlayerState != PS_ZACKS && m_ePlayerState != PS_WINDMILL && m_ePlayerState != PS_MAHA)
		&& (m_ePlayerState != PS_GUNGUARD && m_ePlayerState != PS_DBR && m_ePlayerState != PS_HEADSHOT && m_ePlayerState != PS_MOVINGSHOT && m_ePlayerState != PS_SPREE)
		&& (m_ePlayerState != PS_AWAKEN && m_ePlayerState != PS_LAWAKENING && m_ePlayerState != PS_RAWAKENING)
		&& m_ePlayerState != PS_SATELITE && m_ePlayerState != PS_DEAD)
	{
		// ���ٸ� ȿ�� : ���ݷ� + 300, ũ��Ȯ�� + 50%
		Set_DBR(true);
		m_tInfo.fAtk += 300;
		Set_CriRatio(50);

		// ���ٸ� ������
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

	// E �ǰ���
	if (CKeyMgr::Get_Instance()->Key_Pressing('E') && MANA_GUNGUARD < m_tInfo.fMp && COOL_GUNGUARD < m_GunGuardCool
		&& (m_ePlayerState != PS_NORMAL_ATTACKED && m_ePlayerState != PS_THRUST_ATTACKED && m_ePlayerState != PS_LEVITATE_ATTACKED)
		&& (m_ePlayerState != PS_LSLIDE && m_ePlayerState != PS_RSLIDE)
		&& (m_ePlayerState != PS_JUMP && m_ePlayerState != PS_JUMPATTACK)
		&& (m_ePlayerState != PS_ZACKS && m_ePlayerState != PS_WINDMILL && m_ePlayerState != PS_MAHA)
		&& (m_ePlayerState != PS_GUNGUARD && m_ePlayerState != PS_DBR && m_ePlayerState != PS_HEADSHOT && m_ePlayerState != PS_MOVINGSHOT && m_ePlayerState != PS_SPREE)
		&& (m_ePlayerState != PS_AWAKEN && m_ePlayerState != PS_LAWAKENING && m_ePlayerState != PS_RAWAKENING)
		&& m_ePlayerState != PS_SATELITE && m_ePlayerState != PS_DEAD)
	{
		// �ǰ��� ȿ�� : 1�ʰ� ����
		Set_GunGuard(true);
		Set_IsImmune(true);

		// CSoundMgr::Get_Instance()->PlaySoundW(L"revolver.wav", SOUND_EFFECT, g_fVolume);
		m_ePlayerState = PS_GUNGUARD;
		Take_Mana(MANA_GUNGUARD);
		SkillCool_Making(612.f, 532.f, (float)COOL_GUNGUARD, L"GunGuard");
		m_GunGuardCool = 0;
		m_dwTime = 0;
	}

	// Z �轺����ũ
	if (CKeyMgr::Get_Instance()->Key_Pressing('Z') && MANA_ZACKS < m_tInfo.fMp && COOL_ZACKS < m_ZacksCool
		&& (m_ePlayerState != PS_NORMAL_ATTACKED && m_ePlayerState != PS_THRUST_ATTACKED && m_ePlayerState != PS_LEVITATE_ATTACKED)
		&& (m_ePlayerState != PS_LSLIDE && m_ePlayerState != PS_RSLIDE)
		&& (m_ePlayerState != PS_JUMP && m_ePlayerState != PS_JUMPATTACK)
		&& (m_ePlayerState != PS_ZACKS && m_ePlayerState != PS_MAHA)
		&& (m_ePlayerState != PS_DBR && m_ePlayerState != PS_GUNGUARD && m_ePlayerState != PS_HEADSHOT && m_ePlayerState != PS_MOVINGSHOT && m_ePlayerState != PS_SPREE)
		&& (m_ePlayerState != PS_AWAKEN && m_ePlayerState != PS_LAWAKENING && m_ePlayerState != PS_RAWAKENING)
		&& m_ePlayerState != PS_SATELITE && m_ePlayerState != PS_DEAD)
	{
		// �ܻ� - ��Ÿ�� ��Ÿ�ϸ��� ��ų�� �������� �轺����ũ ������
		if (((m_ePlayerState == PS_ATTACK1 || m_ePlayerState == PS_ATTACK2 || m_ePlayerState == PS_ATTACK3 || m_ePlayerState == PS_ATTACK4 || m_ePlayerState == PS_ATTACK5)
			|| (m_ePlayerState == PS_DATTACK1 || m_ePlayerState == PS_DATTACK2 || m_ePlayerState == PS_DATTACK3 || m_ePlayerState == PS_DATTACK4 || m_ePlayerState == PS_DATTACK5)
			&& 0.245 > m_dwTime)
			|| (m_ePlayerState == PS_WINDMILL || m_ePlayerState == PS_MAHA || m_ePlayerState == PS_HEADSHOT))
		{
			CObjMgr::Get_Instance()->Delete_ID(OBJ_EFFECT);

			// �ܻ� �����
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

	// S �����
	if (CKeyMgr::Get_Instance()->Key_Pressing('S') && MANA_WINDMILL < m_tInfo.fMp && COOL_WINDMILL < m_WindmillCool
		&& (m_ePlayerState != PS_NORMAL_ATTACKED && m_ePlayerState != PS_THRUST_ATTACKED && m_ePlayerState != PS_LEVITATE_ATTACKED)
		&& (m_ePlayerState != PS_LSLIDE && m_ePlayerState != PS_RSLIDE)
		&& (m_ePlayerState != PS_JUMP && m_ePlayerState != PS_JUMPATTACK)
		&& (m_ePlayerState != PS_DBR && m_ePlayerState != PS_GUNGUARD && m_ePlayerState != PS_WINDMILL)
		&& (m_ePlayerState != PS_MOVINGSHOT && m_ePlayerState != PS_SPREE)
		&& (m_ePlayerState != PS_AWAKEN && m_ePlayerState != PS_LAWAKENING && m_ePlayerState != PS_RAWAKENING)
		&& m_ePlayerState != PS_SATELITE && m_ePlayerState != PS_DEAD)
	{
		// Ʈ���� Ŭ��ġ - ��Ÿ ����߿� ����� ����
		// �ܻ� - ��Ÿ�� ��Ÿ�ϸ��� ��ų�� �������� ���� ������
		if (((m_ePlayerState == PS_ATTACK1 || m_ePlayerState == PS_ATTACK2 || m_ePlayerState == PS_ATTACK3 || m_ePlayerState == PS_ATTACK4 || m_ePlayerState == PS_ATTACK5)
			|| (m_ePlayerState == PS_DATTACK1 || m_ePlayerState == PS_DATTACK2 || m_ePlayerState == PS_DATTACK3 || m_ePlayerState == PS_DATTACK4 || m_ePlayerState == PS_DATTACK5)
			&& 0.245 > m_dwTime)
			|| (m_ePlayerState == PS_ZACKS || m_ePlayerState == PS_MAHA || m_ePlayerState == PS_HEADSHOT))
		{
			CObjMgr::Get_Instance()->Delete_ID(OBJ_EFFECT);

			// �ܻ� �����
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

	// D ����ű
	if (CKeyMgr::Get_Instance()->Key_Pressing('D') && MANA_MAHA < m_tInfo.fMp && COOL_MAHA < m_MahaCool
		&& (m_ePlayerState != PS_NORMAL_ATTACKED && m_ePlayerState != PS_THRUST_ATTACKED && m_ePlayerState != PS_LEVITATE_ATTACKED)
		&& (m_ePlayerState != PS_LSLIDE && m_ePlayerState != PS_RSLIDE)
		&& (m_ePlayerState != PS_JUMP && m_ePlayerState != PS_JUMPATTACK)
		&& (m_ePlayerState != PS_DBR && m_ePlayerState != PS_GUNGUARD && m_ePlayerState != PS_MAHA)
		&& (m_ePlayerState != PS_MOVINGSHOT && m_ePlayerState != PS_SPREE)
		&& (m_ePlayerState != PS_AWAKEN && m_ePlayerState != PS_LAWAKENING && m_ePlayerState != PS_RAWAKENING)
		&& m_ePlayerState != PS_SATELITE && m_ePlayerState != PS_DEAD)
	{
		// Ʈ���� Ŭ��ġ - ������̳� ��Ÿ ����߿� ����ű ����
		// �ܻ� - ��Ÿ�� ��Ÿ�ϸ��� ��ų�� �������� ���� ������
		if (((m_ePlayerState == PS_ATTACK1 || m_ePlayerState == PS_ATTACK2 || m_ePlayerState == PS_ATTACK3 || m_ePlayerState == PS_ATTACK4 || m_ePlayerState == PS_ATTACK5)
			|| (m_ePlayerState == PS_DATTACK1 || m_ePlayerState == PS_DATTACK2 || m_ePlayerState == PS_DATTACK3 || m_ePlayerState == PS_DATTACK4 || m_ePlayerState == PS_DATTACK5)
			&& 0.245 > m_dwTime)
			|| (m_ePlayerState == PS_ZACKS || m_ePlayerState == PS_WINDMILL || m_ePlayerState == PS_HEADSHOT))
		{
			// �� ���� �ΰ��� ����Ʈ�� �����(����� ����Ʈ)
			CObjMgr::Get_Instance()->Delete_ID(OBJ_EFFECT);
			
			// �ܻ� �����
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

	// A ��弦
	if (CKeyMgr::Get_Instance()->Key_Pressing('A') && MANA_HEADSHOT < m_tInfo.fMp && COOL_HEADSHOT < m_HeadShotCool
		&& (m_ePlayerState != PS_NORMAL_ATTACKED && m_ePlayerState != PS_THRUST_ATTACKED && m_ePlayerState != PS_LEVITATE_ATTACKED)
		&& (m_ePlayerState != PS_LSLIDE && m_ePlayerState != PS_RSLIDE)
		&& (m_ePlayerState != PS_JUMP && m_ePlayerState != PS_JUMPATTACK)
		&& (m_ePlayerState != PS_DBR && m_ePlayerState != PS_GUNGUARD && m_ePlayerState != PS_HEADSHOT && m_ePlayerState != PS_MOVINGSHOT && m_ePlayerState != PS_SPREE)
		&& (m_ePlayerState != PS_AWAKEN && m_ePlayerState != PS_LAWAKENING && m_ePlayerState != PS_RAWAKENING)
		&& m_ePlayerState != PS_SATELITE && m_ePlayerState != PS_DEAD)
	{
		// Ʈ���� Ŭ��ġ - ����ű�̳� ��Ÿ �����߿� ��弦 ������
		// �ܻ� - ��Ÿ�� ��Ÿ�ϸ��� ��ų�� �������� ���� ������
		if (((m_ePlayerState == PS_ATTACK1 || m_ePlayerState == PS_ATTACK2 || m_ePlayerState == PS_ATTACK3 || m_ePlayerState == PS_ATTACK4 || m_ePlayerState == PS_ATTACK5)
			|| (m_ePlayerState == PS_DATTACK1 || m_ePlayerState == PS_DATTACK2 || m_ePlayerState == PS_DATTACK3 || m_ePlayerState == PS_DATTACK4 || m_ePlayerState == PS_DATTACK5)
			&& 0.245 > m_dwTime)
			|| (m_ePlayerState == PS_ZACKS || m_ePlayerState == PS_WINDMILL || m_ePlayerState == PS_MAHA))
		{
			// �� ���� �ΰ��� ����Ʈ�� �����(����ű ����Ʈ)
			CObjMgr::Get_Instance()->Delete_ID(OBJ_EFFECT);

			// �ܻ� �����
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

	// R �̵����
	if (CKeyMgr::Get_Instance()->Key_Pressing('R') && MANA_MOVINGSHOT < m_tInfo.fMp && COOL_MOVINGSHOT < m_MovingShotCool
		&& (m_ePlayerState != PS_NORMAL_ATTACKED && m_ePlayerState != PS_THRUST_ATTACKED && m_ePlayerState != PS_LEVITATE_ATTACKED)
		&& (m_ePlayerState != PS_LSLIDE && m_ePlayerState != PS_RSLIDE)
		&& (m_ePlayerState != PS_JUMP && m_ePlayerState != PS_JUMPATTACK)
		&& (m_ePlayerState != PS_DBR && m_ePlayerState != PS_GUNGUARD && m_ePlayerState != PS_MOVINGSHOT && m_ePlayerState != PS_SPREE)
		&& (m_ePlayerState != PS_AWAKEN && m_ePlayerState != PS_LAWAKENING && m_ePlayerState != PS_RAWAKENING)
		&& m_ePlayerState != PS_SATELITE && m_ePlayerState != PS_DEAD)
	{
		// �ܻ� - ��Ÿ�� ��Ÿ�ϸ��� �������� �̵���� ������
		// �ܻ� - ��Ÿ�� ��Ÿ�ϸ��� ��ų�� �������� ���� ������
		if (((m_ePlayerState == PS_ATTACK1 || m_ePlayerState == PS_ATTACK2 || m_ePlayerState == PS_ATTACK3 || m_ePlayerState == PS_ATTACK4 || m_ePlayerState == PS_ATTACK5)
			|| (m_ePlayerState == PS_DATTACK1 || m_ePlayerState == PS_DATTACK2 || m_ePlayerState == PS_DATTACK3 || m_ePlayerState == PS_DATTACK4 || m_ePlayerState == PS_DATTACK5)
			&& 0.245 > m_dwTime)
			|| (m_ePlayerState == PS_ZACKS || m_ePlayerState == PS_WINDMILL || m_ePlayerState == PS_MAHA || m_ePlayerState == PS_HEADSHOT))
		{
			// �� ���� �ΰ��� ����Ʈ�� �����(����� ����Ʈ)
			CObjMgr::Get_Instance()->Delete_ID(OBJ_EFFECT);

			// �ܻ� �����
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

	// F ����
	if (CKeyMgr::Get_Instance()->Key_Pressing('F') && MANA_SPREE < m_tInfo.fMp && COOL_SPREE < m_SpreeCool
		&& (m_ePlayerState != PS_NORMAL_ATTACKED && m_ePlayerState != PS_THRUST_ATTACKED && m_ePlayerState != PS_LEVITATE_ATTACKED)
		&& (m_ePlayerState != PS_LSLIDE && m_ePlayerState != PS_RSLIDE)
		&& (m_ePlayerState != PS_JUMP && m_ePlayerState != PS_JUMPATTACK)
		&& (m_ePlayerState != PS_DBR && m_ePlayerState != PS_GUNGUARD && m_ePlayerState != PS_MOVINGSHOT && m_ePlayerState != PS_SPREE)
		&& (m_ePlayerState != PS_AWAKEN && m_ePlayerState != PS_LAWAKENING && m_ePlayerState != PS_RAWAKENING)
		&& m_ePlayerState != PS_SATELITE && m_ePlayerState != PS_DEAD)
	{
		// �ܻ� - ��Ÿ�� ��Ÿ�ϸ��� ��ų�� �������� ���� ������
		if (((m_ePlayerState == PS_ATTACK1 || m_ePlayerState == PS_ATTACK2 || m_ePlayerState == PS_ATTACK3 || m_ePlayerState == PS_ATTACK4 || m_ePlayerState == PS_ATTACK5)
			|| (m_ePlayerState == PS_DATTACK1 || m_ePlayerState == PS_DATTACK2 || m_ePlayerState == PS_DATTACK3 || m_ePlayerState == PS_DATTACK4 || m_ePlayerState == PS_DATTACK5)
			&& 0.245 > m_dwTime)
			|| (m_ePlayerState == PS_ZACKS || m_ePlayerState == PS_WINDMILL || m_ePlayerState == PS_MAHA || m_ePlayerState == PS_HEADSHOT))
		{
			// �� ���� �ΰ��� ����Ʈ�� �����
			CObjMgr::Get_Instance()->Delete_ID(OBJ_EFFECT);

			// �ܻ� �����
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

	// G ��Ʋ����Ʈ��
	if (CKeyMgr::Get_Instance()->Key_Pressing('G') && MANA_SATELITE < m_tInfo.fMp && COOL_SATELITE < m_SateliteCool
		&& (m_ePlayerState != PS_NORMAL_ATTACKED && m_ePlayerState != PS_THRUST_ATTACKED && m_ePlayerState != PS_LEVITATE_ATTACKED)
		&& (m_ePlayerState != PS_LSLIDE && m_ePlayerState != PS_RSLIDE)
		&& (m_ePlayerState != PS_JUMP && m_ePlayerState != PS_JUMPATTACK)
		&& (m_ePlayerState != PS_DBR && m_ePlayerState != PS_GUNGUARD && m_ePlayerState != PS_MOVINGSHOT && m_ePlayerState != PS_SPREE)
		&& (m_ePlayerState != PS_AWAKEN && m_ePlayerState != PS_LAWAKENING && m_ePlayerState != PS_RAWAKENING)
		&& m_ePlayerState != PS_SATELITE && m_ePlayerState != PS_DEAD)
	{
		// ��Ʋ����Ʈ�� ���� ����
		CSoundMgr::Get_Instance()->PlaySoundW(L"satellitebeam_call.ogg", SOUND_EFFECT, g_fVolume);
		m_ePlayerState = PS_SATELITE;
		Take_Mana(MANA_SATELITE);
		SkillCool_Making(642.f, 532.f, (float)COOL_SATELITE, L"Icon_Satelaser");
		m_SateliteCool = 0;
		m_dwTime = 0;
	}

	// Y ������
	if (CKeyMgr::Get_Instance()->Key_Pressing('Y') && MANA_AWAKENING < m_tInfo.fMp && COOL_AWAKENING < m_AwakeningCool
		&& (m_ePlayerState != PS_NORMAL_ATTACKED && m_ePlayerState != PS_THRUST_ATTACKED && m_ePlayerState != PS_LEVITATE_ATTACKED)
		&& (m_ePlayerState != PS_LSLIDE && m_ePlayerState != PS_RSLIDE)
		&& (m_ePlayerState != PS_JUMP && m_ePlayerState != PS_JUMPATTACK)
		&& (m_ePlayerState != PS_DBR && m_ePlayerState != PS_GUNGUARD && m_ePlayerState != PS_MOVINGSHOT && m_ePlayerState != PS_SPREE)
		&& (m_ePlayerState != PS_AWAKEN && m_ePlayerState != PS_LAWAKENING && m_ePlayerState != PS_RAWAKENING)
		&& m_ePlayerState != PS_SATELITE && m_ePlayerState != PS_DEAD)
	{
		// �ܻ� - ��Ÿ�� ��Ÿ�ϸ��� ��ų�� �������� ������ ������
		if (((m_ePlayerState == PS_ATTACK1 || m_ePlayerState == PS_ATTACK2 || m_ePlayerState == PS_ATTACK3 || m_ePlayerState == PS_ATTACK4 || m_ePlayerState == PS_ATTACK5)
			|| (m_ePlayerState == PS_DATTACK1 || m_ePlayerState == PS_DATTACK2 || m_ePlayerState == PS_DATTACK3 || m_ePlayerState == PS_DATTACK4 || m_ePlayerState == PS_DATTACK5)
			&& 0.245 > m_dwTime)
			|| (m_ePlayerState == PS_ZACKS || m_ePlayerState == PS_WINDMILL || m_ePlayerState == PS_MAHA || m_ePlayerState == PS_HEADSHOT))
		{
			CObjMgr::Get_Instance()->Delete_ID(OBJ_EFFECT);

			// �ܻ� �����
			if (L"Player_LEFT" == Get_FrameKey())
				Making_Shadow(L"Player_LEFT", 0.5f);
			else
				Making_Shadow(L"Player_RIGHT", 0.5f);
		}
		// CSoundMgr::Get_Instance()->PlaySoundW(L"RdShotStart.wav", SOUND_EFFECT, g_fVolume);
		Set_IsImmune(true);		// ������ �����϶� ���� Ȱ��ȭ
		m_ePlayerState = PS_AWAKEN;
		Take_Mana(MANA_AWAKENING);
		SkillCool_Making(702.f, 572.f, (float)COOL_AWAKENING, L"Seven'sFlow_Off");
		m_AwakeningCool = 0;
		m_dwTime = 0;
	}

	// �κ��丮 I
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
	
	// ���� U
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

	// ������ M
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

	// Hp���� 1
	if (CKeyMgr::Get_Instance()->Key_Pressing('1') && 0.5 < m_HpCoolTime)
	{
		CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Set_Hp(CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front()->Get_Hp() + 20000);
		if (m_tInfo.fHp > m_tInfo.fMaxHp)
			m_tInfo.fHp = m_tInfo.fMaxHp;

		CSoundMgr::Get_Instance()->PlaySoundW(L"Hp_recover.ogg", SOUND_EFFECT, g_fVolume);
		m_HpCoolTime = 0;
	}

	// Mp���� 2
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
	// ���̵�
	case PS_IDLE:
		Set_StopMotion(false);
		m_iNormalFinalCount = 0;
		m_iDNormalCount = 0;
		m_iJumpAttackCount = 0;
		m_iSateliteCount = 0;
		break;

	// �׳� ���� �ȱ�
	case PS_JUSTWALKUP:
		m_tInfo.fY -= m_fSpeed * 0.7f;
		break;

	// �׳� �Ʒ��� �ȱ�
	case PS_JUSTWALKDOWN:
		m_tInfo.fY += m_fSpeed * 0.7f;
		break;

	// �������� �ȱ�
	case PS_LWALK:
		if (currentTime - m_lWalkTime > 20)
			m_ePlayerState = PS_IDLE;
		m_tInfo.fX -= m_fSpeed;
		break;

	// ���������� �ȱ�
	case PS_RWALK:
		if (currentTime - m_lWalkTime > 20)
			m_ePlayerState = PS_IDLE;
		m_tInfo.fX += m_fSpeed;
		break;

	// ���� �޸���
	case PS_LRUN:
		if (m_dwTime > 0.4)
		{
			CSoundMgr::Get_Instance()->PlaySoundW(L"run_floor_01.ogg", SOUND_EFFECT, g_fVolume - 0.05);
			m_dwTime = 0;
		}
		m_tInfo.fX -= 1.5f * m_fSpeed;
		break;

	// ������ �޸���
	case PS_RRUN:
		if (m_dwTime > 0.4)
		{
			CSoundMgr::Get_Instance()->PlaySoundW(L"run_floor_01.ogg", SOUND_EFFECT, g_fVolume - 0.05);
			m_dwTime = 0;
		}
		m_tInfo.fX += 1.5f * m_fSpeed;
		break;

	// ���� �����̵�
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

	// ������ �����̵�
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

	// ����
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

		// ������ �ö󰡷��� ���� �߷����� ���� ���������� ���� ���������� �ñ�(�ְ���)
		// if (-m_fJumptDistance < m_fFallDistance)
			// int a = 0;

		m_tInfo.fY += m_fJumptDistance + m_fFallDistance;
		break;
	}
	break;

	// ���� ����
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

	// ��Ÿ1
	case PS_ATTACK1:

		if (m_dwTime > 0.245)
		{
			m_dwTime = 0;
			m_ePlayerState = PS_IDLE;
		}
		break;

	// ��Ÿ2
	case PS_ATTACK2:
		if (m_dwTime > 0.245)
		{
			m_dwTime = 0;
			m_ePlayerState = PS_IDLE;
		}
		break;

	// ��Ÿ3
	case PS_ATTACK3:
		if (m_dwTime > 0.245)
		{
			m_dwTime = 0;
			m_ePlayerState = PS_IDLE;
		}
		break;

	// ��Ÿ4
	case PS_ATTACK4:
		if (m_dwTime > 0.350)
		{
			m_dwTime = 0;
			m_ePlayerState = PS_IDLE;
		}
		break;

	// ��Ÿ5
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

		// �Ʒ���Ÿ1
	case PS_DATTACK1:
		if (m_dwTime > 0.21)
		{
			m_dwTime = 0;
			m_ePlayerState = PS_IDLE;
		}
		break;

		// �Ʒ���Ÿ2
	case PS_DATTACK2:
		if (m_dwTime > 0.21)
		{
			m_dwTime = 0;
			m_ePlayerState = PS_IDLE;
		}
		break;

		// �Ʒ���Ÿ3
	case PS_DATTACK3:
		if (m_dwTime > 0.21)
		{
			m_dwTime = 0;
			m_ePlayerState = PS_IDLE;
		}
		break;

		// �Ʒ���Ÿ4
	case PS_DATTACK4:
		if (m_dwTime > 0.315)
		{
			m_dwTime = 0;
			m_ePlayerState = PS_IDLE;
		}
		break;

	// �Ʒ���Ÿ5
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

	// SPACE ���� ���� ������
	case PS_DBR:
		if (m_dwTime > 0.6)
		{
			m_dwTime = 0;
			m_ePlayerState = PS_IDLE;
		}
		break;

	// Z �轺����ũ
	case PS_ZACKS:
		if (m_dwTime > 0.4)
		{
			m_dwTime = 0;
			m_ePlayerState = PS_IDLE;
		}
		break;

	// E �ǰ���
	case PS_GUNGUARD:
		if (m_dwTime > 1)
		{
			m_dwTime = 0;
			m_ePlayerState = PS_IDLE;
		}
		break;

	// S �����
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

		// D ����ű
	case PS_MAHA:
		if (m_dwTime > 0.3)
		{
			m_dwTime = 0;
			m_iWindmillCount = 0;
			m_ePlayerState = PS_IDLE;
		}
		break;

		// A ��弦
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

		// R �̵����
	case PS_MOVINGSHOT:
		// �̵������ V ������ ���
		if (CKeyMgr::Get_Instance()->Key_Pressing('V'))
		{
			m_dwTime = 0;
			m_iMovingShotCount = 0;
			m_ePlayerState = PS_IDLE;
			break;
		}

		// �̵������ Z ������ ������ȯ
		if (CKeyMgr::Get_Instance()->Key_Pressing('Z') && 0.2 < m_dwTime)
		{
			m_dwTime = 0;
			if (L"Player_LEFT" == Get_FrameKey())
				Set_FrameKey(L"Player_RIGHT");
			else
				Set_FrameKey(L"Player_LEFT");
		}

		// �̵������ ����Ű�� �̵�����
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
		
		// F ����
	case PS_SPREE:
		// ������ V ������ ���
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

		// G ��Ʋ����Ʈ��
	case PS_SATELITE:
		if (0 < m_dwTime && 0 == m_iSateliteCount)
		{
			Set_IsImmune(true);
			++m_iSateliteCount;
			// �ƽ�
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

		// Y ������
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
			Set_IsImmune(false);	// ���� ����
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
			Set_IsImmune(false);	// ���� ����
			m_dwTime = 0;
			m_iSeventhCount = 0;
			if (L"LAwakening" == Get_FrameKey())
				Set_FrameKey(L"Player_LEFT");
			if (L"RAwakening" == Get_FrameKey())
				Set_FrameKey(L"Player_RIGHT");
			m_ePlayerState = PS_IDLE;
		}
		break;

	// �Ϲ� �ǰ�(���ڸ�)
	case PS_NORMAL_ATTACKED:
		if (!m_bKnockback)
		{
			m_dwTime = 0;
			m_iSpreeCount = 0;
			m_ePlayerState = PS_IDLE;
		}
		break;

	// �˹� �ǰ�(�з���)
	case PS_THRUST_ATTACKED:
		if (!m_bKnockback)
		{
			m_dwTime = 0;
			m_iSpreeCount = 0;
			m_ePlayerState = PS_IDLE;
		}

		break;

	// ��� �ǰ�(�����)
	case PS_LEVITATE_ATTACKED:
		if (!m_bKnockback)
		{
			m_dwTime = 0;
			m_iSpreeCount = 0;
			// m_tInfo.fY = m_tTileCollision.bottom - (0.5f * m_tInfo.fCY);
			m_ePlayerState = PS_IDLE;
		}
		break;

	// ���
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
	// ��ũ���� �����ϱ� ���� ȭ����� �ּ�, �ִ� ��ġ
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

// ��� ���¸� ��ȭ�����ִ� �Լ�(���� ���� �ӽ�)
void CPlayer::Motion_Change()
{
	// ���� ���¿� �ܺ� ���ο� ����(ex.����Ű, ��ųŰ ��...) ���Ӱ� �ٲ� ���°� �������� ���� ��,
	if (m_ePlayerPreState != m_ePlayerState)
	{
		// ���� ���� ���°� ...���
		switch (m_ePlayerState)
		{
			// �ش� ���¿� �°� ������ ����ü�� ������ �������ش�.

		// ���̵�
		case PS_IDLE:
			Set_StopMotion(false);
			m_tFrame.iFrameStart = 0; 
			m_tFrame.iFrameEnd	 = 12;
			m_tFrame.iMotion	 = 0;
			m_tFrame.dwSpeed	 = 0.3;
			break;

		// ���ڸ� ���� �ȱ�
		case PS_JUSTWALKUP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 6;
			m_tFrame.dwSpeed = 0.15;
			break;

		// ���ڸ� �Ʒ��� �ȱ�
		case PS_JUSTWALKDOWN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 6;
			m_tFrame.dwSpeed = 0.15;
			break;

		// ���� �ȱ�
		case PS_LWALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 6;
			m_tFrame.dwSpeed = 0.15;
			break;

		// ������ �ȱ�
		case PS_RWALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 6;
			m_tFrame.dwSpeed = 0.15;
			break;

		// ���� �޸���
		case PS_LRUN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 12;
			m_tFrame.dwSpeed = 0.10;
			break;

		// ������ �޸���
		case PS_RRUN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 12;
			m_tFrame.dwSpeed = 0.10;
			break;

		// X ���� �����̵�
		case PS_LSLIDE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 13;
			m_tFrame.dwSpeed = 0.15;
			break;

		// X ������ �����̵�
		case PS_RSLIDE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 13;
			m_tFrame.dwSpeed = 0.15;
			break;

		// C ����
		case PS_JUMP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 7;
			m_tFrame.dwSpeed = 0.25;
			break;

		// X ���� ����
		case PS_JUMPATTACK:
			m_tFrame.iFrameStart = 1;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 8;
			m_tFrame.dwSpeed = 0.06;
			break;

		// X ��Ÿ1
		case PS_ATTACK1:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 0.035;
			break;

		// X ��Ÿ2
		case PS_ATTACK2:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 0.035;
			break;

		// X ��Ÿ3
		case PS_ATTACK3:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 0.035;
			break;

		// X ��Ÿ4
		case PS_ATTACK4:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 0.035;
			break;

		// X ��Ÿ5
		case PS_ATTACK5:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 0.045;
			break;

		// X �Ʒ���Ÿ1
		case PS_DATTACK1:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 0.04;
			break;

		// X �Ʒ���Ÿ2
		case PS_DATTACK2:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 0.04;
			break;

		// X �Ʒ���Ÿ3
		case PS_DATTACK3:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 0.04;
			break;

		// X �Ʒ���Ÿ4
		case PS_DATTACK4:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 0.05;
			break;

		// X �Ʒ���Ÿ5
		case PS_DATTACK5:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 5;
			m_tFrame.dwSpeed = 0.035;
			break;

		// SPACE �������̸�����
		case PS_DBR:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 27;
			m_tFrame.dwSpeed = 0.15;
			break;

		// Z �轺����ũ
		case PS_ZACKS:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 22;
			m_tFrame.dwSpeed = 0.1;
			break;

		// E �ǰ���
		case PS_GUNGUARD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 26;
			m_tFrame.dwSpeed = 0.75;
			break;

		// S �����
		case PS_WINDMILL:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 14;
			m_tFrame.dwSpeed = 0.18;
			break;

		// D ����ű
		case PS_MAHA:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 23;
			m_tFrame.dwSpeed = 0.05;
			break;

		// A ��弦
		case PS_HEADSHOT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 0.035;
			break;

		// R �̵����
		case PS_MOVINGSHOT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 12;
			m_tFrame.iMotion = 10;
			m_tFrame.dwSpeed = 0.1;
			break;

		// F ����
		case PS_SPREE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 12;
			m_tFrame.iMotion = 25;
			m_tFrame.dwSpeed = 0.05;
			break;

		// Y ��Ʋ����Ʈ��
		case PS_SATELITE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 27;
			m_tFrame.dwSpeed = 0.25;
			break;

		// Y ������
		case PS_AWAKEN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 10;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 0.05;
			break;

		// �Ϲ� �ǰ� ���
		case PS_NORMAL_ATTACKED:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 15;
			m_tFrame.dwSpeed = 0.4;
			break;

		// �������� �ǰ� ���
		case PS_THRUST_ATTACKED:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 15;
			m_tFrame.dwSpeed = 0.4;
			break;

		// ���ư��� �ǰ� ���
		case PS_LEVITATE_ATTACKED:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 16;
			m_tFrame.dwSpeed = 0.2;
			break;

		// ���
		case PS_DEAD:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 16;
			m_tFrame.dwSpeed = 0.3;
			break;
		}

		// ���Ӱ� ����� ���¸� m_ePreState�� �����Ѵ�.
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
	// �������� ������ ��ġ, ��Ÿ��, �̹��� Ű
	CObjMgr::Get_Instance()->Add_Object(OBJ_SKILLICON, CAbstractFactory<CUI_SkillIcon>::Create_Obj(_fX, _fY, _fLifeTime, _pKey));
}

// �÷��̾� �ܻ� ���ۿ� �Լ�
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

// �̵���� źȯ ���ۿ� �Լ�
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

// ���� ����Ʈ ���ۿ� �Լ�
void CPlayer::Making_Spree()
{
	if(0 == m_iSpreeCount % 2)
		CSoundMgr::Get_Instance()->PlaySoundW(L"RdShotBullet.wav", SOUND_EFFECT, g_fVolume);

	int iRand = rand();

	switch (iRand % 8)
	{
		// �� ���
	case 0:
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_ATTACK, CAbstractFactory<CPlayerAttack>::
			Create_Obj(ATT_LEVITATE, false, m_tInfo.fX - 130.f, m_tInfo.fY - 40.f, 250.f, 259.f, 0.f, 0.f, 0.f, 0.f, 0.3f, 150.f, 150.f, float(Get_TileCollision().bottom),
				m_tInfo.fAtk, 400.f, 3.f, 0.f, 9.5f, 90.f, 180.f, 0.4f, L"LU", { 255, 255, 255 }));

		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
			Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX - 130.f, m_tInfo.fY - 40.f, 250.f, 259.f, 0.f, 0.f, 0.f, 0.f, 0.3f, 150.f, 150.f, float(Get_TileCollision().bottom),
				m_tInfo.fAtk, 400.f, 1.5f, 0.f, 0.f, 90.f, 0.f, 0.4f, L"LUSpree", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 5, 0, 0.05, 0. });
		break;

		// �� �ߴ�
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

		// �� ���ϴ�
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

		// �� �ϴ�
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
		// �� ���
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

		// �� �ߴ�
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

		// �� ���ϴ�
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

		// �� �ϴ�
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

// ������ ���ۿ� �Լ�
void CPlayer::Making_Awakening(float _fX, float _fY, float _fCX, float _fCY, float _fECX, float _fECY, TCHAR* _pKey, TCHAR* _pEKey
	, int _Start, int _End, float _FrameSpeed, float _LifeTime, int _EStart, int _EEnd, float _EFrameSpeed, float _ELifeTime)
{
	// ��Ʈ �ڽ�
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_WIDEATTACK, CAbstractFactory<CPlayerAttack>::
		Create_Obj(ATT_THRUST, false, _fX, _fY, 500.f, 400.f, 0.f, 0.f, 0.f, 0.f, 0.2f, 700.f, 400.f, float(Get_TileCollision().bottom),
			m_tInfo.fAtk, 2500.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.2f, L"SeventhAttack", { 255, 0, 255 }));
	// ���� ����Ʈ
	CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
		Create_Obj(ATT_JUSTEFFECT, false, _fX, _fY, _fCX, _fCY, 0.f, 0.f, 0.f, 0.f, _LifeTime, _fCX, _fCY, float(Get_TileCollision().bottom),
			m_tInfo.fAtk, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, _pKey, { 255, 0, 255 }));
	CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ _Start, _End, 0, _FrameSpeed, 0. });
	// ���� ����Ʈ
	CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
		Create_Obj(ATT_JUSTEFFECT, false, _fX, _fY, _fECX, _fECY, 0.f, 0.f, 0.f, 0.f, _ELifeTime, _fECX, _fECY, float(Get_TileCollision().bottom),
			m_tInfo.fAtk, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, _pEKey, { 255, 0, 255 }));
	CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ _EStart, _EEnd, 0, _EFrameSpeed, 0. });

}

// ������ ����Ʈ ���ۿ� �Լ�
void CPlayer::Making_AwakeningE(float _fX, float _fY, float _fECX, float _fECY, TCHAR* _pEKey
	, int _EStart, int _EEnd, float _EFrameSpeed, float _ELifeTime)
{
	// ���� ����Ʈ
	CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
		Create_Obj(ATT_JUSTEFFECT, false, _fX, _fY, _fECX, _fECY, 0.f, 0.f, 0.f, 0.f, _ELifeTime, _fECX, _fECY, float(Get_TileCollision().bottom),
			m_tInfo.fAtk, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, _pEKey, { 255, 0, 255 }));
	CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ _EStart, _EEnd, 0, _EFrameSpeed, 0. });

}

// ���⿡ ���� ������
void CPlayer::DoSeventhL()
{
	if (m_dwTime > 0 && 0 == m_iSeventhCount)
	{
		++m_iSeventhCount;

		// �ƽ�
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CNonAlpha>::
			Create_Obj(ATT_JUSTEFFECT, false, 400.f, 440.f, 800.f, 260.f, 0.f, 0.f, 0.f, 0.f, 0.8f, 800.f, 260.f, float(Get_TileCollision().bottom),
				0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, L"Cutsin", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 15, 0, 0.05, 0. });

		Set_FrameKey(L"LAwakening");
		Set_Frame(tagFrame{ 0, 9, 0, 0.05, 0. });
		// �ܻ� �����
		if (L"LAwakening" == Get_FrameKey())
			Making_Shadow(L"LAwaken_Black", 1.0f);
		else
			Making_Shadow(L"RAwaken_Black", 1.0f);
		Set_PosX(-20.f);

	}
	// 1Ÿ
	if (m_dwTime > 0.5 && 1 == m_iSeventhCount)
	{
		++m_iSeventhCount;

		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			368.f, 400.f,
			L"SeventhFeather3",
			0, 10, 0.07, 0.77);
		Set_Frame(tagFrame{ 0, 3, 1, 0.075, 0. });
		// �ܻ� �����
		if (L"LAwakening" == Get_FrameKey())
			Making_Shadow(L"LAwaken_Black", 1.0f);
		else
			Making_Shadow(L"RAwaken_Black", 1.0f);
		Set_PosX(-75.f);
		Set_PosY(-110.f);
		// ����
		Making_Awakening(m_tInfo.fX - 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 369.f, 400.f,
			L"LSeventhNormal", L"SeventhFeather5",
			0, 5, 0.03, 0.18, 0, 6, 0.07, 0.49);
		// ������
		Making_Awakening(m_tInfo.fX + 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 167.f, 194.f,
			L"LSeventhNormal", L"SeventhFeather1",
			0, 5, 0.03, 0.18, 0, 8, 0.07, 0.63);
	}
	// 2Ÿ
	if (m_dwTime > 0.8 && 2 == m_iSeventhCount)
	{

		++m_iSeventhCount;

		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			368.f, 400.f,
			L"SeventhFeather3",
			0, 10, 0.07, 0.77);
		Set_Frame(tagFrame{ 0, 3, 2, 0.075, 0. });
		// �ܻ� �����
		if (L"LAwakening" == Get_FrameKey())
			Making_Shadow(L"LAwaken_Black", 1.0f);
		else
			Making_Shadow(L"RAwaken_Black", 1.0f);
		Set_PosX(-75.f);
		Set_PosY(+220.f);
		// ����
		Making_Awakening(m_tInfo.fX - 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 167.f, 194.f,
			L"LSeventhNormal", L"SeventhFeather1",
			0, 5, 0.03, 0.18, 0, 8, 0.07, 0.63);
		// ������
		Making_Awakening(m_tInfo.fX + 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 167.f, 194.f,
			L"LSeventhNormal", L"SeventhFeather1",
			0, 5, 0.03, 0.18, 0, 8, 0.07, 0.63);
	}
	// 3Ÿ
	if (m_dwTime > 1.1 && 3 == m_iSeventhCount)
	{
		++m_iSeventhCount;

		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			368.f, 400.f,
			L"SeventhFeather3",
			0, 10, 0.1, 1.1);
		Set_Frame(tagFrame{ 0, 9, 3, 0.03, 0. });
		// �ܻ� �����
		if (L"LAwakening" == Get_FrameKey())
			Making_Shadow(L"LAwaken_Black", 1.0f);
		else
			Making_Shadow(L"RAwaken_Black", 1.0f);
		Set_PosX(-75.f);
		Set_PosY(-240.f);
		// ����
		Making_Awakening(m_tInfo.fX + 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 0.f, 0.f,
			L"LSeventhNormal", L"-",
			0, 5, 0.03, 0.18, 0, 0, 0, 0);

		// ������
		Making_Awakening(m_tInfo.fX + 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 0.f, 0.f,
			L"LSeventhNormal", L"-",
			0, 5, 0.03, 0.18, 0, 0, 0, 0);
		Making_AwakeningE(m_tInfo.fX + 100.f, m_tInfo.fY + 50.f,
			100.f, 55.f,
			L"SeventhDust1",
			0, 5, 0.07, 0.42);
	}
	// 4Ÿ
	if (m_dwTime > 1.4 && 4 == m_iSeventhCount)
	{
		++m_iSeventhCount;

		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			368.f, 400.f,
			L"SeventhFeather3",
			0, 10, 0.1, 1.1);
		Set_Frame(tagFrame{ 0, 3, 4, 0.075, 0. });
		// �ܻ� �����
		if (L"LAwakening" == Get_FrameKey())
			Making_Shadow(L"LAwaken_Black", 1.0f);
		else
			Making_Shadow(L"RAwaken_Black", 1.0f);
		Set_PosX(-75.f);
		Set_PosY(+180.f);

		// ����
		Making_Awakening(m_tInfo.fX - 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 0.f, 0.f,
			L"LSeventhNormal", L"-",
			0, 5, 0.03, 0.18, 0, 0, 0, 0);
		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			167.f, 194.f,
			L"SeventhFeather1",
			0, 8, 0.07, 0.63);
		// ������
		Making_Awakening(m_tInfo.fX + 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 0.f, 0.f,
			L"LSeventhNormal", L"-",
			0, 5, 0.03, 0.18, 0, 0, 0, 0);
		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			167.f, 194.f,
			L"SeventhFeather1",
			0, 8, 0.07, 0.63);
		// ����
		Making_Awakening(m_tInfo.fX, m_tInfo.fY - 120.f,
			316.f, 274.f, 0.f, 0.f,
			L"LSeventhNormal", L"-",
			0, 5, 0.03, 0.18, 0, 0, 0, 0);
	}
	// 5Ÿ
	if (m_dwTime > 1.7 && 5 == m_iSeventhCount)
	{
		++m_iSeventhCount;

		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			368.f, 400.f,
			L"SeventhFeather3",
			0, 10, 0.1, 1.1);
		Set_Frame(tagFrame{ 0, 3, 5, 0.075, 0. });
		// �ܻ� �����
		if (L"LAwakening" == Get_FrameKey())
			Making_Shadow(L"LAwaken_Black", 1.0f);
		else
			Making_Shadow(L"RAwaken_Black", 1.0f);
		Set_PosX(-75.f);
		Set_PosY(-200.f);

		// ����
		Making_AwakeningE(m_tInfo.fX - 100.f, m_tInfo.fY,
			369.f, 400.f,
			L"SeventhFeather5",
			0, 6, 0.07, 0.49);
		// ������
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
		// �ܻ� �����
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

		// ������
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

		// ������
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

		// ������
		Making_Awakening(m_tInfo.fX + 155.f, m_tInfo.fY + 80.f,
			337.f, 407.f, 0.f, 0.f,
			L"RSeventhFinalBeforeThree3", L"-",
			0, 6, 0.07, 0.49, 0, 0, 0, 0);
		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			345.f, 304.f,
			L"SeventhFeather2",
			0, 6, 0.07, 0.49);
	}
	// 7Ÿ(��Ÿ)
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

		// �ƽ�
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CNonAlpha>::
			Create_Obj(ATT_JUSTEFFECT, false, 400.f, 440.f, 800.f, 260.f, 0.f, 0.f, 0.f, 0.f, 0.8f, 800.f, 260.f, float(Get_TileCollision().bottom),
				0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, L"Cutsin", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 15, 0, 0.05, 0. });


		Set_FrameKey(L"RAwakening");
		Set_Frame(tagFrame{ 0, 9, 0, 0.05, 0. });
		// �ܻ� �����
		if (L"LAwakening" == Get_FrameKey())
			Making_Shadow(L"LAwaken_Black", 1.0f);
		else
			Making_Shadow(L"RAwaken_Black", 1.0f);
		Set_PosX(-20.f);
	}
	// 1Ÿ
	if (m_dwTime > 0.5 && 1 == m_iSeventhCount)
	{
		++m_iSeventhCount;

		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			368.f, 400.f,
			L"SeventhFeather3",
			0, 10, 0.07, 0.77);
		Set_Frame(tagFrame{ 0, 3, 1, 0.075, 0. });
		// �ܻ� �����
		if (L"LAwakening" == Get_FrameKey())
			Making_Shadow(L"LAwaken_Black", 1.0f);
		else
			Making_Shadow(L"RAwaken_Black", 1.0f);
		Set_PosX(75.f);
		Set_PosY(-110.f);
		// ����
		Making_Awakening(m_tInfo.fX + 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 369.f, 400.f,
			L"RSeventhNormal", L"SeventhFeather5",
			0, 5, 0.03, 0.18, 0, 6, 0.07, 0.49);
		// ������
		Making_Awakening(m_tInfo.fX - 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 167.f, 194.f,
			L"RSeventhNormal", L"SeventhFeather1",
			0, 5, 0.03, 0.18, 0, 8, 0.07, 0.63);
	}
	// 2Ÿ
	if (m_dwTime > 0.8 && 2 == m_iSeventhCount)
	{

		++m_iSeventhCount;

		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			368.f, 400.f,
			L"SeventhFeather3",
			0, 10, 0.07, 0.77);
		Set_Frame(tagFrame{ 0, 3, 2, 0.075, 0. });
		// �ܻ� �����
		if (L"LAwakening" == Get_FrameKey())
			Making_Shadow(L"LAwaken_Black", 1.0f);
		else
			Making_Shadow(L"RAwaken_Black", 1.0f);
		Set_PosX(75.f);
		Set_PosY(+220.f);
		// ����
		Making_Awakening(m_tInfo.fX + 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 167.f, 194.f,
			L"RSeventhNormal", L"SeventhFeather1",
			0, 5, 0.03, 0.18, 0, 8, 0.07, 0.63);
		// ������
		Making_Awakening(m_tInfo.fX - 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 167.f, 194.f,
			L"RSeventhNormal", L"SeventhFeather1",
			0, 5, 0.03, 0.18, 0, 8, 0.07, 0.63);
	}
	// 3Ÿ
	if (m_dwTime > 1.1 && 3 == m_iSeventhCount)
	{
		++m_iSeventhCount;

		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			368.f, 400.f,
			L"SeventhFeather3",
			0, 10, 0.1, 1.1);
		Set_Frame(tagFrame{ 0, 9, 3, 0.03, 0. });
		// �ܻ� �����
		if (L"LAwakening" == Get_FrameKey())
			Making_Shadow(L"LAwaken_Black", 1.0f);
		else
			Making_Shadow(L"RAwaken_Black", 1.0f);
		Set_PosX(75.f);
		Set_PosY(-240.f);
		// ����
		Making_Awakening(m_tInfo.fX - 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 0.f, 0.f,
			L"RSeventhNormal", L"-",
			0, 5, 0.03, 0.18, 0, 0, 0, 0);

		// ������
		Making_Awakening(m_tInfo.fX - 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 0.f, 0.f,
			L"RSeventhNormal", L"-",
			0, 5, 0.03, 0.18, 0, 0, 0, 0);
		Making_AwakeningE(m_tInfo.fX - 100.f, m_tInfo.fY + 50.f,
			100.f, 55.f,
			L"SeventhDust1",
			0, 5, 0.07, 0.42);
	}
	// 4Ÿ
	if (m_dwTime > 1.4 && 4 == m_iSeventhCount)
	{
		++m_iSeventhCount;

		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			368.f, 400.f,
			L"SeventhFeather3",
			0, 10, 0.1, 1.1);
		Set_Frame(tagFrame{ 0, 3, 4, 0.075, 0. });
		// �ܻ� �����
		if (L"LAwakening" == Get_FrameKey())
			Making_Shadow(L"LAwaken_Black", 1.0f);
		else
			Making_Shadow(L"RAwaken_Black", 1.0f);
		Set_PosX(75.f);
		Set_PosY(+180.f);

		// ����
		Making_Awakening(m_tInfo.fX + 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 0.f, 0.f,
			L"RSeventhNormal", L"-",
			0, 5, 0.03, 0.18, 0, 0, 0, 0);
		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			167.f, 194.f,
			L"SeventhFeather1",
			0, 8, 0.07, 0.63);
		// ������
		Making_Awakening(m_tInfo.fX - 100.f, m_tInfo.fY + 50.f,
			316.f, 274.f, 0.f, 0.f,
			L"RSeventhNormal", L"-",
			0, 5, 0.03, 0.18, 0, 0, 0, 0);
		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			167.f, 194.f,
			L"SeventhFeather1",
			0, 8, 0.07, 0.63);
		// ����
		Making_Awakening(m_tInfo.fX, m_tInfo.fY - 120.f,
			316.f, 274.f, 0.f, 0.f,
			L"RSeventhNormal", L"-",
			0, 5, 0.03, 0.18, 0, 0, 0, 0);
	}
	// 5Ÿ
	if (m_dwTime > 1.7 && 5 == m_iSeventhCount)
	{
		++m_iSeventhCount;

		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			368.f, 400.f,
			L"SeventhFeather3",
			0, 10, 0.1, 1.1);
		Set_Frame(tagFrame{ 0, 3, 5, 0.075, 0. });
		// �ܻ� �����
		if (L"LAwakening" == Get_FrameKey())
			Making_Shadow(L"LAwaken_Black", 1.0f);
		else
			Making_Shadow(L"RAwaken_Black", 1.0f);
		Set_PosX(75.f);
		Set_PosY(-200.f);

		// ����
		Making_AwakeningE(m_tInfo.fX + 100.f, m_tInfo.fY,
			369.f, 400.f,
			L"SeventhFeather5",
			0, 6, 0.07, 0.49);
		// ������
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
		// �ܻ� �����
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
		// �ܻ� �����
		if (L"Player_RIGHT" == Get_FrameKey())
			Making_Shadow(L"Player_RIGHT", 1.0f);
		else
			Making_Shadow(L"Player_LEFT", 1.0f);
		Set_PosY(-50.f);
		Set_PosX(50.f);

		// ������
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

		// ������
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

		// ������
		Making_Awakening(m_tInfo.fX - 155.f, m_tInfo.fY + 80.f,
			337.f, 407.f, 0.f, 0.f,
			L"LSeventhFinalBeforeThree3", L"-",
			0, 6, 0.07, 0.49, 0, 0, 0, 0);
		Making_AwakeningE(m_tInfo.fX, m_tInfo.fY,
			345.f, 304.f,
			L"SeventhFeather2",
			0, 6, 0.07, 0.49);
	}
	// 7Ÿ(��Ÿ)
	if (m_dwTime > 3.05 && 10 == m_iSeventhCount)
	{
		++m_iSeventhCount;
		Set_FrameKey(L"LAwakening");
		Set_Frame(tagFrame{ 0, 11, 0, 0.05, 0. });
		// �ܻ� �����
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
