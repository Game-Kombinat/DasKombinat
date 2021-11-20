// Copyright (c) Game Kombinat


#include "DataContextContainer.h"

#include "Logging.h"


// Add default functionality here for any IDataContextContainer functions that are not pure virtual.
UGameDataContext* IDataContextContainer::GetDataContext() {
    LOG_ERROR("Called GetDataContext base class!")
    return nullptr;
}