// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPowerupActor.h"
#include "SPowerup_HealPotion.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASPowerup_HealPotion : public ASPowerupActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category="Powerup")
	float HealthHeal;

	UPROPERTY(EditAnywhere, Category="HealPotion")
	int32 CreditsCost;
	
public:
	ASPowerup_HealPotion();

	virtual FText GetInteractText_Implementation(APawn* InstigatorPawn) override;
	
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
};
