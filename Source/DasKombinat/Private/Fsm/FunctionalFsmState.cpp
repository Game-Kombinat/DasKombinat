// Fill out your copyright notice in the Description page of Project Settings.


#include "Fsm/FunctionalFsmState.h"

void UFunctionalFsmState::MarkTickable() {
    shouldTick = true;
}

void UFunctionalFsmState::Prepare_Implementation(UWorld* inWorld) {
    // does not need any further preparation.
}

void UFunctionalFsmState::Enter_Implementation() {
    if (enterFunc.IsValid()) {
        enterFunc->Call();
    }
}

void UFunctionalFsmState::Tick_Implementation() {
    if (tickFunc.IsValid()) {
        tickFunc->Call();
    }
}

void UFunctionalFsmState::Exit_Implementation() {
    if (exitFunc.IsValid()) {
        exitFunc->Call();
    }
}
