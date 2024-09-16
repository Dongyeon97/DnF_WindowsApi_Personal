#pragma once
#include "UI.h"
class CUI_Inven :
    public CUI
{
public:
	CUI_Inven();
	virtual ~CUI_Inven();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	void		Set_Render(bool _b) { m_bRender = _b; };
	bool		Get_Render() { return m_bRender; }

	void		Set_PickMode(bool _b)	{ m_bPickMode = _b; }
	bool		Get_PickMode()			{ return m_bPickMode; }

	void		Add_Item(int _iIndex,float _fAtk, float _fHp, wstring _strName, tagColor _tRGB, TCHAR* _pKey, ITEM_TYPE _eItemType);
	void		Set_ItemPos(CObj* _pItem, int _iIndex);

	static int		Find_InvenIndex();
	static void		Check_InvenIndex(int _bIndex) { m_bIndex[_bIndex] = !m_bIndex[_bIndex]; }

	static bool		Is_EquipIndex(ITEM_TYPE _eItemType);
	static void		Check_EquipIndex(ITEM_TYPE _eItemType) { m_bEquipIndex[_eItemType] = !m_bEquipIndex[_eItemType]; }

	friend class CItem;
	friend class CCollsionMgr;

private:
	static bool	m_bEquipIndex[12];	// 0 ~ 11 : 현재 장착중인 아이템
	static bool	m_bIndex[56];		// 0 ~ 55 : 인벤토리 아이템
	bool		m_bRender;

	POINT		m_Prept;			// 전 프레임 클릭위치
	bool		m_bClicked;			// 클릭 여부
	bool		m_bPickMode;
	// Index //
	// 0. 무기
	// 1. 칭호
	// 2. 어깨
	// 3. 상의
	// 4. 하의
	// 5. 허리
	// 6. 신발
	// 7. 팔찌
	// 8. 목걸이
	// 9. 반지
	// 10. 보조장비
	// 11. 마법석
};