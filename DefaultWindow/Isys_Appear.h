#pragma once
#include "State.h"
class CIsys_Appear :
    public CState
{
public:
    CIsys_Appear();
    ~CIsys_Appear();

public:
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

