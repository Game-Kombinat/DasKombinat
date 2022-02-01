// 


#include "Pooling/SimpleObjectPool.h"

#include "Logging.h"

void USimpleObjectPool::InitPool(int size, TSubclassOf<APoolableActor> type) {
    const auto world = GetWorld();
    if (!world) {
        LOG_ERROR("No world to spawn the actors of type %s in!", *type.Get()->GetName());
        return;
    }

    FActorSpawnParameters spawnParams;
    spawnParams.ObjectFlags = RF_Transient;
    spawnParams.bHideFromSceneOutliner = true;
    spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    pooledObjects.Reset();
    for (int i = 0; i < size; ++i) {
        auto a = Cast<APoolableActor>(world->SpawnActor(type.Get(), &FVector::ZeroVector, &FRotator::ZeroRotator, spawnParams));
        a->OnPutBack();
        pooledObjects.AddUnique(a);
    }
}

void USimpleObjectPool::DrainPool() {
    for (int i = 0; i < pooledObjects.Num(); ++i) {
        pooledObjects[i]->Destroy();
    }
    pooledObjects.Reset();
}

APoolableActor* USimpleObjectPool::Get() {
    for (int i = 0; i < pooledObjects.Num(); ++i) {
        const auto object = pooledObjects[i];
        if (!object) {
            LOG_WARNING("Object in pool is null!");
            continue;
        }
        if (object->CanBeTaken()) {
            object->OnDispense();
            return object;
        }
    }
    LOG_WARNING("No free objects in pool!");
    return nullptr;
}

bool USimpleObjectPool::Get(APoolableActor** geddit) {
    for (int i = 0; i < pooledObjects.Num(); ++i) {
        const auto object = pooledObjects[i];
        if (!object) {
            LOG_WARNING("Object in pool is null!");
            continue;
        }
        if (object->CanBeTaken()) {
            object->OnDispense();
            *geddit = object;
            return true;
        }
    }
    *geddit = nullptr;
    LOG_WARNING("No free objects in pool!");
    return false;
}

void USimpleObjectPool::PutBack(APoolableActor* actor) {
    actor->OnPutBack();
}
