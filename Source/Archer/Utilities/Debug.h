#pragma once

#define DEBUG_LOG(Message) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,  FString(__FUNCTION__) + "(" + FString::FromInt(__LINE__) + ") " + Message); 
