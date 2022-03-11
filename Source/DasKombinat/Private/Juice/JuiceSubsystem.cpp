// Fill out your copyright notice in the Description page of Project Settings.


#include "Juice/JuiceSubsystem.h"

void UJuiceSubsystem::Initialize(FSubsystemCollectionBase& Collection) {
    Super::Initialize(Collection);
    registeredProfiles.Reset();
}

void UJuiceSubsystem::Deinitialize() {
    Super::Deinitialize();
    for (auto kvp : registeredProfiles) {
        for (const auto rt : kvp.Value.runtimeProfiles) {
            rt->DeinitProfile();
        }
    }
}

URuntimeJuiceProfile* UJuiceSubsystem::GetRuntimeProfile(UJuiceProfile* juiceProfile, UObject* owner) {
    // This could be called periodically to ensure we got no instantiated profiles without a valid owner.
    // Calling it here everytime is a really really bad idea so I don't and expect that you will call ClearProfilesFor()
    // When you use profiles on your things.
    // CheckForDeadRecords();
    
    const FString ownerName = owner->GetFullName();
    if (!registeredProfiles.Contains(ownerName)) {
        return AddRuntimeProfile(juiceProfile, owner);
    }
    const auto rt = registeredProfiles[ownerName].GetRuntimeProfileFor(juiceProfile);
    if (!rt) {
        return AddRuntimeProfile(juiceProfile, owner);
    }
    return rt;
}

void UJuiceSubsystem::ClearProfilesFor(const UObject* owner) {
    const FString ownerName = owner->GetFullName();
    if (!registeredProfiles.Contains(ownerName)) {
        return;
    }

    for (const auto rt : registeredProfiles[ownerName].runtimeProfiles) {
        rt->DeinitProfile();
    }

    registeredProfiles.Remove(ownerName);
}

void UJuiceSubsystem::CheckForDeadRecords() {
    TArray<FString> forDeletion;
    for (auto kvp : registeredProfiles) {
        if (!kvp.Value.owner.IsValid()) {
            for (const auto rt : kvp.Value.runtimeProfiles) {
                rt->DeinitProfile();
            }
            kvp.Value.runtimeProfiles.Reset();
            forDeletion.Add(kvp.Key);
        }
    }

    for (auto dp : forDeletion) {
        registeredProfiles.Remove(dp);
    }
}

URuntimeJuiceProfile* UJuiceSubsystem::AddRuntimeProfile(UJuiceProfile* juiceProfile, UObject* owner) {

    const FString ownerName = owner->GetFullName();
    if (!registeredProfiles.Contains(ownerName)) {
        FProfileOwnerRegister r;
        r.owner = owner;
        registeredProfiles.Add(ownerName, r);
    }

    const auto newRt = NewObject<URuntimeJuiceProfile>(GetTransientPackage(), URuntimeJuiceProfile::StaticClass(), NAME_None, RF_Transient);
    newRt->InitProfile(juiceProfile, owner);
    registeredProfiles[ownerName].runtimeProfiles.Add(newRt);
    return newRt;
}
