#pragma once
#include "State.h"
class CIsys_Idle :
    public CState
{
public:
    CIsys_Idle();
    ~CIsys_Idle();

public:
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

