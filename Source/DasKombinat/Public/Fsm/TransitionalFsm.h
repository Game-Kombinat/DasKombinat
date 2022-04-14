// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FsmTransition.h"
#include "UObject/Object.h"
#include "TransitionalFsm.generated.h"

USTRUCT()
struct DASKOMBINAT_API FTransitionList {
    GENERATED_BODY()
    
    UPROPERTY()
    TArray<struct FFsmTransition> transitionList;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStateSwitched, class UFsmState*, newState);

UCLASS()
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
    
    bool ShouldBeTicked() const;
    
    void Prepare(UWorld* world);

    void CheckTransitions();

    void Tick() const;

    void AddState(int stateId, UFsmState* stateObj);

    template<typename T>
    void AddTransition(int from, int to, T* host, bool(T::*method)());

    void SetDefaultState(int state);

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