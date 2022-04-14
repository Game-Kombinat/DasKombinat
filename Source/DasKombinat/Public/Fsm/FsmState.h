// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FsmState.generated.h"

///
/// A state that can be run in a state machine.
///
UCLASS(Blueprintable, BlueprintType)
class DASKOMBINAT_API UFsmState : public UObject {
    GENERATED_BODY()
public:
    // The ID is given when setting up the states.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int id;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool shouldTick;

    UFUNCTION(BlueprintNativeEvent, meta=(WorldContext=inWorld))
    void Prepare(UWorld* inWorld);
    virtual void Prepare_Implementation(UWorld* inWorld);

    UFUNCTION(BlueprintNativeEvent)
    void Enter();
    // explicit virtual implementation as we use these when creating native states.
    virtual void Enter_Implementation();

    UFUNCTION(BlueprintNativeEvent)
    void Tick();
    // explicit virtual implementation as we use these when creating native states.
    virtual void Tick_Implementation();

    UFUNCTION(BlueprintNativeEvent)
    void Exit();
    // explicit virtual implementation as we use these when creating native states.
    virtual void Exit_Implementation();

    ///
    /// By default a state is not ticked. If you need the state to be ticked, mark shouldTick = true.
    ///
    bool NeedsTicking() const { return shouldTick; }

};
