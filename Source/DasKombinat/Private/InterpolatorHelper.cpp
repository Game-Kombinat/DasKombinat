// Copyright (c) Game Kombinat


#include "InterpolatorHelper.h"

#include "Interpolator.h"

UInterpolatorHelper* UInterpolatorHelper::Interpolate(UObject* worldContext, float duration) {
    const auto interp = NewObject<UInterpolatorHelper>();

    FAnim8Sample sample;
    sample.BindUFunction(interp, "OnInterpolatorTick");

    FAnim8Done done;
    done.BindUFunction(interp, "OnFinished");
    
    FInterpolator::Anim8(worldContext->GetWorld(), duration, true, sample, done);
    return interp;
}

void UInterpolatorHelper::OnFinished() {
    if (done.IsBound()) {
        done.Broadcast();
    }
}

void UInterpolatorHelper::OnInterpolatorTick(const float t) {
    if (tick.IsBound()) {
        tick.Broadcast(t);
    }
}
