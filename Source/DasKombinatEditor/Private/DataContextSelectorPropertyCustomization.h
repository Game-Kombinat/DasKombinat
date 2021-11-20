// Copyright (c) Game Kombinat

#pragma once

#include "CoreMinimal.h"
#include "DataContextContainer.h"

struct FGameDataContextKey;
/**
 * 
 */
class DASKOMBINATEDITOR_API FDataContextSelectorPropertyCustomization : public IPropertyTypeCustomization {
    typedef TSharedPtr<FGameDataContextKey> FItemType;
    TArray<FItemType> keyList;
    IDataContextContainer* outerContainer = nullptr;
public:
    static TSharedRef<IPropertyTypeCustomization> MakeInstance() {
        return MakeShareable(new FDataContextSelectorPropertyCustomization());
    }
    FDataContextSelectorPropertyCustomization();
    
    TSharedPtr<FGameDataContextKey> GetInitiallySelectedObject();
    
    // IPropertyTypeCustomization interface
    virtual void CustomizeHeader(
        TSharedRef<IPropertyHandle> StructPropertyHandle,
        class FDetailWidgetRow& HeaderRow,
        IPropertyTypeCustomizationUtils& StructCustomizationUtils
    ) override;

    virtual void CustomizeChildren(
        TSharedRef<class IPropertyHandle> StructPropertyHandle,
        class IDetailChildrenBuilder& StructBuilder,
        IPropertyTypeCustomizationUtils& StructCustomizationUtils
    ) override;

private:
    TSharedPtr<IPropertyHandle> propertyHandle;
    FItemType selectedObject;
    void CollectDataContextKeys();
    void OnSelectionChanged(const FItemType newItem, ESelectInfo::Type SelectInfo);
    void EnsureNodeData();
    void OnDataKeyNameChanged(const FText& newText, ETextCommit::Type textType) const;
    TSharedRef<SWidget> GenerateEventWidget(FItemType element) const;
    FText GetSelectedKeyDisplayName() const;
    TSharedRef<SWidget> GetDefaultPropertyViewWidget() const;
};
