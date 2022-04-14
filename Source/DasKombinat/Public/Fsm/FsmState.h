// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FsmState.generated.h"

///
/// Implement this FsmState according to whatever logic it requires.
/// todo: make this thing blueprintable and turn virtuals into blueprint native events
/// so we can have states in blueprints. professional.
///
UCLASS(Abstract)
class DASKOMBINAT_API UFsmState : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY()
    int id;

    UPROPERTY()
    bool shouldTick;

    virtual void Prepare(UWorld* inWorld) PURE_VIRTUAL(return);

    virtual void Enter() PURE_VIRTUAL(return);

    ///
    /// Implement this only if your state requires ticking.
    /// See NeedsTicking() for details.
    ///
    virtual void Tick() {}

    virtual void Exit() PURE_VIRTUAL(return);


    ///
    /// By default a state is not ticked. If you need the state to be ticked, mark shouldTick = true.
    ///
    bool NeedsTicking() const { return shouldTick; }

};
