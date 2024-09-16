#include "stdafx.h"
#include "MonsterAttack.h"

#include "TimeMgr.h"
#include "ScrollMgr.h"
#include "CollsionMgr.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "MonsterAttack2.h"
#include "SoundMgr.h"

CMonsterAttack::CMonsterAttack()
{
}

CMonsterAttack::~CMonsterAttack()
{
	Release();
}

void CMonsterAttack::Initialize()
{
	m_eRender = GAMEOBJECT;

	// Ÿ���浹 Rect ũ��
	m_fTileCollisionSizeX = 64.f;
	m_fTileCollisionSizeY = 64.f;
}

int CMonsterAttack::Update()
{
	m_dwTime += CTimeMgr::Get_Instance()->GetfDT();
	m_tFrame.dwTime += CTimeMgr::Get_Instance()->GetfDT();

	LifeTimeOver();
	if (m_bDead && L"Isys_Feather" == Get_FrameKey())
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonsterAttack2>::
			Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX - 70.f, m_tInfo.fY - 200.f, 420.f, 525.f, 0.f, 0.f, 0.f, 0.f, 1.3f, 400.f, 400.f, 0.f,
				0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.1f, L"Isys_FeatherAttack", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 12, 0, 0.1, 0. });
		CSoundMgr::Get_Instance()->PlaySoundW(L"isys_finalatk_explo.ogg", SOUND_EFFECT, g_fVolume);
		return OBJ_DEAD;
	}
	else if (m_bDead)
		return OBJ_DEAD;

	// �߻� ���� ��ǥ�� ( 0.f, 0.f )�� ����ü�� ���� ���Ǿ��� �׳� �߻�Ǵ� ������Ʈ��
	if (0.f == m_fEndPosX && 0.f == m_fEndPosY)
	{
		m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
		m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));
	}
	// ���� �ϳ��� ���� ��ǥ�� ������ �� ������ �����ϸ� ����
	else
	{
		// �߻�ü�� �������� + 20.f���� �����ʿ� ������ Ȥ�� -20.f���� ���ʿ� ������
		// �߻縦 �����Ѵ�
		if (m_fEndPosX + 20.f < m_tInfo.fX || m_fEndPosX - 20.f > m_tInfo.fX)
		{
			m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
		}
		// y�� ���� ����
		if (m_fEndPosY + 20.f < m_tInfo.fY || m_fEndPosY - 20.f > m_tInfo.fY)
		{
			m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));
		}
		// ���� �ߴٸ�
		else
		{
			if (m_iDrawLineCount < 1)
			{
				++m_iDrawLineCount;
				CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonsterAttack2>::
					Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX - 70.f, m_tInfo.fY - 200.f, 420.f, 525.f, 0.f, 0.f, 0.f, 0.f, 1.3f, 400.f, 400.f, 0.f,
						0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.1f, L"Isys_FeatherAttack", { 255, 255, 255 }));
				CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 12, 0, 0.1, 0. });
				CSoundMgr::Get_Instance()->PlaySoundW(L"isys_finalatk_explo.ogg", SOUND_EFFECT, g_fVolume);
				CSoundMgr::Get_Instance()->PlaySoundW(L"isys_finalatk_feather.ogg", SOUND_EFFECT2, g_fVolume);
			}
		}
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMonsterAttack::Late_Update()
{
	__super::Move_Frame();
}

void CMonsterAttack::Render(HDC hDC)
{
	float fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	// Rectangle(hDC, m_tRectCollision.left + fScrollX, m_tRectCollision.top + fScrollY,
		// m_tRectCollision.right + fScrollX, m_tRectCollision.bottom + fScrollY);

	// ���� ����
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 255;

	if (L"Isys_MeetLightning" == Get_FrameKey())
	{
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
			RGB(m_tRGB.R, m_tRGB.G, m_tRGB.B));
	}
	else
	{
		GdiAlphaBlend(hDC,
			m_tRect.left + (long)fScrollX,
			m_tRect.top + (long)fScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hMemDC,
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			bf);
	}
}

void CMonsterAttack::Release()
{
}