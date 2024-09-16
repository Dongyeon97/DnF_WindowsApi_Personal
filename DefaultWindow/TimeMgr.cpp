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
	QueryPerformanceCounter(&m_llPrevCount);		// init����� ī��Ʈ�� �޾ƿͼ� ����
	QueryPerformanceFrequency(&m_llFrequency);		// �ʴ� ī��Ʈ Ƚ���� �޾ƿͼ� ����
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_llCurCount);			// update����� ī��Ʈ�� �޾ƿͼ� ����

	// ���� �����Ӱ� ���� �������� ī��Ʈ ���� ���� ���Ѵ�. -> 1update�� �ش�Ǵ� ī��Ʈ ���� ����
	// �� ���� �ʴ� ī��Ʈ ���� Frequency�� ������.		-> 1update�� �ɸ� �ð��� ���� �� �ִ�.
	// m_dDT : 1 �����Ӵ� �ɸ� �ð���
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;

	// ���� ī��Ʈ ���� ���� ī��Ʈ ������ ����(���� �����ӿ����� ����� ���ؼ�)
	m_llPrevCount = m_llCurCount;
}

void CTimeMgr::Render()
{
	// update�� �ѹ� �� ������ iCallCount ����
	++m_iCallCount;

	m_dAcc += m_dDT; // 1�ʰ� ������ ������ üũ�ϱ� ���� DT�� �� update���� ����

	// 1�ʰ� �ɸ� ���� : m_dAcc�� 1�� �Ѿ��� ����

	if (m_dAcc >= 1.)
	{
		m_iFPS = m_iCallCount;	// 1�ʰ� ������ ���� �Լ� ȣ�� Ƚ���� FPS�� �����Ѵ�.
		m_dAcc = 0.;			// ������ 1�ʸ� ���� ������ �ʱ�ȭ
		m_iCallCount = 0;		// ������ 1�ʸ� ���� ���� Ƚ�� �ʱ�ȭ
	}
}
