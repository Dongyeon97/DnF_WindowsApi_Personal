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

	GdiTransparentBlt(hDC,			// 복사 받을(최종적으로 그림을 그릴) DC를 전달
		m_tRect.left, // 복사 받을 위치의 좌표를 전달 (x,y 좌표)
		m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,				// 비트맵을 가지고 있는 DC 전달
		m_iSpriteIndex * (int)m_tInfo.fCX,					// 비트맵을 출력할 시작 X,Y 좌표
		0,
		(int)m_tInfo.fCX,	// 복사할 비트맵의 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));
}

void CUI_MonHpNum::Release()
{
}