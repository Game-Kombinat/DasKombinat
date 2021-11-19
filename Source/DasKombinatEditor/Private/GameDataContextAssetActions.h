// Copyright (c) Game Kombinat

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

/**
 * 
 */
class DASKOMBINATEDITOR_API FGameDataContextAssetActions : public FAssetTypeActions_Base {
    // /** Pointer to the style set to use for toolkits. */
    // TSharedRef<ISlateStyle> Style;
    
public:
    // explicit FGameDataContextAssetActions(const TSharedRef<ISlateStyle>& inStyle);
    FGameDataContextAssetActions();

    virtual bool CanFilter() override;
    virtual void GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder) override;
    virtual uint32 GetCategories() override;
    virtual FText GetName() const override;
    virtual UClass* GetSupportedClass() const override;
    virtual FColor GetTypeColor() const override;
    virtual bool HasActions(const TArray<UObject*>& InObjects) const override;
    // virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
};
