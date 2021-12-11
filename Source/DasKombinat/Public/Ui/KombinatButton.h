// Copyright (c) Game Kombinat

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "KombinatButton.generated.h"

/**
 * Special button that has some improvements for keyboard/gamepad ui navigation.
 */
UCLASS()
class DASKOMBINAT_API UKombinatButton : public UButton {
    GENERATED_BODY()
protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Kombinat Button")
    FButtonStyle normal;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Kombinat Button")
    FButtonStyle focus;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Kombinat Button")
    class USoundCue* clickCue;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Kombinat Button")
    class USoundCue* hoverCue;

    bool isFocused;
public:
    void Start();
    virtual TSharedRef<SWidget> RebuildWidget() override;

    UFUNCTION()
    void KombinatHandleClicked();
    UFUNCTION()
    void KombinatHandleHover();
private:
    UFUNCTION()
    void CheckFocus();

};
