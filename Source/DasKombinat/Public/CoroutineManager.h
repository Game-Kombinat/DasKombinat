// Copyright (c) Game Kombinat

#pragma once

#include "CoreMinimal.h"
#include "Coroutine.h"


/**
 * Manages simple coroutine like stuff.
 * Bit like the latent action manager but without the blueprint shebang attached.
 * Just raw and simple
 */
class DASKOMBINAT_API UCoroutineManager {
    
    static UCoroutineManager* instance;
    TArray<FCoroutine*> runningRoutines;
    TArray<FCoroutine*> scheduledAdds;
    TArray<FCoroutine*> scheduledRemovals;
public:
    ~UCoroutineManager();
    void Prepare();

    class FCoroutineControl Add(FCoroutine* coroutine);

    void Tick();

    bool NeedsTicking() const;
    static UCoroutineManager* Instance() { return instance; }

};
