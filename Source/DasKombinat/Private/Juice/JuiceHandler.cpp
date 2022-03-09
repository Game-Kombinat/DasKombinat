// Fill out your copyright notice in the Description page of Project Settings.


#include "Juice/JuiceHandler.h"

void UJuiceHandler::DecommissionHandler() {
    if (isPrimed) {
        InternalDecommissionHandler();
        isPrimed = false;
    }
    
}

void UJuiceHandler::InitHandler(UWorld* inWorld) {
    if (!isPrimed) {
        world = inWorld;
        InternalInitHandler(inWorld);
        isPrimed = true;
    }
}
