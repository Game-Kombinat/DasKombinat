// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Saveable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class DASKOMBINAT_API USaveable : public UInterface {
    GENERATED_BODY()
};

/**
 * 
 */
class DASKOMBINAT_API ISaveable {
    GENERATED_BODY()

public:
    ///
    /// Gives a chance to do some pre-save preparations
    ///
    UFUNCTION()
    virtual void BeforeSaveActor();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta=(Displayname="BeforeSaveActor"))
    void K2_BeforeSaveActor();

    ///
    /// Gives a chance to do some post-load housekeeping
    /// to properly restore an actor.
    ///
    UFUNCTION()
    virtual void AfterLoadActor();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta=(Displayname="AfterLoadActor"))
    void K2_AfterLoadActor();
};
