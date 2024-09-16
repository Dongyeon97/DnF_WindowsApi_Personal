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

	// �������� ������ ����ش�.
	int iIndex = Find_InvenIndex();
	Add_Item(iIndex, 200.f, 0.f, L"������ ���� ��", { 200, 60, 200 }, L"Weapon4", ITEM_WEAPON);

	iIndex = Find_InvenIndex();
	Add_Item(iIndex, 300.f, 0.f, L"���̽�Ÿ��", { 165, 120, 215 }, L"Weapon3", ITEM_WEAPON);

	iIndex = Find_InvenIndex();
	Add_Item(iIndex, 50.f, 0.f, L"��ȯ���� �㸧�� ������", { 170, 95, 30 }, L"Weapon1", ITEM_WEAPON);

	iIndex = Find_InvenIndex();
	Add_Item(iIndex, 20.f, 500.f, L"���� ����", { 165, 120, 215 }, L"Title2", ITEM_TITLE);

	// < �ڿ��� ��ȣ�� >
	iIndex = Find_InvenIndex();
	Add_Item(iIndex, 150.f, 1000.f, L"���Ͻ� ���� ���", { 220, 170, 0 }, L"Shoulder4", ITEM_SHOULDER);

	iIndex = Find_InvenIndex();
	Add_Item(iIndex, 300.f, 2000.f, L"����Ʈ�Ͻ� ���� ����", { 220, 170, 0 }, L"Armor4", ITEM_TOP);

	iIndex = Find_InvenIndex();
	Add_Item(iIndex, 300.f, 2000.f, L"���̾�Ͻ� ���� ����", { 220, 170, 0 }, L"Pant4", ITEM_PANTS);

	iIndex = Find_InvenIndex();
	Add_Item(iIndex, 150.f, 1000.f, L"���̴Ͻ� ���� ��Ʈ", { 220, 170, 0 }, L"Belt4", ITEM_WAIST);

	iIndex = Find_InvenIndex();
	Add_Item(iIndex, 150.f, 1000.f, L"����Ͻ� ���� �Ź�", { 220, 170, 0 }, L"Shoes4", ITEM_SHOES);

	// < �ؽ��� ���� >
	iIndex = Find_InvenIndex();
	Add_Item(iIndex, 25.f, 150.f, L"�ؽ��� ���� ���", { 170, 95, 30 }, L"Shoulder5", ITEM_SHOULDER);

	iIndex = Find_InvenIndex();
	Add_Item(iIndex, 50.f, 300.f, L"�ؽ��� ���� ����", { 170, 95, 30 }, L"Armor5", ITEM_TOP);

	iIndex = Find_InvenIndex();
	Add_Item(iIndex, 50.f, 300.f, L"�ؽ��� ���� ����", { 170, 95, 30 }, L"Pant5", ITEM_PANTS);

	iIndex = Find_InvenIndex();
	Add_Item(iIndex, 25.f, 150.f, L"�ؽ��� ���� ��Ʈ", { 170, 95, 30 }, L"Belt5", ITEM_WAIST);

	iIndex = Find_InvenIndex();
	Add_Item(iIndex, 25.f, 150.f, L"�ؽ��� ���� �Ź�", { 170, 95, 30 }, L"Shoes5", ITEM_SHOES);
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
		// ���콺�� ��ġ�� �κ��丮�� �巡�׹� �ȿ� ���´ٸ�
		if (PtInRect(&m_clickRect, pt))
		{
			if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
			{
				// �����̳� �������� ȭ��� ǥ�õǰ� ������
				if (dynamic_cast<CUI_Store*>((CObjMgr::Get_Instance()->GetObjList(OBJ_STORE)).front())->Get_Render() ||
					dynamic_cast<CUI_Info*>((CObjMgr::Get_Instance()->GetObjList(OBJ_MYINFO)).front())->Get_Render())
				{
					// �κ��丮�� QUADOVERDUI�� �����ϰ�, �κ� �������� OCTAOVERDUI�� ����
					Set_RenderID(OCTAOVERDUI);
					list<CObj*> invenItem = CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM);
					for (auto& iter : invenItem)
						iter->Set_RenderID(HEXAOVERDUI);

					// ���� �ٸ� â�� �ִٸ�, �ٸ� â���� RenderID�� ����
					// ������ �� ���� �ִ� ���
					if (int(CObjMgr::Get_Instance()->GetObjList(OBJ_STORE).front()->Get_RenderID())
					> int(CObjMgr::Get_Instance()->GetObjList(OBJ_MYINFO).front()->Get_RenderID()) - 2)
					{
						CObjMgr::Get_Instance()->GetObjList(OBJ_STORE).front()->Set_RenderID(TWOOVERDUI);
						list<CObj*> storeItem = CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM);
						for (auto& iter : storeItem)
							iter->Set_RenderID(TRIPLEOVERDUI);

						CObjMgr::Get_Instance()->GetObjList(OBJ_MYINFO).front()->Set_RenderID(OVERDUI);
					}
					// �������� �� ���� �ִ� ���
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

	// �Ű����� : �ε���, ������ ���ݷ�, ������ Hp������(MaxHp�� �÷�����), ������Ű, ������Ÿ��, 
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
