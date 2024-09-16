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
	LARGE_INTEGER		m_llCurCount;	// update�� ���� ī��Ʈ
	LARGE_INTEGER		m_llPrevCount;	// init�� ���� ī��Ʈ
	LARGE_INTEGER		m_llFrequency;	// �ʴ� ī��Ʈ Ƚ��

	double				m_dDT;			// 1�����Ӵ� �ð��� Delta Time
	double				m_dAcc;			// 1�� üũ�� ���� ���� �ð���
	UINT				m_iCallCount;   // �Լ� ȣ�� Ƚ�� üũ(FPS�� ����� ���ؼ�)
	UINT				m_iFPS;			// 1�ʴ� ȣ�� Ƚ��

	// FPS

public:
	void Initialize();
	void Update(); // �� �����Ӹ��� ȣ���
	void Render();

public:
	double GetDT()	{ return m_dDT; }
	double GetfDT() { return (float)m_dDT; }
};