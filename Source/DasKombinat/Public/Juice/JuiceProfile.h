// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "JuiceProfile.generated.h"

USTRUCT()
struct DASKOMBINAT_API FHandlerPlayData {
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    class UJuiceHandler* handler;

    UPROPERTY(EditAnywhere)
    float delay;

    UPROPERTY()
    FTimerHandle timerHandle;
};

USTRUCT(BlueprintType)
struct DASKOMBINAT_API FJuiceInfo {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite)
    FVector location;
    
    UPROPERTY(BlueprintReadWrite)
    FVector orientation;
    
    UPROPERTY(BlueprintReadWrite)
    FLinearColor color;
};

///
/// juice profile. it's a databasset because I'm lazy and don't want to
/// make editor code to instantiate then under a special category.
///
UCLASS()
class DASKOMBINAT_API UJuiceProfile : public UDataAsset {
    GENERATED_BODY()
protected:
    UPROPERTY(EditAnywhere)
    TArray<FHandlerPlayData> handlers;

    UPROPERTY()
    UWorld* world;
    
public:
    void InitHandlers(UWorld* inWorld);

    void DecommissionHandlers();

    void Play(FJuiceInfo& fji);

};
