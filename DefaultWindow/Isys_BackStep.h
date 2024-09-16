#pragma once
#include "State.h"
class CIsys_BackStep :
    public CState
{
public:
    CIsys_BackStep();
    ~CIsys_BackStep();

public:
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

