// 


#include "Pooling/SimpleObjectPool.h"

#include "Logging.h"

void USimpleObjectPool::InitPool() {
    
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
