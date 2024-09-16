#pragma once
#include "State.h"
class CIsys_Attack3 :
    public CState
{
public:
    CIsys_Attack3();
    ~CIsys_Attack3();

public:
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

