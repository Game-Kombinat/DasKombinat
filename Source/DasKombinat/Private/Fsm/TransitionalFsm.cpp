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

void UTransitionalFsm::SetDefaultState(const int state) {
    defaultStateId = state;
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
