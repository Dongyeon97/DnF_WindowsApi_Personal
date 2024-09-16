#include "stdafx.h"
#include "MyButton.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"


CMyButton::CMyButton()
{
}


CMyButton::~CMyButton()
{
	Release();
}

void CMyButton::Initialize()
{
	m_eRender = GAMEOBJECT;

	m_tInfo.fCX = 168.f;
	m_tInfo.fCY = 45.f;
}

int CMyButton::Update()
{
	m_eRender = UI;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMyButton::Late_Update()
{
	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	// ���� ������ �󿡼� ���콺�� ��ġ�� ��ư�� Rect�ȿ� ���´ٸ�
	if (PtInRect(&m_tRect, pt))
	{
		// �׸��� ���콺 ���ʹ�ư�� �����ٸ�
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
		{
			// lstrcmp�Լ� : �� ���ڿ��� ���ٸ� 0�� ��ȯ
			// ���� ������ ��ư�� FrameKey�� Start��� ���� STAGE�� ��ȯ
			if (!lstrcmp(L"Start", m_pFrameKey))
				CSceneMgr::Get_Instance()->Scene_Change(SC_SERIAROOM);

			// ���� ������ ��ư�� FrameKey�� Edit��� ���� STAGE�� ��ȯ
			else if (!lstrcmp(L"Edit", m_pFrameKey))
				CSceneMgr::Get_Instance()->Scene_Change(SC_EDIT_SERIAROOM);

			// ���� ������ ��ư�� FrameKey�� Exit��� �Ű������� �ش��ϴ� â�� �ݴ´�
			else if (!lstrcmp(L"Exit", m_pFrameKey))
				DestroyWindow(g_hWnd);
		}

		// ���콺�� ��ư�� Rect�ȿ� ������ ��ư�� DrawID�� �ٲ۴�(bmp���Ͽ��� �׷��� ���� ��ġ�� ũ�⸸ŭ �����ϱ� ����)
		m_iDrawID = 1;
	}

	else
	{
		m_iDrawID = 0;
	}
}

void CMyButton::Render(HDC hDC)
{
	// m_pFrameKey�� �ش��ϴ� ��ư�� �׷��� DC�� �ڵ� �� �޾ƿ�
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	// �ش� DC�� ��ư�� �׸��� hDC�� ����
	GdiTransparentBlt(hDC,			
		m_tRect.left,		// hDC�� ��ư�� �׷��� ���� ��ġ
		m_tRect.top,
		(int)m_tInfo.fCX,	// �׷��� ��ư�� ������
		(int)m_tInfo.fCY,
		hMemDC,				// ��Ʈ���� ������ �ִ� DC ����
		m_iDrawID * (int)m_tInfo.fCX,
		0,					// ��Ʈ���� ����� ���� X,Y ��ǥ
		(int)m_tInfo.fCX,	// ������ ��Ʈ���� ����, ���� ������(�׻� ���� m_tInfo.fCX, m_tInfo.fCY�� �����־�� ��)
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));	// �����ϰ��� �ϴ� ����
}

void CMyButton::Release()
{
}
