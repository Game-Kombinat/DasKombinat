// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JuiceProfile.h"
#include "UObject/Object.h"
#include "RuntimeJuiceProfile.generated.h"

///
/// This whole thing is a runtime initialised version of a juice profile.
/// This is necessary because we can't reliably have runtime data on
/// the profile asset instances themselves. If nothing else it breaks in PIE.
///
UCLASS()
class DASKOMBINAT_API URuntimeJuiceProfile : public UObject {
    GENERATED_BODY()
protected:
    UPROPERTY(Transient)
    TArray<FHandlerPlayData> runtimeHandlers;
    
    UPROPERTY(Transient)
    UWorld* world;

public:
    UPROPERTY(Transient)
    UJuiceProfile* originalProfile;

public:
    void InitProfile(UJuiceProfile* inOriginalProfile, UObject* inOwner);

    void DeinitProfile();

    void Play(FJuiceInfo& fji);

};
