// Fill out your copyright notice in the Description page of Project Settings.


#include "KombinatActor.h"

void AKombinatActor::OnConstruction(const FTransform& Transform) {
    Super::OnConstruction(Transform);
    SetActive(isActive);
}

void AKombinatActor::SetActive(bool activate) {
    wasTickingWhenDeactivated = IsActorTickEnabled();
    isActive = activate;
    
    SetActorTickEnabled(activate);
    SetActorEnableCollision(activate);
    SetActorHiddenInGame(!activate);
}

void AKombinatActor::K2_AfterLoadActor_Implementation() {
    SetActive(isActive);
}

void AKombinatActor::K2_BeforeSaveActor_Implementation() {
    
}
