// Copyright (c) Game Kombinat

#pragma once

#include "CoreMinimal.h"
#include "GameDataContext.h"
#include "UObject/Interface.h"
#include "DataContextContainer.generated.h"

// This class does not need to be modified.
UINTERFACE()
class DASKOMBINAT_API UDataContextContainer : public UInterface {
    GENERATED_BODY()
};

/**
 * 
 */
class DASKOMBINAT_API IDataContextContainer {
    GENERATED_BODY()
    // Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    virtual UGameDataContext* GetDataContext() PURE_VIRTUAL(IDataContextContainer::GetDataContext, return nullptr;); 
};
