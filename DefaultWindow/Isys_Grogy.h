#pragma once
#include "State.h"
class CIsys_Grogy :
    public CState
{
public:
    CIsys_Grogy();
    ~CIsys_Grogy();

public:
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

