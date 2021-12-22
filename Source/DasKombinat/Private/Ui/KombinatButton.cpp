// Copyright (c) Game Kombinat


#include "Ui/KombinatButton.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Sound/SoundCue.h"

void UKombinatButton::Start() {
    UKismetSystemLibrary::K2_SetTimer(this, "CheckFocus", 0.01f, true);
}

TSharedRef<SWidget> UKombinatButton::RebuildWidget() {
    auto btn = Super::RebuildWidget();

    // in case this was already added and not removed, remove it again.
    OnClicked.RemoveDynamic(this, &UKombinatButton::KombinatHandleClicked);
    OnHovered.RemoveDynamic(this, &UKombinatButton::KombinatHandleHover);
    
    OnClicked.AddDynamic(this, &UKombinatButton::KombinatHandleClicked);
    OnHovered.AddDynamic(this, &UKombinatButton::KombinatHandleHover);
    Start();
    return btn;
}

void UKombinatButton::BeginDestroy() {
    if (IsValid(this)) {
        UKismetSystemLibrary::K2_ClearTimer(this, "CheckFocus");
        OnClicked.RemoveDynamic(this, &UKombinatButton::KombinatHandleClicked);
        OnHovered.RemoveDynamic(this, &UKombinatButton::KombinatHandleHover);
    }
    
    Super::BeginDestroy();
}

void UKombinatButton::KombinatHandleClicked() {
    UGameplayStatics::PlaySound2D(this, clickCue);
}

void UKombinatButton::KombinatHandleHover() {
    UGameplayStatics::PlaySound2D(this, hoverCue);
}

void UKombinatButton::CheckFocus() {
    TSharedPtr<SWidget> SafeWidget = GetCachedWidget();
    if (HasKeyboardFocus() || IsHovered()) {
        if (!isFocused) {
            isFocused = true;
            KombinatHandleHover();
        }
        SetStyle(focus);
    }
    else {
        SetStyle(normal);
        isFocused = false;
    }
}
