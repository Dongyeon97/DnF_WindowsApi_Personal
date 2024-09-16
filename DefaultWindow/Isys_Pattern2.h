#pragma once
#include "State.h"
class CIsys_Pattern2 :
    public CState
{
public:
    CIsys_Pattern2();
    ~CIsys_Pattern2();

public:
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Enter() override;
    virtual void Exit() override;

private:
    void    Making_vortex(float _fX, float _fY, float _fSpeed, float _fAngle, float _fLifeTime);
    void    Making_Thunder(float _fX, float _fY, float _fLifeTime);
};

