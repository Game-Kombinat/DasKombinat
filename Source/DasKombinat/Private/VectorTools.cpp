// Fill out your copyright notice in the Description page of Project Settings.


#include "VectorTools.h"


float UVectorTools::FindHeading(const FTransform& fromHere, const FVector& toHere) {
    return FVector::DotProduct(fromHere.Rotator().Vector(), (toHere - fromHere.GetLocation()).GetSafeNormal());
}

float UVectorTools::FindHeading(const AActor* from, const AActor* to) {
    return FindHeading(from->GetTransform(), to->GetActorLocation());
}

float UVectorTools::K2_FindHeadingWithActors(const AActor* from, const AActor* to) {
    return FindHeading(from, to);
}

bool UVectorTools::IsFacing(const FVector& normal, const FVector& fromHere, const FVector& facingThis, const float precision) {
    return FVector::DotProduct(normal, (facingThis - fromHere).GetSafeNormal()) >= precision;
    
}

bool UVectorTools::IsFacingDirection(const FVector& direction, const FVector& targetDirection, float precision) {
    return FVector::DotProduct(direction, targetDirection) >= precision;
}

bool UVectorTools::IsFacingWithinAngle(const FVector& normal, const FVector& fromHere, const FVector& facingThis, const float angle) {
    const float dot = FVector::DotProduct(normal, (facingThis - fromHere).GetSafeNormal());
    const float vectorAngle = FMath::RadiansToDegrees(FMath::Acos(dot));
    return vectorAngle <= angle;
}

bool UVectorTools::IsFacingDirectionWithinAngle(const FVector& normal, const FVector& direction, float angle) {
    const float dot = FVector::DotProduct(normal, direction);
    const float vectorAngle = FMath::RadiansToDegrees(FMath::Acos(dot));
    return vectorAngle <= angle;
}
