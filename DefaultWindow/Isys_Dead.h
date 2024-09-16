#pragma once
#include "State.h"
class CIsys_Dead :
    public CState
{
public:
    CIsys_Dead();
    ~CIsys_Dead();

public:
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Enter() override;
    virtual void Exit() override;

};

