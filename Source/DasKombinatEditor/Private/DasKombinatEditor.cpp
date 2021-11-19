#include "DasKombinatEditor.h"

#include "AssetToolsModule.h"
#include "DataContextAssetFactoryNew.h"
#include "DataContextSelectorPropertyCustomization.h"
#include "GameDataContext.h"
#include "GameDataContextAssetActions.h"
#include "IAssetTools.h"


FDasKombinatEditorModule::FDasKombinatEditorModule() : dataContextType(MakeShareable(new FGameDataContextAssetActions())) {
}

void FDasKombinatEditorModule::StartupModule() {
    if (!FModuleManager::Get().IsModuleLoaded("AssetTools")) {
        return;
    }
    IAssetTools& assetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
    // register category for game kombinat asset types
    GameKombinat = assetTools.RegisterAdvancedAssetCategory(FName(TEXT("GameKombinat")),FText::FromString("Game Kombinat"));

    // asset type data for game data context
    //dataContextType = MakeShareable(new FGameDataContextAssetActions());
    assetTools.RegisterAssetTypeActions(dataContextType);

    // register data context property drawer
    FPropertyEditorModule& propertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
    const FName dcName = FGameDataContextKey::StaticStruct()->GetFName();
	
    propertyModule.RegisterCustomPropertyTypeLayout(
        dcName,
        FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FDataContextSelectorPropertyCustomization::MakeInstance)
    );
    // we can add this here, it'll be handled with the class layouts when unregistering in one go.
    customClassLayouts.Add(dcName);
    // notify on customization change
    propertyModule.NotifyCustomizationModuleChanged();
    
}

void FDasKombinatEditorModule::ShutdownModule() {
    if (!FModuleManager::Get().IsModuleLoaded("AssetTools")) {
        return;
    }
    
    IAssetTools& assetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
    assetTools.UnregisterAssetTypeActions(dataContextType);

    FPropertyEditorModule& propertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
    for (const FName layout : customClassLayouts) {
        // propertyModule.UnregisterCustomClassLayout(layout); // if we had custom class layouts, we can call this additionally
        propertyModule.UnregisterCustomPropertyTypeLayout(layout);
    }
}

IMPLEMENT_MODULE(FDasKombinatEditorModule, DasKombinatEditor)
