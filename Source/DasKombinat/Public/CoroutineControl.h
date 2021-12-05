// Copyright (c) Game Kombinat

#pragma once

#include "CoreMinimal.h"
#include "Coroutine.h"

/**
 * 
 */
class DASKOMBINAT_API FCoroutineControl {
private:
    TSharedPtr<FCoroutine> handle;
    
public:
    explicit FCoroutineControl();
    explicit FCoroutineControl(TSharedPtr<FCoroutine> routine);
    ~FCoroutineControl();

    bool IsDone() const;

    void ForceEnd() const;
};
