// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KombinatActor.h"
#include "GameFramework/Actor.h"
#include "SaveableActor.generated.h"

UCLASS()
class DASKOMBINAT_API ASaveableActor : public AKombinatActor, public ISaveable {
    GENERATED_BODY()

public:
    virtual void K2_AfterLoadActor_Implementation() override;

    virtual void K2_BeforeSaveActor_Implementation() override;


};
