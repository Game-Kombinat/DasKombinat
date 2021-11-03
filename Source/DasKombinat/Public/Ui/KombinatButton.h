// Copyright (c) Game Kombinat

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "UObject/Object.h"
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
public:
    void Start();
private:
    UFUNCTION()
    void CheckFocus();

};
