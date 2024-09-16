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

	// HpBar ���ۿ�
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

	// ��Ʈ ���ۿ�
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

	// ���� ������
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

	// �ܻ�
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

	// ��ų ������
	static CObj* Create_Obj(float _fX, float _fY, float _fLifeTime,TCHAR* _pFrameKey)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_LifeTime(_fLifeTime);
		pObj->Set_FrameKey(_pFrameKey);

		return pObj;
	}

	// ���� ����, ��ų Rect���ۿ�
	static CObj* Create_Obj(ATT_TYPE _eAttType, bool _bDeadType,float _fX, float _fY, float _fCX, float _fCY
	, float _fSpeed , float _fAngle, float _fEndX, float _fEndY,float _fLifeTime
	, float _fColSizeX, float _fColSizeY, float _fBottom, float _fAttPoint, float _fAttRatio, float _fThrustPower, float _fThrustAccel
	, float _fLevitatePower, float _fLevitateAngle, float _fKnockbackAngle, float _fKnockbackTime, TCHAR* _cFrameKey, RGB _tRGB)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_AttackType(_eAttType);	// ������Ʈ ����Ÿ��
		pObj->Set_DeadType(_bDeadType);		// ������Ʈ�� �浹�� ��������� ����
		pObj->Set_Pos(_fX, _fY);			// ������Ʈ�� ��ġ�� ��ǥ
		pObj->Set_ScaleX(_fCX);				// ���� ������Ʈ ũ�Ⱚ(�̹��� ���ϰ� ��ġ���Ѿ� ��)
		pObj->Set_ScaleY(_fCY);
		pObj->Set_Speed(_fSpeed);			// ������Ʈ �߻� �ӵ�
		pObj->Set_Angle(_fAngle);			// ������Ʈ�� �߻�� ����
		pObj->Set_EndPos(_fEndX, _fEndY);	// �߻�Ǵٰ� ���� x,y ��ǥ
		pObj->Set_LifeTime(_fLifeTime);		// ������Ʈ �����ֱ�
		pObj->Set_RectCollisionX(_fColSizeX);	// ������Ʈ �浹ü xũ��
		pObj->Set_RectCollisionY(_fColSizeY);	// ������Ʈ �浹ü yũ��
		pObj->Set_CreatedBottom(_fBottom);	// ������Ʈ ���������� ������ü�� bottom��

		pObj->Set_AttPoint(_fAttPoint);					// �ǰݹڽ��� ������ ��ü�� ���ݷ�(m_tInfo.Att)
		pObj->Set_AttRatio(_fAttRatio);					// �ǰݹڽ���ü(��ų)�� ���ݷ� ���
		pObj->Set_ThrustPower(_fThrustPower);			// ��ġ�� ��
		pObj->Set_ThrustAccel(_fThrustAccel);			// ��ġ�� ���� �پ��ų� �þ ���ӵ�
		pObj->Set_LevitatePower(_fLevitatePower);		// ���� ��
		pObj->Set_LevitateAngle(_fLevitateAngle);		// ���� ����
		pObj->Set_ThrustAngle(_fKnockbackAngle);		// ������ ����
		pObj->Set_KnockbackTime(_fKnockbackTime);		// �˹��� ���ӵǸ鼭 ������ �ð�

		pObj->Set_FrameKey(_cFrameKey);					// ������Ʈ ������ Ű
		pObj->Set_RGB(_tRGB);

		return pObj;
	}

	// �Ѿ�
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

	// �ʻ�ȭ
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

	// ���� ü����
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

