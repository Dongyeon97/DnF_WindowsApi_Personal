#pragma once
#include "State.h"
class CIsys_Trace :
    public CState
{
public:
    CIsys_Trace();
    ~CIsys_Trace();

public:
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    void    MoveToPlayer();
};

