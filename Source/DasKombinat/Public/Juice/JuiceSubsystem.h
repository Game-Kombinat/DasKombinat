// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "JuiceSubsystem.generated.h"

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
    TMap<FString, class UJuiceProfile*> loadedProfiles;
    
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    
    void ProcessProfile(UJuiceProfile* profile);
};
