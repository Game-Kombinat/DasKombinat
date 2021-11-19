// Copyright (c) Game Kombinat

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeCategories.h"
#include "UObject/Object.h"
#include "DataContextAssetFactoryNew.generated.h"

static EAssetTypeCategories::Type GameKombinat;
/**
 * 
 */
UCLASS()
class DASKOMBINATEDITOR_API UDataContextAssetFactoryNew : public UFactory {
    GENERATED_BODY()
    UDataContextAssetFactoryNew();
    virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
    virtual bool ShouldShowInNewMenu() const override;
};
