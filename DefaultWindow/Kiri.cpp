#include "stdafx.h"
#include "Kiri.h"

#include "BmpMgr.h"
#include "SoundMgr.h"
#include "TimeMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"

#include "Player.h"
#include "ObjMgr.h"
#include "UI_Shop.h"

CKiri::CKiri()
{
}

CKiri::~CKiri()
{
	Release();
}

void CKiri::Initialize()
{
	// 스테이터스
	m_tInfo = { 2000.f, 350.f , 50.f, 164.f };

	// 타일충돌 Rect 크기
	m_fTileCollisionSizeX = 64.f;
	m_fTileCollisionSizeY = 64.f;

	// 피격 Rect 크기
	m_fCollisionSizeX = 50.f;
	m_fCollisionSizeY = 164.f;

	// 애니메이션
	m_eRender = GAMEOBJECT;
	m_eCurState = MON_IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 0.4;
	m_tFrame.dwTime = 0;

	m_pFrameKey = L"Kiri";

	// 상하좌우 방향 상태 이미지 불러오기
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/NPC/키리/Kiri.bmp", L"Kiri");
}

int CKiri::Update()
{
	m_dwTime += CTimeMgr::Get_Instance()->GetfDT();
	m_tFrame.dwTime += CTimeMgr::Get_Instance()->GetfDT();
	m_TextTerm += CTimeMgr::Get_Instance()->GetfDT();

	CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).back();

	float fDistance = fabsf(pPlayer->Get_Info().fX - m_tInfo.fX);

	if (6 < m_dwTime && 400.f > fDistance)
	{
		m_dwTime = 0;
		switch (rand() % 2)
		{
		case 0:
			CSoundMgr::Get_Instance()->PlaySoundW(L"kiri1.wav", SOUND_EFFECT, g_fVolume);
			break;

		case 1:
			CSoundMgr::Get_Instance()->PlaySoundW(L"kiri2.wav", SOUND_EFFECT, g_fVolume);
			break;
		}
	}

	Motion_Change();

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CKiri::Late_Update()
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	RECT m_clickRect = {};

	m_clickRect.left = m_tRectCollision.left + fScrollX;
	m_clickRect.top = m_tRectCollision.top + fScrollY;
	m_clickRect.right = m_tRectCollision.right + fScrollX;
	m_clickRect.bottom = m_tRectCollision.bottom + fScrollY;

	__super::Move_Frame();
}

void CKiri::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	// 충돌 테스트용 렉트
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
	// 충돌 테스트용 렉트

	GdiTransparentBlt(hDC,
		m_tRect.left + (int)fScrollX,
		m_tRect.top + (int)fScrollY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(0, 0, 0));

	// 대사 출력
	if (0 < m_TextTerm && 6 > m_TextTerm)
	{
		wstring str1 = L"거기 잘생긴 모험가! 강화좀 해보는게 어때?";

		HFONT font = CreateFont(20, 0, 0, 0, 850, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
			VARIABLE_PITCH | FF_ROMAN, L"Tahoma");
		HFONT oldfont = (HFONT)SelectObject(hDC, font);

		SetTextColor(hDC, RGB(0, 0, 0));
		SetBkMode(hDC, TRANSPARENT); // 매개변수 DC의 글자배경을 투명하게 한다. 
		SetTextAlign(hDC, TA_LEFT);
		TextOut(hDC, m_tInfo.fX + fScrollX - 130, m_tInfo.fY + fScrollY - 100, str1.c_str(), str1.size());
		SetBkMode(hDC, OPAQUE);

		SelectObject(hDC, oldfont);
		DeleteObject(font);
	}
	if (10 < m_TextTerm)
		m_TextTerm = 0;
}

void CKiri::Release()
{

}

void CKiri::Update_Rect()
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
}

void CKiri::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case MON_IDLE:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 0.4;
			break;
		}

		// 새롭게 변경된 상태를 m_ePreState에 저장한다.
		m_ePreState = m_eCurState;
	}
}