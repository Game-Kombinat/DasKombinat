// Fill out your copyright notice in the Description page of Project Settings.


#include "Saveable.h"

#include "Logging.h"


// Add default functionality here for any ISaveableActor functions that are not pure virtual.
void ISaveable::BeforeSaveActor() {
    const auto me = Cast<AActor>(this);
    if (!me) {
        LOG_WARNING("About to call before save on non-actor or actor is not castable");
    }
    Execute_K2_BeforeSaveActor(me);
}

void ISaveable::AfterLoadActor() {
    const auto me = Cast<AActor>(this);
    if (!me) {
        LOG_WARNING("About to call after load on non-actor or actor is not castable");
    }
    Execute_K2_AfterLoadActor(me);
}