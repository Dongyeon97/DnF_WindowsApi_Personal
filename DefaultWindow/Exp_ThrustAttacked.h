#pragma once
#include "State.h"
class CExp_ThrustAttacked :
    public CState
{
public:
    CExp_ThrustAttacked();
    ~CExp_ThrustAttacked();

public:
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Enter() override;
    virtual void Exit() override;

private:
    double  m_dwTime;
};

