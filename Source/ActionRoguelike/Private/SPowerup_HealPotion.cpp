// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerup_HealPotion.h"

#include "SAttributeComponent.h"

ASPowerup_HealPotion::ASPowerup_HealPotion()
{
	HealthHeal = 50.0f;
}

void ASPowerup_HealPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		UE_LOG(LogTemp, Warning, TEXT("None instigator pawn interact with the heal potion"));
		return;
	}

	USAttributeComponent* AttrComp = InstigatorPawn->FindComponentByClass<USAttributeComponent>();
	if (ensure(AttrComp) && !AttrComp->IsFullHealth())
	{
		AttrComp->ApplyHealthChange(this, HealthHeal);
		HideAndCooldown();
	}
}
