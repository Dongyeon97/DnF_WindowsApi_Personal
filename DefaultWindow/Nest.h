#pragma once
#include "Scene.h"

enum WEATHER
{
	LIGHT,		// ��	: 0
	DARK,		// ���	: 1
	END
};

class CNest :
    public CScene
{
public:
	CNest();
	virtual ~CNest();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;

	// ���� �������� ������
	WEATHER	Get_Weather() { return m_eWeather; }

	// �ٲ� ���������� ���� �ٸ������� �齺�� ����/�������
	void	Set_StoneImmune();

	// ���輱 �ٲٴ� Ű �Է� ó��
	void	Key_Input();
private:
	double		m_TabTime;
	WEATHER		m_eWeather;
};

