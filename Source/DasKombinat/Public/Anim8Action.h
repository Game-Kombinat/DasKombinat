// Copyright (c) Game Kombinat

#pragma once

#include "CoreMinimal.h"
#include "Coroutine.h"
#include "Interpolator.h"

/**
 * 
 */
class DASKOMBINAT_API FAnim8Action : public FCoroutine {
private:
    FAnim8Sample onSample;
    FAnim8Done onFinish;
    bool directionIsForward;
    FInterpolator interpolator;
public:
    FAnim8Action(bool directionIsForward, FInterpolator interpolator, FAnim8Sample onSample, FAnim8Done onFinish);
    virtual void PreTick() override;
    virtual ~FAnim8Action() override;
    virtual bool Tick() override;
};
