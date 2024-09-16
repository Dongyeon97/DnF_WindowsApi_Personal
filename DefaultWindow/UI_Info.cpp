#include "stdafx.h"
#include "UI_Info.h"

#include "SceneMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "CollsionMgr.h"
#include "Item.h"
#include "UI_Shop.h"
#include "UI_Inven.h"

CUI_Info::CUI_Info()
	:m_bRender(false)
	, m_bClicked(false)
{

}

CUI_Info::~CUI_Info()
{
	Release();
}

void CUI_Info::Initialize()
{
	m_eRender = UI;

	m_bOpened = true;

	m_tInfo.fX = 200.f;
	m_tInfo.fY = 100.f;

	m_tInfo.fCX = 246.f;
	m_tInfo.fCY = 279.f;

	m_tRect.left = m_tInfo.fX - (m_tInfo.fCX * 0.5f);
	m_tRect.top = m_tInfo.fY - (m_tInfo.fCY * 0.5f);
	m_tRect.right = m_tInfo.fX + (m_tInfo.fCX * 0.5f);
	m_tRect.bottom = m_tInfo.fY + (m_tInfo.fCY * 0.5f);
}

int CUI_Info::Update()
{
	m_dwTime += CTimeMgr::Get_Instance()->GetfDT();

	m_tRect.left = m_tInfo.fX - (m_tInfo.fCX * 0.5f);
	m_tRect.top = m_tInfo.fY - (m_tInfo.fCY * 0.5f);
	m_tRect.right = m_tInfo.fX + (m_tInfo.fCX * 0.5f);
	m_tRect.bottom = m_tInfo.fY + (m_tInfo.fCY * 0.5f);

	__super::Update_Rect();

	return 0;
}

void CUI_Info::Late_Update()
{
	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	RECT m_clickRect = {};

	m_clickRect.left = m_tRect.left;
	m_clickRect.top = m_tRect.top;
	m_clickRect.right = m_tRect.right;
	m_clickRect.bottom = m_tRect.bottom - 200;

	// ���콺�� ��ġ�� �κ��丮�� �巡�׹� �ȿ� ���´ٸ�
	if (PtInRect(&m_clickRect, pt))
	{
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
		{
			// �����̳� �κ��丮�� ȭ��� ǥ�õǰ� ������
			if (dynamic_cast<CUI_Store*>((CObjMgr::Get_Instance()->GetObjList(OBJ_STORE)).front())->Get_Render() ||
				dynamic_cast<CUI_Inven*>((CObjMgr::Get_Instance()->GetObjList(OBJ_INVEN)).front())->Get_Render())
			{
				// �������� QUADOVERDUI�� ����
				Set_RenderID(OCTAOVERDUI);

				// ���� �ٸ� â�� �ִٸ�, �ٸ� â���� RenderID�� ����
				// ������ �� ���� �ִ� ���
				if (CObjMgr::Get_Instance()->GetObjList(OBJ_STORE).front()->Get_RenderID()
					> CObjMgr::Get_Instance()->GetObjList(OBJ_INVEN).front()->Get_RenderID())
				{
					CObjMgr::Get_Instance()->GetObjList(OBJ_STORE).front()->Set_RenderID(TWOOVERDUI);
					list<CObj*> storeItem = CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM);
					for (auto& iter : storeItem)
						iter->Set_RenderID(TRIPLEOVERDUI);

					CObjMgr::Get_Instance()->GetObjList(OBJ_INVEN).front()->Set_RenderID(UI);
					list<CObj*> invenItem = CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM);
					for (auto& iter : invenItem)
						iter->Set_RenderID(OVERDUI);
				}
				// �κ��丮�� �� ���� �ִ� ���
				else
				{
					CObjMgr::Get_Instance()->GetObjList(OBJ_STORE).front()->Set_RenderID(UI);
					list<CObj*> storeItem = CObjMgr::Get_Instance()->GetObjList(OBJ_STOREITEM);
					for (auto& iter : storeItem)
						iter->Set_RenderID(OVERDUI);

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

			for (auto& Item : CObjMgr::Get_Instance()->GetObjList(OBJ_EQUIPMENT))
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

void CUI_Info::Render(HDC hDC)
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

	if (m_bRender)
	{
		// < �÷��̾� ���� >
		if (!CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).empty())
		{
			CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front();

			// ��Ʈ
			HFONT font = CreateFont(15, 0, 0, 0, 850, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
				VARIABLE_PITCH | FF_ROMAN, L"���� ���");
			HFONT oldfont = (HFONT)SelectObject(hDC, font);

#pragma region HP, Mp ��º�

			float fHp = pPlayer->Get_Info().fHp;
			float fMaxHp = pPlayer->Get_Info().fMaxHp;
			float fMp = pPlayer->Get_Info().fMp;
			float fMaxMp = pPlayer->Get_Info().fMaxMp;

			SetTextColor(hDC, RGB(65, 170, 100));
			SetBkMode(hDC, TRANSPARENT); // �Ű����� DC�� ���ڹ���� �����ϰ� �Ѵ�. 
			SetTextAlign(hDC, TA_RIGHT);

			// Hp
			TextOut(hDC, m_tRect.left + 82, m_tRect.top + 136, (to_wstring((int)fHp)).c_str(), (to_wstring((int)fHp)).size());
			TextOut(hDC, m_tRect.left + 87, m_tRect.top + 136, L"/", 1);
			TextOut(hDC, m_tRect.left + 122, m_tRect.top + 136, (to_wstring((int)fMaxHp)).c_str(), (to_wstring((int)fMaxHp)).size());

			//	// Mp
			TextOut(hDC, m_tRect.left + 200, m_tRect.top + 136, (to_wstring((int)fMp)).c_str(), (to_wstring((int)fMp)).size());
			TextOut(hDC, m_tRect.left + 205, m_tRect.top + 136, L"/", 1);
			TextOut(hDC, m_tRect.left + 240, m_tRect.top + 136, (to_wstring((int)fMaxMp)).c_str(), (to_wstring((int)fMaxMp)).size());

#pragma endregion HP, Mp ��º�

#pragma region ��, ����

			float	iStrength = pPlayer->Get_Info().fStrength;
			float	fAtkSpeed = pPlayer->Get_Info().fAtkSpeed;

			float idd = (round(fAtkSpeed * 10) / 10);
			wstring str = to_wstring(idd);
			wstring sub = str.substr(0, 4);

			// ��
			TextOut(hDC, m_tRect.left + 122, m_tRect.top + 154, to_wstring((int)iStrength).c_str(), (to_wstring((int)iStrength).size()));

			// ����
			TextOut(hDC, m_tRect.left + 228, m_tRect.top + 154, sub.c_str(), sub.size());
			TextOut(hDC, m_tRect.left + 240, m_tRect.top + 154, L"%", 1);

#pragma endregion ��, ����

#pragma region ü��, �̼�

			float	fHealth = pPlayer->Get_Info().fHealth;
			float	fMoveSpeed = pPlayer->Get_Info().fMoveSpeed;

			idd = (round(fMoveSpeed * 10) / 10);
			str = to_wstring(idd);
			sub = str.substr(0, 4);

			// ü��
			TextOut(hDC, m_tRect.left + 122, m_tRect.top + 172, to_wstring((int)fHealth).c_str(), (to_wstring((int)fHealth).size()));

			// �̼�
			TextOut(hDC, m_tRect.left + 228, m_tRect.top + 172, sub.c_str(), sub.size());
			TextOut(hDC, m_tRect.left + 240, m_tRect.top + 172, L"%", 1);

#pragma endregion ü��, �̼�

#pragma region ����, ����

			float	fAtk = pPlayer->Get_Info().fAtk;
			float	fDef = pPlayer->Get_Info().fDef;

			// ����
			TextOut(hDC, m_tRect.left + 122, m_tRect.top + 190, to_wstring((int)fAtk).c_str(), (to_wstring((int)fAtk).size()));

			// ����
			TextOut(hDC, m_tRect.left + 240, m_tRect.top + 190, to_wstring((int)fDef).c_str(), (to_wstring((int)fDef).size()));

#pragma endregion ����, ����

#pragma region ����, ����

			float	fMAtk = pPlayer->Get_Info().fMAtk;
			float	fMDef = pPlayer->Get_Info().fMDef;

			// ����
			TextOut(hDC, m_tRect.left + 122, m_tRect.top + 208, to_wstring((int)fMAtk).c_str(), (to_wstring((int)fMAtk).size()));

			// ����
			TextOut(hDC, m_tRect.left + 240, m_tRect.top + 208, to_wstring((int)fMDef).c_str(), (to_wstring((int)fMDef).size()));

#pragma endregion ����, ����

#pragma region ȭ, ��

			float	fFire = pPlayer->Get_Info().fFire;
			float	fWater = pPlayer->Get_Info().fWater;

			// ȭ
			TextOut(hDC, m_tRect.left + 122, m_tRect.top + 226, to_wstring((int)fFire).c_str(), (to_wstring((int)fFire).size()));

			// ��
			TextOut(hDC, m_tRect.left + 240, m_tRect.top + 226, to_wstring((int)fWater).c_str(), (to_wstring((int)fWater).size()));

#pragma endregion ȭ, ��

#pragma region ��, ��

			float	fLightness = pPlayer->Get_Info().fLightness;
			float	fDarkness = pPlayer->Get_Info().fDarkness;

			// ��
			TextOut(hDC, m_tRect.left + 122, m_tRect.top + 244, to_wstring((int)fLightness).c_str(), (to_wstring((int)fLightness).size()));

			// ��
			TextOut(hDC, m_tRect.left + 240, m_tRect.top + 244, to_wstring((int)fDarkness).c_str(), (to_wstring((int)fDarkness).size()));

#pragma endregion ��, ��

#pragma region �׸���

			float	fExorcism = pPlayer->Get_Info().fExorcism;

			// �׸���
			TextOut(hDC, m_tRect.left + 122, m_tRect.top + 262, to_wstring((int)fExorcism).c_str(), (to_wstring((int)fExorcism).size()));

#pragma endregion �׸���


#pragma region 

			SetTextColor(hDC, RGB(0, 0, 0));
			SetBkMode(hDC, OPAQUE);
			SetTextAlign(hDC, TA_LEFT);

			SelectObject(hDC, oldfont);
			DeleteObject(font);
		}
	}
		

	// < �������� ������ >
	if (m_bRender)
	{
		for (auto& Item : CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM))
		{
			if (Item->Get_Equip())
			{
				HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(Item->Get_FrameKey());

				float ItemSizeX = Item->Get_ScaleX();
				float ItemSizeY = Item->Get_ScaleY();

				switch (Item->Get_ItemType())
				{
				case ITEM_WEAPON:
					// Item->Set_Pos(m_tRect.right - 45, m_tRect.top + 85);
					GdiTransparentBlt(hDC,
						m_tRect.right - 66,
						m_tRect.top + 28,
						(int)ItemSizeX,
						(int)ItemSizeY,
						hMemDC,
						0,
						0,
						(int)ItemSizeX,
						(int)ItemSizeY,
						RGB(255, 255, 255));
					break;

				case ITEM_TITLE:
					// Item->Set_Pos(m_tRect.right - 27, m_tRect.top + 85);
					GdiTransparentBlt(hDC,
						m_tRect.right - 34,
						m_tRect.top + 28,
						(int)ItemSizeX,
						(int)ItemSizeY,
						hMemDC,
						0,
						0,
						(int)ItemSizeX,
						(int)ItemSizeY,
						RGB(255, 255, 255));
					break;

				case ITEM_BRACELET:
					// Item->Set_Pos(m_tRect.right - 59, m_tRect.top + 117);
					GdiTransparentBlt(hDC,
						m_tRect.right - 66,
						m_tRect.top + 60,
						(int)ItemSizeX,
						(int)ItemSizeY,
						hMemDC,
						0,
						0,
						(int)ItemSizeX,
						(int)ItemSizeY,
						RGB(255, 255, 255));
					break;

				case ITEM_NECKLACE:
					// Item->Set_Pos(m_tRect.right - 27, m_tRect.top + 117);
					GdiTransparentBlt(hDC,
						m_tRect.right - 34,
						m_tRect.top + 60,
						(int)ItemSizeX,
						(int)ItemSizeY,
						hMemDC,
						0,
						0,
						(int)ItemSizeX,
						(int)ItemSizeY,
						RGB(255, 255, 255));
					break;

				case ITEM_RING:
					// Item->Set_Pos(m_tRect.right - 27, m_tRect.top + 149);
					GdiTransparentBlt(hDC,
						m_tRect.right - 34,
						m_tRect.top + 92,
						(int)ItemSizeX,
						(int)ItemSizeY,
						hMemDC,
						0,
						0,
						(int)ItemSizeX,
						(int)ItemSizeY,
						RGB(255, 255, 255));
					break;

				case ITEM_STONE:
					// Item->Set_Pos(m_tRect.right - 66, m_tRect.top + 154);
					GdiTransparentBlt(hDC,
						m_tRect.right - 72,
						m_tRect.top + 98,
						(int)ItemSizeX,
						(int)ItemSizeY,
						hMemDC,
						0,
						0,
						(int)ItemSizeX,
						(int)ItemSizeY,
						RGB(255, 255, 255));
					break;

				case ITEM_ASSIST:
					// Item->Set_Pos(m_tRect.left + 66, m_tRect.top + 154);
					GdiTransparentBlt(hDC,
						m_tRect.left + 44,
						m_tRect.top + 98,
						(int)ItemSizeX,
						(int)ItemSizeY,
						hMemDC,
						0,
						0,
						(int)ItemSizeX,
						(int)ItemSizeY,
						RGB(255, 255, 255));
					break;

				case ITEM_SHOULDER:
					// Item->Set_Pos(m_tRect.left + 27, m_tRect.top + 85);
					GdiTransparentBlt(hDC,
						m_tRect.left + 6,
						m_tRect.top + 28,
						(int)ItemSizeX,
						(int)ItemSizeY,
						hMemDC,
						0,
						0,
						(int)ItemSizeX,
						(int)ItemSizeY,
						RGB(255, 255, 255));
					break;

				case ITEM_TOP:
					// Item->Set_Pos(m_tRect.left + 59, m_tRect.top + 85);
					GdiTransparentBlt(hDC,
						m_tRect.left + 38,
						m_tRect.top + 28,
						(int)ItemSizeX,
						(int)ItemSizeY,
						hMemDC,
						0,
						0,
						(int)ItemSizeX,
						(int)ItemSizeY,
						RGB(255, 255, 255));
					break;

				case ITEM_PANTS:
					// Item->Set_Pos(m_tRect.left + 27, m_tRect.top + 117);
					GdiTransparentBlt(hDC,
						m_tRect.left + 6,
						m_tRect.top + 60,
						(int)ItemSizeX,
						(int)ItemSizeY,
						hMemDC,
						0,
						0,
						(int)ItemSizeX,
						(int)ItemSizeY,
						RGB(255, 255, 255));
					break;

				case ITEM_WAIST:
					// Item->Set_Pos(m_tRect.left + 59, m_tRect.top + 117);
					GdiTransparentBlt(hDC,
						m_tRect.left + 38,
						m_tRect.top + 60,
						(int)ItemSizeX,
						(int)ItemSizeY,
						hMemDC,
						0,
						0,
						(int)ItemSizeX,
						(int)ItemSizeY,
						RGB(255, 255, 255));
					break;

				case ITEM_SHOES:
					// Item->Set_Pos(m_tRect.left + 27, m_tRect.top + 149);
					GdiTransparentBlt(hDC,
						m_tRect.left + 6,
						m_tRect.top + 92,
						(int)ItemSizeX,
						(int)ItemSizeY,
						hMemDC,
						0,
						0,
						(int)ItemSizeX,
						(int)ItemSizeY,
						RGB(255, 255, 255));
					break;
				}
			}
		}
	}
}

void CUI_Info::Release()
{
}