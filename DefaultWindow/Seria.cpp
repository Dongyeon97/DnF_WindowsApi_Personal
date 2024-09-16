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
	// �������ͽ�
	m_tInfo = { (SERIAROOM_SIZEX * 0.5f), (SERIAROOM_SIZEY * 0.5f) + 30.f, 56.f, 111.f };

	// Ÿ���浹 Rect ũ��
	m_fTileCollisionSizeX = 64.f;
	m_fTileCollisionSizeY = 64.f;

	// �ǰ� Rect ũ��
	m_fCollisionSizeX = 54.f;
	m_fCollisionSizeY = 140.f;

	// �ִϸ��̼�
	m_eRender = GAMEOBJECT;
	m_eCurState = MON_IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 9;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 0.2;
	m_tFrame.dwTime = 0;

	m_pFrameKey = L"Seria";

	// �����¿� ���� ���� �̹��� �ҷ�����
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/NPC/������/Seria.bmp", L"Seria");
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

	// ���콺�� ��ġ�� �������� Rect�ȿ� ���´ٸ�
	if (PtInRect(&m_clickRect, pt))
	{
		// �׸��� ���콺 ���ʹ�ư�� �����ٸ�
		// ������ ������ ������ ���尡 ������
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

	// �浹 �׽�Ʈ�� ��Ʈ
	/*HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Rectangle(hDC, m_tRectCollision.left + fScrollX, m_tRectCollision.top + fScrollY,
		m_tRectCollision.right + fScrollX, m_tRectCollision.bottom + fScrollY);

	Rectangle(hDC, m_tRect.left + fScrollX, m_tRect.top + fScrollY,
		m_tRect.right + fScrollX, m_tRect.bottom + fScrollY);

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);*/
	// �浹 �׽�Ʈ�� ��Ʈ

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

		// ���Ӱ� ����� ���¸� m_ePreState�� �����Ѵ�.
		m_ePreState = m_eCurState;
	}
}