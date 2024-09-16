#pragma once
#include "State.h"
class CIsys_Attacked :
    public CState
{
public:
    CIsys_Attacked();
    ~CIsys_Attacked();

public:
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Enter() override;
    virtual void Exit() override;

private:
    double  m_dwTime;
};

