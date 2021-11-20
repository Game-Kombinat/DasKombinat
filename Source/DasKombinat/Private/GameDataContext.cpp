// Copyright (c) Game Kombinat


#include "GameDataContext.h"

bool UGameDataContext::GetTruthyness(const FGameDataContextKey& key) const {
    FGameDataContextKey out;
    if (FindEntry(key, out)) {
        return out.value > 0;
    }
    return false;
}

int32 UGameDataContext::GetValue(const FGameDataContextKey& key) const {
    FGameDataContextKey out;
    if (FindEntry(key, out)) {
        return out.value;
    }
    return -1;
}

void UGameDataContext::SetValue(const FGameDataContextKey& key) const {
    const int32 idx = GetIndex(key);
    if (idx != INDEX_NONE) {
        runtimeInstance->data[idx] = key;
    }
    else if (parent) {
        parent->SetValue(key);
    }
}

TArray<FGameDataContextKey> UGameDataContext::GetKeyList() {
    if (!keyListGenerated) {
        keyListGenerated = true;
        TArray<FGameDataContextKey> keys;
        if (parent) {
            keys.Append(parent->GetKeyList());
        }
        consolidatedKeyList.Empty();
        consolidatedKeyList.Append(keys);
        consolidatedKeyList.Append(data);
    }
    return consolidatedKeyList;
}

void UGameDataContext::InvalidateKeyCache() {
    if (parent) {
        parent->InvalidateKeyCache();
    }
    keyListGenerated = false;
    consolidatedKeyList.Empty();
}

bool UGameDataContext::FindEntry(const FGameDataContextKey key, FGameDataContextKey& out) const {
    if (!runtimeInstance.IsValid()) {
        return false;
    }
    const int32 idx = GetIndex(key);
    if (idx != INDEX_NONE) {
        out = runtimeInstance->data[idx];
        return true;
    }
    if (parent) {
        return parent->FindEntry(key, out);
    }
    return false;
}

void UGameDataContext::InternalSpawnRuntimeData(const TWeakObjectPtr<UObject>& worldContext) {
    if (!worldContext.IsValid()) {
        UE_LOG(LogTemp, Error, TEXT("World context invalid for %s!"), *GetFName().ToString());
        return;
    }
    const auto world = worldContext->GetWorld();
    if (!world) {
        UE_LOG(LogTemp, Error, TEXT("No world found in world context object!"));
        return;
    }
    runtimeInstance = NewObject<UGameDataContext>(world, FName(FString::Format(TEXT("{0}_Runtime"), {GetFName().ToString()})), RF_Transient, this);
}

int32 UGameDataContext::GetIndex(const FGameDataContextKey& key) const {
    if (!runtimeInstance.IsValid()) {
        return INDEX_NONE;
    }
    return runtimeInstance->data.IndexOfByKey(key);
}

void UGameDataContext::PrepareRuntimeData(const TWeakObjectPtr<UObject>& worldContext) {
    if (parent) {
        parent->PrepareRuntimeData(worldContext);
    }

    if (!runtimeInstance.IsValid()) {
        InternalSpawnRuntimeData(worldContext);
    }
}

UGameDataContext* UGameDataContext::GetParent() const {
    return parent;
}
