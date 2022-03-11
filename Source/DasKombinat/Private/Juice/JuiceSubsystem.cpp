// Fill out your copyright notice in the Description page of Project Settings.


#include "Juice/JuiceSubsystem.h"

#include "Logging.h"
#include "Juice/JuiceProfile.h"

void UJuiceSubsystem::Initialize(FSubsystemCollectionBase& Collection) {
    Super::Initialize(Collection);
    registeredProfiles.Reset();
}

void UJuiceSubsystem::Deinitialize() {
    Super::Deinitialize();
    for (auto lp : registeredProfiles) {
        for (auto p : lp.Value.runtimeProfiles) {
            p->DecommissionHandlers();
        } 
    }
    registeredProfiles.Reset();
}

UJuiceProfile* UJuiceSubsystem::RegisterProfile(UJuiceProfile* profile, UObject* owner) {
    const auto runtimeProfile = NewObject<UJuiceProfile>(GetTransientPackage(), UJuiceProfile::StaticClass(), NAME_None, RF_Transient, profile, false);
    if (!registeredProfiles.Contains(owner)) {
        registeredProfiles.Add(owner, FProfileOwnerRegister());
    }
    const auto klass = profile->GetClass();
    auto reg = registeredProfiles[owner];
    if (!reg.registeredProfileTypes.Contains(klass)) {
        runtimeProfile->InitHandlers(owner->GetWorld());
        runtimeProfile->MarkAsInstance();
        reg.registeredProfileTypes.Add(klass);
        reg.runtimeProfiles.Add(runtimeProfile);
        registeredProfiles[owner] = reg;
        return runtimeProfile;
    }
    

    return GetRuntimeProfile(profile, owner);
}

UJuiceProfile* UJuiceSubsystem::GetRuntimeProfile(const UJuiceProfile* profile, UObject* owner) {
    if (!registeredProfiles.Contains(owner)) {
        LOG_WARNING("owner %s not registered for %s", *owner->GetName(), *profile->GetName());
        return nullptr;
    }

    const auto klass = profile->GetClass();
    if (!registeredProfiles[owner].registeredProfileTypes.Contains(klass)) {
        LOG_WARNING("profile %s not registered for owner %s", *profile->GetName(), *owner->GetName());
        return nullptr;
    }

    return registeredProfiles[owner].GetRuntimeProfileFor(klass);
}
