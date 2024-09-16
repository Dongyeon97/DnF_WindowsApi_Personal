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
	// ������Ʈ �⺻����
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
	MON_STATE	m_ePreState;	// ���� ����
	MON_STATE	m_eCurState;	// ���� ����

public:
	// ������Ʈ �浹����
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

	// ������Ʈ �̹�������
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

	// ������Ʈ ����/�ǰ� ����
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
	double		m_TextTerm;	// ��� ��

protected:
	ITEM_TYPE		m_eItemType;		// ������Ʈ Ÿ������
	INFO			m_tInfo;			// ������Ʈ �⺻����
	wstring			m_strName;			// ������Ʈ �̸�
	RECT			m_tRect;			// ������Ʈ ����ũ�� Rect
	RGB				m_tRGB;				// GdiTrans�� ������ ���� ����ü

	RECT		m_tRectCollision;		// ������Ʈ �浹���� Rect
	POINT		m_lRectCollisionCenter;	// �浹ü�� �߽�
	float		m_fCollisionSizeX;		// �浹ü Xũ��
	float		m_fCollisionSizeY;		// �浹ü Yũ��

	RECT		m_tTileCollision;		// Ÿ���浹��
	POINT		m_lTileCollisionCenter;	//
	float		m_fTileCollisionSizeX;	//
	float		m_fTileCollisionSizeY;	//

	float		m_fCreatedBottomPosY;// ���� ������ ���� ��ü�� bottom��ǥ

	FRAME		m_tFrame;				// ��������Ʈ ������ ���� ������ ����ü 
	int			m_iSpriteIndex;			// ��������Ʈ�� ��������Ʈ �ε���
	float		m_fDrawRatio;			// HpBar���� ���� �ٿ� �󸶳� �׸������� ����
	int			m_iDrawLineCount;		// HpBar�� ǥ���� ���� �� ��
	int			m_iMaxDrawLineCount;	// HpBar�� ǥ���� �ִ� �� ��

	DIRECTION	m_eDir;				// ������Ʈ�� �ٶ󺸴� ����
	RENDERID	m_eRender;			// ���� ���� ����
	TCHAR*		m_pFrameKey;		// ��������Ʈ Ű
	TCHAR*		m_pPortrait;		// �ʻ�ȭ �̹��� Ű
	bool		m_bStopMotion;		// ��������Ʈ�� ���߱� ���� �Ұ�

	int			m_iLifeNum;			// ü�� �� �� ǥ���
	
	float		m_fPortraitX;		// �ʻ�ȭ Xũ��
	float		m_fPortraitY;		// �ʻ�ȭ Yũ��

	int			m_iInvenIndex;		// �κ��丮�󿡼��� �������� �ε���

	int			m_iDrawID = 0;
	int			m_iOption = 0;
	int			m_iAlpha;

	// ������ ������, Ÿ��
	float		m_fAttPoint;		// ���� ��ü�κ��� �޾ƿ� ���ݷ� ��
	float		m_fAttRatio;		// ���� ��ü�κ��� �޾ƿ� ���ݷ� ��� ��
	float		m_fThrustPower;		// ��ġ�� ��
	float		m_fThrustAccel;		// ��ġ�� ���� �����ǰų� ���ҵǱ� ���� ���ӷ�
	float		m_fThrustAngle;		// ��ġ�� ����
	double		m_lKnockbackTime;	// ��ġ�� �ð�
	float		m_fLevitatePower;	// ���� ��
	float		m_fLevitateAngle;	// ����� ����

	DWORD		m_lHitStartTime;		// �ǰ��ϱ� ������ �ð�
	DWORD		m_lNormalAttackTime;	// �Ϲ� �ǰݸ�� ���ӽð�
	DWORD		m_lThrustAttackTime;	// ��ġ�� �ǰݸ�� ���ӽð�
	DWORD		m_lLevitateAttackTime;	// ���� �ǰݸ�� ���ӽð�

	bool		m_bDeadType;			// ���� ���߽� ��������� ����
	bool		m_bKnockback;			// �˹� ����
	float		m_fCriRatio;			// ũ��Ƽ�� Ȯ��

	bool		m_bImmune;			// ������Ʈ ���� ����
	double		m_GrogyBuffTime;	// ���� �׷α���� �ð�

	ATT_TYPE	m_eAttType;			// ������Ʈ�� ���� Ÿ��
	float		m_fSpeed;
	float		m_fAngle;			// �̵� ����
	float		m_fEndPosX;			// ���ư��ٰ� ���� X��ǥ
	float		m_fEndPosY;			// ���ư��ٰ� ���� Y��ǥ
	float		m_fFallSpeed;		// �������� �ӵ�
	bool		m_bDead;
	bool		m_bEquip;
	bool		m_bBuy;
	bool		m_bSell;
	bool		m_bUnEquip;
	float		m_fLifeTime;		// �����ֱ�
	double		m_dwTime;			// ��ŸŸ��

	bool		m_bOpened;			// UI���� �͵��� �̹� �����Ǿ����� üũ�ϱ� ���� ����

	friend class CCollisionMgr;
};

