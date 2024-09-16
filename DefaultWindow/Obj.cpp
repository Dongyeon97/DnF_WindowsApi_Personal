#include "stdafx.h"
#include "Obj.h"
#include "TimeMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "Effect.h"
#include "SoundMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"

#include "UI_Font.h"
#include "UI_BossHp.h"
#include "UI_BossBar.h"
#include "UI_Portrait.h"
#include "UI_MonHpNum.h"
#include "PlayerAttack.h"
#include "PlayerAttack2.h"
#include "UI_MonsterBar.h"
#include "UI_MonsterHp.h"

#include "Scene.h"
#include "UI_Combo.h"

CObj::CObj() :
	m_fSpeed(0.f),
	m_eDir(DIR_END),
	m_eRender(RENDER_END),
	m_tRGB{},
	m_TextTerm(0),
	m_strName{},
	m_iSpriteIndex(0),
	m_fDrawRatio(0.f),
	m_iDrawLineCount(0),
	m_iMaxDrawLineCount(0),
	m_iInvenIndex(0),
	m_bDead(false),
	m_bEquip(false),
	m_bUnEquip(false),
	m_bBuy(false),
	m_bSell(false),
	m_fAngle(0.f),
	m_fEndPosX(0.f),
	m_fEndPosY(0.f),
	m_pFrameKey(L""),
	m_bStopMotion(false),
	m_fPortraitX(0.f),
	m_fPortraitY(0.f),
	m_iLifeNum(0),
	m_dwTime(0.f),
	m_fCollisionSizeX(0.f),
	m_fCollisionSizeY(0.f),
	m_lRectCollisionCenter{ 0, 0 },
	m_bOpened(false),
	m_fLifeTime(0.f),
	m_lTileCollisionCenter{ 0, 0 },
	m_fTileCollisionSizeX(0.f),
	m_fTileCollisionSizeY(0.f),
	m_fFallSpeed(0.f),
	m_lNormalAttackTime(0),
	m_lThrustAttackTime(0),
	m_lLevitateAttackTime(0),
	m_fAttPoint(0.f),
	m_fAttRatio(0.f),
	m_fThrustPower(0.f),
	m_fThrustAccel(0.f),
	m_fLevitatePower(0.f),
	m_fLevitateAngle(0.f),
	m_fThrustAngle(0.f),
	m_lKnockbackTime(0.f),
	m_bDeadType(false),
	m_bKnockback(false),
	m_fCriRatio(0.f),
	m_bImmune(false),
	m_GrogyBuffTime(0),
	m_iAlpha(0)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tRectCollision, sizeof(RECT)); 
	ZeroMemory(&m_tTileCollision, sizeof(RECT));
}


CObj::~CObj()
{
}

void CObj::Set_Frame(tagFrame _tFrame)
{
	m_tFrame.dwSpeed = _tFrame.dwSpeed;
	m_tFrame.dwTime = _tFrame.dwTime;
	m_tFrame.iFrameEnd = _tFrame.iFrameEnd;
	m_tFrame.iFrameStart = _tFrame.iFrameStart;
	m_tFrame.iMotion = _tFrame.iMotion;
}
void CObj::Take_Damage(float _fDamage)
{
	m_tInfo.fHp -= _fDamage;
	if (PLAYER != m_eMonType)
	{
		// ���ٸ� ����Ʈ
		if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).back())->Get_DBR()
			&& (0 == rand() % 2))
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
				Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX, m_tRectCollision.top, 107.f, 101.f, 0.f, 0.f, 0.f, 0.f, 0.4f, 107.f, 101.f, 0.f,
					0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, L"DeathByRevolver2", { 255, 255, 255 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 4, 0, 0.08, 0. });
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_AlphaValue(150);
		}
		CSoundMgr::Get_Instance()->PlaySoundW(L"mon_bullet_hit_04.ogg", SOUND_EFFECT, g_fVolume);

		CScene::Plus_Combo();
		CSceneMgr::Get_Instance()->Get_CurScene()->Reset_Time();
	}
}
// ������Ʈ�� �˹� ���ݿ� �¾��� �� �ߵ�
void CObj::OnKnockback(HIT_INFO _tHitInfo, float _fBottomPosY)
{
	if (m_bImmune)
		return;

	if (m_bKnockback)
	{
		if (4 < m_dwTime)
		{
			m_dwTime = 0;
			m_bKnockback = false;
			Set_StopMotion(false);
		}
		if (m_dwTime < 0.00001)
		{
			float fTotal_Damage = 0.f;

			// ���� �ǰ�
			if (PLAYER != m_eMonType)
			{
				bool bCritical = false;

				// �÷��̾��� ũ��Ƽ�� Ȯ���� ���� ġ��Ÿ ����
				if (rand() % 100 < CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).back()->Get_CriRatio())
					bCritical = true;

				// ������ ���� ����
				fTotal_Damage = (_tHitInfo.fAttPoint * _tHitInfo.fAttRatio) + float(rand() % 15000);
				if (bCritical)
					fTotal_Damage *= 1.5f;

				Take_Damage(fTotal_Damage);
				Draw_Font(int(fTotal_Damage), bCritical);
				Draw_HitEffect();
			}
			// �÷��̾� �ǰ�
			else
			{
				fTotal_Damage = (_tHitInfo.fAttPoint * _tHitInfo.fAttRatio) + float(rand() % 15000);
				Take_Damage(fTotal_Damage);
				Draw_Font(int(fTotal_Damage), false);
				Draw_HitEffect();
			}

			// ���� ���
			if (PLAYER == m_eMonType)
			{
				switch (rand() % 2)
				{
				case 0:
					CSoundMgr::Get_Instance()->PlaySoundW(L"gn_dmg_02.wav", SOUND_EFFECT, g_fVolume);
					break;

				case 1:
					CSoundMgr::Get_Instance()->PlaySoundW(L"gn_dmg_03.wav", SOUND_EFFECT, g_fVolume);
					break;
				}
			}
			else if(BOSS != m_eMonType)
			{
				CSoundMgr::Get_Instance()->PlaySoundW(L"mon_gun_hit_02.wav", SOUND_EFFECT, g_fVolume);
			}

			// ���⼭ ���� Ÿ�� : BOSS / NORMAL�� ���� UI����ϸ�ɵ�
			if(PLAYER != m_eMonType)
				Draw_HpBar(m_tInfo.fMaxHp, m_iMaxDrawLineCount, fTotal_Damage);
		}
		
		// X�� �˹�(���߿� ��������� x�������� �˹���� ����)
		if (MON_LEVITATE_ATTACKED != m_eCurState || (PLAYER == m_eMonType && CPlayer::PLAYERSTATE::PS_LEVITATE_ATTACKED != dynamic_cast<CPlayer*>(this)->Get_PlayerState()))
			m_tInfo.fX += _tHitInfo.fThrustPower * cosf(_tHitInfo.fKnockbackAngle * (PI / 180.f)) * m_dwTime;

		// ���� ������ ��� Y�� ���
		if ((ATT_LEVITATE == _tHitInfo.eAttType)
			|| (ATT_THRUST == _tHitInfo.eAttType && MON_LEVITATE_ATTACKED == m_eCurState)
			|| (ATT_NORMAL == _tHitInfo.eAttType && MON_LEVITATE_ATTACKED == m_eCurState)
			|| (MON_LEVITATE_ATTACKED == m_eCurState)
			|| (PLAYER == m_eMonType && CPlayer::PLAYERSTATE::PS_LEVITATE_ATTACKED == dynamic_cast<CPlayer*>(this)->Get_PlayerState()))
		{
			float fFallingSpeed = 25.4f * powf(m_dwTime, 2);
			float fLevitateSpeed = 2.f * _tHitInfo.fLevitatePower;

			if (fFallingSpeed > 4.f * _tHitInfo.fLevitatePower)
				fFallingSpeed = 4.f * _tHitInfo.fLevitatePower;

			m_tInfo.fY += fLevitateSpeed * -sinf(_tHitInfo.fLevitateAngle * (PI / 180.f)) * m_dwTime + fFallingSpeed;

			if (Get_Frame().iFrameStart == Get_Frame().iFrameEnd)
			{
				Set_StopMotion(true);
			}

			if (0.3 < m_dwTime && m_tRectCollision.bottom > m_tTileCollision.bottom - 10)
			{
				m_tRectCollision.bottom = m_tTileCollision.bottom;
				m_dwTime += 10;
				m_bKnockback = false;
				Set_StopMotion(false);
			}
		}
		else
		{
			if (Get_Frame().iFrameStart == Get_Frame().iFrameEnd)
			{
				Set_StopMotion(true);
			}
			if (_tHitInfo.fKnockbackTime < m_dwTime)
			{
				m_dwTime += 10;
				m_bKnockback = false;
				Set_StopMotion(false);
			}
		}
	}
}

void CObj::Draw_HitEffect()
{
	// ����
	CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
		Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX, m_tInfo.fY - 100.f, 62.f, 73.f, 0.f, 0.f, 0.f, 0.f, 0.48f, 62.f, 73.f, 0.f,
			0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, L"LHitEffect", { 255, 255, 255 }));
	CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 6, 0, 0.07, 0. });

	// Ÿ�� ����Ʈ
	switch (rand() % 2)
	{
		case 0:
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
				Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX, m_tInfo.fY + 30.f, 48.f, 41.f, 0.f, 0.f, 0.f, 0.f, 0.48f, 48.f, 41.f, 0.f,
					0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, L"PlayerHit", { 255, 255, 255 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 6, 0, 0.07, 0. });

			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack2>::
				Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX - 50.f, m_tInfo.fY, 271.f, 261.f, 0.f, 0.f, 0.f, 0.f, 0.3f, 271.f, 261.f, 0.f,
					0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, L"PlayerHit_Daegak", { 0, 0, 0 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 2, 0, 0.1, 0. });
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_AlphaValue(180);

			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack2>::
				Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX, m_tInfo.fY, 133.f, 122.f, 0.f, 0.f, 0.f, 0.f, 0.3f, 133.f, 122.f, 0.f,
					0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, L"PlayerHit_Normal", { 0, 0, 0 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 2, 0, 0.1, 0. });
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_AlphaValue(180);
			break;

		case 1:
			break;
	}
	
}

// ������ ���ϰ� ���� �ڸ����� ���� ������, �� �ڸ����� ���� ������ ����ִ� �Լ�
int CObj::Get_NumIndex(int _iNum, int _iIndex)
{
	return (_iNum / (int)pow(10, _iIndex - 1)) % 10;
}

void CObj::Draw_Font(int _iDmg, bool _bCritical)
{
	int n = _iDmg;		// n : ������
	int iCount = 0;
	while (n != 0)
	{
		n = n / 10;
		++iCount;		// iCount : ������ �ڸ��� 
	}

	// ũƼƼ���� �� ���
	if(_bCritical)
	{
		// �� �������� �ڸ������� �ݺ�
		for (int i = 1; i <= iCount; ++i)
		{
			int iResult = Get_NumIndex(_iDmg, i);

			CObjMgr::Get_Instance()->Add_Object(OBJ_DAMAGEFONT,
				CAbstractFactory<CUI_Font>::
				Create_Obj(m_tInfo.fX - 24.f * i, m_tRectCollision.top, 2.f, 90.f, 1.2f, iResult, L"Damage"));
			CObjMgr::Get_Instance()->GetObjList(OBJ_DAMAGEFONT).back()->Set_ScaleX(32.f);
			CObjMgr::Get_Instance()->GetObjList(OBJ_DAMAGEFONT).back()->Set_ScaleY(26.f);
		}

		// ũ��Ƽ�� ��Ʈ
		// ������ ���� ũ��Ƽ�� ��Ʈ�� �����ش�
		if (!CObjMgr::Get_Instance()->GetObjList(OBJ_CRITICALFONT).empty())
			CObjMgr::Get_Instance()->Delete_ID(OBJ_CRITICALFONT);

		CObjMgr::Get_Instance()->Add_Object(OBJ_CRITICALFONT,
			CAbstractFactory<CUI_Combo>::
			Create_Obj(710.f, 420.f, 2.f, 0.f, 1.f, 4, L"Combo_Bonus"));
		CObjMgr::Get_Instance()->GetObjList(OBJ_CRITICALFONT).back()->Set_ScaleX(154.f);
		CObjMgr::Get_Instance()->GetObjList(OBJ_CRITICALFONT).back()->Set_ScaleY(16.f);
	}
	// ũƼ������ �ƴѰ��
	else
	{
		// �� �������� �ڸ������� �ݺ�
		for (int i = 1; i <= iCount; ++i)
		{
			int iResult = Get_NumIndex(_iDmg, i);

			CObjMgr::Get_Instance()->Add_Object(OBJ_DAMAGEFONT,
				CAbstractFactory<CUI_Font>::
				Create_Obj(m_tInfo.fX - 30.f - 13.f * i, m_tRectCollision.top, 2.f, 90.f, 1.2f, iResult, L"DamageFont1"));
		}
	}

	// ���߿� ������ ��� Airial
	if (m_eCurState == MON_LEVITATE_ATTACKED)
	{
		// ����� ��Ʈ
		// ������ ���� ����� ��Ʈ�� �����ش�
		if (!CObjMgr::Get_Instance()->GetObjList(OBJ_AIRIALFONT).empty())
			CObjMgr::Get_Instance()->Delete_ID(OBJ_AIRIALFONT);

		// ����� ��Ʈ���� ��� ũ��Ƽ�� ��Ʈ�� �����Ѵٸ� �Ʒ��� �������
		if (CObjMgr::Get_Instance()->GetObjList(OBJ_CRITICALFONT).empty())
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_AIRIALFONT,
				CAbstractFactory<CUI_Combo>::
				Create_Obj(710.f, 425.f, 2.f, 0.f, 1.f, 0, L"Combo_Bonus"));
			CObjMgr::Get_Instance()->GetObjList(OBJ_AIRIALFONT).back()->Set_ScaleX(154.f);
			CObjMgr::Get_Instance()->GetObjList(OBJ_AIRIALFONT).back()->Set_ScaleY(16.f);
		}
		else
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_AIRIALFONT,
				CAbstractFactory<CUI_Combo>::
				Create_Obj(710.f, 435.f, 2.f, 0.f, 1.f, 0, L"Combo_Bonus"));
			CObjMgr::Get_Instance()->GetObjList(OBJ_AIRIALFONT).back()->Set_ScaleX(154.f);
			CObjMgr::Get_Instance()->GetObjList(OBJ_AIRIALFONT).back()->Set_ScaleY(16.f);
		}
	}
}

// HpBar
void CObj::Draw_HpBar(float _fHp, int _iLine, float _fDmg)
{	
	// �� �� �ȿ��� Bar�� �󸶳� ǥ���Ұ��� ������ ���ϱ� ���� ���� fOneLineDmg
	// ���߿� (fOneLineDmg / ��)�� ������ŭ ü�¹ٸ� ǥ���� ���̴�
	float	fOneLineDmg = _fDmg;
	int		iLineCount = 0;

	// fHp		= ������ MaxHp
	// iLine	= ǥ���ϰ� ���� �� ��(���� ���� ����)
	// fDmg		= ���� �� ������

	// 1. �ϴ� ������ ü���� ǥ�� �� ���� ���� ���� ���Ѵ�
	float fShare = (_fHp / (float)_iLine);
	
	// 2. �� �򺸴� �������� �۾��������� �� �� ī������ ���� �ݺ��� ��ȸ
	while (fShare < fOneLineDmg)
	{
		fOneLineDmg -= fShare;
		++iLineCount;
	}

	// ���� ���� ü���� ��������
	/*if (m_iDrawLineCount < iLineCount)
		m_iDrawLineCount = 0;*/

	if(0 < m_iDrawLineCount)
		m_iDrawLineCount -= iLineCount;

	// �׸� �� �����ε���
	int	iSpreiteIndex	= m_iDrawLineCount % 5;

	// �������ٿ��� �ǰ� ���� ����
	float	fDrawRatio		= fOneLineDmg / fShare;

	if (!(CObjMgr::Get_Instance()->GetObjList(OBJ_BOSSHPBAR).empty()))
		CObjMgr::Get_Instance()->Delete_ID(OBJ_BOSSHPBAR);
	if (!(CObjMgr::Get_Instance()->GetObjList(OBJ_BOSSHP).empty()))
		CObjMgr::Get_Instance()->Delete_ID(OBJ_BOSSHP);
	if (!(CObjMgr::Get_Instance()->GetObjList(OBJ_MONHPBAR).empty()))
		CObjMgr::Get_Instance()->Delete_ID(OBJ_MONHPBAR);
	if (!(CObjMgr::Get_Instance()->GetObjList(OBJ_MONHP).empty()))
		CObjMgr::Get_Instance()->Delete_ID(OBJ_MONHP);
	if (!(CObjMgr::Get_Instance()->GetObjList(OBJ_MONPORTRAIT).empty()))
		CObjMgr::Get_Instance()->Delete_ID(OBJ_MONPORTRAIT);

	if (!(CObjMgr::Get_Instance()->GetObjList(OBJ_BOSSHPNUM).empty()))
		CObjMgr::Get_Instance()->Delete_ID(OBJ_BOSSHPNUM);
	if (!(CObjMgr::Get_Instance()->GetObjList(OBJ_MONHPNUM).empty()))
		CObjMgr::Get_Instance()->Delete_ID(OBJ_MONHPNUM);

	if (BOSS == m_eMonType)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_BOSSHPBAR, CAbstractFactory<CUI_BossBar>::Create_Obj(350.f, 100.f, L"BossBar"));
		CObjMgr::Get_Instance()->Add_Object(OBJ_BOSSHP, CAbstractFactory<CUI_BossHp>::Create_Obj(364.f, 100.f, iSpreiteIndex, fDrawRatio, m_iDrawLineCount, L"BossHp"));
		CObjMgr::Get_Instance()->GetObjList(OBJ_BOSSHP).back()->Set_Name(m_strName);
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONPORTRAIT, CAbstractFactory<CUI_Portrait>::Create_Obj(49.f, 98.5f, m_fPortraitX, m_fPortraitY, m_pPortrait, tagColor{ 0, 0, 0 }));
	}
	else
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONHPBAR, CAbstractFactory<CUI_MonsterBar>::Create_Obj(350.f, 100.f, L"MonsterBar"));
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONHP, CAbstractFactory<CUI_MonsterHp>::Create_Obj(364.f, 107.f, iSpreiteIndex, fDrawRatio, m_iDrawLineCount, L"MonsterHp"));
		CObjMgr::Get_Instance()->GetObjList(OBJ_MONHP).back()->Set_Name(m_strName);
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONPORTRAIT, CAbstractFactory<CUI_Portrait>::Create_Obj(49.f, 98.5f, m_fPortraitX, m_fPortraitY, m_pPortrait, tagColor{ 0, 0, 0 }));
	}
	
	int n = m_iDrawLineCount;
	int iCount = 0;
	if (0 < n && 0 < m_tInfo.fHp)
	{
		while (n != 0)
		{
			n = n / 10;
			++iCount;		// iCount : Hp�� �ڸ��� 
		}
	}
	else
		m_iDrawLineCount = 0;;

	// ���� Hp�� 0���Ϸ� ����������
	if (0 == m_iDrawLineCount)
	{
		// Hp�ٰ� �׷��������� �����
		if (!(CObjMgr::Get_Instance()->GetObjList(OBJ_MONHP).empty()))
			CObjMgr::Get_Instance()->Delete_ID(OBJ_MONHP);
		if (!(CObjMgr::Get_Instance()->GetObjList(OBJ_BOSSHP).empty()))
			CObjMgr::Get_Instance()->Delete_ID(OBJ_BOSSHP);
	}

	if (BOSS == m_eMonType)
	{
		if (0 == m_iDrawLineCount)
		{
			// X �� ǥ��
			CObjMgr::Get_Instance()->Add_Object(OBJ_BOSSHPNUM,
				CAbstractFactory<CUI_MonHpNum>::
				Create_Obj(622.f, 99.f, 7.5f, 10));

			CObjMgr::Get_Instance()->Add_Object(OBJ_BOSSHPNUM,
				CAbstractFactory<CUI_MonHpNum>::
				Create_Obj(641.f, 99.f, 7.5f, 0));
		}
		else
		{
			// X �� ǥ��
			CObjMgr::Get_Instance()->Add_Object(OBJ_BOSSHPNUM,
				CAbstractFactory<CUI_MonHpNum>::
				Create_Obj(660.f - 19.f * (iCount + 1), 99.f, 7.5f, 10));

			// ���� ������ Hp�� �ڸ������� �ݺ�
			for (int i = 1; i <= iCount; ++i)
			{
				int iResult = Get_NumIndex(m_iDrawLineCount, i);

				CObjMgr::Get_Instance()->Add_Object(OBJ_BOSSHPNUM,
					CAbstractFactory<CUI_MonHpNum>::
					Create_Obj(660.f - 19.f * i, 99.f, 7.5f, iResult));
			}
		}
	}
	else
	{
		if (0 == m_iDrawLineCount)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONHPNUM,
				CAbstractFactory<CUI_MonHpNum>::
				Create_Obj(622.f, 105.f, 7.5f, 10));

			CObjMgr::Get_Instance()->Add_Object(OBJ_MONHPNUM,
				CAbstractFactory<CUI_MonHpNum>::
				Create_Obj(641.f, 105.f, 7.5f, 0));
		}
		else
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONHPNUM,
				CAbstractFactory<CUI_MonHpNum>::
				Create_Obj(660.f - 19.f * (iCount + 1), 105.f, 7.5f, 10));

			// ���� ������ Hp�� �ڸ������� �ݺ�
			for (int i = 1; i <= iCount; ++i)
			{
				int iResult = Get_NumIndex(m_iDrawLineCount, i);

				CObjMgr::Get_Instance()->Add_Object(OBJ_BOSSHPNUM,
					CAbstractFactory<CUI_MonHpNum>::
					Create_Obj(660.f - 19.f * i, 105.f, 7.5f, iResult));
			}
		}
	}
}

void CObj::LifeTimeOver()
{
	if (m_fLifeTime < m_dwTime)
	{
		Set_Dead(true);
	}
}

void CObj::Update_Rect()
{
	// ������Ʈ ���� ũ�� ������Ʈ
	m_tRect.left	= LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top		= LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right	= LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom	= LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));

	// ������Ʈ �浹ü ������Ʈ
	m_tRectCollision.left = LONG(m_tInfo.fX - (m_fCollisionSizeX * 0.5f));
	m_tRectCollision.top = LONG(m_tInfo.fY - (m_fCollisionSizeY * 0.5f));
	m_tRectCollision.right = LONG(m_tInfo.fX + (m_fCollisionSizeX * 0.5f));
	m_tRectCollision.bottom = LONG(m_tInfo.fY + (m_fCollisionSizeY * 0.5f));

	m_lRectCollisionCenter = { m_tRectCollision.left + LONG(m_fCollisionSizeX * 0.5f),
							m_tRectCollision.top + LONG(m_fCollisionSizeY * 0.5f) };

	if (m_eCurState != MON_LEVITATE_ATTACKED)
	{
		// ������Ʈ - Ÿ�� �浹�� ������Ʈ
		m_tTileCollision.left = LONG(m_tInfo.fX - (m_fTileCollisionSizeX * 0.5f));
		m_tTileCollision.top = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f) - m_fTileCollisionSizeY);
		m_tTileCollision.right = LONG(m_tInfo.fX + (m_fTileCollisionSizeX * 0.5f));
		m_tTileCollision.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));

		m_lTileCollisionCenter = { m_tTileCollision.left + LONG(m_fTileCollisionSizeX * 0.5f),
								m_tTileCollision.top + LONG(m_fTileCollisionSizeY * 0.5f) };
	}
}

void CObj::Move_Frame()
{
	// �ð��� �帧�� ���� ������ ��ȭ
	if (m_tFrame.dwSpeed < m_tFrame.dwTime)
	{
		// if���� �ѹ� ���� ������ ������ ��ȭ�� ��
		++m_tFrame.iFrameStart;

		// ����ؼ� ��Ÿ Ÿ�� ����
		m_tFrame.dwTime = 0;

		// ��������Ʈ ���� �����ϸ� ù ��������Ʈ�� ���ư�
		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
	}
}
