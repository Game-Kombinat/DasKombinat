// Fill out your copyright notice in the Description page of Project Settings.


#include "Juice/JuiceSubsystem.h"

#include "Juice/JuiceProfile.h"

void UJuiceSubsystem::Initialize(FSubsystemCollectionBase& Collection) {
    Super::Initialize(Collection);
}

void UJuiceSubsystem::Deinitialize() {
    Super::Deinitialize();
}

void UJuiceSubsystem::ProcessProfile(UJuiceProfile* profile) {
    FString profileName;
    profile->GetName(profileName);
    if (loadedProfiles.Contains(profileName)) {
        return;
    }
    profile->InitHandlers(GetWorld());
    loadedProfiles.Add(profileName, profile);
}
