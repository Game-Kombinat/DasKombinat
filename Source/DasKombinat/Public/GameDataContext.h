﻿// Copyright (c) Game Kombinat

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameDataContext.generated.h"

USTRUCT(BlueprintType)
struct FGameDataContextKey {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName name;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 value;
    // used to identify keys instead of display name because it may change.
    // and we sure don't want shit to break when a name has been changed.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FGuid guid;

    friend bool operator==(const FGameDataContextKey& lhs, const FGameDataContextKey& rhs) {
        return lhs.guid == rhs.guid;
    }

    friend bool operator!=(const FGameDataContextKey& lhs, const FGameDataContextKey& rhs) {
        return !(lhs == rhs);
    }

    explicit FGameDataContextKey() : name("None"), value(-1), guid(FGuid::NewGuid()) {
    }

    explicit FGameDataContextKey(FName keyName, int32 keyValue) : name(keyName), value(keyValue), guid(FGuid::NewGuid()) {
    }

    FGameDataContextKey(const FGameDataContextKey& original) : name(original.name), value(original.value), guid(original.guid) {
    }
};

/**
 * 
 */
UCLASS(ClassGroup = GameKombinat, Category="GameKombinat", BlueprintType)
class DASKOMBINAT_API UGameDataContext : public UObject {
    GENERATED_BODY()
    TArray<FGameDataContextKey> consolidatedKeyList;
    bool keyListGenerated;
protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UGameDataContext* parent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FGameDataContextKey> data;

    /** Is spawned with a world as parent and is therefore removed when the world is removed. */
    UPROPERTY(VisibleAnywhere, Transient)
    TWeakObjectPtr<UGameDataContext> runtimeInstance;

public:
    UFUNCTION(BlueprintCallable)
    /** Returns the general truthyness of the value at this key. That means it returns true if the value is greater than 0 */
    bool GetTruthyness(const FGameDataContextKey& key) const;

    UFUNCTION(BlueprintCallable)
    /** Used in runtime to get a value from the context. */
    int32 GetValue(const FGameDataContextKey& key) const;

    /** Used in runtime to override a value in the context. This can not add new values!*/
    void SetValue(const FGameDataContextKey& key) const;

    /** Returns a copy of the game data context keys within this context. This will merge parent keys into one list, if any. It's for editor purposes. */
    TArray<FGameDataContextKey> GetKeyList();

    /** Call in editor to invalidate the key list cache of this data context and all its parents. */
    void InvalidateKeyCache();

    void PrepareRuntimeData(const TWeakObjectPtr<UObject>& worldContext);

private:
    bool FindEntry(FGameDataContextKey key, FGameDataContextKey& out) const;

    void InternalSpawnRuntimeData(const TWeakObjectPtr<UObject>& worldContext);

    FORCEINLINE int32 GetIndex(const FGameDataContextKey& key) const;

};
