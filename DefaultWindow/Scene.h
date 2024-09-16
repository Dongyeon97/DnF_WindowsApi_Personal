#pragma once

#include "Define.h"

class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual void		Initialize()	PURE;
	virtual int			Update()		PURE;
	virtual void		Late_Update()	PURE;
	virtual void		Render(HDC hDC)	PURE;
	virtual void		Release()		PURE;

	static void			Plus_Combo() { ++m_iComboCount; };
	static void			Reset_Combo() { m_iComboCount = 0; }

	void				Reset_Time() { m_dwTime = 0; }

	int		Get_ComboNumIndex(int _iNum, int _iIndex);
	void	Draw_ComboFont(int _iComboCount);

protected:
	double		m_dwTime;
	
	static int	m_iComboCount;
};

