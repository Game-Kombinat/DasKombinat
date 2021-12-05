// Copyright (c) Game Kombinat

#pragma once

#include "CoreMinimal.h"
#include "Coroutine.h"
#include "Logging.h"

#include "CoroutineManager.generated.h"

/**
 * Manages simple coroutine like stuff.
 * Bit like the latent action manager but without the blueprint shebang attached.
 * Just raw and simple
 */
UCLASS()
class DASKOMBINAT_API UCoroutineManager : public UObject {
    GENERATED_BODY()
    // this is less janky than a raw pointer at least 
    static TWeakObjectPtr<UCoroutineManager> instance;
    TArray<TSharedPtr<FCoroutine>> runningRoutines;
    TArray<TSharedPtr<FCoroutine>> scheduledAdds;
    TArray<TSharedPtr<FCoroutine>> scheduledRemovals;
public:
    virtual ~UCoroutineManager() override;
    void Prepare();

    class FCoroutineControl Add(TSharedPtr<FCoroutine> coroutine);

    void Tick();

    bool NeedsTicking() const;

    static UCoroutineManager* Instance() {
        if (!instance.IsValid()) {
            LOG_ERROR("No Coroutine manager instance is running! Will create a transient one. This is bad!");
            instance = NewObject<UCoroutineManager>();
        }
        
        return instance.Get();
    }

};
