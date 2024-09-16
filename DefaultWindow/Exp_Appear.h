#pragma once
#include "State.h"
class CExp_Appear :
    public CState
{
public:
    CExp_Appear();
    ~CExp_Appear();

public:
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

