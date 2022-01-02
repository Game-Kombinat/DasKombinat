// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveableActor.h"


void ASaveableActor::K2_AfterLoadActor_Implementation() {
    SetActive(isActive);
}

void ASaveableActor::K2_BeforeSaveActor_Implementation() {
    
}
