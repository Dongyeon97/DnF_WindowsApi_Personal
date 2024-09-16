#pragma once
#include "UI.h"
class CUI_Inven :
    public CUI
{
public:
	CUI_Inven();
	virtual ~CUI_Inven();

public:
	// CObj��(��) ���� ��ӵ�
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
	static bool	m_bEquipIndex[12];	// 0 ~ 11 : ���� �������� ������
	static bool	m_bIndex[56];		// 0 ~ 55 : �κ��丮 ������
	bool		m_bRender;

	POINT		m_Prept;			// �� ������ Ŭ����ġ
	bool		m_bClicked;			// Ŭ�� ����
	bool		m_bPickMode;
	// Index //
	// 0. ����
	// 1. Īȣ
	// 2. ���
	// 3. ����
	// 4. ����
	// 5. �㸮
	// 6. �Ź�
	// 7. ����
	// 8. �����
	// 9. ����
	// 10. �������
	// 11. ������
};