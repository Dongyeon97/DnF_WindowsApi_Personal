#pragma once
#include "UI.h"
class CUI_Store :
    public CUI
{
public:
	CUI_Store();
	virtual ~CUI_Store();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	void		Set_PickMode(bool _b) { m_bPickMode = _b; }
	bool		Get_PickMode() { return m_bPickMode; }

	void		Set_Render(bool _b) { m_bRender = _b; };
	bool		Get_Render() { return m_bRender; }

private:
	bool m_bRender;

	POINT		m_Prept;			// 전 프레임 클릭위치
	bool		m_bClicked;			// 클릭 여부
	bool		m_bPickMode;
};