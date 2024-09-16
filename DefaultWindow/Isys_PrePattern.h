#pragma once
#include "State.h"
class CIsys_PrePattern :
    public CState
{
public:
    CIsys_PrePattern();
    ~CIsys_PrePattern();

public:
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

