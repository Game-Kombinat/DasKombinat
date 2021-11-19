// Copyright (c) Game Kombinat

#pragma once

#include "CoreMinimal.h"

class IAssetTypeActions;
/**
 * 
 */
class DASKOMBINATEDITOR_API FDasKombinatEditorModule : public IModuleInterface {
    TSharedRef<IAssetTypeActions> dataContextType;
public:
    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
