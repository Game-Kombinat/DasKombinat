// Fill out your copyright notice in the Description page of Project Settings.


#include "VectorTools.h"

float UVectorTools::CosineAngle(const FVector& normal, const FVector& facingThis) {
    return normal.GetSafeNormal().Dot((facingThis - normal).GetSafeNormal());
}

float UVectorTools::CosineAngleDirection(const FVector& normal, const FVector& direction) {
    return normal.GetSafeNormal().Dot(direction.GetSafeNormal());
}

bool UVectorTools::IsFacing(const FVector& normal, const FVector& facingThis, const float precision) {
    return CosineAngle(normal, facingThis) >= precision;
    
}

bool UVectorTools::IsFacingAngle(const FVector& normal, const FVector& facingThis, const float angle) {
    const float dot = CosineAngle(normal, facingThis);
    const float vectorAngle = FMath::RadiansToDegrees(FMath::Acos(dot));
    return vectorAngle <= angle;
}

bool UVectorTools::IsFacingAngleDirection(const FVector& normal, const FVector& direction, float angle) {
    const float dot = CosineAngleDirection(normal, direction);
    const float vectorAngle = FMath::RadiansToDegrees(FMath::Acos(dot));
    return vectorAngle <= angle;
}
