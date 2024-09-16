#pragma once
#include "State.h"
class CIsys_Razor :
    public CState
{
public:
    CIsys_Razor();
    ~CIsys_Razor();

public:
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

