#include "stdafx.h"
#include "UI_Shop.h"

#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "Item.h"
#include "UI_Inven.h"
#include "StoreItem.h"
#include "CollsionMgr.h"
#include "KeyMgr.h"
#include "UI_Info.h"

CUI_Store::CUI_Store()
	: m_bRender(false)
	, m_bClicked(false)
	, m_bPickMode(false)
{
}

CUI_Store::~CUI_Store()
{
	Release();
}

void CUI_Store::Initialize()
{
	m_eRender = UI;

	m_bOpened = true;

	m_tInfo.fX = 200.f;
	m_tInfo.fY = 300.f;

	m_tInfo.fCX = 368.f;
	m_tInfo.fCY = 464.f;

	m_tRect.left = m_tInfo.fX - (m_tInfo.fCX * 0.5f);
	m_tRect.top = m_tInfo.fY - (m_tInfo.fCY * 0.5f);
	m_tRect.right = m_tInfo.fX + (m_tInfo.fCX * 0.5f);
	m_tRect.bottom = m_tInfo.fY + (m_tInfo.fCY * 0.5f);

	// 아이템의 중점을 잡아준다.
	float	fX = m_tRect.left + (LONG)31 + (0 * 170);
	float	fY = m_tRect.top + (LONG)100 + (0 * 59);

	// 구원의 이기 리볼버
	CObjMgr::Get_Instance()->Add_Object(OBJ_STOREITEM, CAbstractFactory<CStoreItem>::Create_Obj(fX, fY, 1200, 0, L"구원의 이기 - 리볼버", L"Weapon2"));
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_ItemType(ITEM_WEAPON);
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_RGB({ 220, 170, 0 });

	fX = m_tRect.left + (LONG)31 + (1 * 170);
	fY = m_tRect.top + (LONG)100 + (0 * 59);

	// 무한한 탐식의 증적
	CObjMgr::Get_Instance()->Add_Object(OBJ_STOREITEM, CAbstractFactory<CStoreItem>::Create_Obj(fX, fY, 250, 1500, L"무한한 탐식의 증적", L"SupportItem"));
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_ItemType(ITEM_ASSIST);
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_RGB({ 220, 170, 0 });

	fX = m_tRect.left + (LONG)31 + (0 * 170);
	fY = m_tRect.top + (LONG)100 + (1 * 59);

	// 무한한 탐식의 얼개
	CObjMgr::Get_Instance()->Add_Object(OBJ_STOREITEM, CAbstractFactory<CStoreItem>::Create_Obj(fX, fY, 275, 0, L"무한한 탐식의 얼개", L"Bracelet3"));
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_ItemType(ITEM_BRACELET);
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_RGB({ 220, 170, 0 });

	fX = m_tRect.left + (LONG)31 + (1 * 170);
	fY = m_tRect.top + (LONG)100 + (1 * 59);

	// 무한한 탐식의 형상
	CObjMgr::Get_Instance()->Add_Object(OBJ_STOREITEM, CAbstractFactory<CStoreItem>::Create_Obj(fX, fY, 200, 2500, L"무한한 탐식의 형상", L"Neckless3"));
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_ItemType(ITEM_NECKLACE);
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_RGB({ 220, 170, 0 });

	fX = m_tRect.left + (LONG)31 + (0 * 170);
	fY = m_tRect.top + (LONG)100 + (2 * 59);

	// 무한한 탐식의 잔재
	CObjMgr::Get_Instance()->Add_Object(OBJ_STOREITEM, CAbstractFactory<CStoreItem>::Create_Obj(fX, fY, 275, 0, L"무한한 탐식의 잔재", L"Ring3"));
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_ItemType(ITEM_RING);
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_RGB({ 220, 170, 0 });

	fX = m_tRect.left + (LONG)31 + (1 * 170);
	fY = m_tRect.top + (LONG)100 + (2 * 59);

	// 무한한 탐식의 근원
	CObjMgr::Get_Instance()->Add_Object(OBJ_STOREITEM, CAbstractFactory<CStoreItem>::Create_Obj(fX, fY, 0, 5000, L"무한한 탐식의 근원", L"MasicStone3"));
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_ItemType(ITEM_STONE);
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_RGB({ 220, 170, 0 });

	fX = m_tRect.left + (LONG)31 + (0 * 170);
	fY = m_tRect.top + (LONG)100 + (3 * 59);

	// 택틱컬 커맨더 상의
	CObjMgr::Get_Instance()->Add_Object(OBJ_STOREITEM, CAbstractFactory<CStoreItem>::Create_Obj(fX, fY, 600, 4000, L"택틱컬 커맨더 상의", L"Armor6"));
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_ItemType(ITEM_TOP);
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_RGB({ 220, 170, 0 });

	fX = m_tRect.left + (LONG)31 + (1 * 170);
	fY = m_tRect.top + (LONG)100 + (3 * 59);

	// 택틱컬 리더 하의
	CObjMgr::Get_Instance()->Add_Object(OBJ_STOREITEM, CAbstractFactory<CStoreItem>::Create_Obj(fX, fY, 600, 4000, L"택틱컬 리더 하의", L"Pant6"));
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_ItemType(ITEM_PANTS);
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_RGB({ 220, 170, 0 });

	fX = m_tRect.left + (LONG)31 + (0 * 170);
	fY = m_tRect.top + (LONG)100 + (4 * 59);

	// 택틱컬 오피서 어깨
	CObjMgr::Get_Instance()->Add_Object(OBJ_STOREITEM, CAbstractFactory<CStoreItem>::Create_Obj(fX, fY, 300, 2000, L"택틱컬 오피서 어깨", L"Shoulder6"));
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_ItemType(ITEM_SHOULDER);
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_RGB({ 220, 170, 0 });

	fX = m_tRect.left + (LONG)31 + (1 * 170);
	fY = m_tRect.top + (LONG)100 + (4 * 59);

	// 택틱컬 로드 벨트
	CObjMgr::Get_Instance()->Add_Object(OBJ_STOREITEM, CAbstractFactory<CStoreItem>::Create_Obj(fX, fY, 300, 2000, L"택틱컬 로드 벨트", L"Belt6"));
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_ItemType(ITEM_WAIST);
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_RGB({ 220, 170, 0 });

	fX = m_tRect.left + (LONG)31 + (0 * 170);
	fY = m_tRect.top + (LONG)100 + (5 * 59);

	// 택틱컬 치프 신발
	CObjMgr::Get_Instance()->Add_Object(OBJ_STOREITEM, CAbstractFactory<CStoreItem>::Create_Obj(fX, fY, 300, 2000, L"택틱컬 치프 신발", L"Shoes6"));
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_ItemType(ITEM_SHOES);
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_RGB({ 220, 170, 0 });

	fX = m_tRect.left + (LONG)31 + (1 * 170);
	fY = m_tRect.top + (LONG)100 + (5 * 59);

	// 쥬신 140기 화이팅
	CObjMgr::Get_Instance()->Add_Object(OBJ_STOREITEM, CAbstractFactory<CStoreItem>::Create_Obj(fX, fY, 50, 200, L"쥬신 140기 화이팅", L"Title1"));
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_ItemType(ITEM_TITLE);
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_RGB({ 165, 120, 215 });
}

int CUI_Store::Update()
{
	m_dwTime += CTimeMgr::Get_Instance()->GetfDT();

	__super::Update_Rect();

	return 0;
}

void CUI_Store::Late_Update()
{
	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	RECT m_clickRect = {};

	m_clickRect.left = m_tRect.left;
	m_clickRect.top = m_tRect.top;
	m_clickRect.right = m_tRect.right;
	m_clickRect.bottom = m_tRect.bottom - 400;

	if (m_bRender)
	{
		// 마우스의 위치가 세리아의 Rect안에 들어온다면
		if (PtInRect(&m_clickRect, pt))
		{
			// 그리고 마우스 왼쪽버튼을 누른다면
			// 다른 UI와 겹쳐 있을시 화면 맨 위로 와야함
			if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
			{
				// 인벤토리나 내정보가 화면상에 표시되고 있을시
				if (dynamic_cast<CUI_Inven*>((CObjMgr::Get_Instance()->GetObjList(OBJ_INVEN)).front())->Get_Render() ||
					dynamic_cast<CUI_Info*>((CObjMgr::Get_Instance()->GetObjList(OBJ_MYINFO)).front())->Get_Render())
				{
					// 상점을 QUADOVERDUI로 변경하고, 상점 아이템을 OCTAOVERDUI로 변경
					Set_RenderID(OCTAOVERDUI);
					list<CObj*> storeItem = CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM);
					for (auto& iter : storeItem)
						iter->Set_RenderID(HEXAOVERDUI);

					// 만약 다른 창이 있다면, 다른 창들의 RenderID를 변경
					// 인벤토리가 더 위에 있는 경우
					if (int(CObjMgr::Get_Instance()->GetObjList(OBJ_INVEN).front()->Get_RenderID())
					> int(CObjMgr::Get_Instance()->GetObjList(OBJ_MYINFO).front()->Get_RenderID()) - 2)
					{
						CObjMgr::Get_Instance()->GetObjList(OBJ_INVEN).front()->Set_RenderID(TWOOVERDUI);
						list<CObj*> invenItem = CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM);
						for (auto& iter : invenItem)
							iter->Set_RenderID(TRIPLEOVERDUI);

						CObjMgr::Get_Instance()->GetObjList(OBJ_MYINFO).front()->Set_RenderID(OVERDUI);
					}
					// 내정보가 더 위에 있는 경우
					else
					{
						CObjMgr::Get_Instance()->GetObjList(OBJ_MYINFO).front()->Set_RenderID(QUADOVERDUI);

						CObjMgr::Get_Instance()->GetObjList(OBJ_INVEN).front()->Set_RenderID(TWOOVERDUI);
						list<CObj*> invenItem = CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM);
						for (auto& iter : invenItem)
							iter->Set_RenderID(TRIPLEOVERDUI);
					}
				}
				m_dwTime = 0;
			}

			if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON) && !m_bClicked)
			{
				m_bClicked = true;

				m_Prept = pt;
			}

			else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON) && m_bClicked)
			{
				m_tInfo.fX += pt.x - m_Prept.x;
				m_tInfo.fY += pt.y - m_Prept.y;

				for (auto& Item : CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM))
				{
					Item->Set_PosX(pt.x - m_Prept.x);
					Item->Set_PosY(pt.y - m_Prept.y);
				}

				m_Prept = pt;
			}
			else if (CKeyMgr::Get_Instance()->Key_Up(VK_LBUTTON) && m_bClicked)
			{
				m_bClicked = false;
			}
		}
	}
	if (!m_bPickMode)
	{
		for (auto& iter : CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM))
			iter->Set_AlphaValue(255);
	}

	CCollsionMgr::Collision_Rect2(CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM), CObjMgr::Get_Instance()->GetObjList(OBJ_MOUSEPOINT));
}

void CUI_Store::Render(HDC hDC)
{
	if (m_bRender)
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

		GdiTransparentBlt(hDC,
			m_tRect.left,
			m_tRect.top,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hMemDC,
			0,
			0,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 255, 255));
	}

}

void CUI_Store::Release()
{
}
