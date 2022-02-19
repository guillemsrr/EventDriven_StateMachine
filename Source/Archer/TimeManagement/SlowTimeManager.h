#pragma once

#include "SlowTimeManager.generated.h"

UCLASS()
class ARCHER_API USlowTimeManager : public UObject
{
	GENERATED_BODY()

public:
	void AddFreeTicker(AActor* Ticker);
	void AddFreeTicker(UActorComponent* Ticker);
	void SetGlobalTimeDilation();
	void SetSlowModeTimeDilation();
	
	FORCEINLINE void SetWorldContext(AActor* ContextActor){WorldContext = ContextActor;}

private:
	const float SLOW_TIME_DILATION = 0.1f;
	const float NORMAL_TIME_DILATION = 1.f;
	
	UPROPERTY()
	TArray<AActor*> TimeFreeActors;
	
	UPROPERTY()
	TArray<UActorComponent*> TimeFreeActorComponents;
	
	UPROPERTY()
	AActor* WorldContext;
};
