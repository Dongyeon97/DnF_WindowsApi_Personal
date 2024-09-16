#pragma once

#include "Obj.h"

template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory(){}
	~CAbstractFactory(){}

public:
	static CObj*	Create_Obj()
	{
		CObj*	pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj* Create_Obj(float _fX, float _fY)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);

		return pObj;
	}

	static CObj* Create_Obj(float _fX, float _fY, float _fCX, float _fCY, TCHAR* _cFrameKey)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_ScaleX(_fCX);
		pObj->Set_ScaleY(_fCY);
		pObj->Set_FrameKey(_cFrameKey);

		return pObj;
	}

	// HpBar 제작용
	static CObj* Create_Obj(float _fX, float _fY, int _iSpriteIndex, float _fDrawRatio, int _iLineCount, TCHAR* _pFrameKey)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_SpriteIndex(_iSpriteIndex);
		pObj->Set_DrawRatio(_fDrawRatio);
		pObj->Set_DrawLineCount(_iLineCount);
		pObj->Set_FrameKey(_pFrameKey);

		return pObj;
	}

	// 폰트 제작용
	static CObj* Create_Obj(float _fX, float _fY, float _fSpeed, float _fAngle, float _fLifeTime, int _iDmgIndex, TCHAR* _pFrameKey)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Speed(_fSpeed);
		pObj->Set_Angle(_fAngle);
		pObj->Set_LifeTime(_fLifeTime);
		pObj->Set_SpriteIndex(_iDmgIndex);
		pObj->Set_FrameKey(_pFrameKey);

		return pObj;
	}

	static CObj* Create_Obj(float _fX, float _fY, TCHAR* _pFrameKey)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_FrameKey(_pFrameKey);

		return pObj;
	}

	// 상점 아이템
	static CObj* Create_Obj(float _fX, float _fY, int _iAtk, int iHp, wstring _strName, TCHAR* _pFrameKey)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Attack(float(_iAtk));
		pObj->Set_Hp(float(iHp));
		pObj->Set_Name(_strName);
		pObj->Set_FrameKey(_pFrameKey);

		return pObj;
	}

	// 잔상
	static CObj* Create_Obj(ATT_TYPE _eAttType, float _fX, float _fY, float _fCX, float _fCY, float _fLifeTime, TCHAR* _pFrameKey)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_AttackType(_eAttType);
		pObj->Set_ScaleX(_fCX);
		pObj->Set_ScaleY(_fCY);
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_LifeTime(_fLifeTime);
		pObj->Set_FrameKey(_pFrameKey);

		return pObj;
	}

	// 스킬 아이콘
	static CObj* Create_Obj(float _fX, float _fY, float _fLifeTime,TCHAR* _pFrameKey)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_LifeTime(_fLifeTime);
		pObj->Set_FrameKey(_pFrameKey);

		return pObj;
	}

	// 몬스터 공격, 스킬 Rect제작용
	static CObj* Create_Obj(ATT_TYPE _eAttType, bool _bDeadType,float _fX, float _fY, float _fCX, float _fCY
	, float _fSpeed , float _fAngle, float _fEndX, float _fEndY,float _fLifeTime
	, float _fColSizeX, float _fColSizeY, float _fBottom, float _fAttPoint, float _fAttRatio, float _fThrustPower, float _fThrustAccel
	, float _fLevitatePower, float _fLevitateAngle, float _fKnockbackAngle, float _fKnockbackTime, TCHAR* _cFrameKey, RGB _tRGB)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_AttackType(_eAttType);	// 오브젝트 공격타입
		pObj->Set_DeadType(_bDeadType);		// 오브젝트가 충돌시 사라지는지 여부
		pObj->Set_Pos(_fX, _fY);			// 오브젝트가 위치할 좌표
		pObj->Set_ScaleX(_fCX);				// 실제 오브젝트 크기값(이미지 파일과 일치시켜야 함)
		pObj->Set_ScaleY(_fCY);
		pObj->Set_Speed(_fSpeed);			// 오브젝트 발사 속도
		pObj->Set_Angle(_fAngle);			// 오브젝트가 발사될 각도
		pObj->Set_EndPos(_fEndX, _fEndY);	// 발사되다가 멈출 x,y 좌표
		pObj->Set_LifeTime(_fLifeTime);		// 오브젝트 생명주기
		pObj->Set_RectCollisionX(_fColSizeX);	// 오브젝트 충돌체 x크기
		pObj->Set_RectCollisionY(_fColSizeY);	// 오브젝트 충돌체 y크기
		pObj->Set_CreatedBottom(_fBottom);	// 오브젝트 생성시점의 생성주체의 bottom값

		pObj->Set_AttPoint(_fAttPoint);					// 피격박스를 생성한 주체의 공격력(m_tInfo.Att)
		pObj->Set_AttRatio(_fAttRatio);					// 피격박스객체(스킬)의 공격력 계수
		pObj->Set_ThrustPower(_fThrustPower);			// 밀치는 힘
		pObj->Set_ThrustAccel(_fThrustAccel);			// 밀치는 힘이 줄어들거나 늘어날 가속도
		pObj->Set_LevitatePower(_fLevitatePower);		// 띄우는 힘
		pObj->Set_LevitateAngle(_fLevitateAngle);		// 띄우는 각도
		pObj->Set_ThrustAngle(_fKnockbackAngle);		// 밀쳐질 각도
		pObj->Set_KnockbackTime(_fKnockbackTime);		// 넉백이 지속되면서 증가될 시간

		pObj->Set_FrameKey(_cFrameKey);					// 오브젝트 프레임 키
		pObj->Set_RGB(_tRGB);

		return pObj;
	}

	// 총알
	static CObj* Create_Obj(float _fX, float _fY, float _fCX, float _fCY, float _fAngle, float _fLifeTime, TCHAR* _cFrameKey)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_ScaleX(_fCX);
		pObj->Set_ScaleY(_fCY);
		pObj->Set_Angle(_fAngle);
		pObj->Set_LifeTime(_fLifeTime);
		pObj->Set_FrameKey(_cFrameKey);

		return pObj;
	}

	// 초상화
	static CObj* Create_Obj(float _fX, float _fY, float _fCX, float _fCY, TCHAR* _cFrameKey, tagColor _tRGB)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_ScaleX(_fCX);
		pObj->Set_ScaleY(_fCY);
		pObj->Set_RGB(_tRGB);
		pObj->Set_FrameKey(_cFrameKey);

		return pObj;
	}

	// 몬스터 체력줄
	static CObj* Create_Obj(float _fX, float _fY, float _fLifeNum, int _iFontIndex)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_LifeNum(_fLifeNum);
		pObj->Set_SpriteIndex(_iFontIndex);

		return pObj;
	}
};

