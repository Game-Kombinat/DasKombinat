// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "JuiceHandler.generated.h"

struct FJuiceInfo;
/**
 * 
 */
UCLASS()
class DASKOMBINAT_API UJuiceHandler : public UDataAsset {
    GENERATED_BODY()
protected:
    UPROPERTY(Transient)
    bool isPrimed = false;
    UPROPERTY()
    UWorld* world;
    
public:

    virtual void Play(FJuiceInfo& fji) PURE_VIRTUAL(return);
    
    virtual void BeforePlay() PURE_VIRTUAL(return);

    void DecommissionHandler();

    void InitHandler(UWorld* inWorld);
    
protected:
    virtual void InternalDecommissionHandler() PURE_VIRTUAL(return);
    virtual void InternalInitHandler(UWorld* inWorld) PURE_VIRTUAL(return);

};
