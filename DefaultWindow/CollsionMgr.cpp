#include "stdafx.h"
#include "CollsionMgr.h"
#include "SoundMgr.h"
#include "KeyMgr.h"
#include "TileNode.h"
#include "Player.h"
#include "MonsterAttack.h"
#include "Monster.h"
#include "PlayerAttack.h"
#include "AI.h"
#include "State.h"
#include "ObjMgr.h"
#include "UI_Inven.h"
#include "UI_Shop.h"
#include "Item.h"

static DWORD m_lClickTime = 0;

CCollsionMgr::CCollsionMgr()
{
}


CCollsionMgr::~CCollsionMgr()
{
}

// �ܼ� �浹 - [ �κ��丮 <-> ���콺 ] üũ��
void CCollsionMgr::Collision_Rect1(list<CObj*> Dst, list<CObj*> Src)
{
	RECT		rc{};

	float	fX = 0.f, fY = 0.f;

	for (auto& DstList : Dst)
	{
		for (auto& SrcList : Src)
		{
			if (Check_Rect(DstList, SrcList, &fX, &fY))
			{	
				// ���콺 �����͸� �����ٴ�� �����ʹ�ư�� Ŭ���ϸ�
				if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RBUTTON))
				{
					DWORD currentTime = GetTickCount64();
					RENDERID preID = DstList->Get_RenderID();

					// 1. �κ��丮�� ���� �Ѵ� �����ִ� ��� �Ǹ�
					if (dynamic_cast<CUI_Inven*>(CObjMgr::Get_Instance()->GetObjList(OBJ_INVEN).front())->Get_Render()
						&& dynamic_cast<CUI_Store*>(CObjMgr::Get_Instance()->GetObjList(OBJ_STORE).front())->Get_Render()
						&& currentTime - m_lClickTime > 300)
					{
						DstList->Set_Dead(true);
						CUI_Inven::Check_InvenIndex(DstList->Get_Index());
						PlayItemSound(DstList->Get_ItemType());
						m_lClickTime = GetTickCount64();
					}
					// 2. �κ��丮�� �����ִ� ���(��Ŭ���� ����)
					// �̹� ���� Ÿ���� �������� �����Ǿ� ������� ��ġ�� ��ȯ��
					else if (dynamic_cast<CUI_Inven*>(CObjMgr::Get_Instance()->GetObjList(OBJ_INVEN).front())->Get_Render()
						&& currentTime - m_lClickTime > 300)
					{
						// ��Ŭ���� ��� �������� �����, ���� ������ �κ��丮�� �̵�
						if (DstList->Get_Equip())
						{
							int iIndex = CUI_Inven::Find_InvenIndex();

							int Xindex = iIndex % 8;
							int Yindex = iIndex / 8;

							LONG lRectLeft = CObjMgr::Get_Instance()->GetObjList(OBJ_INVEN).back()->Get_Rect().left;
							LONG lRectTop = CObjMgr::Get_Instance()->GetObjList(OBJ_INVEN).back()->Get_Rect().top;

							// �־��ش�
							CObjMgr::Get_Instance()->Add_Object(OBJ_INVENITEM,
								CAbstractFactory<CItem>::Create_Obj(lRectLeft + (LONG)24 + (Xindex * 30.f), lRectTop + (LONG)245 + (Yindex * 30.f),
																DstList->Get_Attack(), DstList->Get_Hp(), DstList->Get_Name(), DstList->Get_FrameKey()));
							CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM).back()->Set_ItemType(DstList->Get_ItemType());
							CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM).back()->Set_RGB(DstList->Get_RGB());
							CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM).back()->Set_Index(iIndex);
							CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM).back()->Set_RenderID(preID);

							// �ش� ĭ�� �������� ���ٰ� �˸���, ���ĭ ������ �˸���, �ɷ�ġ�� �����Ѵ�
							CUI_Inven::m_bIndex[iIndex] = true;
							CUI_Inven::Check_EquipIndex(DstList->Get_ItemType());

							if (!CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).empty())
							{
								CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).back();
								pPlayer->Minus_Attack(DstList->Get_Attack());
								pPlayer->Minus_MaxHp(DstList->Get_Hp());
							}

							DstList->Set_Equip(false);
							DstList->Set_Dead(true);
							PlayItemSound(DstList->Get_ItemType());

							break;
						}

						// ���� �̹� �������� ��� �ִٸ�
						if (!(CUI_Inven::Is_EquipIndex(DstList->Get_ItemType())))
						{
							// ���� ������ ����ش�
							CUI_Inven::Check_InvenIndex(DstList->Get_Index());
							
							// �������� ��� �������� �κ��丮���� ã�´�
							list<CObj*> inven = CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM);
							
							auto iter = inven.begin();

							for (iter; iter != inven.end(); ++iter)
							{
								if ((*iter)->Get_ItemType() == DstList->Get_ItemType() && (*iter)->Get_Equip())
								{
									break;
								}
							}

							// ��������� �н�
							// if (DstList->Get_FrameKey() == (*iter)->Get_FrameKey())
								// break;

							// ���������� �����Ǿ��ٰ� ã���� �����۰� ���õ� �������� Ÿ���� ���ٸ�

							// �κ����� ��ĭ�߿� �� ������ ã�Ƽ�
							if (inven.end() != iter)
							{
								int iIndex = CUI_Inven::Find_InvenIndex();

								int Xindex = iIndex % 8;
								int Yindex = iIndex / 8;

								LONG lRectLeft = CObjMgr::Get_Instance()->GetObjList(OBJ_INVEN).back()->Get_Rect().left;
								LONG lRectTop = CObjMgr::Get_Instance()->GetObjList(OBJ_INVEN).back()->Get_Rect().top;

								// �־��ش�
								CObjMgr::Get_Instance()->Add_Object(OBJ_INVENITEM,
								CAbstractFactory<CItem>::Create_Obj(lRectLeft + (LONG)24 + (Xindex * 30.f), lRectTop + (LONG)245 + (Yindex * 30.f),
									(*iter)->Get_Attack(), (*iter)->Get_Hp(), (*iter)->Get_Name(), (*iter)->Get_FrameKey()));
								CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM).back()->Set_ItemType((*iter)->Get_ItemType());
								CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM).back()->Set_RGB((*iter)->Get_RGB());
								CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM).back()->Set_Index(iIndex);
								CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM).back()->Set_RenderID(preID);

								// �ش� ĭ�� �������� ���ٰ� �˸���
								CUI_Inven::m_bIndex[iIndex] = true;

								// �ش� ������ ��������, �Ҹ�, �ɷ�ġ ����
								(*iter)->Set_Equip(false);
								(*iter)->Set_Dead(true);
								if (!CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).empty())
								{
									CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).back();
									pPlayer->Minus_Attack((*iter)->Get_Attack());
									pPlayer->Minus_MaxHp((*iter)->Get_Hp());
								}

								// ���� ������ ����, �ɷ�ġ ����
								DstList->Set_Equip(true);
								DstList->Set_RenderID(preID);
								if (!CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).empty())
								{
									CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).back();
									pPlayer->Plus_Attack(DstList->Get_Attack());
									pPlayer->Plus_MaxHp(DstList->Get_Hp());
								}
								PlayItemSound(DstList->Get_ItemType());

								m_lClickTime = GetTickCount64();
							}
						}
						// �������� ��� ���ٸ� �׳� ����, �ɷ�ġ ����
						else
						{
							DstList->Set_Equip(true);
							CUI_Inven::Check_InvenIndex(DstList->Get_Index());
							CUI_Inven::Check_EquipIndex(DstList->Get_ItemType());
							CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM).back()->Set_RenderID(preID);
							if (!CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).empty())
							{
								CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).back();
								pPlayer->Plus_Attack(DstList->Get_Attack());
								pPlayer->Plus_MaxHp(DstList->Get_Hp());
							}
							PlayItemSound(DstList->Get_ItemType());
							m_lClickTime = GetTickCount64();
						}
					}
				}
			}
		}
	}
}

// �ܼ� �浹 - [ ���� <-> ���콺 ] üũ��
void CCollsionMgr::Collision_Rect2(list<CObj*> Dst, list<CObj*> Src)
{
	RECT		rc{};

	float	fX = 0.f, fY = 0.f;

	for (auto& DstList : Dst)
	{
		for (auto& SrcList : Src)
		{
			if (Check_Rect(DstList, SrcList, &fX, &fY))
			{
				// ���콺 �����͸� �����ٴ�� �����ʹ�ư�� Ŭ���ϸ�
				if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RBUTTON))
				{
					// ������ ����
					DWORD currentTime = GetTickCount64();
					if (currentTime - m_lClickTime > 200)
					{
						int iIndex = CUI_Inven::Find_InvenIndex();

						int Xindex = iIndex % 8;
						int Yindex = iIndex / 8;

						LONG lRectLeft = CObjMgr::Get_Instance()->GetObjList(OBJ_INVEN).back()->Get_Rect().left;
						LONG lRectTop = CObjMgr::Get_Instance()->GetObjList(OBJ_INVEN).back()->Get_Rect().top;

						CObjMgr::Get_Instance()->Add_Object(OBJ_INVENITEM,
							CAbstractFactory<CItem>::Create_Obj(lRectLeft + (LONG)24 + (Xindex * 30.f), lRectTop + (LONG)245 + (Yindex * 30.f),
																DstList->Get_Attack(), DstList->Get_Hp(), DstList->Get_Name(), DstList->Get_FrameKey()));
						CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM).back()->Set_ItemType(DstList->Get_ItemType());
						CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM).back()->Set_RGB(DstList->Get_RGB());
						CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM).back()->Set_Index(iIndex);
						CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM).back()->Set_RenderID(RENDERID(CObjMgr::Get_Instance()->GetObjList(OBJ_INVEN).back()->Get_RenderID() + 1));

						PlayItemSound(DstList->Get_ItemType());
						CUI_Inven::m_bIndex[iIndex] = true;

						m_lClickTime = GetTickCount64();
					}
				}
			}
		}
	}
}

// �ܼ� �浹 ���� - [ ������ <-> ���콺 ] üũ��
bool CCollsionMgr::Check_Rect(CObj* pDst, CObj* pSrc, float* pX, float* pY)
{
	float		fWidth = abs(pDst->Get_Info().fX - pSrc->Get_Info().fX);
	float		fHeight = abs(pDst->Get_Info().fY - pSrc->Get_Info().fY);

	float		fCX = (pDst->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;
	float		fCY = (pDst->Get_Info().fCY + pSrc->Get_Info().fCY) * 0.5f;

	if ((fCX >= fWidth) && (fCY >= fHeight))
	{
		*pX = fCX - fWidth;
		*pY = fCY - fHeight;

		return true;
	}

	return false;
}

// (������Ʈ - ������Ʈ) �ǰ� ����
void CCollsionMgr::Collision_RectEx(list<CObj*> Dst, list<CObj*> Src)
{
	float	fX = 0.f, fY = 0.f;

	for (auto& DstList : Dst)
	{
		for (auto& SrcList : Src)
		{
			if (Check_Rect(DstList, SrcList, &fX, &fY))
			{
				// ���� �浹
				if (fX > fY)
				{
					if (DstList->Get_Info().fY < SrcList->Get_Info().fY)
					{
						DstList->Set_PosY(-fY);
					}
					else // �� �浹
					{
						DstList->Set_PosY(fY);
					}
				}
				// �¿� �浹
				else
				{
					if (DstList->Get_Info().fX < SrcList->Get_Info().fX)
					{
						DstList->Set_PosX(-fX);
					}
					else // �� �浹
					{
						DstList->Set_PosX(fX);
					}
				}

			}
		}
	}
}

// =====================================================================================
// =====================================================================================
// =====================================================================================

// (�÷��̾� - ���� ����Rect) �浹
void CCollsionMgr::Collision_AttackRectPM(list<CObj*> Dst, list<CObj*> Src)
{
	float	fX = 0.f, fY = 0.f;

	for (auto& SrcList : Src)
	{
		tagHitInfo HInfo;

		HInfo.eAttType = SrcList->Get_AttackType();
		HInfo.bIsHit = SrcList->Get_IsHit();
		HInfo.fAttPoint = SrcList->Get_AttPoint();
		HInfo.fAttRatio = SrcList->Get_AttRatio();
		HInfo.fThrustPower = SrcList->Get_ThrustPower();
		HInfo.fThrustAccel = SrcList->Get_ThrustAccel();
		HInfo.fLevitatePower = SrcList->Get_LevitatePower();
		HInfo.fLevitateAngle = SrcList->Get_LevitateAngle();
		HInfo.fKnockbackAngle = SrcList->Get_KnockbackAngle();
		HInfo.fKnockbackTime = SrcList->Get_KnockbackTime();

		for (auto& DstList : Dst)
		{
			if (Check_AttackRect(DstList, SrcList, &fX, &fY))
			{
				if (DstList->Get_IsImmune())
					continue;

				if (ATT_JUSTEFFECT == HInfo.eAttType)
					continue;

				// ���⼭ ���� Ÿ���� �Ǵ��ؼ� SetState�� ���ش�
				switch (HInfo.eAttType)
				{
				case ATT_NORMAL:
					if (CPlayer::PLAYERSTATE::PS_LEVITATE_ATTACKED == dynamic_cast<CPlayer*>(DstList)->Get_PlayerState() ||
											CPlayer::PS_JUMP == dynamic_cast<CPlayer*>(DstList)->Get_PlayerState() ||
											CPlayer::PS_JUMPATTACK == dynamic_cast<CPlayer*>(DstList)->Get_PlayerState())
					{
						dynamic_cast<CPlayer*>(DstList)->Set_PlayerState(CPlayer::PLAYERSTATE::PS_LEVITATE_ATTACKED);
						DstList->Set_dwTime(0);
						DstList->Set_KnockBack(true);
						break;
					}
					dynamic_cast<CPlayer*>(DstList)->Set_PlayerState(CPlayer::PLAYERSTATE::PS_NORMAL_ATTACKED);
					DstList->Set_dwTime(0);
					DstList->Set_KnockBack(true);
					break;

				case ATT_THRUST:
					if (CPlayer::PLAYERSTATE::PS_LEVITATE_ATTACKED == dynamic_cast<CPlayer*>(DstList)->Get_PlayerState() ||
											CPlayer::PS_JUMP == dynamic_cast<CPlayer*>(DstList)->Get_PlayerState() ||
											CPlayer::PS_JUMPATTACK == dynamic_cast<CPlayer*>(DstList)->Get_PlayerState())
					{
						dynamic_cast<CPlayer*>(DstList)->Set_PlayerState(CPlayer::PLAYERSTATE::PS_LEVITATE_ATTACKED);
						DstList->Set_dwTime(0);
						DstList->Set_KnockBack(true);
						break;
					}
					dynamic_cast<CPlayer*>(DstList)->Set_PlayerState(CPlayer::PLAYERSTATE::PS_THRUST_ATTACKED);
					DstList->Set_dwTime(0);
					DstList->Set_KnockBack(true);
					break;

				case ATT_LEVITATE:
					dynamic_cast<CPlayer*>(DstList)->Set_PlayerState(CPlayer::PLAYERSTATE::PS_LEVITATE_ATTACKED);
					DstList->Set_dwTime(0);
					DstList->Set_KnockBack(true);
					break;
				}
				DstList->m_tHitInfo = HInfo;
				SrcList->Set_IsHit(true);
			}
		}
		if (ATT_JUSTEFFECT == HInfo.eAttType)
			continue;
		if (SrcList->Get_IsHit())
			SrcList->Set_Dead(true);
	}

	//for (auto& DstList : Dst)
	//{
	//	for (auto& SrcList : Src)
	//	{
	//		if (DstList->Get_IsImmune())
	//			continue;

	//		tagHitInfo HInfo;

	//		HInfo.eAttType = SrcList->Get_AttackType();
	//		HInfo.bIsHit = SrcList->Get_IsHit();
	//		HInfo.fAttPoint = SrcList->Get_AttPoint();
	//		HInfo.fAttRatio = SrcList->Get_AttRatio();
	//		HInfo.fThrustPower = SrcList->Get_ThrustPower();
	//		HInfo.fThrustAccel = SrcList->Get_ThrustAccel();
	//		HInfo.fLevitatePower = SrcList->Get_LevitatePower();
	//		HInfo.fLevitateAngle = SrcList->Get_LevitateAngle();
	//		HInfo.fKnockbackAngle = SrcList->Get_KnockbackAngle();
	//		HInfo.fKnockbackTime = SrcList->Get_KnockbackTime();

	//		if (ATT_JUSTEFFECT == HInfo.eAttType || HInfo.bIsHit)
	//			continue;

	//		if (Check_AttackRect(DstList, SrcList, &fX, &fY))
	//		{
	//			// ���⼭ ���� Ÿ���� �Ǵ��ؼ� SetState�� ���ش�
	//			switch (HInfo.eAttType)
	//			{
	//			case ATT_NORMAL:
	//				if (CPlayer::PS_LEVITATE_ATTACKED == dynamic_cast<CPlayer*>(DstList)->Get_State() ||
	//					CPlayer::PS_JUMP == dynamic_cast<CPlayer*>(DstList)->Get_State() ||
	//					CPlayer::PS_JUMPATTACK == dynamic_cast<CPlayer*>(DstList)->Get_State())
	//				{
	//					dynamic_cast<CPlayer*>(DstList)->Set_State(CPlayer::PLAYERSTATE::PS_LEVITATE_ATTACKED);
	//					break;
	//				}
	//				dynamic_cast<CPlayer*>(DstList)->Set_State(CPlayer::PLAYERSTATE::PS_NORMAL_ATTACKED);
	//				break;

	//			case ATT_THRUST:
	//				if (CPlayer::PS_LEVITATE_ATTACKED == dynamic_cast<CPlayer*>(DstList)->Get_State() ||
	//					CPlayer::PS_JUMP == dynamic_cast<CPlayer*>(DstList)->Get_State() ||
	//					CPlayer::PS_JUMPATTACK == dynamic_cast<CPlayer*>(DstList)->Get_State())
	//				{
	//					dynamic_cast<CPlayer*>(DstList)->Set_State(CPlayer::PLAYERSTATE::PS_LEVITATE_ATTACKED);
	//					break;
	//				}
	//				dynamic_cast<CPlayer*>(DstList)->Set_State(CPlayer::PLAYERSTATE::PS_THRUST_ATTACKED);
	//				break;

	//			case ATT_LEVITATE:
	//				dynamic_cast<CPlayer*>(DstList)->Set_State(CPlayer::PLAYERSTATE::PS_LEVITATE_ATTACKED);
	//				break;
	//			}
	//			DstList->m_tHitInfo = HInfo;
	//			DstList->Set_dwTime(0);
	//			DstList->Set_KnockBack(true);
	//			SrcList->Set_IsHit(true);
	//			if (SrcList->Get_DeadType())
	//				SrcList->Set_Dead(true);
	//		}
	//	}
	//}
}

// (�÷��̾� - ���� ��������) �浹
void CCollsionMgr::Collision_WAttackRectPM(list<CObj*> Dst, list<CObj*> Src)
{
	float	fX = 0.f, fY = 0.f;

	for (auto& DstList : Dst)
	{
		for (auto& SrcList : Src)
		{
			if (DstList->Get_IsImmune())
				continue;

			tagHitInfo HInfo;

			HInfo.eAttType = SrcList->Get_AttackType();
			HInfo.bIsHit = SrcList->Get_IsHit();
			HInfo.fAttPoint = SrcList->Get_AttPoint();
			HInfo.fAttRatio = SrcList->Get_AttRatio();
			HInfo.fThrustPower = SrcList->Get_ThrustPower();
			HInfo.fThrustAccel = SrcList->Get_ThrustAccel();
			HInfo.fLevitatePower = SrcList->Get_LevitatePower();
			HInfo.fLevitateAngle = SrcList->Get_LevitateAngle();
			HInfo.fKnockbackAngle = SrcList->Get_KnockbackAngle();
			HInfo.fKnockbackTime = SrcList->Get_KnockbackTime();

			if (ATT_JUSTEFFECT == HInfo.eAttType || HInfo.bIsHit)
				continue;

			if (Check_WAttackRect(DstList, SrcList, &fX, &fY))
			{
				// ���⼭ ���� Ÿ���� �Ǵ��ؼ� SetState�� ���ش�
				switch (HInfo.eAttType)
				{
				case ATT_NORMAL:
					if (CPlayer::PS_LEVITATE_ATTACKED == dynamic_cast<CPlayer*>(DstList)->Get_PlayerState() ||
						CPlayer::PS_JUMP == dynamic_cast<CPlayer*>(DstList)->Get_PlayerState() ||
						CPlayer::PS_JUMPATTACK == dynamic_cast<CPlayer*>(DstList)->Get_PlayerState())
					{
						dynamic_cast<CPlayer*>(DstList)->Set_PlayerState(CPlayer::PLAYERSTATE::PS_LEVITATE_ATTACKED);
						break;
					}
					dynamic_cast<CPlayer*>(DstList)->Set_PlayerState(CPlayer::PLAYERSTATE::PS_NORMAL_ATTACKED);
					break;

				case ATT_THRUST:
					if (CPlayer::PS_LEVITATE_ATTACKED == dynamic_cast<CPlayer*>(DstList)->Get_PlayerState() ||
						CPlayer::PS_JUMP == dynamic_cast<CPlayer*>(DstList)->Get_PlayerState() ||
						CPlayer::PS_JUMPATTACK == dynamic_cast<CPlayer*>(DstList)->Get_PlayerState())
					{
						dynamic_cast<CPlayer*>(DstList)->Set_PlayerState(CPlayer::PLAYERSTATE::PS_LEVITATE_ATTACKED);
						break;
					}
					dynamic_cast<CPlayer*>(DstList)->Set_PlayerState(CPlayer::PLAYERSTATE::PS_THRUST_ATTACKED);
					break;

				case ATT_LEVITATE:
					dynamic_cast<CPlayer*>(DstList)->Set_PlayerState(CPlayer::PLAYERSTATE::PS_LEVITATE_ATTACKED);
					break;
				}
				DstList->m_tHitInfo = HInfo;
				DstList->Set_KnockBack(true);
				SrcList->Set_IsHit(true);
				DstList->Set_dwTime(0);
				if (SrcList->Get_DeadType())
					SrcList->Set_Dead(true);
			}
		}
	}
}

// (�÷��̾����Src - ����Dst) �浹
void CCollsionMgr::Collision_AttackRectMP(list<CObj*> Src, list<CObj*> Dst)
{
	float	fX = 0.f, fY = 0.f;

	for (auto& SrcList : Src)
	{
		tagHitInfo HInfo;

		HInfo.eAttType = SrcList->Get_AttackType();
		HInfo.bIsHit = SrcList->Get_IsHit();
		HInfo.fAttPoint = SrcList->Get_AttPoint();
		HInfo.fAttRatio = SrcList->Get_AttRatio();
		HInfo.fThrustPower = SrcList->Get_ThrustPower();
		HInfo.fThrustAccel = SrcList->Get_ThrustAccel();
		HInfo.fLevitatePower = SrcList->Get_LevitatePower();
		HInfo.fLevitateAngle = SrcList->Get_LevitateAngle();
		HInfo.fKnockbackAngle = SrcList->Get_KnockbackAngle();
		HInfo.fKnockbackTime = SrcList->Get_KnockbackTime();

		for (auto& DstList : Dst)
		{
			if (Check_AttackRect(DstList, SrcList, &fX, &fY))
			{
				if (DstList->Get_IsImmune())
					continue;

				if (ATT_JUSTEFFECT == HInfo.eAttType)
					continue;

				// �浹����� �齺���̶�� �������� �������ʰ� Set_Dead()��
				if (L"BlueRune" == DstList->Get_FrameKey() || L"RedRune" == DstList->Get_FrameKey())
				{
					SrcList->Set_Dead(true);
					DstList->Set_Dead(true);
					continue;
				}

				float fTotal_Damage = 0.f;
				bool bCritical = false;

				// ���⼭ ���� Ÿ���� �Ǵ��ؼ� SetState�� ���ش�
				switch (HInfo.eAttType)
				{
				case ATT_NORMAL:
					if (BOSS == DstList->m_eMonType)
					{
						// �÷��̾��� ũ��Ƽ�� Ȯ���� ���� ġ��Ÿ ����
						if (rand() % 100 < CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).back()->Get_CriRatio())
							bCritical = true;

						// ������ ���� ����
						fTotal_Damage = (HInfo.fAttPoint * HInfo.fAttRatio) + float(rand() % 15000);
						if (bCritical)
							fTotal_Damage *= 1.5f;

						DstList->Take_Damage(fTotal_Damage);
						DstList->Draw_Font(int(fTotal_Damage), bCritical);
						DstList->Draw_HitEffect();
						DstList->Draw_HpBar(DstList->Get_Info().fMaxHp, DstList->Get_MaxDrawLineCount(), fTotal_Damage);
						break;
					}
					if (MON_LEVITATE_ATTACKED == dynamic_cast<CMonster*>(DstList)->Get_State())
					{
						dynamic_cast<CMonster*>(DstList)->Set_State(MON_LEVITATE_ATTACKED);
						dynamic_cast<CMonster*>(DstList)->Get_AI()->SetCurState(MON_LEVITATE_ATTACKED);
						dynamic_cast<CMonster*>(DstList)->Get_AI()->GetCurState()->Enter();
						DstList->Set_dwTime(0);
						DstList->Set_KnockBack(true);
						break;
					}
					dynamic_cast<CMonster*>(DstList)->Set_State(MON_NORMAL_ATTACKED);
					dynamic_cast<CMonster*>(DstList)->Get_AI()->SetCurState(MON_NORMAL_ATTACKED);
					dynamic_cast<CMonster*>(DstList)->Get_AI()->GetCurState()->Enter();
					DstList->Set_dwTime(0);
					DstList->Set_KnockBack(true);
					break;

				case ATT_THRUST:
					if (BOSS == DstList->m_eMonType)
					{
						// �÷��̾��� ũ��Ƽ�� Ȯ���� ���� ġ��Ÿ ����
						if (rand() % 100 < CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).back()->Get_CriRatio())
							bCritical = true;

						// ������ ���� ����
						fTotal_Damage = (HInfo.fAttPoint * HInfo.fAttRatio) + float(rand() % 15000);
						if (bCritical)
							fTotal_Damage *= 1.5f;

						DstList->Take_Damage(fTotal_Damage);
						DstList->Draw_Font(int(fTotal_Damage), bCritical);
						DstList->Draw_HitEffect();
						DstList->Draw_HpBar(DstList->Get_Info().fMaxHp, DstList->Get_MaxDrawLineCount(), fTotal_Damage);
						break;
					}
					if (MON_LEVITATE_ATTACKED == dynamic_cast<CMonster*>(DstList)->Get_State())
					{
						dynamic_cast<CMonster*>(DstList)->Set_State(MON_LEVITATE_ATTACKED);
						dynamic_cast<CMonster*>(DstList)->Get_AI()->SetCurState(MON_LEVITATE_ATTACKED);
						dynamic_cast<CMonster*>(DstList)->Get_AI()->GetCurState()->Enter();
						DstList->Set_dwTime(0);
						DstList->Set_KnockBack(true);
						break;
					}
					dynamic_cast<CMonster*>(DstList)->Set_State(MON_THRUST_ATTACKED);
					dynamic_cast<CMonster*>(DstList)->Get_AI()->SetCurState(MON_THRUST_ATTACKED);
					dynamic_cast<CMonster*>(DstList)->Get_AI()->GetCurState()->Enter();
					DstList->Set_dwTime(0);
					DstList->Set_KnockBack(true);
					break;

				case ATT_LEVITATE:
					if (BOSS == DstList->m_eMonType)
					{
						// �÷��̾��� ũ��Ƽ�� Ȯ���� ���� ġ��Ÿ ����
						if (rand() % 100 < CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).back()->Get_CriRatio())
							bCritical = true;

						// ������ ���� ����
						fTotal_Damage = (HInfo.fAttPoint * HInfo.fAttRatio) + float(rand() % 15000);
						if (bCritical)
							fTotal_Damage *= 1.5f;

						DstList->Take_Damage(fTotal_Damage);
						DstList->Draw_Font(int(fTotal_Damage), bCritical);
						DstList->Draw_HitEffect();
						DstList->Draw_HpBar(DstList->Get_Info().fMaxHp, DstList->Get_MaxDrawLineCount(), fTotal_Damage);
						break;
					}
					dynamic_cast<CMonster*>(DstList)->Set_State(MON_LEVITATE_ATTACKED);
					dynamic_cast<CMonster*>(DstList)->Get_AI()->SetCurState(MON_LEVITATE_ATTACKED);
					dynamic_cast<CMonster*>(DstList)->Get_AI()->GetCurState()->Enter();
					DstList->Set_dwTime(0);
					DstList->Set_KnockBack(true);
					break;
				}
				DstList->m_tHitInfo = HInfo;
				SrcList->Set_IsHit(true);
			}
		}
		if (ATT_JUSTEFFECT == HInfo.eAttType)
			continue;
		if (SrcList->Get_IsHit())
			SrcList->Set_Dead(true);
	}
}

// (�÷��̾� ��������Src - ����Dst) �浹
void CCollsionMgr::Collision_WAttackRectMP(list<CObj*> Src, list<CObj*> Dst)
{
	float	fX = 0.f, fY = 0.f;

	for (auto& SrcList : Src)
	{
		tagHitInfo HInfo;

		HInfo.eAttType = SrcList->Get_AttackType();
		HInfo.bIsHit = SrcList->Get_IsHit();
		HInfo.fAttPoint = SrcList->Get_AttPoint();
		HInfo.fAttRatio = SrcList->Get_AttRatio();
		HInfo.fThrustPower = SrcList->Get_ThrustPower();
		HInfo.fThrustAccel = SrcList->Get_ThrustAccel();
		HInfo.fLevitatePower = SrcList->Get_LevitatePower();
		HInfo.fLevitateAngle = SrcList->Get_LevitateAngle();
		HInfo.fKnockbackAngle = SrcList->Get_KnockbackAngle();
		HInfo.fKnockbackTime = SrcList->Get_KnockbackTime();

		for (auto& DstList : Dst)
		{
			if (Check_AwakenAttackRect(DstList, SrcList, &fX, &fY))
			{
				if (DstList->Get_IsImmune())
					continue;

				if (ATT_JUSTEFFECT == HInfo.eAttType)
					continue;

				float fTotal_Damage = 0.f;
				bool bCritical = false;

				// ���⼭ ���� Ÿ���� �Ǵ��ؼ� SetState�� ���ش�
				switch (HInfo.eAttType)
				{
				case ATT_NORMAL:
					if (BOSS == DstList->m_eMonType)
					{
						// �÷��̾��� ũ��Ƽ�� Ȯ���� ���� ġ��Ÿ ����
						if (rand() % 100 < CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).back()->Get_CriRatio())
							bCritical = true;

						// ������ ���� ����
						fTotal_Damage = (HInfo.fAttPoint * HInfo.fAttRatio) + float(rand() % 15000);
						if (bCritical)
							fTotal_Damage *= 1.5f;

						DstList->Take_Damage(fTotal_Damage);
						DstList->Draw_Font(int(fTotal_Damage), bCritical);
						DstList->Draw_HitEffect();
						DstList->Draw_HpBar(DstList->Get_Info().fMaxHp, DstList->Get_MaxDrawLineCount(), fTotal_Damage);
						break;
					}
					if (MON_LEVITATE_ATTACKED == dynamic_cast<CMonster*>(DstList)->Get_State())
					{
						dynamic_cast<CMonster*>(DstList)->Set_State(MON_LEVITATE_ATTACKED);
						dynamic_cast<CMonster*>(DstList)->Get_AI()->SetCurState(MON_LEVITATE_ATTACKED);
						dynamic_cast<CMonster*>(DstList)->Get_AI()->GetCurState()->Enter();
						DstList->Set_dwTime(0);
						DstList->Set_KnockBack(true);
						break;
					}
					dynamic_cast<CMonster*>(DstList)->Set_State(MON_NORMAL_ATTACKED);
					dynamic_cast<CMonster*>(DstList)->Get_AI()->SetCurState(MON_NORMAL_ATTACKED);
					dynamic_cast<CMonster*>(DstList)->Get_AI()->GetCurState()->Enter();
					DstList->Set_dwTime(0);
					DstList->Set_KnockBack(true);
					break;

				case ATT_THRUST:
					if (BOSS == DstList->m_eMonType)
					{
						// �÷��̾��� ũ��Ƽ�� Ȯ���� ���� ġ��Ÿ ����
						if (rand() % 100 < CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).back()->Get_CriRatio())
							bCritical = true;

						// ������ ���� ����
						fTotal_Damage = (HInfo.fAttPoint * HInfo.fAttRatio) + float(rand() % 15000);
						if (bCritical)
							fTotal_Damage *= 1.5f;

						DstList->Take_Damage(fTotal_Damage);
						DstList->Draw_Font(int(fTotal_Damage), bCritical);
						DstList->Draw_HitEffect();
						DstList->Draw_HpBar(DstList->Get_Info().fMaxHp, DstList->Get_MaxDrawLineCount(), fTotal_Damage);
						break;
					}
					if (MON_LEVITATE_ATTACKED == dynamic_cast<CMonster*>(DstList)->Get_State())
					{
						dynamic_cast<CMonster*>(DstList)->Set_State(MON_LEVITATE_ATTACKED);
						dynamic_cast<CMonster*>(DstList)->Get_AI()->SetCurState(MON_LEVITATE_ATTACKED);
						break;
					}
					dynamic_cast<CMonster*>(DstList)->Set_State(MON_THRUST_ATTACKED);
					dynamic_cast<CMonster*>(DstList)->Get_AI()->SetCurState(MON_THRUST_ATTACKED);
					dynamic_cast<CMonster*>(DstList)->Get_AI()->GetCurState()->Enter();
					DstList->Set_dwTime(0);
					DstList->Set_KnockBack(true);
					break;

				case ATT_LEVITATE:
					if (BOSS == DstList->m_eMonType)
					{
						// �÷��̾��� ũ��Ƽ�� Ȯ���� ���� ġ��Ÿ ����
						if (rand() % 100 < CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).back()->Get_CriRatio())
							bCritical = true;

						// ������ ���� ����
						fTotal_Damage = (HInfo.fAttPoint * HInfo.fAttRatio) + float(rand() % 15000);
						if (bCritical)
							fTotal_Damage *= 1.5f;

						DstList->Take_Damage(fTotal_Damage);
						DstList->Draw_Font(int(fTotal_Damage), bCritical);
						DstList->Draw_HitEffect();
						DstList->Draw_HpBar(DstList->Get_Info().fMaxHp, DstList->Get_MaxDrawLineCount(), fTotal_Damage);
						break;
					}
					dynamic_cast<CMonster*>(DstList)->Set_State(MON_LEVITATE_ATTACKED);
					dynamic_cast<CMonster*>(DstList)->Get_AI()->SetCurState(MON_LEVITATE_ATTACKED);
					dynamic_cast<CMonster*>(DstList)->Get_AI()->GetCurState()->Enter();
					DstList->Set_dwTime(0);
					DstList->Set_KnockBack(true);
					break;
				}
				DstList->m_tHitInfo = HInfo;
				SrcList->Set_IsHit(true);
			}
		}
		if (ATT_JUSTEFFECT == HInfo.eAttType)
			continue;
		if (SrcList->Get_IsHit())
			SrcList->Set_Dead(true);
	}
}

// (�ǰݴ��(Dst) - ���ݴ��(Src)) ���� �浹 ����
bool CCollsionMgr::Check_AttackRect(CObj* pDst, CObj* pSrc, float* pX, float* pY)
{
	float		fWidth = abs(float(pDst->Get_RectCollisionCenter().x) - pSrc->Get_Info().fX);
	float		fHeight = abs(float(pDst->Get_RectCollisionCenter().y) - pSrc->Get_Info().fY);

	float		fCX = (pDst->Get_RectCollisionSizeX() * 0.5f) + (pSrc->Get_Info().fCX * 0.5f);
	float		fCY = (pDst->Get_RectCollisionSizeY() * 0.5f) + (pSrc->Get_Info().fCY * 0.5f);

	// �÷��̾��� ���� ������ ���� y��ǥ��
	// ���� ������ ������� y��ǥ�� ���Ͽ� ���� ���� ���ϸ� �ǰ�����
	if ((fCX >= fWidth && fCY >= fHeight) && (abs(pDst->Get_TileCollision().bottom - pSrc->Get_CreatedBottom()) < 60.f))
	{
		*pX = fCX - fWidth;
		*pY = fCY - fHeight;

		return true;
	}

	return false;
}

// (�ǰݴ��(Dst) - ��������(Src)) ���� �浹 ����
bool CCollsionMgr::Check_WAttackRect(CObj* pDst, CObj* pSrc, float* pX, float* pY)
{
	float		fWidth = abs(float(pDst->Get_RectCollisionCenter().x) - pSrc->Get_RectCollisionCenter().x);
	float		fHeight = abs(float(pDst->Get_RectCollisionCenter().y) - pSrc->Get_RectCollisionCenter().y);

	float		fCX = (pDst->Get_RectCollisionSizeX() * 0.5f) + (pSrc->Get_RectCollisionSizeX() * 0.5f);
	float		fCY = (pDst->Get_RectCollisionSizeY() * 0.5f) + (pSrc->Get_RectCollisionSizeY() * 0.5f);

	if ((fCX >= fWidth && fCY >= fHeight) && (abs(pDst->Get_TileCollision().bottom - pSrc->Get_RectCollision().bottom) < 40.f))
	{
		*pX = fCX - fWidth;
		*pY = fCY - fHeight;

		return true;
	}

	return false;
}

// ������� ��ü ����
bool CCollsionMgr::Check_AwakenAttackRect(CObj* pDst, CObj* pSrc, float* pX, float* pY)
{
	float		fWidth = abs(float(pDst->Get_RectCollisionCenter().x) - pSrc->Get_RectCollisionCenter().x);
	float		fHeight = abs(float(pDst->Get_RectCollisionCenter().y) - pSrc->Get_RectCollisionCenter().y);

	float		fCX = (pDst->Get_RectCollisionSizeX() * 0.5f) + (pSrc->Get_RectCollisionSizeX() * 0.5f);
	float		fCY = (pDst->Get_RectCollisionSizeY() * 0.5f) + (pSrc->Get_RectCollisionSizeY() * 0.5f);

	if ((fCX >= fWidth && fCY >= fHeight) && (abs(pDst->Get_TileCollision().bottom - pSrc->Get_RectCollision().bottom) < 60.f))
	{
		*pX = fCX - fWidth;
		*pY = fCY - fHeight;

		return true;
	}

	return false;
}

// (�÷��̾� ��������Src - ����Dst) �浹2
void CCollsionMgr::Collision_WAttackRectMP2(list<CObj*> Src, list<CObj*> Dst)
{
	float	fX = 0.f, fY = 0.f;

	for (auto& SrcList : Src)
	{
		tagHitInfo HInfo;

		HInfo.eAttType = SrcList->Get_AttackType();
		HInfo.bIsHit = SrcList->Get_IsHit();
		HInfo.fAttPoint = SrcList->Get_AttPoint();
		HInfo.fAttRatio = SrcList->Get_AttRatio();
		HInfo.fThrustPower = SrcList->Get_ThrustPower();
		HInfo.fThrustAccel = SrcList->Get_ThrustAccel();
		HInfo.fLevitatePower = SrcList->Get_LevitatePower();
		HInfo.fLevitateAngle = SrcList->Get_LevitateAngle();
		HInfo.fKnockbackAngle = SrcList->Get_KnockbackAngle();
		HInfo.fKnockbackTime = SrcList->Get_KnockbackTime();

		for (auto& DstList : Dst)
		{
			if (Check_AwakenAttackRect2(DstList, SrcList, &fX, &fY))
			{
				if (DstList->Get_IsImmune())
					continue;

				if (ATT_JUSTEFFECT == HInfo.eAttType)
					continue;

				float fTotal_Damage = 0.f;
				bool bCritical = false;

				// ���⼭ ���� Ÿ���� �Ǵ��ؼ� SetState�� ���ش�
				switch (HInfo.eAttType)
				{
				case ATT_NORMAL:
					if (BOSS == DstList->m_eMonType)
					{
						// �÷��̾��� ũ��Ƽ�� Ȯ���� ���� ġ��Ÿ ����
						if (rand() % 100 < CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).back()->Get_CriRatio())
							bCritical = true;

						// ������ ���� ����
						fTotal_Damage = (HInfo.fAttPoint * HInfo.fAttRatio) + float(rand() % 15000);
						if (bCritical)
							fTotal_Damage *= 1.5f;

						DstList->Take_Damage(fTotal_Damage);
						DstList->Draw_Font(int(fTotal_Damage), bCritical);
						DstList->Draw_HitEffect();
						DstList->Draw_HpBar(DstList->Get_Info().fMaxHp, DstList->Get_MaxDrawLineCount(), fTotal_Damage);
						break;
					}
					if (MON_LEVITATE_ATTACKED == dynamic_cast<CMonster*>(DstList)->Get_State())
					{
						dynamic_cast<CMonster*>(DstList)->Set_State(MON_LEVITATE_ATTACKED);
						dynamic_cast<CMonster*>(DstList)->Get_AI()->SetCurState(MON_LEVITATE_ATTACKED);
						dynamic_cast<CMonster*>(DstList)->Get_AI()->GetCurState()->Enter();
						DstList->Set_dwTime(0);
						DstList->Set_KnockBack(true);
						break;
					}
					dynamic_cast<CMonster*>(DstList)->Set_State(MON_NORMAL_ATTACKED);
					dynamic_cast<CMonster*>(DstList)->Get_AI()->SetCurState(MON_NORMAL_ATTACKED);
					dynamic_cast<CMonster*>(DstList)->Get_AI()->GetCurState()->Enter();
					DstList->Set_dwTime(0);
					DstList->Set_KnockBack(true);
					break;

				case ATT_THRUST:
					if (BOSS == DstList->m_eMonType)
					{
						// �÷��̾��� ũ��Ƽ�� Ȯ���� ���� ġ��Ÿ ����
						if (rand() % 100 < CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).back()->Get_CriRatio())
							bCritical = true;

						// ������ ���� ����
						fTotal_Damage = (HInfo.fAttPoint * HInfo.fAttRatio) + float(rand() % 15000);
						if (bCritical)
							fTotal_Damage *= 1.5f;

						DstList->Take_Damage(fTotal_Damage);
						DstList->Draw_Font(int(fTotal_Damage), bCritical);
						DstList->Draw_HitEffect();
						DstList->Draw_HpBar(DstList->Get_Info().fMaxHp, DstList->Get_MaxDrawLineCount(), fTotal_Damage);
						break;
					}
					if (MON_LEVITATE_ATTACKED == dynamic_cast<CMonster*>(DstList)->Get_State())
					{
						dynamic_cast<CMonster*>(DstList)->Set_State(MON_LEVITATE_ATTACKED);
						dynamic_cast<CMonster*>(DstList)->Get_AI()->SetCurState(MON_LEVITATE_ATTACKED);
						break;
					}
					dynamic_cast<CMonster*>(DstList)->Set_State(MON_THRUST_ATTACKED);
					dynamic_cast<CMonster*>(DstList)->Get_AI()->SetCurState(MON_THRUST_ATTACKED);
					dynamic_cast<CMonster*>(DstList)->Get_AI()->GetCurState()->Enter();
					DstList->Set_dwTime(0);
					DstList->Set_KnockBack(true);
					break;

				case ATT_LEVITATE:
					if (BOSS == DstList->m_eMonType)
					{
						// �÷��̾��� ũ��Ƽ�� Ȯ���� ���� ġ��Ÿ ����
						if (rand() % 100 < CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).back()->Get_CriRatio())
							bCritical = true;

						// ������ ���� ����
						fTotal_Damage = (HInfo.fAttPoint * HInfo.fAttRatio) + float(rand() % 15000);
						if (bCritical)
							fTotal_Damage *= 1.5f;

						DstList->Take_Damage(fTotal_Damage);
						DstList->Draw_Font(int(fTotal_Damage), bCritical);
						DstList->Draw_HitEffect();
						DstList->Draw_HpBar(DstList->Get_Info().fMaxHp, DstList->Get_MaxDrawLineCount(), fTotal_Damage);
						break;
					}
					dynamic_cast<CMonster*>(DstList)->Set_State(MON_LEVITATE_ATTACKED);
					dynamic_cast<CMonster*>(DstList)->Get_AI()->SetCurState(MON_LEVITATE_ATTACKED);
					dynamic_cast<CMonster*>(DstList)->Get_AI()->GetCurState()->Enter();
					DstList->Set_dwTime(0);
					DstList->Set_KnockBack(true);
					break;
				}
				DstList->m_tHitInfo = HInfo;
				SrcList->Set_IsHit(true);
			}
		}
		if (ATT_JUSTEFFECT == HInfo.eAttType)
			continue;
		if (SrcList->Get_IsHit())
			SrcList->Set_Dead(true);
	}
}

// ������� ��ü ����2
bool CCollsionMgr::Check_AwakenAttackRect2(CObj* pDst, CObj* pSrc, float* pX, float* pY)
{
	float		fWidth = abs(float(pDst->Get_RectCollisionCenter().x) - pSrc->Get_RectCollisionCenter().x);
	float		fHeight = abs(float(pDst->Get_RectCollisionCenter().y) - pSrc->Get_RectCollisionCenter().y);

	float		fCX = (pDst->Get_RectCollisionSizeX() * 0.5f) + (pSrc->Get_RectCollisionSizeX() * 0.5f);
	float		fCY = (pDst->Get_RectCollisionSizeY() * 0.5f) + (pSrc->Get_RectCollisionSizeY() * 0.5f);

	if ((fCX >= fWidth && fCY >= fHeight) && (abs(pDst->Get_TileCollision().bottom - pSrc->Get_RectCollision().bottom) < 60.f))
	{
		*pX = fCX - fWidth;
		*pY = fCY - fHeight;

		return true;
	}

	return true;
}

// =====================================================================================
// =====================================================================================
// =====================================================================================

// (�÷��̾� - Ÿ��)
void CCollsionMgr::Collision_RectExTile(list<CObj*> Dst, vector<CObj*> Src)
{
	float	fX = 0.f, fY = 0.f;

	for (auto& DstList : Dst)
	{
		for (auto& SrcVec : Src)
		{
			// Ÿ���� ��ο�ɼ��� 1�̸� �̵� �Ұ����� Ÿ��
			if (-1 == dynamic_cast<CTileNode*>(SrcVec)->Get_Option())
			{
				if (Check_TileRect(DstList, SrcVec, &fX, &fY))
				{
					// ���� �浹
					if (fX > fY)
					{
							 // �� �浹
						if (DstList->Get_TileCollisionCenter().y < SrcVec->Get_Info().fY)
						{
							DstList->Set_PosY(-fY);
						}
						else // �� �浹
						{
							DstList->Set_PosY(fY);
						}
					}
					// �¿� �浹
					else
					{
						if (DstList->Get_TileCollisionCenter().x < SrcVec->Get_Info().fX)
						{
							DstList->Set_PosX(-fX);
						}
						else // �� �浹
						{
							DstList->Set_PosX(fX);
						}
					}

				}
			}
		}
	}
}

// (�÷��̾� - Ÿ��) �浹 ����
bool CCollsionMgr::Check_TileRect(CObj * pDst, CObj * pSrc, float * pX, float * pY)
{
	float		fWidth  = abs(float(pDst->Get_TileCollisionCenter().x) - pSrc->Get_Info().fX);
	float		fHeight = abs(float(pDst->Get_TileCollisionCenter().y) - pSrc->Get_Info().fY);

	float		fCX = float(TILECX);
	float		fCY = float(TILECX);

	if ((fCX >= fWidth) && (fCY >= fHeight))
	{
		*pX = fCX - fWidth;
		*pY = fCY - fHeight;

		return true;
	}
	
	return false;
}

// �� �浹
bool CCollsionMgr::Check_Sphere(CObj * pDst, CObj * pSrc)
{
	float		fWidth = fabs(pDst->Get_Info().fX - pSrc->Get_Info().fX);
	float		fHeight = fabs(pDst->Get_Info().fY - pSrc->Get_Info().fY);

	float		fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float		fRadius = (pDst->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;
	
	return fRadius >= fDiagonal;
}

// �� �浹 ����
void CCollsionMgr::Collision_Sphere(list<CObj*> Dst, list<CObj*> Src)
{

	for (auto& DstList : Dst)
	{
		for (auto& SrcList : Src)
		{
			if (Check_Sphere(DstList, SrcList))
			{
				DstList->Set_Dead(true);
				SrcList->Set_Dead(true);
			}
		}
	}

}

void CCollsionMgr::PlayItemSound(ITEM_TYPE _eItemType)
{
	switch (_eItemType)
	{
	case ITEM_WEAPON:
		CSoundMgr::Get_Instance()->PlaySoundW(L"WeaponUse.wav", SOUND_EFFECT, g_fVolume);
		break;

	case ITEM_TITLE:
		CSoundMgr::Get_Instance()->PlaySoundW(L"click2.ogg", SOUND_EFFECT, g_fVolume);
		break;

	case ITEM_SHOULDER:
		CSoundMgr::Get_Instance()->PlaySoundW(L"click2.ogg", SOUND_EFFECT, g_fVolume);
		break;

	case ITEM_TOP:
		CSoundMgr::Get_Instance()->PlaySoundW(L"click2.ogg", SOUND_EFFECT, g_fVolume);
		break;

	case ITEM_PANTS:
		CSoundMgr::Get_Instance()->PlaySoundW(L"click2.ogg", SOUND_EFFECT, g_fVolume);
		break;

	case ITEM_WAIST:
		CSoundMgr::Get_Instance()->PlaySoundW(L"click2.ogg", SOUND_EFFECT, g_fVolume);
		break;

	case ITEM_SHOES:
		CSoundMgr::Get_Instance()->PlaySoundW(L"click2.ogg", SOUND_EFFECT, g_fVolume);
		break;

	case ITEM_BRACELET:
		CSoundMgr::Get_Instance()->PlaySoundW(L"bracelet.ogg", SOUND_EFFECT, g_fVolume);
		break;

	case ITEM_NECKLACE:
		CSoundMgr::Get_Instance()->PlaySoundW(L"NecklessUse.ogg", SOUND_EFFECT, g_fVolume);
		break;

	case ITEM_RING:
		CSoundMgr::Get_Instance()->PlaySoundW(L"RingUse.ogg", SOUND_EFFECT, g_fVolume);
		break;

	case ITEM_ASSIST:
		CSoundMgr::Get_Instance()->PlaySoundW(L"bracelet.ogg", SOUND_EFFECT, g_fVolume);
		break;

	case ITEM_STONE:
		CSoundMgr::Get_Instance()->PlaySoundW(L"bracelet.ogg", SOUND_EFFECT, g_fVolume);
		break;
	}
}