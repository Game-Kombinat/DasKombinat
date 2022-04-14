// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FsmTransition.h"
#include "UObject/Object.h"
#include "TransitionalFsm.generated.h"

class UFsmState;

USTRUCT()
struct DASKOMBINAT_API FTransitionList {
    GENERATED_BODY()
    
    UPROPERTY()
    TArray<struct FFsmTransition> transitionList;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStateSwitched, UFsmState*, newState);

UCLASS(Blueprintable, BlueprintType)
class DASKOMBINAT_API UTransitionalFsm : public UObject {
    GENERATED_BODY()
protected:
    UPROPERTY()
    TMap<int, FTransitionList> transitions;
    UPROPERTY()
    TMap<int, class UFsmState*> stateList;
    UPROPERTY()
    TArray<FFsmTransition> currentTransitions;
    
    static TArray<FFsmTransition> emptyTransitionList;

    UPROPERTY()
    UFsmState* currentState;
    
    UPROPERTY()
    int defaultStateId;

public:
    UPROPERTY()
    FOnStateSwitched onStateSwitched;

    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool ShouldBeTicked() const;

    ///
    /// Call this after all the setup is done.
    /// Ideally somewhere in a BeginPlay callback.
    ///
    UFUNCTION(BlueprintCallable)
    void Prepare(UWorld* world);

    ///
    /// Call this whenever you believe that state transitions should be checked.
    /// Quick and dirty way is to call this in a Tick callback.
    /// But there are ways to avoid it.
    ///
    UFUNCTION(BlueprintCallable)
    void CheckTransitions();

    UFUNCTION(BlueprintCallable)
    void Tick() const;

    
    void AddState(int stateId, UFsmState* stateObj);

    UFUNCTION(BlueprintCallable)
    void AddState(int stateId, TSubclassOf<UFsmState> stateClass);

    template<typename T>
    void AddTransition(int from, int to, T* host, bool(T::*method)());

    UFUNCTION(BlueprintCallable, meta=(DisplayName="Add Transition"))
    void AddTransitionViaBlueprint(int from, int to, FTransitionTest func);

    UFUNCTION(BlueprintCallable)
    void SetDefaultState(int state);

    // convenience callback for blueprint FSMs so they have an entry point
    // to construct their state.
    // Can be used native as well for orderly state creation but
    UFUNCTION(BlueprintNativeEvent)
    void ConstructState();

protected:
    UFsmState* GetState(int stateId);

    void SetActiveState(UFsmState* newState);

    bool FindTransition(FFsmTransition& outTransition);
};

template <typename T>
void UTransitionalFsm::AddTransition(int from, int to, T* host, bool(T::* method)()) {
    const auto transitionTargetState = GetState(to);
    const auto transitionSourceState = GetState(from);
    
    if (!transitionSourceState || !transitionTargetState) {
        LOG_ERROR("Transition invalid. Target (%i) or Source (%i) state are unknown - not adding it.", to, from)
        return;
    }

    TSharedPtr<FTransitionCondition> func = MakeShared<FTransitionCondition>();
    func->RegisterCall(host, method);
    
    if (!transitions.Contains(from)) {
        transitions.Add(from, FTransitionList());
    }
    transitions[from].transitionList.AddUnique(FFsmTransition(transitionTargetState, func));
}