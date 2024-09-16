#pragma once
#include "UI.h"
class CUI_Info :
    public CUI
{
public:
	CUI_Info();
	virtual ~CUI_Info();

public:
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	void		Set_Render(bool _b) { m_bRender = _b; };
	bool		Get_Render() { return m_bRender; }

private:
	bool		m_bRender;

	POINT		m_Prept;			// �� ������ Ŭ����ġ
	bool		m_bClicked;			// Ŭ�� ����
};