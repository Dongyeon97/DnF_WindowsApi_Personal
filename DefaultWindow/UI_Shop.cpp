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

	// �������� ������ ����ش�.
	float	fX = m_tRect.left + (LONG)31 + (0 * 170);
	float	fY = m_tRect.top + (LONG)100 + (0 * 59);

	// ������ �̱� ������
	CObjMgr::Get_Instance()->Add_Object(OBJ_STOREITEM, CAbstractFactory<CStoreItem>::Create_Obj(fX, fY, 1200, 0, L"������ �̱� - ������", L"Weapon2"));
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_ItemType(ITEM_WEAPON);
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_RGB({ 220, 170, 0 });

	fX = m_tRect.left + (LONG)31 + (1 * 170);
	fY = m_tRect.top + (LONG)100 + (0 * 59);

	// ������ Ž���� ����
	CObjMgr::Get_Instance()->Add_Object(OBJ_STOREITEM, CAbstractFactory<CStoreItem>::Create_Obj(fX, fY, 250, 1500, L"������ Ž���� ����", L"SupportItem"));
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_ItemType(ITEM_ASSIST);
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_RGB({ 220, 170, 0 });

	fX = m_tRect.left + (LONG)31 + (0 * 170);
	fY = m_tRect.top + (LONG)100 + (1 * 59);

	// ������ Ž���� ��
	CObjMgr::Get_Instance()->Add_Object(OBJ_STOREITEM, CAbstractFactory<CStoreItem>::Create_Obj(fX, fY, 275, 0, L"������ Ž���� ��", L"Bracelet3"));
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_ItemType(ITEM_BRACELET);
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_RGB({ 220, 170, 0 });

	fX = m_tRect.left + (LONG)31 + (1 * 170);
	fY = m_tRect.top + (LONG)100 + (1 * 59);

	// ������ Ž���� ����
	CObjMgr::Get_Instance()->Add_Object(OBJ_STOREITEM, CAbstractFactory<CStoreItem>::Create_Obj(fX, fY, 200, 2500, L"������ Ž���� ����", L"Neckless3"));
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_ItemType(ITEM_NECKLACE);
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_RGB({ 220, 170, 0 });

	fX = m_tRect.left + (LONG)31 + (0 * 170);
	fY = m_tRect.top + (LONG)100 + (2 * 59);

	// ������ Ž���� ����
	CObjMgr::Get_Instance()->Add_Object(OBJ_STOREITEM, CAbstractFactory<CStoreItem>::Create_Obj(fX, fY, 275, 0, L"������ Ž���� ����", L"Ring3"));
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_ItemType(ITEM_RING);
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_RGB({ 220, 170, 0 });

	fX = m_tRect.left + (LONG)31 + (1 * 170);
	fY = m_tRect.top + (LONG)100 + (2 * 59);

	// ������ Ž���� �ٿ�
	CObjMgr::Get_Instance()->Add_Object(OBJ_STOREITEM, CAbstractFactory<CStoreItem>::Create_Obj(fX, fY, 0, 5000, L"������ Ž���� �ٿ�", L"MasicStone3"));
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_ItemType(ITEM_STONE);
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_RGB({ 220, 170, 0 });

	fX = m_tRect.left + (LONG)31 + (0 * 170);
	fY = m_tRect.top + (LONG)100 + (3 * 59);

	// ��ƽ�� Ŀ�Ǵ� ����
	CObjMgr::Get_Instance()->Add_Object(OBJ_STOREITEM, CAbstractFactory<CStoreItem>::Create_Obj(fX, fY, 600, 4000, L"��ƽ�� Ŀ�Ǵ� ����", L"Armor6"));
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_ItemType(ITEM_TOP);
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_RGB({ 220, 170, 0 });

	fX = m_tRect.left + (LONG)31 + (1 * 170);
	fY = m_tRect.top + (LONG)100 + (3 * 59);

	// ��ƽ�� ���� ����
	CObjMgr::Get_Instance()->Add_Object(OBJ_STOREITEM, CAbstractFactory<CStoreItem>::Create_Obj(fX, fY, 600, 4000, L"��ƽ�� ���� ����", L"Pant6"));
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_ItemType(ITEM_PANTS);
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_RGB({ 220, 170, 0 });

	fX = m_tRect.left + (LONG)31 + (0 * 170);
	fY = m_tRect.top + (LONG)100 + (4 * 59);

	// ��ƽ�� ���Ǽ� ���
	CObjMgr::Get_Instance()->Add_Object(OBJ_STOREITEM, CAbstractFactory<CStoreItem>::Create_Obj(fX, fY, 300, 2000, L"��ƽ�� ���Ǽ� ���", L"Shoulder6"));
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_ItemType(ITEM_SHOULDER);
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_RGB({ 220, 170, 0 });

	fX = m_tRect.left + (LONG)31 + (1 * 170);
	fY = m_tRect.top + (LONG)100 + (4 * 59);

	// ��ƽ�� �ε� ��Ʈ
	CObjMgr::Get_Instance()->Add_Object(OBJ_STOREITEM, CAbstractFactory<CStoreItem>::Create_Obj(fX, fY, 300, 2000, L"��ƽ�� �ε� ��Ʈ", L"Belt6"));
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_ItemType(ITEM_WAIST);
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_RGB({ 220, 170, 0 });

	fX = m_tRect.left + (LONG)31 + (0 * 170);
	fY = m_tRect.top + (LONG)100 + (5 * 59);

	// ��ƽ�� ġ�� �Ź�
	CObjMgr::Get_Instance()->Add_Object(OBJ_STOREITEM, CAbstractFactory<CStoreItem>::Create_Obj(fX, fY, 300, 2000, L"��ƽ�� ġ�� �Ź�", L"Shoes6"));
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_ItemType(ITEM_SHOES);
	CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM).back()->Set_RGB({ 220, 170, 0 });

	fX = m_tRect.left + (LONG)31 + (1 * 170);
	fY = m_tRect.top + (LONG)100 + (5 * 59);

	// ��� 140�� ȭ����
	CObjMgr::Get_Instance()->Add_Object(OBJ_STOREITEM, CAbstractFactory<CStoreItem>::Create_Obj(fX, fY, 50, 200, L"��� 140�� ȭ����", L"Title1"));
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
		// ���콺�� ��ġ�� �������� Rect�ȿ� ���´ٸ�
		if (PtInRect(&m_clickRect, pt))
		{
			// �׸��� ���콺 ���ʹ�ư�� �����ٸ�
			// �ٸ� UI�� ���� ������ ȭ�� �� ���� �;���
			if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
			{
				// �κ��丮�� �������� ȭ��� ǥ�õǰ� ������
				if (dynamic_cast<CUI_Inven*>((CObjMgr::Get_Instance()->GetObjList(OBJ_INVEN)).front())->Get_Render() ||
					dynamic_cast<CUI_Info*>((CObjMgr::Get_Instance()->GetObjList(OBJ_MYINFO)).front())->Get_Render())
				{
					// ������ QUADOVERDUI�� �����ϰ�, ���� �������� OCTAOVERDUI�� ����
					Set_RenderID(OCTAOVERDUI);
					list<CObj*> storeItem = CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM);
					for (auto& iter : storeItem)
						iter->Set_RenderID(HEXAOVERDUI);

					// ���� �ٸ� â�� �ִٸ�, �ٸ� â���� RenderID�� ����
					// �κ��丮�� �� ���� �ִ� ���
					if (int(CObjMgr::Get_Instance()->GetObjList(OBJ_INVEN).front()->Get_RenderID())
					> int(CObjMgr::Get_Instance()->GetObjList(OBJ_MYINFO).front()->Get_RenderID()) - 2)
					{
						CObjMgr::Get_Instance()->GetObjList(OBJ_INVEN).front()->Set_RenderID(TWOOVERDUI);
						list<CObj*> invenItem = CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM);
						for (auto& iter : invenItem)
							iter->Set_RenderID(TRIPLEOVERDUI);

						CObjMgr::Get_Instance()->GetObjList(OBJ_MYINFO).front()->Set_RenderID(OVERDUI);
					}
					// �������� �� ���� �ִ� ���
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
