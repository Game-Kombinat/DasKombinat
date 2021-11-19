// Copyright (c) Game Kombinat

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class DASKOMBINATEDITOR_API FDasKombinatEditorModule : public IModuleInterface {
    TSharedRef<class IAssetTypeActions> dataContextType;
    TArray<FName> customClassLayouts;
public:
    FDasKombinatEditorModule();
    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
