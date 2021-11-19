// Copyright (c) Game Kombinat


#include "GameDataContextAssetActions.h"

#include "DataContextAssetFactoryNew.h"
#include "GameDataContext.h"


// FGameDataContextAssetActions::FGameDataContextAssetActions(const TSharedRef<ISlateStyle>& inStyle) : Style(inStyle) {
// }

FGameDataContextAssetActions::FGameDataContextAssetActions() {
}

bool FGameDataContextAssetActions::CanFilter() {
    return true;
}

void FGameDataContextAssetActions::GetActions(const TArray<UObject*>& inObjects, FMenuBuilder& menuBuilder) {
    FAssetTypeActions_Base::GetActions(inObjects, menuBuilder);
    // yep, this is example code. ima keep it here in case we might want to use context menu options
    // menuBuilder.AddMenuEntry(
    //     TEXT("Reverse Text"),
    //     TEXT("Reverse the text stored in the selected text asset(s)."),
    //     FSlateIcon(),
    //     FUIAction(
    //         FExecuteAction::CreateLambda([=]{
    //             for (auto& TextAsset : TextAssets)
    //             {
    //                 if (TextAsset.IsValid() && !TextAsset->Text.IsEmpty())
    //                 {
    //                     TextAsset->Text = FText::FromString(TextAsset->Text.ToString().Reverse());
    //                     TextAsset->PostEditChange();
    //                     TextAsset->MarkPackageDirty();
    //                 }
    //             }
    //         }),
    //         FCanExecuteAction::CreateLambda([=] {
    //             for (auto& TextAsset : TextAssets)
    //             {
    //                 if (TextAsset.IsValid() && !TextAsset->Text.IsEmpty())
    //                 {
    //                     return true;
    //                 }
    //             }
    //             return false;
    //         })
    //     )
    // );
}

uint32 FGameDataContextAssetActions::GetCategories() {
    return GameKombinat;
}

FText FGameDataContextAssetActions::GetName() const {
    return FText::FromString("Game Data Context");
}

UClass* FGameDataContextAssetActions::GetSupportedClass() const {
    return UGameDataContext::StaticClass();
}

FColor FGameDataContextAssetActions::GetTypeColor() const {
    return FColor::Green;
}

bool FGameDataContextAssetActions::HasActions(const TArray<UObject*>& inObjects) const {
    return false;
}

// void FGameDataContextAssetActions::OpenAssetEditor(const TArray<UObject*>& inObjects, TSharedPtr<IToolkitHost> editWithinLevelEditor) {
//     FAssetTypeActions_Base::OpenAssetEditor(inObjects, editWithinLevelEditor);
// }
