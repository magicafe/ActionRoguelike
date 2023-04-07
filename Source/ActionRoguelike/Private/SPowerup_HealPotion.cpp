// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerup_HealPotion.h"

#include "SAttributeComponent.h"
#include "SPlayerState.h"

ASPowerup_HealPotion::ASPowerup_HealPotion()
{
	HealthHeal = 50.0f;
	CreditsCost = 2;
}

void ASPowerup_HealPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		UE_LOG(LogTemp, Warning, TEXT("None instigator pawn interact with the heal potion"));
		return;
	}

	USAttributeComponent* AttrComp = USAttributeComponent::GetAttributes(InstigatorPawn);
	if (ensure(AttrComp) && !AttrComp->IsFullHealth())
	{
		if (ASPlayerState* PS = InstigatorPawn->GetPlayerState<ASPlayerState>())
		{
			if (PS->RemoveCredits(CreditsCost) && AttrComp->ApplyHealthChange(this, HealthHeal))
			{
				HideAndCooldown();
			}
		}
	}
}
