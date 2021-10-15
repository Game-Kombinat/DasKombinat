#include "Interpolator.h"

#include "Anim8Action.h"
#include "CoroutineManager.h"
#include "Kismet/KismetMathLibrary.h"

FInterpolator::FInterpolator(float duration, UWorld* world): startTime(0), stateA(0), stateB(0), currentValue(0),
                                                             timeOfPause(0) {
    duration01 = duration;
    duration10 = duration;
    this->world = world;
}

FInterpolator::FInterpolator(float forwardDuration, float backwardDuration, UWorld* world): startTime(0), stateA(0),
    stateB(0), currentValue(0), timeOfPause(0) {
    duration01 = forwardDuration;
    duration10 = backwardDuration;
    this->world = world;
}

void FInterpolator::Pause() {
    if (timeOfPause != 0 || !world) {
        return;
    }

    Sample();
    timeOfPause = world->GetTimeSeconds();
}

void FInterpolator::Resume() {
    if (timeOfPause == 0 || !world) {
        return;
    }
    startTime = world->GetTimeSeconds() - (timeOfPause - startTime);
    timeOfPause = 0;
}

void FInterpolator::StartFadeForward(bool reset) {
    StartFade(0, 1, reset);
}

void FInterpolator::StartFadeBackward(bool reset) {
    StartFade(1, 0, reset);
}

void FInterpolator::ForceForward() {
    Force(1);
}

void FInterpolator::ForceBackward() {
    Force(0);
}

float FInterpolator::Sample() {
    if (timeOfPause != 0 || !world) {
        return currentValue;
    }
    const float currentAlpha = (world->GetTimeSeconds() - startTime) / Duration();

    currentValue = FMath::Lerp(stateA, stateB, FMath::Clamp(currentAlpha, 0.0f, 1.0f));
    return currentValue;
}

float FInterpolator::SampleTime() const {
    if (!world) {
        return startTime;
    }
    return FMath::Clamp(world->GetTimeSeconds() - startTime, 0.0f, Duration());
}

void FInterpolator::Anim8(UWorld* world, float duration, bool playForward, FAnim8Sample onSample, FAnim8Done onFinish) {
    UCoroutineManager::Instance()->Add(new FAnim8Action(playForward, FInterpolator(duration, world), onSample, onFinish));
}

void FInterpolator::Force(float target) {
    if (!world) {
        return;
    }
    stateA = 1.0f - target;
    stateB = target;
    startTime = world->GetTimeSeconds() - duration01;
}

void FInterpolator::StartFade(float a, float b, bool reset) {
    if (!world) {
        return;
    }
    stateA = a;
    stateB = b;
    if (reset) {
        //Just start at A and go to B
        startTime = world->GetTimeSeconds();
    }
    else {
        float time = world->GetTimeSeconds();
        //If the interpolator gets interrupted in the middle of a fading, continue at the same position
        startTime = FMath::Lerp(time, time - Duration(),
                                UKismetMathLibrary::NormalizeToRange(currentValue, stateA, stateB));
    }
}
