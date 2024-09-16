#pragma once
#include "State.h"
class CIsys_Attack1 :
    public CState
{
public:
    CIsys_Attack1();
    ~CIsys_Attack1();

public:
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Enter() override;
    virtual void Exit() override;

private:
    int     m_iAttackCount;
};

