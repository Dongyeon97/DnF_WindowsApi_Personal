#pragma once
#include "State.h"
class CExp_LevitateAttacked :
    public CState
{
public:
    CExp_LevitateAttacked();
    ~CExp_LevitateAttacked();

public:
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Enter() override;
    virtual void Exit() override;

private:
    double  m_dwTime;
};

