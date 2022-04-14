#pragma once
#include "Logging.h"

#include "TransitionCondition.generated.h"

class FDelegateInterface {
public:
    virtual ~FDelegateInterface() = default;
    virtual bool Call() = 0;
};

template<typename T>
class FDelegate : public FDelegateInterface {
public:
    typedef bool (T::*Method)();

    static TSharedPtr<FDelegate<T>> Create(T* instance, Method method) {
        return MakeShared<FDelegate<T>>(instance, method);
    }
    
    FDelegate(T* target, const Method operation) : methodHandle(operation), instance(target) {
    }

    virtual ~FDelegate() override {
        methodHandle = 0;
        instance = 0;
    }

    virtual bool Call() override {
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

USTRUCT()
struct DASKOMBINAT_API FTransitionCondition {
    GENERATED_BODY()
protected:
    // This must be the non-generic base type here because at this point we can't have template type info
    // that would be required to make this work.
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
            LOG_ERROR("Unbound FTransitionTest! Returning true per default");
            return true;
        }
        return callable->Call();
    };

    template<typename T>
    void RegisterCall(T* obj, bool (T::*Func)()) {
        callable = FDelegate<T>::Create(obj, Func);
    }

    friend bool operator==(const FTransitionCondition& lhs, const FTransitionCondition& rhs) {
        return lhs.callable == rhs.callable
            && lhs.objRef == rhs.objRef;
    }

    friend bool operator!=(const FTransitionCondition& lhs, const FTransitionCondition& rhs) {
        return !(lhs == rhs);
    }
};
