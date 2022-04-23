#pragma once
#include "Logging.h"

#include "TransitionCondition.generated.h"

DECLARE_DYNAMIC_DELEGATE_RetVal(bool, FTransitionTest);

class FDelegateInterface {
public:
    virtual ~FDelegateInterface() = default;
    virtual bool Call() = 0;
};

// Handles in-code ez-sneezy function pointers 
template<typename T>
class FNativeDelegate : public FDelegateInterface {
public:
    typedef bool (T::*Method)();

    static TSharedPtr<FNativeDelegate<T>> Create(T* instance, Method method) {
        return MakeShared<FNativeDelegate<T>>(instance, method);
    }
    
    FNativeDelegate(T* target, const Method operation) : methodHandle(operation), instance(target) {
    }

    virtual ~FNativeDelegate() override {
        methodHandle = 0;
        instance = 0;
    }

    virtual bool Call() override {
        if (!instance) {
            LOG_WARNING("Unbound native transition delegate. Returning true per default.");
            return true;
        }
        return (instance->*methodHandle)();
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

// handles blueprint shenanigans
class FUnrealDelegate : public FDelegateInterface {
public:

    static TSharedPtr<FUnrealDelegate> Create(FTransitionTest testMethod) {
        return MakeShared<FUnrealDelegate>(testMethod);
    }
    
    FUnrealDelegate(FTransitionTest testMethod) : methodHandle(testMethod) {
    }

    virtual ~FUnrealDelegate() override {
    }

    virtual bool Call() override {
        if (methodHandle.IsBound()) {
            return methodHandle.Execute();
        }
        LOG_WARNING("Unbound blueprint transition delegate. Returning true per default.")
        return true;
    }

private:

    FTransitionTest methodHandle;
};

// Handles lambda expressions,
class FLambdaDelegate : public FDelegateInterface {
public:

    static TSharedPtr<FLambdaDelegate> Create(TFunction<bool()> testMethod) {
        return MakeShared<FLambdaDelegate>(testMethod);
    }
    
    FLambdaDelegate(TFunction<bool()> testMethod) : methodHandle(testMethod) {
    }

    virtual ~FLambdaDelegate() override {
    }

    virtual bool Call() override {
        // sadly this crashes when unbound and there appears to be nothing to check first
        return methodHandle();
    }

private:

    TFunction<bool()> methodHandle;
};

USTRUCT()
struct DASKOMBINAT_API FTransitionCondition {
    GENERATED_BODY()
protected:

    TSharedPtr<FDelegateInterface> callable;

    // This is referenced in the FDelegateInterface. We keep it here to stop GC from collecting this
    // before the callable is deleted. Because callable is generic and cannot be inside unreals memory system.
    UPROPERTY()
    UObject* objRef;
public:
    FTransitionCondition() {
        callable = nullptr;
        objRef = nullptr;
    }

    bool Call() const {
        if (!callable.IsValid()) {
            LOG_ERROR("Unbound transition callable! Returning true per default");
            return true;
        }
        return callable->Call();
    };

    // For native function binding
    template<typename T>
    void RegisterCall(T* obj, bool (T::*Func)()) {
        callable = FNativeDelegate<T>::Create(obj, Func);
        objRef = obj;
    }

    // For binding blueprint shenanigans
    void RegisterCall(FTransitionTest transitionMethod) {
        callable = FUnrealDelegate::Create(transitionMethod);
        objRef = transitionMethod.GetUObject();
    }

    void RegisterCall(TFunction<bool()> transitionMethod) {
        callable = FLambdaDelegate::Create(transitionMethod);
        // doesn't need a container / doesn't have a container.
        // This may cause issues
        // objRef = transitionMethod.GetUObject();
    }

    friend bool operator==(const FTransitionCondition& lhs, const FTransitionCondition& rhs) {
        return lhs.callable == rhs.callable
            && lhs.objRef == rhs.objRef;
    }

    friend bool operator!=(const FTransitionCondition& lhs, const FTransitionCondition& rhs) {
        return !(lhs == rhs);
    }
};
