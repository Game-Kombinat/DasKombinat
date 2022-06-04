// Fill out your copyright notice in the Description page of Project Settings.


#include "Juice/JuiceProfile.h"

#include "Juice/JuiceSubsystem.h"

void UJuiceProfile::Play(FJuiceInfo& fji, UObject* owner) {
    owner->GetWorld()->GetSubsystem<UJuiceSubsystem>()->GetRuntimeProfile(this, owner)->Play(fji);
}

URuntimeJuiceProfile* UJuiceProfile::GetRuntimeProfile(UObject* owner) {
    return owner->GetWorld()->GetSubsystem<UJuiceSubsystem>()->GetRuntimeProfile(this, owner);
}

void UJuiceProfile::ClearProfilesFor(UObject* owner) {
    if (owner && owner->GetWorld()) {
        auto juiceSys = owner->GetWorld()->GetSubsystem<UJuiceSubsystem>();
        if (juiceSys) {
            juiceSys->ClearProfilesFor(owner);
        }
    }
}

