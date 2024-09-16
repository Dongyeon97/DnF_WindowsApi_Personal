#pragma once
#include "Obj.h"
#include "TimeMgr.h"

extern float g_fVolume;

class CPlayer :
	public CObj
{
public:
	enum PLAYERSTATE {	PS_IDLE,				// 아이들
						PS_JUSTWALKUP,			// 제자리 위로 걷기
						PS_JUSTWALKDOWN,		// 제자리 아래 걷기
						PS_LWALK,				// 왼쪽 걷기
						PS_LRUN,				// 왼쪽 달리기
						PS_RWALK,				// 오른쪽 걷기
						PS_RRUN,				// 오른쪽 달리기
						PS_LSLIDE,				// 왼쪽 슬라이딩
						PS_RSLIDE,				// 오른쪽 슬라이딩
						PS_JUMP,				// 점프
						PS_JUMPATTACK,			// 점프 공격
						PS_ATTACK1,				// 평타1
						PS_ATTACK2,				// 평타2
						PS_ATTACK3,				// 평타3
						PS_ATTACK4,				// 평타4
						PS_ATTACK5,				// 평타5
						PS_DATTACK1,			// 아래평타1
						PS_DATTACK2,			// 아래평타2
						PS_DATTACK3,			// 아래평타3
						PS_DATTACK4,			// 아래평타4
						PS_DATTACK5,			// 아래평타5
						PS_DBR,					// SPACE 데스바이리볼버
						PS_ZACKS,				// Z 잭스파이크
						PS_GUNGUARD,			// E 건가드
						PS_WINDMILL,			// S 윈드밀
						PS_MAHA,				// D 마하킥
						PS_HEADSHOT,			// A 헤드샷
						PS_MOVINGSHOT,			// R 이동사격
						PS_SPREE,				// F 난사
						PS_SATELITE,				// G 세틀라이트빔 시전
						PS_AWAKEN,				// Y 각성기 시작
						PS_LAWAKENING,			// 왼쪽 각성기 시전중
						PS_RAWAKENING,			// 오른쪽 각성기 시전중
						PS_NORMAL_ATTACKED,		// 일반 피격
						PS_THRUST_ATTACKED,		// 밀치는 피격
						PS_LEVITATE_ATTACKED,	// 넘어지는 피격
						PS_DEAD,				// 사망
						PS_END };

public:
	CPlayer();
	virtual ~CPlayer();

public:
	// CObj을(를) 통해 상속됨
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

	// 이시스 그로기 버프 관련
	void		Set_GrogyBuff(double _dTime) { m_GrogyBuffTime = _dTime; m_bBuff = true; m_tInfo.fAtk += 500; }
	void		GrogyBuff_Check();

private:
	void	Key_Input(void);
	void	Moving(void);
	void	Offset(void);
	void	Motion_Change();
	void	Cool_Check();
	void	SkillCool_Making(float _fX, float _fY, float _fLifeTime,TCHAR* _pKey);

	void	Making_Shadow(TCHAR* _pKey, float _fLifeTime);	// 잔상 생성
	void	Making_MovingShot();
	void	Making_Spree();
			// 매개변수 순서 : 생성위치x,y / 포격 x,y크기 / 깃털 x,y크기 / 포격 key / 깃털 key / 포격 Frame / 깃털 Frame
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

	PLAYERSTATE			m_ePlayerPreState;	// 이전 상태
	PLAYERSTATE			m_ePlayerState;		// 현재 상태

	ULONGLONG			m_lInvenOpenTime;
	ULONGLONG			m_lShopOpenTime;

	// ↓↓↓↓ 내 코드 ↓↓↓↓
	// == 키보드 입력 ==
	double				m_lWalkTime;		// 걷기 시간

	double				m_fLRunReadyTime;	// 왼쪽 달리기 준비시간
	double				m_fRRunReadyTime;	// 오른쪽 달리기 준비시간

	double				m_lAtkFinalTime;	// 기본 공격 막타 끝나는시간
	double				m_lAtkEndTime;		// 기본 공격 텀

	double				m_lSlideTime;		// 슬라이딩 시간

	double				m_lJumpEndTime;		// 점프 시간
	double				m_lJumpAttackTime;	// 점프 공격 시간

	// == 캐릭터 동작 ==
	float				m_fSlideSpeed;			// 슬라이딩 속도
	int					m_iJumpAttackCount;

	bool				m_bDBR;					// 데스 바이 리볼버 On 여부
	bool				m_bGunGuard;			// 건가드 On 여부

	int					m_iNormalFinalCount;	// 평타 막타 타격 횟수
	int					m_iDNormalCount;		// 아래평타 막타 타격 횟수
	int					m_iWindmillCount;		// 윈드밀 타격 횟수
	int					m_iHeadShotCount;		// 헤드샷 타격 횟수
	int					m_iMovingShotCount;		// 이동사격 타격 횟수
	int					m_iSpreeCount;			// 난사 타격 횟수

	int					m_iSateliteCount;			// 난사 타격 횟수
	int					m_iSeventhCount;		// 각성기 타격 횟수

	double				m_HpCoolTime;		// Hp물약 쿨타임
	double				m_MpCoolTime;		// Hp물약 쿨타임

	double				m_DBRCool;			// 데스 바이 리볼버 쿨타임
	double				m_ZacksCool;		// 잭스파이크 쿨타임
	double				m_GunGuardCool;		// 건가드 쿨타임
	double				m_WindmillCool;		// 윈드밀 쿨타임
	double				m_MahaCool;			// 마하킥 쿨타임
	double				m_HeadShotCool;		// 헤드샷 쿨타임
	double				m_MovingShotCool;	// 이동사격 쿨타임
	double				m_SpreeCool;		// 난사 쿨타임

	double				m_SateliteCool;		// 세틀라이트빔 쿨타임(객체를 하나 만들어서 주기적으로 히트박스 생성)
	double				m_AwakeningCool;	// 세븐스플로우 쿨타임

	// 이시스 그로기 버프 관련
	bool				m_bBuff;			// 버프가 들어온지 여부
};
