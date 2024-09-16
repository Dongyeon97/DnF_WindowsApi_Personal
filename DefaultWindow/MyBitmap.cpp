#include "stdafx.h"
#include "MyBitmap.h"


CMyBitmap::CMyBitmap()
{
}


CMyBitmap::~CMyBitmap()
{
	Release();
}

void CMyBitmap::Load_Bmp(const TCHAR * pFilePath)
{
	// 메인 윈도우의 DC를 가져온다.
	HDC			hDC = GetDC(g_hWnd);

	// 메인 윈도우의 DC정보를 복제하여 새로운 DC m_hMemDC를 만든다.
	m_hMemDC = CreateCompatibleDC(hDC);

	// 메인 윈도우의 복제카운트를 하나 내린다.
	ReleaseDC(g_hWnd, hDC);

	// 파일 경로에서 이미지를 불러와 비트맵 핸들 변수인 'm_hBitmap'에 저장한다
	m_hBitmap = (HBITMAP)LoadImage(NULL,			//프로그램 인스턴스 핸들
									pFilePath,		// 파일의 경로를 전달
									IMAGE_BITMAP,	// 어떤 타입을 읽어올지 전달
									0,				// 가로, 세로 크기 전달(우리는 파일에서 읽어올 것이기 때문에 별도로 넘겨줄 필요 없음)
									0,
									LR_LOADFROMFILE | LR_CREATEDIBSECTION); // LR_LOADFROMFILE : 파일에서 이미지를 불러오는 옵션 | LR_CREATEDIBSECTION : 읽어온 파일을 DIB 형태로 변환

	// SelectObject : 준비한 DC의 GDI 오브젝트를 불러온 비트맵을 선택하는 함수
	// 복제된 MemDC에 이미지가 저장된 비트맵이 선택된다.
	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
}

void CMyBitmap::Release()
{
	SelectObject(m_hMemDC, m_hOldBmp);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}

