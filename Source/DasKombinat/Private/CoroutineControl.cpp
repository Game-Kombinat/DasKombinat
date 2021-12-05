// Copyright (c) Game Kombinat


#include "CoroutineControl.h"

FCoroutineControl::FCoroutineControl() {
    handle = nullptr;
}

FCoroutineControl::FCoroutineControl(TSharedPtr<FCoroutine> routine) {
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
