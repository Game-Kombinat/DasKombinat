// Fill out your copyright notice in the Description page of Project Settings.


#include "VectorTools.h"

float UVectorTools::CosineAngle(const FVector& a, const FVector& b) {
    return a.GetSafeNormal().Dot((b - a).GetSafeNormal());
}

float UVectorTools::CosineAngleDirection(const FVector& a, const FVector& direction) {
    return a.GetSafeNormal().Dot(direction.GetSafeNormal());
}

bool UVectorTools::IsFacing(const FVector& a, const FVector& b, const float precision) {
    return CosineAngle(a, b) >= precision;
    
}

bool UVectorTools::IsFacingAngle(const FVector& a, const FVector& b, const float angle) {
    const float dot = CosineAngle(a, b);
    const float vectorAngle = FMath::RadiansToDegrees(FMath::Acos(dot));
    return vectorAngle <= angle;
}

bool UVectorTools::IsFacingAngleDirection(const FVector& a, const FVector& direction, float angle) {
    const float dot = CosineAngleDirection(a, direction);
    const float vectorAngle = FMath::RadiansToDegrees(FMath::Acos(dot));
    return vectorAngle <= angle;
}
