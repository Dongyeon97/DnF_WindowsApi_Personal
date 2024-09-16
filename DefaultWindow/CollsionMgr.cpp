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

// 단순 충돌 - [ 인벤토리 <-> 마우스 ] 체크용
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
				// 마우스 포인터를 가져다대고 오른쪽버튼을 클릭하면
				if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RBUTTON))
				{
					DWORD currentTime = GetTickCount64();
					RENDERID preID = DstList->Get_RenderID();

					// 1. 인벤토리와 상점 둘다 열려있는 경우 판매
					if (dynamic_cast<CUI_Inven*>(CObjMgr::Get_Instance()->GetObjList(OBJ_INVEN).front())->Get_Render()
						&& dynamic_cast<CUI_Store*>(CObjMgr::Get_Instance()->GetObjList(OBJ_STORE).front())->Get_Render()
						&& currentTime - m_lClickTime > 300)
					{
						DstList->Set_Dead(true);
						CUI_Inven::Check_InvenIndex(DstList->Get_Index());
						PlayItemSound(DstList->Get_ItemType());
						m_lClickTime = GetTickCount64();
					}
					// 2. 인벤토리만 열려있는 경우(우클릭시 장착)
					// 이미 같은 타입의 아이템이 장착되어 있을경우 위치를 교환함
					else if (dynamic_cast<CUI_Inven*>(CObjMgr::Get_Instance()->GetObjList(OBJ_INVEN).front())->Get_Render()
						&& currentTime - m_lClickTime > 300)
					{
						// 우클릭한 장비가 장착중인 장비라면, 장착 해제후 인벤토리로 이동
						if (DstList->Get_Equip())
						{
							int iIndex = CUI_Inven::Find_InvenIndex();

							int Xindex = iIndex % 8;
							int Yindex = iIndex / 8;

							LONG lRectLeft = CObjMgr::Get_Instance()->GetObjList(OBJ_INVEN).back()->Get_Rect().left;
							LONG lRectTop = CObjMgr::Get_Instance()->GetObjList(OBJ_INVEN).back()->Get_Rect().top;

							// 넣어준다
							CObjMgr::Get_Instance()->Add_Object(OBJ_INVENITEM,
								CAbstractFactory<CItem>::Create_Obj(lRectLeft + (LONG)24 + (Xindex * 30.f), lRectTop + (LONG)245 + (Yindex * 30.f),
																DstList->Get_Attack(), DstList->Get_Hp(), DstList->Get_Name(), DstList->Get_FrameKey()));
							CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM).back()->Set_ItemType(DstList->Get_ItemType());
							CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM).back()->Set_RGB(DstList->Get_RGB());
							CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM).back()->Set_Index(iIndex);
							CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM).back()->Set_RenderID(preID);

							// 해당 칸에 아이템이 들어갔다고 알리고, 장비칸 해제를 알린다, 능력치를 차감한다
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

						// 만약 이미 장착중인 장비가 있다면
						if (!(CUI_Inven::Is_EquipIndex(DstList->Get_ItemType())))
						{
							// 먼저 슬롯을 비워준다
							CUI_Inven::Check_InvenIndex(DstList->Get_Index());
							
							// 장착중인 장비가 무엇인지 인벤토리에서 찾는다
							list<CObj*> inven = CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM);
							
							auto iter = inven.begin();

							for (iter; iter != inven.end(); ++iter)
							{
								if ((*iter)->Get_ItemType() == DstList->Get_ItemType() && (*iter)->Get_Equip())
								{
									break;
								}
							}

							// 같은장비라면 패스
							// if (DstList->Get_FrameKey() == (*iter)->Get_FrameKey())
								// break;

							// 마지막으로 장착되었다고 찾아진 아이템과 선택된 아이템의 타입이 같다면

							// 인벤에서 빈칸중에 맨 왼쪽을 찾아서
							if (inven.end() != iter)
							{
								int iIndex = CUI_Inven::Find_InvenIndex();

								int Xindex = iIndex % 8;
								int Yindex = iIndex / 8;

								LONG lRectLeft = CObjMgr::Get_Instance()->GetObjList(OBJ_INVEN).back()->Get_Rect().left;
								LONG lRectTop = CObjMgr::Get_Instance()->GetObjList(OBJ_INVEN).back()->Get_Rect().top;

								// 넣어준다
								CObjMgr::Get_Instance()->Add_Object(OBJ_INVENITEM,
								CAbstractFactory<CItem>::Create_Obj(lRectLeft + (LONG)24 + (Xindex * 30.f), lRectTop + (LONG)245 + (Yindex * 30.f),
									(*iter)->Get_Attack(), (*iter)->Get_Hp(), (*iter)->Get_Name(), (*iter)->Get_FrameKey()));
								CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM).back()->Set_ItemType((*iter)->Get_ItemType());
								CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM).back()->Set_RGB((*iter)->Get_RGB());
								CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM).back()->Set_Index(iIndex);
								CObjMgr::Get_Instance()->GetObjList(OBJ_INVENITEM).back()->Set_RenderID(preID);

								// 해당 칸에 아이템이 들어갔다고 알리고
								CUI_Inven::m_bIndex[iIndex] = true;

								// 해당 아이템 장착해제, 소멸, 능력치 차감
								(*iter)->Set_Equip(false);
								(*iter)->Set_Dead(true);
								if (!CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).empty())
								{
									CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).back();
									pPlayer->Minus_Attack((*iter)->Get_Attack());
									pPlayer->Minus_MaxHp((*iter)->Get_Hp());
								}

								// 선택 아이템 장착, 능력치 증가
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
						// 장착중인 장비가 없다면 그냥 장착, 능력치 증가
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

// 단순 충돌 - [ 상점 <-> 마우스 ] 체크용
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
				// 마우스 포인터를 가져다대고 오른쪽버튼을 클릭하면
				if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RBUTTON))
				{
					// 아이템 구매
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

// 단순 충돌 판정 - [ 아이템 <-> 마우스 ] 체크용
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

// (오브젝트 - 오브젝트) 피격 판정
void CCollsionMgr::Collision_RectEx(list<CObj*> Dst, list<CObj*> Src)
{
	float	fX = 0.f, fY = 0.f;

	for (auto& DstList : Dst)
	{
		for (auto& SrcList : Src)
		{
			if (Check_Rect(DstList, SrcList, &fX, &fY))
			{
				// 상하 충돌
				if (fX > fY)
				{
					if (DstList->Get_Info().fY < SrcList->Get_Info().fY)
					{
						DstList->Set_PosY(-fY);
					}
					else // 하 충돌
					{
						DstList->Set_PosY(fY);
					}
				}
				// 좌우 충돌
				else
				{
					if (DstList->Get_Info().fX < SrcList->Get_Info().fX)
					{
						DstList->Set_PosX(-fX);
					}
					else // 우 충돌
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

// (플레이어 - 몬스터 공격Rect) 충돌
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

				// 여기서 공격 타입을 판단해서 SetState를 해준다
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
	//			// 여기서 공격 타입을 판단해서 SetState를 해준다
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

// (플레이어 - 몬스터 광역공격) 충돌
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
				// 여기서 공격 타입을 판단해서 SetState를 해준다
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

// (플레이어공격Src - 몬스터Dst) 충돌
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

				// 충돌대상이 룬스톤이라면 데미지를 입히지않고 Set_Dead()만
				if (L"BlueRune" == DstList->Get_FrameKey() || L"RedRune" == DstList->Get_FrameKey())
				{
					SrcList->Set_Dead(true);
					DstList->Set_Dead(true);
					continue;
				}

				float fTotal_Damage = 0.f;
				bool bCritical = false;

				// 여기서 공격 타입을 판단해서 SetState를 해준다
				switch (HInfo.eAttType)
				{
				case ATT_NORMAL:
					if (BOSS == DstList->m_eMonType)
					{
						// 플레이어의 크리티컬 확률에 따른 치명타 판정
						if (rand() % 100 < CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).back()->Get_CriRatio())
							bCritical = true;

						// 데미지 산정 공식
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
						// 플레이어의 크리티컬 확률에 따른 치명타 판정
						if (rand() % 100 < CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).back()->Get_CriRatio())
							bCritical = true;

						// 데미지 산정 공식
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
						// 플레이어의 크리티컬 확률에 따른 치명타 판정
						if (rand() % 100 < CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).back()->Get_CriRatio())
							bCritical = true;

						// 데미지 산정 공식
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

// (플레이어 광역공격Src - 몬스터Dst) 충돌
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

				// 여기서 공격 타입을 판단해서 SetState를 해준다
				switch (HInfo.eAttType)
				{
				case ATT_NORMAL:
					if (BOSS == DstList->m_eMonType)
					{
						// 플레이어의 크리티컬 확률에 따른 치명타 판정
						if (rand() % 100 < CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).back()->Get_CriRatio())
							bCritical = true;

						// 데미지 산정 공식
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
						// 플레이어의 크리티컬 확률에 따른 치명타 판정
						if (rand() % 100 < CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).back()->Get_CriRatio())
							bCritical = true;

						// 데미지 산정 공식
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
						// 플레이어의 크리티컬 확률에 따른 치명타 판정
						if (rand() % 100 < CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).back()->Get_CriRatio())
							bCritical = true;

						// 데미지 산정 공식
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

// (피격대상(Dst) - 공격대상(Src)) 공격 충돌 판정
bool CCollsionMgr::Check_AttackRect(CObj* pDst, CObj* pSrc, float* pX, float* pY)
{
	float		fWidth = abs(float(pDst->Get_RectCollisionCenter().x) - pSrc->Get_Info().fX);
	float		fHeight = abs(float(pDst->Get_RectCollisionCenter().y) - pSrc->Get_Info().fY);

	float		fCX = (pDst->Get_RectCollisionSizeX() * 0.5f) + (pSrc->Get_Info().fCX * 0.5f);
	float		fCY = (pDst->Get_RectCollisionSizeY() * 0.5f) + (pSrc->Get_Info().fCY * 0.5f);

	// 플레이어의 현재 프레임 기준 y좌표와
	// 몬스터 공격의 생성당시 y좌표를 비교하여 일정 범위 이하면 피격판정
	if ((fCX >= fWidth && fCY >= fHeight) && (abs(pDst->Get_TileCollision().bottom - pSrc->Get_CreatedBottom()) < 60.f))
	{
		*pX = fCX - fWidth;
		*pY = fCY - fHeight;

		return true;
	}

	return false;
}

// (피격대상(Dst) - 광역공격(Src)) 공격 충돌 판정
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

// 각성기용 전체 판정
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

// (플레이어 광역공격Src - 몬스터Dst) 충돌2
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

				// 여기서 공격 타입을 판단해서 SetState를 해준다
				switch (HInfo.eAttType)
				{
				case ATT_NORMAL:
					if (BOSS == DstList->m_eMonType)
					{
						// 플레이어의 크리티컬 확률에 따른 치명타 판정
						if (rand() % 100 < CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).back()->Get_CriRatio())
							bCritical = true;

						// 데미지 산정 공식
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
						// 플레이어의 크리티컬 확률에 따른 치명타 판정
						if (rand() % 100 < CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).back()->Get_CriRatio())
							bCritical = true;

						// 데미지 산정 공식
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
						// 플레이어의 크리티컬 확률에 따른 치명타 판정
						if (rand() % 100 < CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).back()->Get_CriRatio())
							bCritical = true;

						// 데미지 산정 공식
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

// 각성기용 전체 판정2
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

// (플레이어 - 타일)
void CCollsionMgr::Collision_RectExTile(list<CObj*> Dst, vector<CObj*> Src)
{
	float	fX = 0.f, fY = 0.f;

	for (auto& DstList : Dst)
	{
		for (auto& SrcVec : Src)
		{
			// 타일의 드로우옵션이 1이면 이동 불가능한 타일
			if (-1 == dynamic_cast<CTileNode*>(SrcVec)->Get_Option())
			{
				if (Check_TileRect(DstList, SrcVec, &fX, &fY))
				{
					// 상하 충돌
					if (fX > fY)
					{
							 // 상 충돌
						if (DstList->Get_TileCollisionCenter().y < SrcVec->Get_Info().fY)
						{
							DstList->Set_PosY(-fY);
						}
						else // 하 충돌
						{
							DstList->Set_PosY(fY);
						}
					}
					// 좌우 충돌
					else
					{
						if (DstList->Get_TileCollisionCenter().x < SrcVec->Get_Info().fX)
						{
							DstList->Set_PosX(-fX);
						}
						else // 우 충돌
						{
							DstList->Set_PosX(fX);
						}
					}

				}
			}
		}
	}
}

// (플레이어 - 타일) 충돌 판정
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

// 원 충돌
bool CCollsionMgr::Check_Sphere(CObj * pDst, CObj * pSrc)
{
	float		fWidth = fabs(pDst->Get_Info().fX - pSrc->Get_Info().fX);
	float		fHeight = fabs(pDst->Get_Info().fY - pSrc->Get_Info().fY);

	float		fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float		fRadius = (pDst->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;
	
	return fRadius >= fDiagonal;
}

// 원 충돌 판정
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