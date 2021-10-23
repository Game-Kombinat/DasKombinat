// Copyright (c) Game Kombinat


#include "CoroutineControl.h"

FCoroutineControl::FCoroutineControl(FCoroutine* routine) {
    handle = routine;
}

FCoroutineControl::~FCoroutineControl() {
}

bool FCoroutineControl::IsDone() const {
    return !handle ||handle->IsDone();
}

void FCoroutineControl::ForceEnd() const {
    if (handle) {
        handle->ForceEnd();
    }
}
