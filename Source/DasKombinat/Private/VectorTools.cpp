// Fill out your copyright notice in the Description page of Project Settings.


#include "VectorTools.h"

float UVectorTools::CosineAngle(const FVector& normal, const FVector& direction) {
    return FVector::DotProduct(normal, direction);
}


bool UVectorTools::IsFacing(const FVector& normal, const FVector& fromHere, const FVector& facingThis, const float precision) {
    return CosineAngle(normal, (facingThis - fromHere).GetSafeNormal()) >= precision;
    
}

bool UVectorTools::IsFacingAngle(const FVector& normal, const FVector& fromHere, const FVector& facingThis, const float angle) {
    const float dot = CosineAngle(normal, (facingThis - fromHere).GetSafeNormal());
    const float vectorAngle = FMath::RadiansToDegrees(FMath::Acos(dot));
    return vectorAngle <= angle;
}

bool UVectorTools::IsFacingAngleDirection(const FVector& normal, const FVector& direction, float angle) {
    const float dot = CosineAngle(normal, direction);
    const float vectorAngle = FMath::RadiansToDegrees(FMath::Acos(dot));
    return vectorAngle <= angle;
}
