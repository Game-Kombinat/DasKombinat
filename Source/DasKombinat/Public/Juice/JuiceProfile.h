// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "JuiceProfile.generated.h"

USTRUCT()
struct DASKOMBINAT_API FHandlerPlayData {
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    class UJuiceHandler* handler = nullptr;

    UPROPERTY(EditAnywhere)
    float delay = 0;

    UPROPERTY()
    FTimerHandle timerHandle;
};

USTRUCT(BlueprintType)
struct DASKOMBINAT_API FJuiceInfo {
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FVector location = FVector::ZeroVector;

    UPROPERTY(BlueprintReadWrite)
    FVector orientation = FVector::ZeroVector;

    UPROPERTY(BlueprintReadWrite)
    FLinearColor color = FLinearColor::Transparent;

    // optional an actor to attach to. handlers may or may not use this where appropriate
    UPROPERTY(BlueprintReadWrite)
    AActor* attachment = nullptr;

    // optional socket on attachment actor. handlers may or may not use this where appropriate
    UPROPERTY(BlueprintReadWrite)
    FName attachmentSocket;
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
    TArray<FHandlerPlayData> runtimeHandlers;

    UPROPERTY(Transient)
    UWorld* world;

    UPROPERTY(Transient)
    class UJuiceSubsystem* juiceSubsystem;

    UPROPERTY(Transient)
    bool isInstance;

public:
    void InitHandlers(UWorld* inWorld);

    bool IsInstance() const { return isInstance; }

    UJuiceProfile* RegisterFor(UObject* owner);

    void DecommissionHandlers();

    void Play(FJuiceInfo& fji, UObject* owner) const;
    void MarkAsInstance();

};
