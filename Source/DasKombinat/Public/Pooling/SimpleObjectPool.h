// 

#pragma once

#include "CoreMinimal.h"
#include "Logging.h"
#include "PoolableActor.h"
#include "SimpleObjectPool.generated.h"

/**
 * We want a number of these somewhere in a container.
 * That is the consideration of them being uobjects and not actors or components or whatnot.
 *
 * I would have liked a generic pool with templates to avoid casting on the call site.
 * But that doesn't work with uclasses and so forth. And in order to not have pooled objects
 * GC'd because their outer isn't the pool and end up with nothing in the pool... gotta do it this way.
 *
 * If you happen to know a trick about this, please do let me know.
 */
UCLASS()
class DASKOMBINAT_API USimpleObjectPool : public UObject {
    GENERATED_BODY()

protected:
    UPROPERTY(Replicated)
    UObject* poolOwner;

    UPROPERTY(Replicated)
    APawn* poolObjectInstigator;
    
    UPROPERTY(Replicated)
    TArray<APoolableActor*> pooledObjects;

    TSubclassOf<APoolableActor> pooledType;

    UPROPERTY(Replicated)
    int capacity;

    UPROPERTY(Replicated)
    bool progressive;

    UPROPERTY()
    UWorld* world;
public:
    USimpleObjectPool();
    virtual void InitPool(int size, bool isProgressive, TSubclassOf<APoolableActor> type, UObject* inPoolOwner);
    
    virtual void InitPool(int size, bool isProgressive, TSubclassOf<APoolableActor> type, UObject* inPoolOwner, APawn* instigator);

    virtual void DrainPool();

    TArray<APoolableActor*> GetPool();

    virtual bool IsSupportedForNetworking() const override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    
    APoolableActor* Get();

    bool Get(APoolableActor** geddit);
    template<typename  T>
    bool Get(T** geddit, bool canSpawnNewObject = true);

    // just some convenience for readability, might not get used
    // because the pooled objects already can put themselves back on their own.
    static void PutBack(APoolableActor* actor);
private:
    APoolableActor* CreateObject();
};

// it's a generic type hence it has to be in the header for compiling purposes.
template <typename T>
bool USimpleObjectPool::Get(T** geddit, bool canSpawnNewObject) {
    *geddit = nullptr;
    for (int i = 0; i < pooledObjects.Num(); ++i) {
        const auto object = pooledObjects[i];
        if (!object) {
            LOG_WARNING("Object in pool is null!");
            continue;
        }
        if (object->CanBeTaken()) {
            object->OnDispense();
            T* tmp = Cast<T>(object);
            if (!tmp) {
                LOG_ERROR("get template provided type is not a poolable actor type! That's all we know.");
                return false;
            }
            *geddit = tmp;
            return true;
        }
    }
    if (progressive && pooledObjects.Num() < capacity && canSpawnNewObject) {
        const auto a = CreateObject();
        a->OnDispense();
        T* tmp = Cast<T>(a);
        if (!tmp) {
            LOG_ERROR("get template provided type is not a poolable actor type! That's all we know.");
            return false;
        }
        *geddit = tmp;
        return true;
    }
    LOG_WARNING("No free objects in pool of type %s owned by %s!", *pooledType.Get()->GetName(), *poolOwner->GetName());
    return false;
}

