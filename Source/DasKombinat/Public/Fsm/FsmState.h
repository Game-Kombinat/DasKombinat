#pragma once

// typedef void*::StateFunc();
DECLARE_DELEGATE(StateFunc);

template<typename TStateId>
struct FFsmState {
    TStateId id;
    StateFunc enter;
    StateFunc tick;
    StateFunc exit;

    FFsmState(const TStateId _id, const StateFunc _enter, const StateFunc _tick, const StateFunc _exit) {
        id = _id;
        enter = _enter;
        tick = _tick;
        exit = _exit;
    }
};
