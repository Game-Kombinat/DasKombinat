// Copyright (c) Game Kombinat

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameDataContext.generated.h"

USTRUCT(BlueprintType)
struct FGameDataContextKey {
    GENERATED_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
    FName name;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
    int32 value;
    // used to identify keys instead of display name because it may change.
    // and we sure don't want shit to break when a name has been changed.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame)
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

    /** This will be part of the asset but the data in it is actually volatile. I can see no other solution around it right now. */
    UPROPERTY(VisibleAnywhere, SaveGame)
    TArray<FGameDataContextKey> runtimeData;

public:
    UFUNCTION(BlueprintCallable)
    /** Returns the general truthyness of the value at this key. That means it returns true if the value is greater than 0 */
    bool GetTruthyness(const FGameDataContextKey& key) const;

    /** Used in runtime to get a value from the context. */
    int32 GetValue(const FGameDataContextKey& key) const;

    /** Used in runtime to get a value from the context. */
    int32 GetValue(const FString& key) const;

    // need a k2_ because of overloads
    UFUNCTION(BlueprintCallable, meta=(DisplayName="Get Value"))
    /** Used in runtime to get a value from the context. */
    int32 K2_GetValue(const FGameDataContextKey& key) const;
    

    /** Used in runtime to override a value in the context. This can not add new values!*/
    void SetValue(const FGameDataContextKey& key);
    void SetValue(const FString& key, int value);

    /** Set values from blueprints. For more obvious use, we explicitly pass a value as second argument. Normally we'd read the value of the context key but it's a little obtuse */
    UFUNCTION(BlueprintCallable, meta=(DisplayName="Set Value"))
    void K2_SetValue(const FGameDataContextKey& key, int value);
    /** Set values from blueprints. For more obvious use, we explicitly pass a value as second argument. Normally we'd read the value of the context key but it's a little obtuse */
    UFUNCTION(BlueprintCallable, meta=(DisplayName="Add Value"))
    void K2_AddValue(const FGameDataContextKey& key, int value);

    /** Sets a value to this context and a key with the given name. Creates a new key that's only part of the runtime data when key not found. */
    void ForceSetValue(const FString& key, int value);

    /** Returns a copy of the game data context keys within this context. This will merge parent keys into one list, if any. It's for editor purposes. */
    TArray<FGameDataContextKey> GetKeyList();

    /** Call in editor to invalidate the key list cache of this data context and all its parents. */
    void InvalidateKeyCache();

    void PrepareRuntimeData();

    UGameDataContext* GetParent() const;

private:
    bool FindEntry(FGameDataContextKey key, FGameDataContextKey& out) const;

    FORCEINLINE int32 GetIndex(const FGameDataContextKey& key) const;

};
