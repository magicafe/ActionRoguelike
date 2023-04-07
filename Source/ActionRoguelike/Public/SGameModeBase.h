// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "GameFramework/GameModeBase.h"
#include "SGameModeBase.generated.h"

class UEnvQuery;
class UEnvQueryInstanceBlueprintWrapper;
class UCurveFloat;

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="AI")
	TSubclassOf<AActor> MinionClass;
	
	UPROPERTY(EditDefaultsOnly, Category="AI")
	UEnvQuery* SpawnBotQuery;
	
	UPROPERTY(EditDefaultsOnly, Category="AI")
	float SpawnTimerInterval;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	UCurveFloat* DifficultyCurve;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	int32 CreditPerKill;

	UPROPERTY(EditDefaultsOnly, Category="Powerup")
	UEnvQuery* PowerupSpawnQuery;
	
	UPROPERTY(EditDefaultsOnly, Category="Powerup")
	int32 DesiredPowerupCount;

	UPROPERTY(EditDefaultsOnly, Category="Powerup")
	float RequiredPowerupDistance;

	UPROPERTY(EditDefaultsOnly, Category="Powerup")
	TArray<TSubclassOf<AActor>> PowerupClasses;

	FTimerHandle TimerHandle_SpawnBots;

	UFUNCTION()
	void SpawnBotTimerElapsed();

	UFUNCTION()
	void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UFUNCTION()
	void OnPowerupSpawnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UFUNCTION()
	void RespawnPlayerElapsed(AController* Controller);

public:
	ASGameModeBase();

	virtual void StartPlay() override;

	virtual void OnActorKilled(AActor* VictimActor, AActor* Killer);

	UFUNCTION(Exec)
	void KillAll();
};
