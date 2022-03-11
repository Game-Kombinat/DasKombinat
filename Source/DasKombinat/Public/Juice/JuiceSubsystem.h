// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JuiceProfile.h"
#include "RuntimeJuiceProfile.h"
#include "UObject/Object.h"
#include "JuiceSubsystem.generated.h"

USTRUCT()
struct FProfileOwnerRegister {
    GENERATED_BODY()

    UPROPERTY()
    TWeakObjectPtr<UObject> owner;
    
    UPROPERTY()
    TArray<class URuntimeJuiceProfile*> runtimeProfiles;

    URuntimeJuiceProfile* GetRuntimeProfileFor(UJuiceProfile* oProfile) {
        for (int i = 0; i < runtimeProfiles.Num(); ++i) {
            if (runtimeProfiles[i]->originalProfile == oProfile) {
                return runtimeProfiles[i];
            }
        }
        return nullptr;
    }
};
///
/// Subsystem for the juice maker.
/// Not sure yet that I want to keep it in the kombinat toolbox
/// as there is currently no way to decide whether a subsystem should be instantiated or not.
/// Meaning having it here, it will always be instantiated.
///
UCLASS()
class DASKOMBINAT_API UJuiceSubsystem : public UWorldSubsystem {
    GENERATED_BODY()
protected:
    UPROPERTY()
    TMap<FString, FProfileOwnerRegister> registeredProfiles;
    
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    URuntimeJuiceProfile* GetRuntimeProfile(UJuiceProfile* juiceProfile, UObject* owner);

    void ClearProfilesFor(const UObject* owner);
    void CheckForDeadRecords();

protected:
    URuntimeJuiceProfile* AddRuntimeProfile(UJuiceProfile* juiceProfile, UObject* owner);
};
