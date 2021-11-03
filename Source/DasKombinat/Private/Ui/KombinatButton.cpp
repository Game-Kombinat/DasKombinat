// Copyright (c) Game Kombinat


#include "Ui/KombinatButton.h"
#include "Kismet/KismetSystemLibrary.h"

void UKombinatButton::Start() {
    UKismetSystemLibrary::K2_SetTimer(this, "CheckFocus", 0.01f, true);
}

void UKombinatButton::CheckFocus() {
    TSharedPtr<SWidget> SafeWidget = GetCachedWidget();
    if (HasKeyboardFocus() || IsHovered()) {
        SetStyle(focus);
    }
    else {
        SetStyle(normal);
    }
}
