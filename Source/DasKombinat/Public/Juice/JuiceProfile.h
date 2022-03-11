// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HandlerPlayData.h"
#include "JuiceProfile.generated.h"


class URuntimeJuiceProfile;
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
public:
    TArray<FHandlerPlayData>& GetHandlers() { return handlers; }

    
    ///
    /// Convenience method to play this profile.
    /// If you are rapidly calling play, it's better to get the runtime
    /// profile and cache it on your call site to save you a whole bunch of lookups.
    ///
    void Play(FJuiceInfo& fji, UObject* owner);
    
    ///
    /// Gets a runtime profile for this juice profile asset
    /// that is bound to the given owner and its world.
    /// If you need to call this juice profile a lot, it's better to
    /// get this runtime profile.
    ///
    URuntimeJuiceProfile* GetRuntimeProfile(UObject* owner);

    
    ///
    /// Clears all registered profiles for the given owner.
    /// Call this before owner is destroyed to clean up.
    ///
    static void ClearProfilesFor(UObject* owner);
};
