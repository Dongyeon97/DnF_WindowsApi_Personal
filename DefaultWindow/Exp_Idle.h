#pragma once
#include "State.h"
class CExp_Idle :
    public CState
{
public:
    CExp_Idle();
    ~CExp_Idle();

public:
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

