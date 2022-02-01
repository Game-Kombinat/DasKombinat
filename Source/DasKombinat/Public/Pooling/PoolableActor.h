// 

#pragma once

#include "CoreMinimal.h"
#include "KombinatActor.h"
#include "GameFramework/Actor.h"
#include "PoolableActor.generated.h"

UCLASS(Abstract)
class DASKOMBINAT_API APoolableActor : public AKombinatActor {
    GENERATED_BODY()
protected:
    UPROPERTY(Transient)
    bool isReady;
public:
    // Sets default values for this actor's properties
    APoolableActor();

    virtual void Init();
    /**
     * Called form the object pool when this actor is taken out of the pool.
     */
    virtual void OnDispense();

    /**
     * Called form the object pool when this actor is put back into the pool.
     */
    virtual void OnPutBack();

    /**
     * Check if this actor can be taken out of the pool.
     * If false, object is already taken.
     */
    bool CanBeTaken() const;
};
