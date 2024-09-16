#pragma once
#include "State.h"
class CIsys_Pattern3 :
    public CState
{
public:
    CIsys_Pattern3();
    ~CIsys_Pattern3();

public:
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Enter() override;
    virtual void Exit() override;

    void    Making_RuneStone(float _fX, float _fY, int _iSpriteIndex, int _iOption, OBJ_ID _eType, TCHAR* _pKey);
    void    Making_Thunder(float _fX, float _fY, float _fLifeTime);
private:
    int     m_iSuccessCount;    // 패턴 성공 횟수
    bool    m_IsSuccess;        // 패턴 성공여부
};

