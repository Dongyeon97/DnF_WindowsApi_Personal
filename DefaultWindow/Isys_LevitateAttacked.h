#pragma once
#include "State.h"
class CIsys_LevitateAttacked :
    public CState
{
public:
    CIsys_LevitateAttacked();
    ~CIsys_LevitateAttacked();

public:
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Enter() override;
    virtual void Exit() override;

private:
    double  m_dwTime;
};

