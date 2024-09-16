#pragma once
#include "State.h"
class CExp_NormalAttacked :
    public CState
{
public:
    CExp_NormalAttacked();
    ~CExp_NormalAttacked();

public:
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Enter() override;
    virtual void Exit() override;

private:
    double  m_dwTime;
};

