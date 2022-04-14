#pragma once
#include "TransitionCondition.h"
#include "FsmTransition.generated.h"

USTRUCT()
struct DASKOMBINAT_API FFsmTransition {
    GENERATED_BODY()

    TSharedPtr<FTransitionCondition> condition;

    UPROPERTY()
    class UFsmState* to;

    FFsmTransition(): to(nullptr) {

    }

    explicit FFsmTransition(UFsmState* inTarget, TSharedPtr<FTransitionCondition> inCondition) {
        to = inTarget;
        condition = inCondition;
    }

    friend bool operator==(const FFsmTransition& lhs, const FFsmTransition& rhs) {
        return lhs.condition == rhs.condition
            && lhs.to == rhs.to;
    }

    friend bool operator!=(const FFsmTransition& lhs, const FFsmTransition& rhs) {
        return !(lhs == rhs);
    }
};
