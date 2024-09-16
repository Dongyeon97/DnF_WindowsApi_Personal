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

	// 현재 윈도우 상에서 마우스의 위치가 버튼의 Rect안에 들어온다면
	if (PtInRect(&m_tRect, pt))
	{
		// 그리고 마우스 왼쪽버튼을 누른다면
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
		{
			// lstrcmp함수 : 두 문자열이 같다면 0을 반환
			// 만약 눌려진 버튼의 FrameKey가 Start라면 씬을 STAGE로 변환
			if (!lstrcmp(L"Start", m_pFrameKey))
				CSceneMgr::Get_Instance()->Scene_Change(SC_SERIAROOM);

			// 만약 눌려진 버튼의 FrameKey가 Edit라면 씬을 STAGE로 변환
			else if (!lstrcmp(L"Edit", m_pFrameKey))
				CSceneMgr::Get_Instance()->Scene_Change(SC_EDIT_SERIAROOM);

			// 만약 눌려진 버튼의 FrameKey가 Exit라면 매개변수에 해당하는 창을 닫는다
			else if (!lstrcmp(L"Exit", m_pFrameKey))
				DestroyWindow(g_hWnd);
		}

		// 마우스가 버튼의 Rect안에 들어오면 버튼의 DrawID를 바꾼다(bmp파일에서 그려질 시작 위치를 크기만큼 수정하기 위함)
		m_iDrawID = 1;
	}

	else
	{
		m_iDrawID = 0;
	}
}

void CMyButton::Render(HDC hDC)
{
	// m_pFrameKey에 해당하는 버튼이 그려질 DC의 핸들 값 받아옴
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	// 해당 DC에 버튼을 그리고 hDC로 송출
	GdiTransparentBlt(hDC,			
		m_tRect.left,		// hDC에 버튼이 그려질 시작 위치
		m_tRect.top,
		(int)m_tInfo.fCX,	// 그려질 버튼의 사이즈
		(int)m_tInfo.fCY,
		hMemDC,				// 비트맵을 가지고 있는 DC 전달
		m_iDrawID * (int)m_tInfo.fCX,
		0,					// 비트맵을 출력할 시작 X,Y 좌표
		(int)m_tInfo.fCX,	// 복사할 비트맵의 가로, 세로 사이즈(항상 위의 m_tInfo.fCX, m_tInfo.fCY와 맞춰주어야 함)
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));	// 제거하고자 하는 색상값
}

void CMyButton::Release()
{
}
