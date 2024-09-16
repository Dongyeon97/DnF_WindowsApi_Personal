#pragma once
#include "State.h"
class CIsys_P3_Fail :
    public CState
{
public:
    CIsys_P3_Fail();
    ~CIsys_P3_Fail();

public:
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Enter() override;
    virtual void Exit() override;

    void    Making_Thunder(float _fX, float _fY, float _fLifeTime);
};

