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
    /**
     * How much is transform fromHere looking in the direction to location toHere?
     */
    UFUNCTION(BlueprintCallable)
    static float FindHeading(const FTransform& fromHere, const FVector& toHere);

    /**
     * How much is actor from looking in the direction to actor to?
     */
    static float FindHeading(const AActor* from, const AActor* to);
 
    UFUNCTION(BlueprintCallable, meta=(DisplayName="Find Heading between Actors"))
    static float K2_FindHeadingWithActors(const AActor* from, const AActor* to);

    /**
     * Is the directional vector a facing in the direction of positional vector b?
     * This just takes a dot product of both vectors and checks the directionality.
     * Precision parameter defines "how much" we need to face at vector b to be facing it.
     */
    UFUNCTION(BlueprintCallable)
    static bool IsFacing(const FVector& normal, const FVector& fromHere, const FVector& facingThis,
                         float precision = .55f);

    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsFacingDirection(const FVector& direction, const FVector& targetDirection, float precision = .55f);

    /**
     * Is the directional vector a facing in the direction of positional vector b?
     * This takes a dot product of both vectors and checks the angle.
     * Precision parameter defines the max angle for the direction a to be considered facing at vector b.
     */
    UFUNCTION(BlueprintCallable)
    static bool IsFacingWithinAngle(const FVector& normal, const FVector& fromHere, const FVector& facingThis,
                                    float angle = 45.f);

    UFUNCTION(BlueprintCallable)
    static bool IsFacingDirectionWithinAngle(const FVector& normal, const FVector& direction, float angle = 45.f);
};
