#pragma once
#include "Monster.h"
class CIsys :
    public CMonster
{
public:
	CIsys();
	virtual ~CIsys();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	virtual void OnKnockback(HIT_INFO _tHitInfo, float _fBottomPosY);

	void	Set_Pattern1(bool _bIsUsed) { m_bPattern1 = _bIsUsed; }
	void	Set_Pattern2(bool _bIsUsed) { m_bPattern2 = _bIsUsed; }
	void	Set_Pattern3(bool _bIsUsed) { m_bPattern3 = _bIsUsed; }
	void	Set_Pattern4(bool _bIsUsed) { m_bPattern4 = _bIsUsed; }

	bool	Get_Pattern1() { return m_bPattern1; }
	bool	Get_Pattern2() { return m_bPattern2; }
	bool	Get_Pattern3() { return m_bPattern3; }
	bool	Get_Pattern4() { return m_bPattern4; }

public:
	void	Motion_Change();
	void	Update_Rect();

private:
	bool	m_IsDead;		// ������ ���� ����

	bool	m_bPattern1;	// 1�� ����ȭ�� ����ߴ��� ����
	bool	m_bPattern2;	// 2�� ����ȭ�� ����ߴ��� ����
	bool	m_bPattern3;	// 3�� ����ȭ�� ����ߴ��� ����
	bool	m_bPattern4;	// 4�� ����ȭ�� ����ߴ��� ����
};

