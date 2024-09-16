#include "stdafx.h"
#include "UI_SkillIcon.h"

#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

CUI_SkillIcon::CUI_SkillIcon()
{
}

CUI_SkillIcon::~CUI_SkillIcon()
{
}

void CUI_SkillIcon::Initialize()
{
	m_eRender = OVERDUI;

	m_tInfo.fCX = 28.f;
	m_tInfo.fCY = 28.f;

	m_tRect.left = m_tInfo.fX - (m_tInfo.fCX * 0.5f);
	m_tRect.top = m_tInfo.fY - (m_tInfo.fCY * 0.5f);
	m_tRect.right = m_tInfo.fX + (m_tInfo.fCX * 0.5f);
	m_tRect.bottom = m_tInfo.fY + (m_tInfo.fCY * 0.5f);

	m_dwTime = 0;
}

int CUI_SkillIcon::Update()
{
	m_dwTime += CTimeMgr::Get_Instance()->GetfDT();

	m_tRect.left = m_tInfo.fX - (m_tInfo.fCX * 0.5f);
	m_tRect.top = m_tInfo.fY - (m_tInfo.fCY * 0.5f);
	m_tRect.right = m_tInfo.fX + (m_tInfo.fCX * 0.5f);
	m_tRect.bottom = m_tInfo.fY + (m_tInfo.fCY * 0.5f);

	LifeTimeOver();

	if (m_bDead)
		return OBJ_DEAD;

	return 0;
}

void CUI_SkillIcon::Late_Update()
{
}

void CUI_SkillIcon::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	// ���� ����
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 200;

	double fRendRatio = 0;
	double dRemainTime = 0;

	if (L"DBR" == Get_FrameKey())
	{
		fRendRatio = m_dwTime / (double)COOL_DBR;
		dRemainTime = COOL_DBR - m_dwTime;
	}
	else if (L"GunGuard" == Get_FrameKey())
	{
		fRendRatio = m_dwTime / (double)COOL_GUNGUARD;
		dRemainTime = COOL_GUNGUARD - m_dwTime;
	}
	else if (L"Zack2" == Get_FrameKey())
	{
		fRendRatio = m_dwTime / (double)COOL_ZACKS;
		dRemainTime = COOL_ZACKS - m_dwTime;
	}
	else if (L"BZack" == Get_FrameKey())
	{
		fRendRatio = m_dwTime / (double)COOL_ZACKS;
		dRemainTime = COOL_ZACKS - m_dwTime;
	}
	else if (L"WindMill_Off" == Get_FrameKey())
	{
		fRendRatio = m_dwTime / (double)COOL_WINDMILL;
		dRemainTime = COOL_WINDMILL - m_dwTime;
	}
	else if (L"MahaKick_Off" == Get_FrameKey())
	{
		fRendRatio = m_dwTime / (double)COOL_MAHA;
		dRemainTime = COOL_MAHA - m_dwTime;
	}
	else if (L"HeadShoot_Off" == Get_FrameKey())
	{
		fRendRatio = m_dwTime / (double)COOL_HEADSHOT;
		dRemainTime = COOL_HEADSHOT - m_dwTime;
	}
	else if (L"Moving_Shoot_Off" == Get_FrameKey())
	{
		fRendRatio = m_dwTime / (double)COOL_MOVINGSHOT;
		dRemainTime = COOL_MOVINGSHOT - m_dwTime;
	}
	else if (L"Random_Shoot_Off" == Get_FrameKey())
	{
		fRendRatio = m_dwTime / (double)COOL_SPREE;
		dRemainTime = COOL_SPREE - m_dwTime;
	}
	else if (L"Icon_Satelaser" == Get_FrameKey())
	{
		fRendRatio = m_dwTime / (double)COOL_SATELITE;
		dRemainTime = COOL_SATELITE - m_dwTime;
	}
	else if (L"Seven'sFlow_Off" == Get_FrameKey())
	{
		fRendRatio = m_dwTime / (double)COOL_AWAKENING;
		dRemainTime = COOL_AWAKENING - m_dwTime;
	}

	GdiAlphaBlend(hDC,
		m_tRect.left,
		m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY - (int)m_tInfo.fCY * fRendRatio,
		hMemDC,
		0,
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY - (int)m_tInfo.fCY * fRendRatio,
		bf);

	double dd = (round(dRemainTime * 10) / 10);

	// ��Ÿ���� 1�� �̻� ���������� ������ ǥ��
	if (1 < dd)
	{
		int idd = ceil(round(dRemainTime * 10) / 10);
		wstring str = to_wstring(idd);
		wstring sub = str.substr(0, 3);

		if (1 < sub.size())
		{
			SetTextColor(hDC, RGB(255, 255, 255));
			SetBkMode(hDC, TRANSPARENT); // �Ű����� DC�� ���ڹ���� �����ϰ� �Ѵ�. 
			SetTextAlign(hDC, TA_LEFT);
			TextOut(hDC, m_tInfo.fX - 8, m_tInfo.fY - 7, sub.c_str(), sub.size());
			SetTextColor(hDC, RGB(0, 0, 0));
			SetBkMode(hDC, OPAQUE);
		}
		else
		{
			SetTextColor(hDC, RGB(255, 255, 255));
			SetBkMode(hDC, TRANSPARENT); // �Ű����� DC�� ���ڹ���� �����ϰ� �Ѵ�. 
			SetTextAlign(hDC, TA_LEFT);
			TextOut(hDC, m_tInfo.fX - 5, m_tInfo.fY - 7, sub.c_str(), sub.size());
			SetTextColor(hDC, RGB(0, 0, 0));
			SetBkMode(hDC, OPAQUE);
		}
	}
	// ��Ÿ���� 1�� ������ ��� �Ҽ��� 1�ڸ����� ǥ��
	else
	{
		wstring str = to_wstring(dd);
		wstring sub = str.substr(0, 3);

		SetTextColor(hDC, RGB(255, 255, 255));
		SetBkMode(hDC, TRANSPARENT); // �Ű����� DC�� ���ڹ���� �����ϰ� �Ѵ�. 
		SetTextAlign(hDC, TA_LEFT);
		TextOut(hDC, m_tInfo.fX - 10, m_tInfo.fY - 7, sub.c_str(), sub.size());
		SetTextColor(hDC, RGB(0, 0, 0));
		SetBkMode(hDC, OPAQUE);
	}
}

void CUI_SkillIcon::Release()
{
}
