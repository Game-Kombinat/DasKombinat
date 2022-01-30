#pragma once
#include "FsmState.h"

DECLARE_DELEGATE_RetVal(bool, FsmTransitionCondition)

template<typename TStateId>
struct FFsmTransition {
    FsmTransitionCondition condition;
    FFsmState<TStateId>* to;

    FFsmTransition(FFsmState<TStateId>* _to, FsmTransitionCondition _condition) {
        to = _to;
        condition = _condition;
    }
};
