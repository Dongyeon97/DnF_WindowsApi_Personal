#include "stdafx.h"
#include "UI_MonHpNum.h"
#include "BmpMgr.h"
#include "UI_Font.h"

CUI_MonHpNum::CUI_MonHpNum()
{
}

CUI_MonHpNum::~CUI_MonHpNum()
{
	Release();
}

void CUI_MonHpNum::Initialize()
{
	m_eRender = TWOOVERDUI;

	m_tInfo.fCX = 21.f;
	m_tInfo.fCY = 18.f;

	m_dwTime = 0.f;

	m_fLifeTime = 7.5f;

	m_pFrameKey = L"MonsterHpNum";

}

int CUI_MonHpNum::Update()
{
	m_dwTime += CTimeMgr::Get_Instance()->GetfDT();

	LifeTimeOver();
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return 0;
}

void CUI_MonHpNum::Late_Update()
{
}

void CUI_MonHpNum::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	__super::Update_Rect();

	GdiTransparentBlt(hDC,			// ���� ����(���������� �׸��� �׸�) DC�� ����
		m_tRect.left, // ���� ���� ��ġ�� ��ǥ�� ���� (x,y ��ǥ)
		m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,				// ��Ʈ���� ������ �ִ� DC ����
		m_iSpriteIndex * (int)m_tInfo.fCX,					// ��Ʈ���� ����� ���� X,Y ��ǥ
		0,
		(int)m_tInfo.fCX,	// ������ ��Ʈ���� ����, ���� ������
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));
}

void CUI_MonHpNum::Release()
{
}