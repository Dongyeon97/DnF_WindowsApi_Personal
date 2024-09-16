#pragma once
#include "State.h"
class CIsys_ThrustAttacked :
    public CState
{
public:
    CIsys_ThrustAttacked();
    ~CIsys_ThrustAttacked();

public:
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Enter() override;
    virtual void Exit() override;

private:
    double  m_dwTime;
};