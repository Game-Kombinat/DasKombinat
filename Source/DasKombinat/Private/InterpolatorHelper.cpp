// Copyright (c) Game Kombinat


#include "InterpolatorHelper.h"

#include "Interpolator.h"

UInterpolatorHelper* UInterpolatorHelper::Interpolate(UObject* worldContext, float duration) {
    const auto interp = NewObject<UInterpolatorHelper>();
    FInterpolator::Anim8(worldContext->GetWorld(), duration, true, interp, &UInterpolatorHelper::OnInterpolatorTick, &UInterpolatorHelper::OnFinished);
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