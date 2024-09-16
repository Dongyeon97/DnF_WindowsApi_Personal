#pragma once

#include "Define.h"

// class CPlayer;

enum FORM_TYPE
{
	HUMAN,
	BEAST,
	COMPLEX,
	UNDEAD,
	DEVIL,

};

class CObj
{
public:
	CObj();
	virtual ~CObj();
public:
	// 오브젝트 기본정보
	void	Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	void	Set_Direction(DIRECTION eDir) { m_eDir = eDir; }
	void	Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void	Set_EndPos(float _fX, float _fY) { m_fEndPosX = _fX; m_fEndPosY = _fY; }
	void	Set_LifeTime(float _fLifeTime) { m_fLifeTime = _fLifeTime; }
	void	Set_PosX(float _fX) { m_tInfo.fX += _fX; }
	void	Set_PosY(float _fY) { m_tInfo.fY += _fY; }
	void	Set_ScaleX(float _fCX) { m_tInfo.fCX = _fCX; }
	void	Set_ScaleY(float _fCY) { m_tInfo.fCY = _fCY; }
	float	Get_ScaleX() { return m_tInfo.fCX; }
	float	Get_ScaleY() { return m_tInfo.fCY; }
	float	Get_Speed() { return m_fSpeed; }
	void	Set_Speed(float _fSpeed) { m_fSpeed = _fSpeed; }

	void	Set_Attack(float _fAtk) { m_tInfo.fAtk = _fAtk; }
	float	Get_Attack() { return m_tInfo.fAtk; }

	void	Plus_Attack(float _fAtk) { m_tInfo.fAtk += _fAtk; }
	void	Minus_Attack(float _fAtk) { m_tInfo.fAtk -= _fAtk; }

	void	Plus_MaxHp(float _fHp) { m_tInfo.fMaxHp += _fHp; }
	void	Minus_MaxHp(float _fHp) { m_tInfo.fMaxHp -= _fHp; }

	void	Set_Hp(float _fHp) { m_tInfo.fHp = _fHp; }
	float	Get_Hp() { return m_tInfo.fHp; }
	void	Set_Mp(float _fMp) { m_tInfo.fMp = _fMp; }
	float	Get_Mp() { return m_tInfo.fMp; }
	INFO	Get_Info() { return m_tInfo; }
	RECT	Get_Rect() { return m_tRect; }
	void	Set_Dead(bool _b) { m_bDead = _b; }
	bool	Get_Dead() { return m_bDead; }
	void	Set_Equip(bool _b) { m_bEquip = _b; }
	bool	Get_Equip() { return m_bEquip; }
	void	Set_UnEquip(bool _b) { m_bUnEquip = _b; }
	bool	Get_UnEquip() { return m_bUnEquip; }
	void	Set_Buy(bool _b) { m_bBuy = _b; }
	bool	Get_Buy() { return m_bBuy; }
	void	Set_Sell(bool _b) { m_bSell = _b; }
	bool	Get_Sell() { return m_bSell; }
	double	Get_dwTime() { return m_dwTime; }
	void	Set_dwTime(double _dwTime) { m_dwTime = _dwTime; }

protected:
	MON_STATE	m_ePreState;	// 이전 상태
	MON_STATE	m_eCurState;	// 현재 상태

public:
	// 오브젝트 충돌정보
	RECT	Get_RectCollision() { return m_tRectCollision; }
	POINT	Get_RectCollisionCenter() { return m_lRectCollisionCenter; }
	float	Get_RectCollisionSizeX() { return m_fCollisionSizeX; }
	float	Get_RectCollisionSizeY() { return m_fCollisionSizeY; }
	RECT	Get_TileCollision() { return m_tTileCollision; }
	POINT	Get_TileCollisionCenter() { return m_lTileCollisionCenter; }
	void	Set_RectCollisionX(float _fSizeX) { m_fCollisionSizeX = _fSizeX; }
	void	Set_RectCollisionY(float _fSizeY) { m_fCollisionSizeY = _fSizeY; }
	void	Set_CreatedBottom(float _fBottom) { m_fCreatedBottomPosY = _fBottom; }
	float	Get_CreatedBottom() { return m_fCreatedBottomPosY; }

	// 오브젝트 이미지정보
	void			Set_FrameKey(TCHAR *pFrameKey) { m_pFrameKey = pFrameKey; }
	TCHAR*			Get_FrameKey() { return m_pFrameKey; }
	void			Set_Frame(tagFrame _tFrame);
	tagFrame		Get_Frame() { return m_tFrame; }

	void			Set_RGB(RGB _tRGB) { m_tRGB = _tRGB; }
	tagColor		Get_RGB() { return m_tRGB; }

	void			Set_RenderID(RENDERID _eID) { m_eRender = _eID; }
	const RENDERID	Get_RenderID() { return m_eRender; }
	void			Set_AlphaValue(int _iValue) { m_iAlpha = _iValue; }

	void			Set_DrawOption(int _iIndex) { m_iOption = _iIndex; }
	int				Get_DrawOption()			{ return m_iOption; }

	void			Set_Name(const wstring _strName) { m_strName = _strName; }
	const wstring	Get_Name() { return m_strName; }

	void			Set_StopMotion(bool _b) { m_bStopMotion = _b; }

	// 오브젝트 공격/피격 정보
	void		Set_AttPoint(float _fAttPoint) { m_fAttPoint = _fAttPoint; }
	void		Set_AttRatio(float _fAttRatio) { m_fAttRatio = _fAttRatio; }
	void		Set_ThrustPower(float _fThrPower) { m_fThrustPower = _fThrPower; }
	void		Set_ThrustAccel(float _fThrAccel) { m_fThrustAccel = _fThrAccel; }
	void		Set_ThrustAngle(float _fThrustAngle) { m_fThrustAngle = _fThrustAngle; }
	void		Set_LevitatePower(float _fLeviPower) { m_fLevitatePower = _fLeviPower; }
	void		Set_LevitateAngle(float _fLeviAngle) { m_fLevitateAngle = _fLeviAngle; }
	void		Set_KnockbackTime(double _fKnockbackTime) { m_lKnockbackTime = _fKnockbackTime; }

	float		Get_AttPoint() { return m_fAttPoint; }
	float		Get_AttRatio() { return m_fAttRatio; }
	float		Get_ThrustPower() { return m_fThrustPower; }
	float		Get_ThrustAccel() { return m_fThrustAccel; }
	float		Get_LevitatePower() { return m_fLevitatePower; }
	float		Get_LevitateAngle() { return m_fLevitateAngle; }
	float		Get_KnockbackAngle() { return m_fThrustAngle; }
	double		Get_KnockbackTime() { return m_lKnockbackTime; }

	void		Set_IsHit(bool _bHit) { m_tHitInfo.bIsHit = _bHit; }
	bool		Get_IsHit() { return m_tHitInfo.bIsHit; }

	void		Set_IsImmune(bool _bImmune) { m_bImmune = _bImmune; }
	bool		Get_IsImmune() { return m_bImmune; }

	void		Set_KnockBack(bool _bKnockback) { m_bKnockback = _bKnockback; }
	bool		Get_KnockBack() { return m_bKnockback; }

	bool		Get_DeadType() { return m_bDeadType; }
	void		Set_DeadType(bool _bDeadType) { m_bDeadType = _bDeadType; }

	void			Take_Damage(float _fDamage);
	void			Take_Mana(float _fMana) { m_tInfo.fMp -= _fMana; }

	virtual void	OnKnockback(HIT_INFO _tHitInfo , float _fBottomPosY);
	ATT_TYPE		Get_AttackType() { return m_eAttType; }
	void			Set_AttackType(ATT_TYPE _eAttType) { m_eAttType = _eAttType; }

	void			Set_HitStartTime(DWORD _lHitStart) { m_lHitStartTime = _lHitStart; }
	DWORD			Get_HitStartTime() { return m_lHitStartTime; }

	void			Draw_HitEffect();
	
	void			Set_SpriteIndex(int _iIndex)	{ m_iSpriteIndex = _iIndex; }
	int				Get_SpriteIndex()				{ return m_iSpriteIndex; }

	int				Get_NumIndex(int _iNum, int _iIndex);
	void			Draw_Font(int _iDmg, bool _bCritical);
	void			Draw_HpBar(float _fHp, int _iLine, float _fDmg);
	void			Set_LifeNum(int _iLifeNum) { m_iLifeNum = _iLifeNum; }

	void			Set_DrawRatio(float _fRatio) { m_fDrawRatio = _fRatio; }
	void			Set_DrawLineCount(int _iCount) { m_iDrawLineCount = _iCount; }

	int				Get_DrawLineCount() { return m_iDrawLineCount; }
	int				Get_MaxDrawLineCount() { return m_iMaxDrawLineCount; }

	void			Set_ItemType(ITEM_TYPE _eID) { m_eItemType = _eID; }
	ITEM_TYPE		Get_ItemType() { return m_eItemType; }

	void			Set_Index(int _iIndex) { m_iInvenIndex = _iIndex; }
	int				Get_Index() { return m_iInvenIndex; }

	void			Set_CriRatio(float _fCriRatio) { m_fCriRatio = _fCriRatio; }
	float			Get_CriRatio() { return m_fCriRatio; }

public:
	virtual void	LifeTimeOver();

public:
	virtual void		Initialize()	PURE;
	virtual int			Update()		PURE;
	virtual void		Late_Update()	PURE;
	virtual void		Render(HDC hDC)	PURE;
	virtual void		Release()		PURE;

protected:
	virtual void		Update_Rect();
	virtual void		Move_Frame();

public:
	HIT_INFO	m_tHitInfo{};
	MON_TYPE	m_eMonType;
	double		m_TextTerm;	// 대사 텀

protected:
	ITEM_TYPE		m_eItemType;		// 오브젝트 타입정보
	INFO			m_tInfo;			// 오브젝트 기본정보
	wstring			m_strName;			// 오브젝트 이름
	RECT			m_tRect;			// 오브젝트 실제크기 Rect
	RGB				m_tRGB;				// GdiTrans로 제거할 색상값 구조체

	RECT		m_tRectCollision;		// 오브젝트 충돌판정 Rect
	POINT		m_lRectCollisionCenter;	// 충돌체의 중심
	float		m_fCollisionSizeX;		// 충돌체 X크기
	float		m_fCollisionSizeY;		// 충돌체 Y크기

	RECT		m_tTileCollision;		// 타일충돌용
	POINT		m_lTileCollisionCenter;	//
	float		m_fTileCollisionSizeX;	//
	float		m_fTileCollisionSizeY;	//

	float		m_fCreatedBottomPosY;// 생성 시점의 생성 주체의 bottom좌표

	FRAME		m_tFrame;				// 스프라이트 구현을 위한 프레임 구조체 
	int			m_iSpriteIndex;			// 데미지폰트의 스프라이트 인덱스
	float		m_fDrawRatio;			// HpBar에서 현재 줄에 얼마나 그릴것인지 비율
	int			m_iDrawLineCount;		// HpBar에 표시할 현재 줄 수
	int			m_iMaxDrawLineCount;	// HpBar에 표시할 최대 줄 수

	DIRECTION	m_eDir;				// 오브젝트가 바라보는 방향
	RENDERID	m_eRender;			// 렌더 순서 결정
	TCHAR*		m_pFrameKey;		// 스프라이트 키
	TCHAR*		m_pPortrait;		// 초상화 이미지 키
	bool		m_bStopMotion;		// 스프라이트를 멈추기 위한 불값

	int			m_iLifeNum;			// 체력 줄 수 표기용
	
	float		m_fPortraitX;		// 초상화 X크기
	float		m_fPortraitY;		// 초상화 Y크기

	int			m_iInvenIndex;		// 인벤토리상에서의 아이템의 인덱스

	int			m_iDrawID = 0;
	int			m_iOption = 0;
	int			m_iAlpha;

	// 공격의 데미지, 타입
	float		m_fAttPoint;		// 생성 주체로부터 받아올 공격력 값
	float		m_fAttRatio;		// 생성 주체로부터 받아올 공격력 계수 값
	float		m_fThrustPower;		// 밀치는 힘
	float		m_fThrustAccel;		// 밀치는 힘이 증가되거나 감소되기 위한 가속력
	float		m_fThrustAngle;		// 밀치는 각도
	double		m_lKnockbackTime;	// 밀치기 시간
	float		m_fLevitatePower;	// 띄우는 힘
	float		m_fLevitateAngle;	// 띄워질 각도

	DWORD		m_lHitStartTime;		// 피격하기 시작한 시간
	DWORD		m_lNormalAttackTime;	// 일반 피격모션 지속시간
	DWORD		m_lThrustAttackTime;	// 밀치는 피격모션 지속시간
	DWORD		m_lLevitateAttackTime;	// 띄우는 피격모션 지속시간

	bool		m_bDeadType;			// 공격 적중시 사라지는지 여부
	bool		m_bKnockback;			// 넉백 여부
	float		m_fCriRatio;			// 크리티컬 확률

	bool		m_bImmune;			// 오브젝트 무적 여부
	double		m_GrogyBuffTime;	// 보스 그로기버프 시간

	ATT_TYPE	m_eAttType;			// 오브젝트의 공격 타입
	float		m_fSpeed;
	float		m_fAngle;			// 이동 각도
	float		m_fEndPosX;			// 날아가다가 멈출 X좌표
	float		m_fEndPosY;			// 날아가다가 멈출 Y좌표
	float		m_fFallSpeed;		// 떨어지는 속도
	bool		m_bDead;
	bool		m_bEquip;
	bool		m_bBuy;
	bool		m_bSell;
	bool		m_bUnEquip;
	float		m_fLifeTime;		// 생명주기
	double		m_dwTime;			// 델타타임

	bool		m_bOpened;			// UI같은 것들이 이미 생성되었는지 체크하기 위한 변수

	friend class CCollisionMgr;
};

