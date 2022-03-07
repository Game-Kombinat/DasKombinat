﻿// 


#include "Pooling/SimpleObjectPool.h"

#include "Logging.h"

void USimpleObjectPool::InitPool(int size, bool isProgressive, TSubclassOf<APoolableActor> type, AActor* inPoolOwner) {
    world = inPoolOwner->GetWorld();
    poolOwner = inPoolOwner;
    
    capacity = size;
    progressive = isProgressive;
    pooledType = type;

    pooledObjects.Reset(capacity);

    if (progressive) {
        return;
    }
    for (int i = 0; i < capacity; ++i) {
        CreateObject();
    }
}

void USimpleObjectPool::InitPool(int size, bool isProgressive, TSubclassOf<APoolableActor> type, AActor* inPoolOwner, APawn* instigator) {
    poolObjectInstigator = instigator;
    InitPool(size, isProgressive, type, inPoolOwner);
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
    if (progressive && pooledObjects.Num() < capacity) {
        const auto a = CreateObject();
        a->OnDispense();
        return a;
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
    if (progressive && pooledObjects.Num() < capacity) {
        const auto a = CreateObject();
        a->OnDispense();
        *geddit = a;
        return true;
    }
    *geddit = nullptr;
    LOG_WARNING("No free objects in pool!");
    return false;
}

void USimpleObjectPool::PutBack(APoolableActor* actor) {
    actor->OnPutBack();
}

APoolableActor* USimpleObjectPool::CreateObject() {
    FActorSpawnParameters spawnParams;
    spawnParams.ObjectFlags = RF_Transient;
#if WITH_EDITOR
    spawnParams.bHideFromSceneOutliner = true;
#endif
    spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    spawnParams.Owner = poolOwner;
    spawnParams.Instigator = poolObjectInstigator;
    const auto a = Cast<APoolableActor>(world->SpawnActor(pooledType.Get(), &FVector::ZeroVector, &FRotator::ZeroRotator, spawnParams));
    a->OnPutBack();
    pooledObjects.AddUnique(a);

    return a;
    
}
