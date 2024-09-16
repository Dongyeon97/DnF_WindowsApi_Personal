#pragma once
#include "State.h"
class CExp_Attack1 :
    public CState
{
public:
    CExp_Attack1();
    ~CExp_Attack1();

public:
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Enter() override;
    virtual void Exit() override;

private:
    int     m_iAttackCount;
};

