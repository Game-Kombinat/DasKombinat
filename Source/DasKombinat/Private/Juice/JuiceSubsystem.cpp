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
    if (!registeredProfiles.Contains(owner)) {
        return AddRuntimeProfile(juiceProfile, owner);
    }
    const auto rt = registeredProfiles[owner].GetRuntimeProfileFor(juiceProfile);
    if (!rt) {
        return AddRuntimeProfile(juiceProfile, owner);
    }
    return rt;
}

void UJuiceSubsystem::ClearProfilesFor(UObject* owner) {
    if (!registeredProfiles.Contains(owner)) {
        return;
    }

    for (auto rt : registeredProfiles[owner].runtimeProfiles) {
        rt->DeinitProfile();
    }

    registeredProfiles.Remove(owner);
}

URuntimeJuiceProfile* UJuiceSubsystem::AddRuntimeProfile(UJuiceProfile* juiceProfile, UObject* owner) {
    // check if we get any null pointers as keys first, those are objects that got deleted and didn't
    // mark their juice stuff for deletion.
    for (auto kvp : registeredProfiles) {
        if (!kvp.Key) {
            for (const auto rt : kvp.Value.runtimeProfiles) {
                rt->DeinitProfile();
            }
            kvp.Value.runtimeProfiles.Reset();
        }
    }
    
    if (!registeredProfiles.Contains(owner)) {
        registeredProfiles.Add(owner, FProfileOwnerRegister());
    }

    const auto newRt = NewObject<URuntimeJuiceProfile>(GetTransientPackage(), URuntimeJuiceProfile::StaticClass(), NAME_None, RF_Transient);
    newRt->InitProfile(juiceProfile, owner);
    registeredProfiles[owner].runtimeProfiles.Add(newRt);
    return newRt;
}
