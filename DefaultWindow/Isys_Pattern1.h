#pragma once
#include "State.h"
class CIsys_Pattern1 :
    public CState
{
public:
    CIsys_Pattern1();
    ~CIsys_Pattern1();

public:
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Enter() override;
    virtual void Exit() override;
    
    void    DropFeather(float _fX, float _fY, float _fEndY);
    void    DropGuideFeather();
};

