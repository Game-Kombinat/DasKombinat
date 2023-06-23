// Copyright (c) Game Kombinat

#pragma once

#include "CoreMinimal.h"
#include "Coroutine.h"

DECLARE_DELEGATE_OneParam(FAnim8Sample, float)
DECLARE_DELEGATE(FAnim8Done)

/**
 * 
 */
class DASKOMBINAT_API FAnim8Action : public FCoroutine {
private:
    FAnim8Sample onSample;
    FAnim8Done onFinish;
    bool directionIsForward;
    bool forceDone;
    TSharedPtr<class FInterpolator> interpolator;
public:
    FAnim8Action();
    FAnim8Action(bool directionIsForward, TSharedPtr<class FInterpolator> interpolator, FAnim8Sample onSample, FAnim8Done onFinish);
    virtual void PreTick() override;
    virtual ~FAnim8Action() override;
    virtual void Tick() override;
    virtual bool IsDone() override;
    virtual void ForceEnd() override;
};
