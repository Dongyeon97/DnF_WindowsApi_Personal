#pragma once
#include "Define.h"
class CTimeMgr
{
public:
	CTimeMgr();
	~CTimeMgr();
public:
	static CTimeMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CTimeMgr;

		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static CTimeMgr* m_pInstance;

private:
	LARGE_INTEGER		m_llCurCount;	// update할 때의 카운트
	LARGE_INTEGER		m_llPrevCount;	// init할 때의 카운트
	LARGE_INTEGER		m_llFrequency;	// 초당 카운트 횟수

	double				m_dDT;			// 1프레임당 시간값 Delta Time
	double				m_dAcc;			// 1초 체크를 위한 누적 시간값
	UINT				m_iCallCount;   // 함수 호출 횟수 체크(FPS의 계산을 위해서)
	UINT				m_iFPS;			// 1초당 호출 횟수

	// FPS

public:
	void Initialize();
	void Update(); // 매 프레임마다 호출됨
	void Render();

public:
	double GetDT()	{ return m_dDT; }
	double GetfDT() { return (float)m_dDT; }
};