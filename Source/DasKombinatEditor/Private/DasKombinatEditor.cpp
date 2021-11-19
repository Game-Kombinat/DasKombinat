#include "DasKombinatEditor.h"

#include "AssetToolsModule.h"
#include "DataContextAssetFactoryNew.h"
#include "GameDataContextAssetActions.h"
#include "IAssetTools.h"


void FDasKombinatEditorModule::StartupModule() {
    IAssetTools& assetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
    // register category for game kombinat asset types
    GameKombinat = assetTools.RegisterAdvancedAssetCategory(FName(TEXT("GameKombinat")),FText::FromString("Game Kombinat"));

    // asset type data for game data context
    dataContextType = MakeShareable(new FGameDataContextAssetActions());
    assetTools.RegisterAssetTypeActions(dataContextType);
    
}

void FDasKombinatEditorModule::ShutdownModule() {
    IAssetTools& assetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
    assetTools.UnregisterAssetTypeActions(dataContextType);
    //IModuleInterface::ShutdownModule();
}

IMPLEMENT_MODULE(FDasKombinatEditorModule, DasKombinatEditor)
