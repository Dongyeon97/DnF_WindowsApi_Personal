#include "stdafx.h"
#include "Seria.h"

#include "BmpMgr.h"
#include "SoundMgr.h"
#include "TimeMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"

#include "Player.h"
#include "ObjMgr.h"
#include "UI_Shop.h"

CSeria::CSeria()
{
}

CSeria::~CSeria()
{
	Release();
}

void CSeria::Initialize()
{
	// 스테이터스
	m_tInfo = { (SERIAROOM_SIZEX * 0.5f), (SERIAROOM_SIZEY * 0.5f) + 30.f, 56.f, 111.f };

	// 타일충돌 Rect 크기
	m_fTileCollisionSizeX = 64.f;
	m_fTileCollisionSizeY = 64.f;

	// 피격 Rect 크기
	m_fCollisionSizeX = 54.f;
	m_fCollisionSizeY = 140.f;

	// 애니메이션
	m_eRender = GAMEOBJECT;
	m_eCurState = MON_IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 9;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 0.2;
	m_tFrame.dwTime = 0;

	m_pFrameKey = L"Seria";

	// 상하좌우 방향 상태 이미지 불러오기
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/NPC/세리아/Seria.bmp", L"Seria");
}

int CSeria::Update()
{
	m_dwTime += CTimeMgr::Get_Instance()->GetfDT();
	m_tFrame.dwTime += CTimeMgr::Get_Instance()->GetfDT();

	if(m_dwTime > 10)
	{
		m_dwTime = 0;
		CSoundMgr::Get_Instance()->PlaySoundW(L"seria_amb_01.wav", SOUND_EFFECT, g_fVolume);
		Motion_Change();
	}
	
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CSeria::Late_Update()
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

	// 마우스의 위치가 세리아의 Rect안에 들어온다면
	if (PtInRect(&m_clickRect, pt))
	{
		// 그리고 마우스 왼쪽버튼을 누른다면
		// 상점이 열리고 세리아 사운드가 나야함
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON) && 0.2 < m_dwTime)
		{
			if (CObjMgr::Get_Instance()->GetObjList(OBJ_STORE).empty())
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_STORE, CAbstractFactory<CUI_Store>::Create_Obj(200.f, 300.f, 368.f, 464.f, L"UIstore2"));
				dynamic_cast<CUI_Store*>((CObjMgr::Get_Instance()->GetObjList(OBJ_STORE)).front())->Set_Render(true);
				CSoundMgr::Get_Instance()->PlaySoundW(L"InvenOn.wav", SOUND_EFFECT, g_fVolume);
			}
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
	}

	else
	{

	}
	__super::Move_Frame();
}

void CSeria::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	// 충돌 테스트용 렉트
	/*HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Rectangle(hDC, m_tRectCollision.left + fScrollX, m_tRectCollision.top + fScrollY,
		m_tRectCollision.right + fScrollX, m_tRectCollision.bottom + fScrollY);

	Rectangle(hDC, m_tRect.left + fScrollX, m_tRect.top + fScrollY,
		m_tRect.right + fScrollX, m_tRect.bottom + fScrollY);

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);*/
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
		RGB(255, 255, 255));
}

void CSeria::Release()
{

}

void CSeria::Update_Rect()
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

void CSeria::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case MON_IDLE:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 0.2;
			break;
		}

		// 새롭게 변경된 상태를 m_ePreState에 저장한다.
		m_ePreState = m_eCurState;
	}
}