// Copyright (c) Game Kombinat


#include "Anim8Action.h"

#include "Interpolator.h"

FAnim8Action::FAnim8Action(): directionIsForward(true), forceDone(false), interpolator(MakeShareable(new FInterpolator())) {
}

FAnim8Action::FAnim8Action(bool directionIsForward, TSharedPtr<FInterpolator> interpolator, FAnim8Sample onSample, FAnim8Done onFinish) {
    this->directionIsForward = directionIsForward;
    this->onSample = onSample;
    this->onFinish = onFinish;
    this->interpolator = interpolator;
    forceDone = false;
}

void FAnim8Action::PreTick() {
    if (directionIsForward) {
        interpolator->StartFadeForward(true);
    }
    else {
        interpolator->StartFadeBackward(true);
    }
}

FAnim8Action::~FAnim8Action() {
}

void FAnim8Action::Tick() {
    onSample.ExecuteIfBound(interpolator->Sample());
    if (interpolator->IsDone() && onFinish.IsBound()) {
        
        onFinish.Execute();
    }
}

bool FAnim8Action::IsDone() {
    return interpolator->IsDone() || forceDone;
}

void FAnim8Action::ForceEnd() {
    forceDone = true;
    // if (directionIsForward) {
    //     interpolator.ForceForward();
    // }
    // else {
    //     interpolator.ForceBackward();
    // }
}
