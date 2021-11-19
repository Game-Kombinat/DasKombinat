// Copyright (c) Game Kombinat


#include "DataContextAssetFactoryNew.h"

#include "GameDataContext.h"

UDataContextAssetFactoryNew::UDataContextAssetFactoryNew() {
    SupportedClass = UGameDataContext::StaticClass();
    bCreateNew = true;
    //bEditAfterNew = true;
}

UObject* UDataContextAssetFactoryNew::FactoryCreateNew(UClass* inClass, UObject* inParent, FName inName, EObjectFlags flags, UObject* context, FFeedbackContext* warn) {
    return NewObject<UGameDataContext>(inParent, inClass, inName, flags);
}

bool UDataContextAssetFactoryNew::ShouldShowInNewMenu() const {
    return true;
}
