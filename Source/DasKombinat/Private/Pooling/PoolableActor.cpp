// 


#include "Pooling/PoolableActor.h"


// Sets default values
APoolableActor::APoolableActor() {
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

void APoolableActor::Init() {
    OnPutBack();
}

void APoolableActor::OnDispense() {
    SetActive(true);
    isReady = false;
}

void APoolableActor::OnPutBack() {
    SetActive(false);
    isReady = true;
}

bool APoolableActor::CanBeTaken() const {
    return isReady;
}
