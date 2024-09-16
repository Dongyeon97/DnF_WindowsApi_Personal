#pragma once
#include "State.h"
class CIsys_Attack2 :
    public CState
{
public:
    CIsys_Attack2();
    ~CIsys_Attack2();

public:
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Enter() override;
    virtual void Exit() override;

    void Explosion(float _fX, float _fY);
};

