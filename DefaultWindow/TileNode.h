#pragma once
#include "Obj.h"

// Obj�� �پ��� �Լ� Ȱ���� ���� Ÿ���� CObjŬ������ ��ӹ޴´�
class CTileNode : public CObj
{
public:
	CTileNode();
	virtual ~CTileNode();

public:
	void		Set_DrawID(int _iDrawID) { m_iDrawID = _iDrawID; }
	void		Set_Option(int _iOption) { m_iOption = _iOption; }
	void		Set_Option2()			 { m_iOption = ~m_iOption; }

	int			Get_DrawID() { return m_iDrawID; }
	int			Get_Option() { return m_iOption; }

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;
};

