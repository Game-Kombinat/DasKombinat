// Fill out your copyright notice in the Description page of Project Settings.


#include "VectorTools.h"

float UVectorTools::Dot(const FVector& normal, const FVector& direction) {
    return FVector::DotProduct(normal, direction);
}


bool UVectorTools::IsFacing(const FVector& normal, const FVector& fromHere, const FVector& facingThis, const float precision) {
    return Dot(normal, (facingThis - fromHere).GetSafeNormal()) >= precision;
    
}

bool UVectorTools::IsFacingDirection(const FVector& direction, const FVector& targetDirection, float precision) {
    return Dot(direction, targetDirection) >= precision;
}

bool UVectorTools::IsFacingWithinAngle(const FVector& normal, const FVector& fromHere, const FVector& facingThis, const float angle) {
    const float dot = Dot(normal, (facingThis - fromHere).GetSafeNormal());
    const float vectorAngle = FMath::RadiansToDegrees(FMath::Acos(dot));
    return vectorAngle <= angle;
}

bool UVectorTools::IsFacingDirectionWithinAngle(const FVector& normal, const FVector& direction, float angle) {
    const float dot = Dot(normal, direction);
    const float vectorAngle = FMath::RadiansToDegrees(FMath::Acos(dot));
    return vectorAngle <= angle;
}
