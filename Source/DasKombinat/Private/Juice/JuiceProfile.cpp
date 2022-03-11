// Fill out your copyright notice in the Description page of Project Settings.


#include "Juice/JuiceProfile.h"

#include "Logging.h"
#include "Juice/JuiceHandler.h"
#include "Juice/JuiceSubsystem.h"

void UJuiceProfile::InitHandlers(UWorld* inWorld) {
    // this is called on a runtime copy of the profile data asset and therefore
    // needs the world set again in order to function properly.
    
    world = inWorld;
    runtimeHandlers.Reset(handlers.Num());
    for (int i = 0; i < handlers.Num(); ++i) {
        const auto newHandler = NewObject<UJuiceHandler>(this, handlers[i].handler->GetClass(), NAME_None, RF_Transient, handlers[i].handler);
        FHandlerPlayData newData;
        newData.delay = handlers[i].delay;
        newData.timerHandle = FTimerHandle();
        newData.handler = newHandler;
        runtimeHandlers.Add(newData);
    }
    for (int i = 0; i < runtimeHandlers.Num(); ++i) {
        runtimeHandlers[i].handler->InitHandler(inWorld);
    }
}

UJuiceProfile* UJuiceProfile::RegisterFor(UObject* owner) {
    return owner->GetWorld()->GetSubsystem<UJuiceSubsystem>()->RegisterProfile(this, owner);
}

void UJuiceProfile::DecommissionHandlers() {
    for (int i = 0; i < runtimeHandlers.Num(); ++i) {
        runtimeHandlers[i].handler->DecommissionHandler();
    }
}

void UJuiceProfile::Play(FJuiceInfo& fji, UObject* owner) const {
    // play is called on the asser version and requests its runtime version registered for the given owner
    // that will be played.
    // const auto rt = owner->GetWorld()->GetSubsystem<UJuiceSubsystem>()->GetRuntimeProfile(this, owner);
    // if (!rt) {
    //     LOG_ERROR("Juice profile %s was not registered for owner %s", *GetName(), *owner->GetName());
    //     return;
    // }
    for (int i = 0; i < runtimeHandlers.Num(); ++i) {
        const auto handlerData = runtimeHandlers[i];
        const auto handler = handlerData.handler;
        handler->BeforePlay();
        if (handlerData.delay > 0) {
            FJuiceInfo delayedFjo = fji; // make a copy so that
            auto timerHandle = handlerData.timerHandle;
            owner->GetWorld()->GetTimerManager().SetTimer(timerHandle, [&]() { handler->Play(delayedFjo); }, handlerData.delay, false);
        }
        else {
            handler->Play(fji);
        }
    }
}

void UJuiceProfile::MarkAsInstance() {
    isInstance = true;
}
