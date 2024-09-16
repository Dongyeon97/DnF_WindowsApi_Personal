#pragma once
#include "Obj.h"
#include "TimeMgr.h"

extern float g_fVolume;

class CPlayer :
	public CObj
{
public:
	enum PLAYERSTATE {	PS_IDLE,				// ���̵�
						PS_JUSTWALKUP,			// ���ڸ� ���� �ȱ�
						PS_JUSTWALKDOWN,		// ���ڸ� �Ʒ� �ȱ�
						PS_LWALK,				// ���� �ȱ�
						PS_LRUN,				// ���� �޸���
						PS_RWALK,				// ������ �ȱ�
						PS_RRUN,				// ������ �޸���
						PS_LSLIDE,				// ���� �����̵�
						PS_RSLIDE,				// ������ �����̵�
						PS_JUMP,				// ����
						PS_JUMPATTACK,			// ���� ����
						PS_ATTACK1,				// ��Ÿ1
						PS_ATTACK2,				// ��Ÿ2
						PS_ATTACK3,				// ��Ÿ3
						PS_ATTACK4,				// ��Ÿ4
						PS_ATTACK5,				// ��Ÿ5
						PS_DATTACK1,			// �Ʒ���Ÿ1
						PS_DATTACK2,			// �Ʒ���Ÿ2
						PS_DATTACK3,			// �Ʒ���Ÿ3
						PS_DATTACK4,			// �Ʒ���Ÿ4
						PS_DATTACK5,			// �Ʒ���Ÿ5
						PS_DBR,					// SPACE �������̸�����
						PS_ZACKS,				// Z �轺����ũ
						PS_GUNGUARD,			// E �ǰ���
						PS_WINDMILL,			// S �����
						PS_MAHA,				// D ����ű
						PS_HEADSHOT,			// A ��弦
						PS_MOVINGSHOT,			// R �̵����
						PS_SPREE,				// F ����
						PS_SATELITE,				// G ��Ʋ����Ʈ�� ����
						PS_AWAKEN,				// Y ������ ����
						PS_LAWAKENING,			// ���� ������ ������
						PS_RAWAKENING,			// ������ ������ ������
						PS_NORMAL_ATTACKED,		// �Ϲ� �ǰ�
						PS_THRUST_ATTACKED,		// ��ġ�� �ǰ�
						PS_LEVITATE_ATTACKED,	// �Ѿ����� �ǰ�
						PS_DEAD,				// ���
						PS_END };

public:
	CPlayer();
	virtual ~CPlayer();

public:
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void		Set_PlayerState(PLAYERSTATE _eState) { m_ePlayerState = _eState; }
	PLAYERSTATE	Get_PlayerState() { return m_ePlayerState; }

	void		Set_DBR(bool _b)	{ m_bDBR = _b; }
	bool		Get_DBR()			{ return m_bDBR; }

	void		Set_GunGuard(bool _b)	{ m_bGunGuard = _b; }
	bool		Get_GunGuard()			{ return m_bGunGuard; }
	
	void		DBR_Check();
	void		GunGuard_Check();

	// �̽ý� �׷α� ���� ����
	void		Set_GrogyBuff(double _dTime) { m_GrogyBuffTime = _dTime; m_bBuff = true; m_tInfo.fAtk += 500; }
	void		GrogyBuff_Check();

private:
	void	Key_Input(void);
	void	Moving(void);
	void	Offset(void);
	void	Motion_Change();
	void	Cool_Check();
	void	SkillCool_Making(float _fX, float _fY, float _fLifeTime,TCHAR* _pKey);

	void	Making_Shadow(TCHAR* _pKey, float _fLifeTime);	// �ܻ� ����
	void	Making_MovingShot();
	void	Making_Spree();
			// �Ű����� ���� : ������ġx,y / ���� x,yũ�� / ���� x,yũ�� / ���� key / ���� key / ���� Frame / ���� Frame
	void	Making_Awakening(float _fX, float _fY, float _fCX, float _fCY, float _fECX, float _fECY, TCHAR* _pKey, TCHAR* _pEKey
							, int _Start, int _End, float _FrameSpeed, float _LifeTime, int _EStart, int _EEnd, float _EFrameSpeed, float _ELifeTime);
	void	Making_AwakeningE(float _fX, float _fY, float _fECX, float _fECY, TCHAR* _pEKey
							, int _EStart, int _EEnd, float _EFrameSpeed, float _ELifeTime);
	void	DoSeventhL();
	void	DoSeventhR();

	virtual void		Update_Rect();
	virtual void		Move_Frame();

protected:
	float				m_fDistance;
	float				m_fJumpSpeed;
	float				m_fJumpTime;

	PLAYERSTATE			m_ePlayerPreState;	// ���� ����
	PLAYERSTATE			m_ePlayerState;		// ���� ����

	ULONGLONG			m_lInvenOpenTime;
	ULONGLONG			m_lShopOpenTime;

	// ����� �� �ڵ� �����
	// == Ű���� �Է� ==
	double				m_lWalkTime;		// �ȱ� �ð�

	double				m_fLRunReadyTime;	// ���� �޸��� �غ�ð�
	double				m_fRRunReadyTime;	// ������ �޸��� �غ�ð�

	double				m_lAtkFinalTime;	// �⺻ ���� ��Ÿ �����½ð�
	double				m_lAtkEndTime;		// �⺻ ���� ��

	double				m_lSlideTime;		// �����̵� �ð�

	double				m_lJumpEndTime;		// ���� �ð�
	double				m_lJumpAttackTime;	// ���� ���� �ð�

	// == ĳ���� ���� ==
	float				m_fSlideSpeed;			// �����̵� �ӵ�
	int					m_iJumpAttackCount;

	bool				m_bDBR;					// ���� ���� ������ On ����
	bool				m_bGunGuard;			// �ǰ��� On ����

	int					m_iNormalFinalCount;	// ��Ÿ ��Ÿ Ÿ�� Ƚ��
	int					m_iDNormalCount;		// �Ʒ���Ÿ ��Ÿ Ÿ�� Ƚ��
	int					m_iWindmillCount;		// ����� Ÿ�� Ƚ��
	int					m_iHeadShotCount;		// ��弦 Ÿ�� Ƚ��
	int					m_iMovingShotCount;		// �̵���� Ÿ�� Ƚ��
	int					m_iSpreeCount;			// ���� Ÿ�� Ƚ��

	int					m_iSateliteCount;			// ���� Ÿ�� Ƚ��
	int					m_iSeventhCount;		// ������ Ÿ�� Ƚ��

	double				m_HpCoolTime;		// Hp���� ��Ÿ��
	double				m_MpCoolTime;		// Hp���� ��Ÿ��

	double				m_DBRCool;			// ���� ���� ������ ��Ÿ��
	double				m_ZacksCool;		// �轺����ũ ��Ÿ��
	double				m_GunGuardCool;		// �ǰ��� ��Ÿ��
	double				m_WindmillCool;		// ����� ��Ÿ��
	double				m_MahaCool;			// ����ű ��Ÿ��
	double				m_HeadShotCool;		// ��弦 ��Ÿ��
	double				m_MovingShotCool;	// �̵���� ��Ÿ��
	double				m_SpreeCool;		// ���� ��Ÿ��

	double				m_SateliteCool;		// ��Ʋ����Ʈ�� ��Ÿ��(��ü�� �ϳ� ���� �ֱ������� ��Ʈ�ڽ� ����)
	double				m_AwakeningCool;	// ���콺�÷ο� ��Ÿ��

	// �̽ý� �׷α� ���� ����
	bool				m_bBuff;			// ������ ������ ����
};
