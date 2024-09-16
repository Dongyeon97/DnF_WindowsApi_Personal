#include "stdafx.h"
#include "UI_Inven.h"

#include "SceneMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "CollsionMgr.h"
#include "Item.h"
#include "UI_Info.h"
#include "UI_Shop.h"

bool CUI_Inven::m_bIndex[56] = {0,};
bool CUI_Inven::m_bEquipIndex[12] = { 0, };

CUI_Inven::CUI_Inven()
	:m_bRender(false)
	, m_bClicked(false)
	, m_bPickMode(false)
{

}

CUI_Inven::~CUI_Inven()
{
	Release();
}

void CUI_Inven::Initialize()
{
	m_eRender = UI;

	m_bOpened = true;

	m_tInfo.fX = 630.f;
	m_tInfo.fY = 265.f;

	m_tInfo.fCX = 260.f;
	m_tInfo.fCY = 530.f;

	m_tRect.left = m_tInfo.fX - (m_tInfo.fCX * 0.5f);
	m_tRect.top = m_tInfo.fY - (m_tInfo.fCY * 0.5f);
	m_tRect.right = m_tInfo.fX + (m_tInfo.fCX * 0.5f);
	m_tRect.bottom = m_tInfo.fY + (m_tInfo.fCY * 0.5f);

	// 아이템의 중점을 잡아준다.
	int iIndex = Find_InvenIndex();
	Add_Item(iIndex, 200.f, 0.f, L"더러운 피의 쾌", { 200, 60, 200 }, L"Weapon4", ITEM_WEAPON);

	iIndex = Find_InvenIndex();
	Add_Item(iIndex, 300.f, 0.f, L"가이스타드", { 165, 120, 215 }, L"Weapon3", ITEM_WEAPON);

	iIndex = Find_InvenIndex();
	Add_Item(iIndex, 50.f, 0.f, L"준환쌤의 허름한 리볼버", { 170, 95, 30 }, L"Weapon1", ITEM_WEAPON);

	iIndex = Find_InvenIndex();
	Add_Item(iIndex, 20.f, 500.f, L"선남 선녀", { 165, 120, 215 }, L"Title2", ITEM_TITLE);

	// < 자연의 수호자 >
	iIndex = Find_InvenIndex();
	Add_Item(iIndex, 150.f, 1000.f, L"블랙니스 오토 어깨", { 220, 170, 0 }, L"Shoulder4", ITEM_SHOULDER);

	iIndex = Find_InvenIndex();
	Add_Item(iIndex, 300.f, 2000.f, L"라이트니스 오토 상의", { 220, 170, 0 }, L"Armor4", ITEM_TOP);

	iIndex = Find_InvenIndex();
	Add_Item(iIndex, 300.f, 2000.f, L"파이어니스 오토 하의", { 220, 170, 0 }, L"Pant4", ITEM_PANTS);

	iIndex = Find_InvenIndex();
	Add_Item(iIndex, 150.f, 1000.f, L"아이니스 오토 벨트", { 220, 170, 0 }, L"Belt4", ITEM_WAIST);

	iIndex = Find_InvenIndex();
	Add_Item(iIndex, 150.f, 1000.f, L"윈드니스 오토 신발", { 220, 170, 0 }, L"Shoes4", ITEM_SHOES);

	// < 해신의 저주 >
	iIndex = Find_InvenIndex();
	Add_Item(iIndex, 25.f, 150.f, L"해신의 저주 어깨", { 170, 95, 30 }, L"Shoulder5", ITEM_SHOULDER);

	iIndex = Find_InvenIndex();
	Add_Item(iIndex, 50.f, 300.f, L"해신의 저주 상의", { 170, 95, 30 }, L"Armor5", ITEM_TOP);

	iIndex = Find_InvenIndex();
	Add_Item(iIndex, 50.f, 300.f, L"해신의 저주 하의", { 170, 95, 30 }, L"Pant5", ITEM_PANTS);

	iIndex = Find_InvenIndex();
	Add_Item(iIndex, 25.f, 150.f, L"해신의 저주 벨트", { 170, 95, 30 }, L"Belt5", ITEM_WAIST);

	iIndex = Find_InvenIndex();
	Add_Item(iIndex, 25.f, 150.f, L"해신의 저주 신발", { 170, 95, 30 }, L"Shoes5", ITEM_SHOES);
}

int CUI_Inven::Update()
{
	m_dwTime += CTimeMgr::Get_Instance()->GetfDT();

	m_tRect.left = m_tInfo.fX - (m_tInfo.fCX * 0.5f);
	m_tRect.top = m_tInfo.fY - (m_tInfo.fCY * 0.5f);
	m_tRect.right = m_tInfo.fX + (m_tInfo.fCX * 0.5f);
	m_tRect.bottom = m_tInfo.fY + (m_tInfo.fCY * 0.5f);

	__super::Update_Rect();

	return 0;
}

void CUI_Inven::Late_Update()
{
	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	RECT m_clickRect = {};

	m_clickRect.left = m_tRect.left;
	m_clickRect.top = m_tRect.top;
	m_clickRect.right = m_tRect.right;
	m_clickRect.bottom = m_tRect.bottom - 480;

	if (m_bRender)
	{
		// 마우스의 위치가 인벤토리의 드래그바 안에 들어온다면
		if (PtInRect(&m_clickRect, pt))
		{
			if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
			{
				// 상점이나 내정보가 화면상에 표시되고 있을시
				if (dynamic_cast<CUI_Store*>((CObjMgr::Get_Instance()->GetObjList(OBJ_STORE)).front())->Get_Render() ||
					dynamic_cast<CUI_Info*>((CObjMgr::Get_Instance()->GetObjList(OBJ_MYINFO)).front())->Get_Render())
				{
					// 인벤토리를 QUADOVERDUI로 변경하고, 인벤 아이템을 OCTAOVERDUI로 변경
					Set_RenderID(OCTAOVERDUI);
					list<CObj*> invenItem = CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM);
					for (auto& iter : invenItem)
						iter->Set_RenderID(HEXAOVERDUI);

					// 만약 다른 창이 있다면, 다른 창들의 RenderID를 변경
					// 상점이 더 위에 있는 경우
					if (int(CObjMgr::Get_Instance()->GetObjList(OBJ_STORE).front()->Get_RenderID())
					> int(CObjMgr::Get_Instance()->GetObjList(OBJ_MYINFO).front()->Get_RenderID()) - 2)
					{
						CObjMgr::Get_Instance()->GetObjList(OBJ_STORE).front()->Set_RenderID(TWOOVERDUI);
						list<CObj*> storeItem = CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM);
						for (auto& iter : storeItem)
							iter->Set_RenderID(TRIPLEOVERDUI);

						CObjMgr::Get_Instance()->GetObjList(OBJ_MYINFO).front()->Set_RenderID(OVERDUI);
					}
					// 내정보가 더 위에 있는 경우
					else
					{
						CObjMgr::Get_Instance()->GetObjList(OBJ_MYINFO).front()->Set_RenderID(QUADOVERDUI);

						CObjMgr::Get_Instance()->GetObjList(OBJ_STORE).front()->Set_RenderID(TWOOVERDUI);
						list<CObj*> storeItem = CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM);
						for (auto& iter : storeItem)
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

				for (auto& Item : CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM))
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

		for (auto& Item : CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM))
		{
			if (Item->Get_Equip())
			{
				switch (Item->Get_ItemType())
				{
				case ITEM_WEAPON:
					Item->Set_Pos(m_tRect.right - 59, m_tRect.top + 85);
					break;

				case ITEM_TITLE:
					Item->Set_Pos(m_tRect.right - 27, m_tRect.top + 85);
					break;

				case ITEM_BRACELET:
					Item->Set_Pos(m_tRect.right - 59, m_tRect.top + 117);
					break;

				case ITEM_NECKLACE:
					Item->Set_Pos(m_tRect.right - 27, m_tRect.top + 117);
					break;

				case ITEM_RING:
					Item->Set_Pos(m_tRect.right - 27, m_tRect.top + 149);
					break;

				case ITEM_STONE:
					Item->Set_Pos(m_tRect.right - 66, m_tRect.top + 154);
					break;

				case ITEM_ASSIST:
					Item->Set_Pos(m_tRect.left + 66, m_tRect.top + 154);
					break;

				case ITEM_SHOULDER:
					Item->Set_Pos(m_tRect.left + 27, m_tRect.top + 85);
					break;

				case ITEM_TOP:
					Item->Set_Pos(m_tRect.left + 59, m_tRect.top + 85);
					break;

				case ITEM_PANTS:
					Item->Set_Pos(m_tRect.left + 27, m_tRect.top + 117);
					break;

				case ITEM_WAIST:
					Item->Set_Pos(m_tRect.left + 59, m_tRect.top + 117);
					break;

				case ITEM_SHOES:
					Item->Set_Pos(m_tRect.left + 27, m_tRect.top + 149);
					break;
				}
			}
		}
	}
	if (!m_bPickMode)
	{
		for (auto& iter : CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM))
			iter->Set_AlphaValue(255);
	}

	CCollsionMgr::Collision_Rect1(CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM), CObjMgr::Get_Instance()->GetObjList(OBJ_MOUSEPOINT));
}

void CUI_Inven::Render(HDC hDC)
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
			RGB(255, 0, 255));
	}
}

void CUI_Inven::Release()
{
}

void CUI_Inven::Add_Item(int _iIndex, float _fAtk, float _fHp, wstring _strName, tagColor _tRGB, TCHAR* _pKey, ITEM_TYPE _eItemType)
{
	int Xindex = _iIndex % 8;
	int Yindex = _iIndex / 8;

	// 매개변수 : 인덱스, 아이템 공격력, 아이템 Hp증가량(MaxHp를 늘려야함), 프레임키, 아이템타입, 
	CObjMgr::Get_Instance()->Add_Object(OBJ_INVENITEM,
		CAbstractFactory<CItem>::Create_Obj(m_tRect.left + (LONG)24 + (Xindex * 30.f), m_tRect.top + (LONG)245 + (Yindex * 30.f),
			(int)_fAtk, (int)_fHp, _strName, _pKey));
	CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM).back()->Set_Index(_iIndex);
	CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM).back()->Set_RGB(_tRGB);
	// CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM).back()->Set_Attack(_fAtk);
	// CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM).back()->Set_Hp(_fHp);
	CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM).back()->Set_ItemType(_eItemType);
	m_bIndex[_iIndex] = true;
}

void CUI_Inven::Set_ItemPos(CObj* _pItem, int _iIndex)
{
	int Xindex = _iIndex % 8;
	int Yindex = _iIndex / 8;

	_pItem->Set_Pos(m_tRect.left + (LONG)24 + (Xindex * 30.f), m_tRect.top + (LONG)245 + (Yindex * 30.f));
}

int CUI_Inven::Find_InvenIndex()
{
	int iCount = 0;
	for (int i = 0; i < sizeof(m_bIndex); ++i)
	{
		if (!(m_bIndex[i]))
		{
			iCount = i;
			break;
		}
	}

	return iCount;
}

bool CUI_Inven::Is_EquipIndex(ITEM_TYPE _eItemType)
{
	if (m_bEquipIndex[_eItemType])
		return false;
	return true;
}
