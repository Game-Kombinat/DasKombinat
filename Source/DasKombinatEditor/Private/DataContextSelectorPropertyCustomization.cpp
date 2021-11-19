// Copyright (c) Game Kombinat


#include "DataContextSelectorPropertyCustomization.h"

#include "DataContextContainer.h"
#include "DetailWidgetRow.h"
#include "GameDataContext.h"
#include "Logging.h"
#include "Widgets/Layout/SWrapBox.h"


FDataContextSelectorPropertyCustomization::FDataContextSelectorPropertyCustomization() {
}

void FDataContextSelectorPropertyCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle,
                                                               FDetailWidgetRow& HeaderRow,
                                                               IPropertyTypeCustomizationUtils&
                                                               StructCustomizationUtils) {
    propertyHandle = StructPropertyHandle;
    EnsureNodeData();

    if (!outerContainer) {
        HeaderRow.NameContent()[
                propertyHandle->CreatePropertyNameWidget()
            ]
            .ValueContent()
            .HAlign(HAlign_Fill)[
                GetDefaultPropertyViewWidget()
            ];
        return;
    }

    HeaderRow.NameContent()[
            propertyHandle->CreatePropertyNameWidget()
        ].ValueContent()
         .HAlign(HAlign_Fill)
        [
            SNew(SComboBox<FItemType>)
                        .OptionsSource(&keyList)
                        .OnGenerateWidget(this, &FDataContextSelectorPropertyCustomization::GenerateEventWidget)
                        .OnSelectionChanged(this, &FDataContextSelectorPropertyCustomization::OnSelectionChanged)
                        .InitiallySelectedItem(GetInitiallySelectedObject())
            [
                SNew(STextBlock)
                .Text(this, &FDataContextSelectorPropertyCustomization::GetSelectedKeyDisplayName)
            ]
        ][
            SNew(SBorder)[
                propertyHandle->CreatePropertyValueWidget()
            ]
        ];
}

void FDataContextSelectorPropertyCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle,
                                                                 IDetailChildrenBuilder& StructBuilder,
                                                                 IPropertyTypeCustomizationUtils&
                                                                 StructCustomizationUtils) {
    propertyHandle = StructPropertyHandle;
}

FDataContextSelectorPropertyCustomization::FItemType FDataContextSelectorPropertyCustomization::GetInitiallySelectedObject() {
    if (!outerContainer) {
        return nullptr;
    }
    if (propertyHandle->GetNumPerObjectValues() > 1) {
        return MakeShareable(new FGameDataContextKey("Multiple Values", -1));
    }
    
    void* rawValue = nullptr;
    auto member = propertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FGameDataContextKey, guid));
    member->GetValueData(rawValue);
    FGuid* selectedKey = static_cast<FGuid*>(rawValue);
    if (!selectedKey) {
        UE_LOG(LogTemp, Error, TEXT("Failed to get value for selected properties GUID. Address invalid."));
        return nullptr;
    }
    int idx = keyList.IndexOfByPredicate([&](FItemType x) {
        return x.Get()->guid == *selectedKey;
    });

    if (idx != INDEX_NONE) {
        selectedObject = keyList[idx];
        return keyList[idx];
    }
    
    return nullptr;
}

void FDataContextSelectorPropertyCustomization::CollectDataContextKeys() {
    if (!outerContainer) {
        return;
    }
    auto dc = outerContainer->GetDataContext()->GetKeyList();
    TArray<UObject*> outers;
    propertyHandle->GetOuterObjects(outers);
    keyList.Empty();
    for (const FGameDataContextKey key : dc) {
        keyList.Add(MakeShareable(new FGameDataContextKey(key)));
    }
}

void FDataContextSelectorPropertyCustomization::OnSelectionChanged(const FItemType newItem,
                                                                  ESelectInfo::Type SelectInfo) {
    selectedObject = newItem;
    void* rawValue = nullptr;
    // for some reason this works for writing but reading (get initially selected object) this doesn't work when reading.
    // I have not the faintest idea why that is. I'm probably getting something confuzzled.
    // Important part is: it works
    propertyHandle->GetValueData(rawValue);
    if (propertyHandle->GetNumPerObjectValues() > 1) {
        return;
    }
    FGameDataContextKey* keyInParent = static_cast<FGameDataContextKey*>(rawValue);
    keyInParent->guid = newItem->guid;
    keyInParent->name = newItem->name;
    keyInParent->value = newItem->value; // this isn't necessary, really but for good measure we oughta keep it.
}

void FDataContextSelectorPropertyCustomization::EnsureNodeData() {
    if (!outerContainer) {
        TArray<UObject*> outers;
        propertyHandle->GetOuterObjects(outers);
        for (const auto outer : outers) {
            outerContainer = Cast<IDataContextContainer>(outer);
            if (outerContainer) {
                break;
            }
        }
        // note: this is actually not an error case. We assume this is the data context object or similar.
        // point in case: it will not cause any trouble if missing but we log it away for diagnostics purposes.
        if (!outerContainer) {
            LOG_WARNING("There is no valid outer container to render the property key. We'll show the defaults!")
            return;
        }
    }
    CollectDataContextKeys();
    selectedObject = GetInitiallySelectedObject();
}

void FDataContextSelectorPropertyCustomization::OnDataKeyNameChanged(const FText& newText, ETextCommit::Type textType) const {
    void* rawValue = nullptr;
    propertyHandle->GetValueData(rawValue);
    FGameDataContextKey* keyInParent = static_cast<FGameDataContextKey*>(rawValue);
    keyInParent->name = FName(newText.ToString());
    TArray<UObject*> outers;
    propertyHandle->GetOuterObjects(outers);
    UGameDataContext* gc = Cast<UGameDataContext>(outers[0]);
    if (gc) {
        gc->InvalidateKeyCache();
    }
}

TSharedRef<SWidget> FDataContextSelectorPropertyCustomization::GenerateEventWidget(FItemType element) const {
    // return entry type for item
    // pretty sure there ain't much else that we need to do here
    return SNew(STextBlock).Text(FText::FromName(element.Get()->name));
}

FText FDataContextSelectorPropertyCustomization::GetSelectedKeyDisplayName() const {
    if (!selectedObject.IsValid()) {
        return FText::FromString("None");
    }
    return  FText::FromString(selectedObject.Get()->name.ToString());
}

TSharedRef<SWidget> FDataContextSelectorPropertyCustomization::GetDefaultPropertyViewWidget() const {
    const auto nameProp = propertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FGameDataContextKey, name));
    const auto defaultValueProp = propertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FGameDataContextKey, value));
    const auto guidProp = propertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FGameDataContextKey, guid));
    void* rawValue = nullptr;
    guidProp.Get()->GetValueData(rawValue);
    FText txt;
    if (rawValue) {
        txt = FText::FromString(static_cast<FGuid*>(rawValue)->ToString());
    }
    else {
        txt = FText::FromString("No GUID");
    }
    FName name;
    nameProp.Get()->GetValue(name);
    auto nameWidget = SNew(SEditableTextBox).Text(FText::FromName(name)).OnTextCommitted(this, &FDataContextSelectorPropertyCustomization::OnDataKeyNameChanged);

    return SNew(SWrapBox)
        .UseAllottedWidth(true)
        + SWrapBox::Slot()
        .Padding(5.f, 0.f)
        [
            SNew(SVerticalBox)
            + SVerticalBox::Slot()
            .AutoHeight()
            [
                nameProp->CreatePropertyNameWidget()
            ]
            + SVerticalBox::Slot()
            .AutoHeight()
            [
                nameWidget
            ]
        ]
        + SWrapBox::Slot()
        .Padding(5.f, 0.f)
        [
            SNew(SBox)
            .MinDesiredWidth(70.f)
            [
                SNew(SVerticalBox)
                + SVerticalBox::Slot()
                .AutoHeight()
                [
                    defaultValueProp->CreatePropertyNameWidget()
                ]
                + SVerticalBox::Slot()
                .AutoHeight()
                [
                    defaultValueProp->CreatePropertyValueWidget()
                ]
            ]
            // ]
        ]
        + SWrapBox::Slot()
        .Padding(5.f, 0.f)
        [
            SNew(SBox)
            .MinDesiredWidth(70.f)
            [
                SNew(SVerticalBox)
                + SVerticalBox::Slot()
                .AutoHeight()
                [
                    guidProp->CreatePropertyNameWidget()
                ]
                + SVerticalBox::Slot()
                .AutoHeight()
                [
                    SNew(STextBlock).Text(txt)
                ]
            ]
            // ]
        ];
}