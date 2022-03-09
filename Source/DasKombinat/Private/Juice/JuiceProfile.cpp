// Fill out your copyright notice in the Description page of Project Settings.


#include "Juice/JuiceProfile.h"

#include "Juice/JuiceHandler.h"
#include "Juice/JuiceSubsystem.h"

void UJuiceProfile::InitHandlers(UWorld* inWorld) {
    world = inWorld;
    for (int i = 0; i < handlers.Num(); ++i) {
        handlers[i].handler->InitHandler(world);
    }
}

void UJuiceProfile::DecommissionHandlers() {
    for (int i = 0; i < handlers.Num(); ++i) {
        handlers[i].handler->DecommissionHandler();
    }
}

void UJuiceProfile::Play(FJuiceInfo& fji) {
    // todo: this is kinda stupid. We either need to handle registration differently
    // or do something more with the juice maker for its existence to make any sense.
    const auto jm = world->GetSubsystem<UJuiceSubsystem>();
    jm->ProcessProfile(this);
    for (int i = 0; i < handlers.Num(); ++i) {
        const auto handlerData = handlers[i];
        const auto handler = handlerData.handler;
        handler->BeforePlay();
        if (handlerData.delay > 0) {
            world->GetTimerManager().SetTimer(handlers[i].timerHandle, [&]() { handler->Play(fji); }, handlerData.delay, false);
        }
        else {
            handler->Play(fji);
        }
    }
}
