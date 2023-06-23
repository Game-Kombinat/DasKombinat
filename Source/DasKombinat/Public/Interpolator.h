#pragma once
#include "Anim8Action.h"
#include "CoroutineControl.h"
#include "CoroutineManager.h"

class DASKOMBINAT_API FInterpolator {
private:
    float startTime;
    float duration01;
    float duration10;
    
    float stateA;
    float stateB;
    float currentValue;

    float timeOfPause;

    UWorld* world;
    
public:
    FInterpolator();
    FInterpolator(float duration, UWorld* world);
    FInterpolator(float forwardDuration, float backwardDuration, UWorld* world);

    bool IsDone() {
        return FMath::Abs(Sample() - stateB) <= 0.00001f;
    }

    bool DirectionIsForward() const {
        return stateA == 0;
    }

    float Duration() const {
        return DirectionIsForward() ? duration01 : duration10;
    }

    void Pause();

    void Resume();

    void StartFadeForward(bool reset = false);

    void StartFadeBackward(bool reset = false);

    void ForceForward();

    void ForceBackward();
    
    float Sample();

    float SampleTime() const;

    /**
     * Start linear interpolation on the game thread. Callbacks are delegates.
     */
    static FCoroutineControl Anim8(UWorld* world, float duration, bool playForward, FAnim8Sample onSample,
                                   FAnim8Done onFinish);

    /**
     * Start linear interpolation on the game thread. Callbacks are lambdas.
     */
    template<typename T>
    static FCoroutineControl Anim8(UWorld* world, float duration, bool playForward, T* objRef, void (T::*onSample)(float), void (T::*onFinish)());
    
private:
    void Force(float target);
    void StartFade(float a, float b, bool reset);
};

template <typename T>
FCoroutineControl FInterpolator::Anim8(UWorld* world, float duration, bool playForward, T* objRef, void(T::* onSample)(float), void(T::* onFinish)()) {

    FAnim8Sample sample;
    sample.BindUObject(objRef, onSample);
    
    FAnim8Done done;
    done.BindUObject(objRef, onFinish);
    const auto p = MakeShared<FInterpolator>(duration, world);
    const auto shared = MakeShared<FAnim8Action>(playForward, p, sample, done);
    
    return UCoroutineManager::Instance()->Add(shared);
}