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

// �̹����� �ҷ��� Ű�� �Բ� map�� ��������ִ� �Լ�
void CBmpMgr::Insert_Bmp(const TCHAR * pFilePath, const TCHAR * pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTagFinder(pImgKey));

	// Ű�� �ش��ϴ� �̹����� ã������ �ʾҴٸ�, �ߺ� Ű�� ���ٸ�?
	if (iter == m_mapBit.end())
	{
		CMyBitmap*		pBmp = new CMyBitmap;

		// ���ϰ�ο� �ش��ϴ� �̹����� ã�Ƽ� MemDC�� ����ش�.
		pBmp->Load_Bmp(pFilePath);

		// Ű�� �Բ� ��Ʈ�������� map�� ����ȴ�.
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

// Ű�� �ش��ϴ� �̹����� ã�Ƽ� �ش� �̹����� MemDC�� ��ȯ���ִ� �Լ�
HDC CBmpMgr::Find_Img(const TCHAR * pImgKey)
{
	// �ʿ��� Ű�� �ش��ϴ� �̹����� ã�´�
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTagFinder(pImgKey));

	// �̹����� ã������ �ʾҴٸ� nullptr�� ��ȯ
	if (iter == m_mapBit.end())
		return nullptr;

	// �̹����� ã�����ٸ� �ش� �̹����� MemDC�� ��ȯ
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
