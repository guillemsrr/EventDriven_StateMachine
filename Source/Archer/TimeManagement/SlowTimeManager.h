#pragma once

#include "SlowTimeManager.generated.h"

UCLASS()
class ARCHER_API USlowTimeManager : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<AActor*> TimeFreeActors;
	
	UPROPERTY()
	TArray<UActorComponent*> TimeFreeActorComponents;
	
public:
	void AddFreeTicker(class AActor* Ticker);
	void AddFreeTicker(class UActorComponent* Ticker);
	void SetGlobalTimeDilation();
	void SetSlowModeTimeDilation();
};
