// Fill out your copyright notice in the Description page of Project Settings.


#include "Fsm/TransitionalFsm.h"

#include "Fsm/FsmState.h"
#include "Fsm/FsmTransition.h"

TArray<FFsmTransition>UTransitionalFsm::emptyTransitionList = TArray<FFsmTransition>();

bool UTransitionalFsm::ShouldBeTicked() const {
    if (currentState) {
        return currentState->shouldTick;
    }
    return false;
}

void UTransitionalFsm::Prepare(UWorld* world) {
    for (const auto kvp : stateList) {
        kvp.Value->Prepare(world);
    }
    
    SetActiveState(GetState(defaultStateId));
}

void UTransitionalFsm::CheckTransitions() {
    FFsmTransition t;
    if (FindTransition(t)) {
        SetActiveState(t.to);
    }
}

void UTransitionalFsm::Tick() const {
    currentState->Tick();
}

void UTransitionalFsm::AddState(int stateId, UFsmState* stateObj) {
    stateObj->id = stateId;
    stateList.Add(stateId, stateObj);
}

void UTransitionalFsm::AddState(const int stateId, const TSubclassOf<UFsmState> stateClass) {
    AddState(stateId, NewObject<UFsmState>(this, stateClass.Get()));
}

void UTransitionalFsm::AddTransition(int from, int to, TFunction<bool()> test) {
    const auto transitionTargetState = GetState(to);
    const auto transitionSourceState = GetState(from);

    if (!transitionSourceState || !transitionTargetState) {
        LOG_ERROR("Transition invalid. Target (%i) or Source (%i) state are unknown - not adding it.", to, from)
        return;
    }

    const TSharedPtr<FTransitionCondition> transitionTest = MakeShared<FTransitionCondition>();
    transitionTest->RegisterCall(test);
    
    if (!transitions.Contains(from)) {
        transitions.Add(from, FTransitionList());
    }
    transitions[from].transitionList.AddUnique(FFsmTransition(transitionTargetState, transitionTest));
}

void UTransitionalFsm::AddTransitionViaBlueprint(int from, int to, FTransitionTest func) {
    const auto transitionTargetState = GetState(to);
    const auto transitionSourceState = GetState(from);
    
    if (!transitionSourceState || !transitionTargetState) {
        LOG_ERROR("Transition invalid. Target (%i) or Source (%i) state are unknown - not adding it.", to, from)
        return;
    }

    const TSharedPtr<FTransitionCondition> transitionTest = MakeShared<FTransitionCondition>();
    transitionTest->RegisterCall(func);
    
    if (!transitions.Contains(from)) {
        transitions.Add(from, FTransitionList());
    }
    transitions[from].transitionList.AddUnique(FFsmTransition(transitionTargetState, transitionTest));
}

void UTransitionalFsm::SetDefaultState(const int state) {
    defaultStateId = state;
}

void UTransitionalFsm::ConstructState_Implementation() {
}

UFsmState* UTransitionalFsm::GetState(int stateId) {
    if (stateList.Contains(stateId)) {
        return stateList[stateId];
    }
    return nullptr;
}

void UTransitionalFsm::SetActiveState(UFsmState* newState) {
    if (newState == currentState) {
        return;
    }
    if (currentState) {
        currentState->Exit();
    }
    
    currentState = newState;
    if (transitions.Contains(currentState->id)) {
        currentTransitions = transitions[currentState->id].transitionList;
    }
    else {
        currentTransitions = emptyTransitionList;
    }

    currentState->Enter();
    if (onStateSwitched.IsBound()) {
        onStateSwitched.Broadcast(currentState);
    }
}

bool UTransitionalFsm::FindTransition(FFsmTransition& outTransition) {
    for (int i = 0; i < currentTransitions.Num(); ++i) {
        auto transition = currentTransitions[i];
        if (transition.condition->Call()) {
            outTransition = transition;
            return true;
        }
    }

    return false;
}
