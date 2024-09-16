#include "Define.h"

class CMyBitmap
{
public:
	CMyBitmap();
	~CMyBitmap();
	
public:
	HDC		Get_MemDC() { return m_hMemDC; }

public:
	void	Load_Bmp(const TCHAR* pFilePath);
	void	Release();


private:
	HDC			m_hMemDC;		// 비트맵 이미지가 그려질 DC의 핸들
	HBITMAP		m_hBitmap;		// 비트맵 이미지의 핸들

	HBITMAP		m_hOldBmp;		// DC에 비트맵을 쥐어주고 가지고 있을 원본 핸들
	};


// DDB(Device Dependent Bitmap) : 장치에 의존적인 비트맵 포맷 형태, 이미지의 크기, 색상 등 기본적인 정보와 이미지 데이터로 구성되어 있어 다양한 해상도의 장치에는 광범위하게 사용되지 못한다.
// DIB(Device Independent Bitmap) : 장치에 독립적인 비트맵 포맷 형태, DDB에 비해 색상 테이블, 해상도 정보 등의 추가 정보를 가지므로 장치에 종속되지 않아 활용도가 더 광범위하고 호환성이 뛰어남