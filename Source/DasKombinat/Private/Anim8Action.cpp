﻿// Copyright (c) Game Kombinat


#include "Anim8Action.h"

FAnim8Action::FAnim8Action(bool directionIsForward, FInterpolator interpolator, FAnim8Sample onSample, FAnim8Done onFinish) {
    this->directionIsForward = directionIsForward;
    this->onSample = onSample;
    this->onFinish = onFinish;
    this->interpolator = interpolator;
}

void FAnim8Action::PreTick() {
    if (directionIsForward) {
        interpolator.StartFadeForward(true);
    }
    else {
        interpolator.StartFadeBackward(true);
    }
}

FAnim8Action::~FAnim8Action() {
}

bool FAnim8Action::Tick() {
    onSample.ExecuteIfBound(interpolator.Sample());
    if (interpolator.IsDone() && onFinish.IsBound()) {
        
        onFinish.Execute();
    }
    return interpolator.IsDone();
}