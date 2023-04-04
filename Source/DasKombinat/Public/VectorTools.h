// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "VectorTools.generated.h"

/**
 * 
 */
UCLASS()
class DASKOMBINAT_API UVectorTools : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable)
    static float Dot(const FVector& normal, const FVector& facingThis);

    /**
     * Is the directional vector a facing in the direction of positional vector b?
     * This just takes a dot product of both vectors and checks the directionality.
     * Precision parameter defines "how much" we need to face at vector b to be facing it.
     */
    UFUNCTION(BlueprintCallable)
    static bool IsFacing(const FVector& normal, const FVector& fromHere, const FVector& facingThis, float precision = .55f);

    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsFacingDirection(const FVector& direction, const FVector& targetDirection, float precision = .55f);

    /**
     * Is the directional vector a facing in the direction of positional vector b?
     * This takes a dot product of both vectors and checks the angle.
     * Precision parameter defines the max angle for the direction a to be considered facing at vector b.
     */
    UFUNCTION(BlueprintCallable)
    static bool IsFacingWithinAngle(const FVector& normal, const FVector& fromHere, const FVector& facingThis, float angle = 45.f);

    UFUNCTION(BlueprintCallable)
    static bool IsFacingDirectionWithinAngle(const FVector& normal, const FVector& direction, float angle = 45.f);
};
