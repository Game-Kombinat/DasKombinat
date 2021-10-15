#pragma once

DECLARE_DELEGATE_OneParam(FAnim8Sample, float)
DECLARE_DELEGATE(FAnim8Done)

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

    static void Anim8(UWorld* world, float duration, bool playForward, FAnim8Sample onSample, FAnim8Done onFinish);
    
private:
    void Force(float target);
    void StartFade(float a, float b, bool reset);
};
