#pragma once
#include "State.h"
class CExp_Trace :
    public CState
{
public:
    CExp_Trace();
    ~CExp_Trace();

public:
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    void    MoveToPlayer();
};

