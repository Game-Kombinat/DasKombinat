#pragma once

#include "Logging/LogMacros.h"


#define LOG_INFO(text, ...) UE_LOG(LogTemp, Display, TEXT(text), __VA_ARGS__)
#define LOG_WARNING(text, ...) UE_LOG(LogTemp, Warning, TEXT(text), __VA_ARGS__)
#define LOG_ERROR(text, ...) UE_LOG(LogTemp, Error, TEXT(text), __VA_ARGS__)