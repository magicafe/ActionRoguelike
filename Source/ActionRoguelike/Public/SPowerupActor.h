// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SPowerupActor.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class ACTIONROGUELIKE_API ASPowerupActor : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPowerupActor();

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
	UPROPERTY(VisibleAnywhere, Category="Components")
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing="OnRep_IsActive", Category="Powerup")
	bool bIsActive;

	UFUNCTION()
	void OnRep_IsActive();

	UPROPERTY(VisibleAnywhere, Category="Powerup")
	float RespawnTime;

	FTimerHandle TimerHandle_Respawn;

	void HideAndCooldown();

	void ShowPowerup();

	void SetPowerupState(bool newState);
};
