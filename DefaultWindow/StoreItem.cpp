#include "stdafx.h"
#include "StoreItem.h"

#include "ObjMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "UI_Inven.h"
#include "UI_Shop.h"


CStoreItem::CStoreItem()
	:m_iIndex(0)
{

}


CStoreItem::~CStoreItem()
{
	Release();
}

void CStoreItem::Initialize()
{
	m_eRender = OVERDUI;

	m_tInfo.fCX = 28.f;
	m_tInfo.fCY = 28.f;

	m_iAlpha = 255;
}

int CStoreItem::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CStoreItem::Late_Update()
{
}

void CStoreItem::Render(HDC hDC)
{
	// m_pFrameKey에 해당하는 버튼이 그려질 DC의 핸들 값 받아옴
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	// 알파 블렌딩
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = m_iAlpha;

	if (dynamic_cast<CUI_Store*>((CObjMgr::Get_Instance()->GetObjList(OBJ_STORE)).front())->Get_Render())
	{
		GdiAlphaBlend(hDC,
			m_tRect.left,
			m_tRect.top,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hMemDC,
			0,
			0,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			bf);

		HFONT font = CreateFont(13, 0, 0, 0, 750, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
			VARIABLE_PITCH | FF_ROMAN, L"굴림");
		HFONT oldfont = (HFONT)SelectObject(hDC, font);

		SetTextColor(hDC, RGB(m_tRGB.R, m_tRGB.G, m_tRGB.B));
		SetBkMode(hDC, TRANSPARENT);
		SetTextAlign(hDC, TA_RIGHT);
		TextOut(hDC, m_tRect.left + 152, m_tRect.top, m_strName.c_str(), m_strName.size());

		SetTextColor(hDC, RGB(0, 0, 0));

		POINT	pt{};
		pt.x = CObjMgr::Get_Instance()->GetObjList(OBJ_MOUSEPOINT).back()->Get_Info().fX;
		pt.y = CObjMgr::Get_Instance()->GetObjList(OBJ_MOUSEPOINT).back()->Get_Info().fY;

		// 마우스의 위치가 아이템의 Rect안에 들어온다면
		if (PtInRect(&m_tRect, pt))
		{
			// m_iOption = 1;
			// dynamic_cast<CUI_Store*>(CObjMgr::Get_Instance()->GetObjList(OBJ_STORE).back())->Set_PickMode(true);

			/*HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Item_Back3");

			BLENDFUNCTION bf2 = {};

			bf2.BlendOp = AC_SRC_OVER;
			bf2.BlendFlags = 0;
			bf2.AlphaFormat = AC_SRC_ALPHA;
			bf2.SourceConstantAlpha = 225;*/

			/*GdiAlphaBlend(hDC,
				m_tRect.left - 50,
				m_tRect.top + 20,
				200,
				300,
				hMemDC,
				0,
				0,
				200,
				300,
				bf);*/

			/*for (auto& iter : CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM))
			{
				if ((m_tRect.left - 50 < iter->Get_Info().fX && m_tRect.left + 150 > iter->Get_Info().fX)
					&& (m_tRect.top + 20 < iter->Get_Info().fY && m_tRect.top + 320 > iter->Get_Info().fY))
					iter->Set_AlphaValue(30);
			}*/

			/*SetTextColor(hDC, RGB(m_tRGB.R, m_tRGB.G, m_tRGB.B));
			SetBkMode(hDC, OPAQUE);
			SetTextAlign(hDC, TA_RIGHT);
			TextOut(hDC, m_tRect.left + 136, m_tRect.top + 80, m_strName.c_str(), m_strName.size());

			SetTextColor(hDC, RGB(0, 0, 0));

			TextOut(hDC, m_tRect.left + 106, m_tRect.top + 100, L"공격력 : ", 7);
			TextOut(hDC, m_tRect.left + 136, m_tRect.top + 100, to_wstring((int)m_tInfo.fAtk).c_str(), to_wstring((int)m_tInfo.fAtk).size());

			TextOut(hDC, m_tRect.left + 106, m_tRect.top + 120, L"체력 : ", 6);
			TextOut(hDC, m_tRect.left + 136, m_tRect.top + 120, to_wstring((int)m_tInfo.fHp).c_str(), to_wstring((int)m_tInfo.fHp).size());*/
		}

		//else if (1 == m_iOption)
		//{
		//	if (dynamic_cast<CUI_Store*>(CObjMgr::Get_Instance()->GetObjList(OBJ_STORE).back())->Get_PickMode())
		//		dynamic_cast<CUI_Store*>(CObjMgr::Get_Instance()->GetObjList(OBJ_STORE).back())->Set_PickMode(false);
		//}

		SelectObject(hDC, oldfont);
		DeleteObject(font);
	}
}

void CStoreItem::Release()
{
}
