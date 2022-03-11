// Fill out your copyright notice in the Description page of Project Settings.


#include "Juice/RuntimeJuiceProfile.h"

#include "Juice/HandlerPlayData.h"
#include "Juice/JuiceHandler.h"

void URuntimeJuiceProfile::InitProfile(UJuiceProfile* inOriginalProfile, UObject* inOwner) {
    originalProfile = inOriginalProfile;
    world = inOwner->IsA(UWorld::StaticClass()) ? Cast<UWorld>(inOwner) : inOwner->GetWorld();
    owner = inOwner;

    auto handlerTemplates = originalProfile->GetHandlers();
    runtimeHandlers.Reset(handlerTemplates.Num());
    for (int i = 0; i < handlerTemplates.Num(); ++i) {
        const auto newHandler = NewObject<UJuiceHandler>(this, handlerTemplates[i].handler->GetClass(), NAME_None, RF_Transient, handlerTemplates[i].handler);
        FHandlerPlayData newData;
        newData.delay = handlerTemplates[i].delay;
        newData.timerHandle = FTimerHandle();
        newData.handler = newHandler;
        runtimeHandlers.Add(newData);
    }
    for (int i = 0; i < runtimeHandlers.Num(); ++i) {
        runtimeHandlers[i].handler->InitHandler(world);
    }
}

void URuntimeJuiceProfile::DeinitProfile() {
    for (int i = 0; i < runtimeHandlers.Num(); ++i) {
        runtimeHandlers[i].handler->DecommissionHandler();
    }
}

void URuntimeJuiceProfile::Play(FJuiceInfo& fji) {
    for (int i = 0; i < runtimeHandlers.Num(); ++i) {
        const auto handlerData = runtimeHandlers[i];
        const auto handler = handlerData.handler;
        handler->BeforePlay();
        if (handlerData.delay > 0) {
            FJuiceInfo delayedFjo = fji; // make a copy so that
            auto timerHandle = handlerData.timerHandle;
            world->GetTimerManager().SetTimer(timerHandle, [&]() { handler->Play(delayedFjo); }, handlerData.delay, false);
        }
        else {
            handler->Play(fji);
        }
    }
}
