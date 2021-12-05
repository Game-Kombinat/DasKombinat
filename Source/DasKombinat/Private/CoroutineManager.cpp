// Copyright (c) Game Kombinat


#include "CoroutineManager.h"

#include "CoroutineControl.h"

TWeakObjectPtr<UCoroutineManager> UCoroutineManager::instance = nullptr;

UCoroutineManager::~UCoroutineManager() {
    // for (auto r : runningRoutines) {
    //     r.Reset();
    // }
    //
    // for (auto r : scheduledAdds) {
    //     r.Reset();
    // }
    //
    // for (auto r : scheduledRemovals) {
    //     r.Reset();
    // }
    // runningRoutines.Empty();
    // scheduledAdds.Empty();
    // scheduledRemovals.Empty();
    //instance.Reset();
}

void UCoroutineManager::Prepare() {
    // todo: this returns "valid" in second playthrough but Reset throws access exception.
    // might be a leak.
    // if (instance.IsValid()) {
    //     instance.Reset();
    // }
    instance = this;
}

FCoroutineControl UCoroutineManager::Add(TSharedPtr<FCoroutine> coroutine) {
    if (!coroutine) {
        return FCoroutineControl(nullptr);
    }

    scheduledAdds.Add(coroutine);

    return FCoroutineControl(coroutine);
}

void UCoroutineManager::Tick() {
    // Process adding new routines
    for (auto r : scheduledAdds) {
        r->PreTick();
        runningRoutines.Add(r);
    }
    scheduledAdds.Empty();

    // run routines
    for (auto r : runningRoutines) {
        r->Tick();
        if (r->IsDone()) {
            scheduledRemovals.Add(r);
        }
    }

    // process routines that need to be removed
    for (auto r : scheduledRemovals) {
        runningRoutines.Remove(r);
        r->Cleanup();
        r.Reset();
    }
    scheduledRemovals.Empty();
}

bool UCoroutineManager::NeedsTicking() const {
    return scheduledAdds.Num() > 0 || scheduledRemovals.Num() > 0 || runningRoutines.Num() > 0;
}
