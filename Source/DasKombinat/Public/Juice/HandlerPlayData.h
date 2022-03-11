#pragma once

#include "HandlerPlayData.generated.h"

USTRUCT()
struct DASKOMBINAT_API FHandlerPlayData {
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    class UJuiceHandler* handler = nullptr;

    UPROPERTY(EditAnywhere)
    float delay = 0;

    UPROPERTY()
    FTimerHandle timerHandle;
};