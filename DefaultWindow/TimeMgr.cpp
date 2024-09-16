#include "stdafx.h"
#include "TimeMgr.h"

CTimeMgr* CTimeMgr::m_pInstance = nullptr;

CTimeMgr::CTimeMgr()
	: m_llCurCount{}
	, m_llPrevCount{}
	, m_llFrequency{}
	, m_dDT(0.f)
	, m_dAcc(0.f)
	, m_iCallCount(0)
	, m_iFPS(0)
{
}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::Initialize()
{
	QueryPerformanceCounter(&m_llPrevCount);		// init당시의 카운트를 받아와서 저장
	QueryPerformanceFrequency(&m_llFrequency);		// 초당 카운트 횟수를 받아와서 저장
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_llCurCount);			// update당시의 카운트를 받아와서 저장

	// 이전 프레임과 현재 프레임의 카운트 차이 값을 구한다. -> 1update에 해당되는 카운트 값이 나옴
	// 그 값을 초당 카운트 값인 Frequency로 나눈다.		-> 1update에 걸린 시간을 구할 수 있다.
	// m_dDT : 1 프레임당 걸린 시간값
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;

	// 이전 카운트 값을 현재 카운트 값으로 갱신(다음 프레임에서의 계산을 위해서)
	m_llPrevCount = m_llCurCount;
}

void CTimeMgr::Render()
{
	// update가 한번 돌 때마다 iCallCount 누적
	++m_iCallCount;

	m_dAcc += m_dDT; // 1초가 지났을 시점을 체크하기 위해 DT를 매 update마다 누적

	// 1초가 걸린 시점 : m_dAcc가 1을 넘었을 시점

	if (m_dAcc >= 1.)
	{
		m_iFPS = m_iCallCount;	// 1초가 지났을 때의 함수 호출 횟수를 FPS에 저장한다.
		m_dAcc = 0.;			// 다음번 1초를 위해 누적값 초기화
		m_iCallCount = 0;		// 다음번 1초를 위해 누적 횟수 초기화
	}
}
