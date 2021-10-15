// Copyright (c) Game Kombinat

#pragma once

#include "CoreMinimal.h"
#include "Coroutine.h"
#include "UObject/Object.h"
#include "CoroutineManager.generated.h"


/**
 * Manages simple coroutine like stuff.
 * Bit like the latent action manager but without the blueprint shebang attached.
 * Just raw and simple
 */
UCLASS()
class DASKOMBINAT_API UCoroutineManager : public UObject {
    GENERATED_BODY()
    static UCoroutineManager* instance;
    TArray<FCoroutine*> runningRoutines;
    TArray<FCoroutine*> scheduledAdds;
    TArray<FCoroutine*> scheduledRemovals;
public:
    virtual ~UCoroutineManager() override;
    void Prepare();

    void Add(FCoroutine* coroutine);

    void Tick();

    bool NeedsTicking() const;
    static UCoroutineManager* Instance() { return instance; }

};
