// Copyright (c) Game Kombinat


#include "CoroutineManager.h"

#include "CoroutineControl.h"

UCoroutineManager* UCoroutineManager::instance = nullptr;

UCoroutineManager::~UCoroutineManager() {
    for (auto r : runningRoutines) {
        if (r) {
            delete r;
        }
    }

    for (auto r : scheduledAdds) {
        if (r) {
            delete r;
        }
    }

    for (auto r : scheduledRemovals) {
        if (r) {
            delete r;
        }
    }
    instance = nullptr;
}

void UCoroutineManager::Prepare() {
    instance = this;
}

FCoroutineControl UCoroutineManager::Add(FCoroutine* coroutine) {
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
        delete r;
    }
    scheduledRemovals.Empty();
}

bool UCoroutineManager::NeedsTicking() const {
    return scheduledAdds.Num() > 0 || scheduledRemovals.Num() > 0 || runningRoutines.Num() > 0;
}
