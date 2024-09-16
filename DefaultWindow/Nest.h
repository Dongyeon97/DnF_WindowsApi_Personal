#pragma once
#include "Scene.h"

enum WEATHER
{
	LIGHT,		// 빛	: 0
	DARK,		// 어둠	: 1
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

	// 현재 날씨정보 얻어오기
	WEATHER	Get_Weather() { return m_eWeather; }

	// 바뀐 날씨정보에 따라 다른세계의 룬스톤 무적/렌더취소
	void	Set_StoneImmune();

	// 세계선 바꾸는 키 입력 처리
	void	Key_Input();
private:
	double		m_TabTime;
	WEATHER		m_eWeather;
};

