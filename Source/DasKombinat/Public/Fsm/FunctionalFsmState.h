// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FsmState.h"
#include "TransitionCondition.h"
#include "UObject/Object.h"
#include "FunctionalFsmState.generated.h"

template<typename T>
class FActionDelegate : public FDelegateInterface {
public:
    typedef void (T::*Method)();

    static TSharedPtr<FNativeDelegate<T>> Create(T* instance, Method method) {
        return MakeShared<FNativeDelegate<T>>(instance, method);
    }
    
    FActionDelegate(T* target, const Method operation) : methodHandle(operation), instance(target) {
    }

    virtual ~FActionDelegate() override {
        methodHandle = 0;
        instance = 0;
    }

    virtual bool Call() override {
        if (!instance) {
            LOG_WARNING("Unbound action delegate.");
            return false;
        }
        (instance->*methodHandle)();
        return true;
    }

private:

    Method methodHandle;
    // this can be a uobject which means it can get deleted
    // because we cannot mark this a uproperty as its generic.
    // So to make sure it won't blow, keep a reference to this object
    // where you keep the instance of this delegate.
    // And make it a uproperty there (the uobject). So you know.
    T* instance;
    
};

/**
 * An FSM state that will accept function pointers and a container
 * to pipe state calls through to. This is used to implement functional-style state machines.
 * It's primary, and probably only, use is in native cpp land to pre-bind state machines.
 */
UCLASS()
class DASKOMBINAT_API UFunctionalFsmState : public UFsmState {
    GENERATED_BODY()
protected:
    UPROPERTY()
    UObject* callbackContainer;

    TSharedPtr<FDelegateInterface> enterFunc;
    TSharedPtr<FDelegateInterface> tickFunc;
    TSharedPtr<FDelegateInterface> exitFunc;
    
public:
    template<typename T>
    void SetCallbacks(T* container, void(T::* enter)(), void(T::* exit)(), void(T::* tick)());

    void MarkTickable();
    
    virtual void Prepare_Implementation(UWorld* inWorld) override;

    virtual void Enter_Implementation() override;

    virtual void Tick_Implementation() override;

    virtual void Exit_Implementation() override;

};

template <typename T>
void UFunctionalFsmState::SetCallbacks(T* container, void(T::* enter)(), void(T::* exit)(), void(T::* tick)()) {
    callbackContainer = Cast<UObject>(container);
    if (!callbackContainer) {
        LOG_ERROR("Callback container is not a UObject, but it must be.")
        return;
    }
    
    if (enter) {
        enterFunc = MakeShared<FActionDelegate<T>>(container, enter);
    }

    if (exit) {
        exitFunc = MakeShared<FActionDelegate<T>>(container, exit);
    }
    
    if (tick) {
        tickFunc = MakeShared<FActionDelegate<T>>(container, tick);
    }
}
