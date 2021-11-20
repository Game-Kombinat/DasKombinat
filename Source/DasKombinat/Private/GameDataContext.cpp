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

void UGameDataContext::SetValue(const FGameDataContextKey& key) {
    const int32 idx = GetIndex(key);
    if (idx != INDEX_NONE) {
        runtimeData[idx] = key;
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
    
    const int32 idx = GetIndex(key);
    if (idx != INDEX_NONE) {
        out = runtimeData[idx];
        return true;
    }
    if (parent) {
        return parent->FindEntry(key, out);
    }
    return false;
}


int32 UGameDataContext::GetIndex(const FGameDataContextKey& key) const {
    return runtimeData.IndexOfByKey(key);
}

void UGameDataContext::PrepareRuntimeData() {
    if (parent) {
        parent->PrepareRuntimeData();
    }

    runtimeData.Empty();
    runtimeData.Append(data);
}

UGameDataContext* UGameDataContext::GetParent() const {
    return parent;
}
