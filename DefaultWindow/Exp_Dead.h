#pragma once
#include "State.h"
class CExp_Dead :
    public CState
{
public:
    CExp_Dead();
    ~CExp_Dead();

public:
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

