// Copyright (c) Game Kombinat


#include "GameDataContext.h"

#include "Logging.h"


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

int32 UGameDataContext::GetValue(const FString& key) const {
    for (int i = 0; i < runtimeData.Num(); ++i) {
        auto realKey = runtimeData[i];
        if (realKey.name.IsEqual(FName(key))) {
            return realKey.value;
        }
    }
    LOG_WARNING("DataContext: There is no key labelled %s", *key);
    return -1;
}

int32 UGameDataContext::K2_GetValue(const FGameDataContextKey& key) const {
    return GetValue(key);
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

void UGameDataContext::SetValue(const FString& key, int value) {
    for (int i = 0; i < runtimeData.Num(); ++i) {
        auto realKey = runtimeData[i];
        if (realKey.name.IsEqual(FName(key))) {
            realKey.value = value;
            SetValue(realKey);
            return;
        }
    }
    LOG_WARNING("DataContext: There is no key labelled %s", *key);
}

void UGameDataContext::K2_SetValue(const FGameDataContextKey& key, int value) {
    SetValue(key.name.ToString(), value);
}

void UGameDataContext::K2_AddValue(const FGameDataContextKey& key, const int value) {
    const int val = GetValue(key);
    K2_SetValue(key, val + value);
}

void UGameDataContext::ForceSetValue(const FString& key, int value) {
    for (int i = 0; i < runtimeData.Num(); ++i) {
        auto realKey = runtimeData[i];
        if (realKey.name.IsEqual(FName(key))) {
            realKey.value = value;
            SetValue(realKey);
            return;
        }
    }
    runtimeData.Add(FGameDataContextKey(FName(key), value));
    LOG_WARNING("DataContext: New key added to runtime data: %s", *key);
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
