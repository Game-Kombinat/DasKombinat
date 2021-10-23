// Copyright (c) Game Kombinat

#pragma once

#include "CoreMinimal.h"
#include "Coroutine.h"

/**
 * 
 */
class DASKOMBINAT_API FCoroutineControl {
private:
    FCoroutine* handle;
    
public:
    explicit FCoroutineControl(FCoroutine* routine);
    ~FCoroutineControl();

    bool IsDone() const;

    void ForceEnd() const;
};
