// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Saveable.h"
#include "GameFramework/Actor.h"
#include "KombinatActor.generated.h"

///
/// This is a base actor that simply provides some convenience and
/// opinionated functionality.
/// 
/// Contains some save game relevant stubs by which it becomes easy
/// to facilitate save games.
///
UCLASS()
class DASKOMBINAT_API AKombinatActor : public AActor {
    GENERATED_BODY()
protected:
    /** Flag that stores ticking state when activation was toggled. Saveable */
    UPROPERTY(SaveGame)
    bool wasTickingWhenDeactivated;

    /** Flag that determines if this actor is active or not. Saveable */
    UPROPERTY(EditAnywhere, SaveGame)
    bool isActive;
    
public:
    AKombinatActor();
    virtual void OnConstruction(const FTransform& Transform) override;
    
    UFUNCTION(BlueprintCallable)
    void SetActive(bool activate);

    
    
};
