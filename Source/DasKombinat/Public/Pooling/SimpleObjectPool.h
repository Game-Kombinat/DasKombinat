// 

#pragma once

#include "CoreMinimal.h"
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
    UPROPERTY(EditAnywhere)
    TArray<APoolableActor*> pooledObjects;
public:
    virtual void InitPool(int size, TSubclassOf<APoolableActor> type);

    virtual void DrainPool();
    
    APoolableActor* Get();

    bool Get(APoolableActor** geddit);

    // just some convenience for readability, might not get used
    // because the pooled objects already can put themselves back on their own.
    static void PutBack(APoolableActor* actor);
};
