#include "stdafx.h"
#include "PlayerAttack.h"

#include "TimeMgr.h"
#include "ScrollMgr.h"
#include "CollsionMgr.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "SoundMgr.h"

CPlayerAttack::CPlayerAttack()
{
}

CPlayerAttack::~CPlayerAttack()
{
	Release();
}

void CPlayerAttack::Initialize()
{
	m_eRender = EFFECT;

	// Ÿ���浹 Rect ũ��
	m_fTileCollisionSizeX = 64.f;
	m_fTileCollisionSizeY = 64.f;

	m_iAlpha = 225;
	m_iAlpha = 225;
}

int CPlayerAttack::Update()
{
	m_eRender = EFFECT;
	m_dwTime += CTimeMgr::Get_Instance()->GetfDT();
	m_tFrame.dwTime += CTimeMgr::Get_Instance()->GetfDT();

	LifeTimeOver();

	// ��弦 �ǰ� �̹���
	if (m_bDead && (L"LHeadShot" == Get_FrameKey()))
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
			Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX, m_tInfo.fY, 235.f, 149.f, 0.f, 0.f, 0.f, 0.f, 0.4f, 235.f, 149.f, 0.f,
				0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.1f, L"LHeadConflictEffect", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 3, 0, 0.1, 0. });

		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
			Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX, m_tInfo.fY, 288.f, 243.f, 0.f, 0.f, 0.f, 0.f, 0.4f, 288.f, 243.f, 0.f,
				0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.1f, L"LHeadShootHit", { 255, 0, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 3, 0, 0.1, 0. });

		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
			Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX, m_tInfo.fY, 272.f, 237.f, 0.f, 0.f, 0.f, 0.f, 0.3f, 272.f, 237.f, 0.f,
				0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.1f, L"LHeadShootNormal", { 255, 0, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 3, 0, 0.075, 0. });
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_AlphaValue(200);
		return OBJ_DEAD;
	}
	else if (m_bDead && (L"RHeadShot" == Get_FrameKey()))
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
			Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX, m_tInfo.fY, 235.f, 149.f, 0.f, 0.f, 0.f, 0.f, 0.4f, 235.f, 149.f, 0.f,
				0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.1f, L"RHeadConflictEffect", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 3, 0, 0.1, 0. });

		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
			Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX, m_tInfo.fY, 288.f, 243.f, 0.f, 0.f, 0.f, 0.f, 0.4f, 288.f, 243.f, 0.f,
				0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.1f, L"RHeadShootHit", { 255, 0, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 3, 0, 0.1, 0. });

		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
			Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX, m_tInfo.fY, 272.f, 237.f, 0.f, 0.f, 0.f, 0.f, 0.3f, 272.f, 237.f, 0.f,
				0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.1f, L"RHeadShootNormal", { 255, 0, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 3, 0, 0.075, 0. });
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_AlphaValue(200);
		return OBJ_DEAD;
	}
	


	// ��Ÿ / �̵���� �ǰ� �̹���
	else if (m_bDead && L"LBullet" == Get_FrameKey())
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
			Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX - 50.f, m_tInfo.fY, 73.f, 45.f, 0.f, 0.f, 0.f, 0.f, 0.3f, 73.f, 45.f, 0.f,
				0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.1f, L"LSFiringEffect", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 2, 0, 0.1, 0. });
		return OBJ_DEAD;
	}
	else if (m_bDead && L"LBullet_Low" == Get_FrameKey() && m_iDrawLineCount < 1)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
			Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX - 50.f, m_tInfo.fY - 15.f, 120.f, 63.f, 0.f, 0.f, 0.f, 0.f, 0.3f, 73.f, 45.f, 0.f,
				0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.1f, L"LFiringEffect", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 2, 0, 0.1, 0. });
		return OBJ_DEAD;
	}
	else if (m_bDead && L"RBullet" == Get_FrameKey())
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
			Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX + 50.f, m_tInfo.fY, 73.f, 45.f, 0.f, 0.f, 0.f, 0.f, 0.3f, 73.f, 45.f, 0.f,
				0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.1f, L"RSFiringEffect", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 2, 0, 0.1, 0. });
		return OBJ_DEAD;
	}
	else if (m_bDead && L"RBullet_Low" == Get_FrameKey() && m_iDrawLineCount < 1)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
			Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX + 50.f, m_tInfo.fY - 15.f, 120.f, 63.f, 0.f, 0.f, 0.f, 0.f, 0.3f, 73.f, 45.f, 0.f,
				0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.1f, L"RFiringEffect", { 255, 255, 255 }));
		CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 2, 0, 0.1, 0. });
		return OBJ_DEAD;
	}
	else if(m_bDead)
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
		// y��ǥ�� ���� ��ġ�� ���� �ߴٸ�
		else
		{
			if (m_iDrawLineCount < 1)
			{
				++m_iDrawLineCount;
				Set_Dead(true);
				// �Ѿ��� �ٴڿ� ����� �� �浹 �̹���
				if (L"LBullet_Low" == Get_FrameKey())
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
						Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX + 30.f, m_tInfo.fY, 82.f, 37.f, 0.f, 0.f, 0.f, 0.f, 0.2f, 82.f, 37.f, 0.f,
							0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.1f, L"LSConflictEffect", { 255, 255, 255 }));
					CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 3, 0, 0.05, 0. });
				}
				else if(L"RBullet_Low" == Get_FrameKey())
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayerAttack>::
						Create_Obj(ATT_JUSTEFFECT, false, m_tInfo.fX - 30.f, m_tInfo.fY, 82.f, 37.f, 0.f, 0.f, 0.f, 0.f, 0.2f, 82.f, 37.f, 0.f,
							0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.1f, L"RSConflictEffect", { 255, 255, 255 }));
					CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 3, 0, 0.05, 0. });
				}
			}
		}
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayerAttack::Late_Update()
{
	__super::Move_Frame();
}

void CPlayerAttack::Render(HDC hDC)
{
	float fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = m_iAlpha;

	if (L"DeathByRevolver2" == m_pFrameKey)
		bf.SourceConstantAlpha = 150;

	// Rectangle(hDC, m_tRectCollision.left + fScrollX, m_tRectCollision.top + fScrollY,
		// m_tRectCollision.right + fScrollX, m_tRectCollision.bottom + fScrollY);

	if (L"LBullet" == m_pFrameKey || L"RBullet" == m_pFrameKey || L"RBullet_Low" == m_pFrameKey || L"LBullet_Low" == m_pFrameKey)
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

void CPlayerAttack::Release()
{

}