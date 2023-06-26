// Copyright (c) Game Kombinat

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "InterpolatorHelper.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInterpolatorFinished);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInterpolatorTick, float, alpha);
/**
 * 
 */
UCLASS(meta=(HideThen=true))
class DASKOMBINAT_API UInterpolatorHelper : public UBlueprintAsyncActionBase  {
    GENERATED_BODY()
protected:
    UPROPERTY(BlueprintAssignable)
    FInterpolatorTick tick;

    // It has to be the second property, otherwise the parameter of tick isn't shown.
    UPROPERTY(BlueprintAssignable)
    FInterpolatorFinished done;

     UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext="worldContext"))
    static UInterpolatorHelper* Interpolate(UObject* worldContext, float duration);

    UFUNCTION()
    void OnFinished();

    UFUNCTION()
    void OnInterpolatorTick(float t);
};
