// Copyright (c) Game Kombinat

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class DASKOMBINATEDITOR_API FDasKombinatEditorModule : public IModuleInterface {
    TSharedRef<class FGameDataContextAssetActions> dataContextType;
public:
    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
