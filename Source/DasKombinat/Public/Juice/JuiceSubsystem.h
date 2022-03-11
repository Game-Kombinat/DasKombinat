// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JuiceProfile.h"
#include "UObject/Object.h"
#include "JuiceSubsystem.generated.h"

USTRUCT()
struct FProfileOwnerRegister {
    GENERATED_BODY()
    UPROPERTY()
    UObject* owner = nullptr;

    UPROPERTY()
    TArray<class UJuiceProfile*> runtimeProfiles;

    UPROPERTY()
    TArray<class UClass*> registeredProfileTypes;

    UJuiceProfile* GetRuntimeProfileFor(UClass* klass) {
        for (int i = 0; i < runtimeProfiles.Num(); ++i) {
            if (runtimeProfiles[i]->GetClass() == klass) {
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
    TMap<UObject*, FProfileOwnerRegister> registeredProfiles;
    
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    
    UJuiceProfile* RegisterProfile(UJuiceProfile* profile, UObject* owner);
    UJuiceProfile* GetRuntimeProfile(const UJuiceProfile* profile, UObject* owner);
};
