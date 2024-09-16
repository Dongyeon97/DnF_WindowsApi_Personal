#include "stdafx.h"
#include "BmpMgr.h"

CBmpMgr* CBmpMgr::m_pInstance = nullptr;

CBmpMgr::CBmpMgr()
{
}

CBmpMgr::~CBmpMgr()
{
	Release();
}

// 이미지를 불러와 키와 함께 map에 저장시켜주는 함수
void CBmpMgr::Insert_Bmp(const TCHAR * pFilePath, const TCHAR * pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTagFinder(pImgKey));

	// 키에 해당하는 이미지가 찾아지지 않았다면, 중복 키가 없다면?
	if (iter == m_mapBit.end())
	{
		CMyBitmap*		pBmp = new CMyBitmap;

		// 파일경로에 해당하는 이미지를 찾아서 MemDC에 쥐어준다.
		pBmp->Load_Bmp(pFilePath);

		// 키와 함께 비트맵정보가 map에 저장된다.
		m_mapBit.emplace(pImgKey, pBmp);
	}

}

void CBmpMgr::Release_Bmp(const TCHAR* pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTagFinder(pImgKey));

	if (iter != m_mapBit.end())
	{
		delete iter->second;
		m_mapBit.erase(iter);
	}
}

// 키에 해당하는 이미지를 찾아서 해당 이미지의 MemDC를 반환해주는 함수
HDC CBmpMgr::Find_Img(const TCHAR * pImgKey)
{
	// 맵에서 키에 해당하는 이미지를 찾는다
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTagFinder(pImgKey));

	// 이미지가 찾아지지 않았다면 nullptr을 반환
	if (iter == m_mapBit.end())
		return nullptr;

	// 이미지가 찾아졌다면 해당 이미지의 MemDC를 반환
	return iter->second->Get_MemDC();
}

void CBmpMgr::Release(void)
{
	for (auto& iter : m_mapBit)
	{
		if (nullptr != iter.second)
		{
			Safe_Delete(iter.second);
			iter.second = nullptr;
		}
	}

	m_mapBit.clear();
}
