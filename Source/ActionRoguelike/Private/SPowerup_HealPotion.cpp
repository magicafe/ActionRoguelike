// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerup_HealPotion.h"

#include "SAttributeComponent.h"
#include "SPlayerState.h"

#define LOCTEXT_NAMESPACE "InteractableActors"

ASPowerup_HealPotion::ASPowerup_HealPotion()
{
	HealthHeal = 50.0f;
	CreditsCost = 2;
}

FText ASPowerup_HealPotion::GetInteractText_Implementation(APawn* InstigatorPawn)
{
	USAttributeComponent* AttrComp = USAttributeComponent::GetAttributes(InstigatorPawn);
	if (AttrComp && AttrComp->IsFullHealth())
	{
		return LOCTEXT("HealthPotion_FullHealthWarning", "Already at full health.");
	}
	return FText::Format(LOCTEXT("HealthPotion_InteractMessage", "Cost {0} Credits. Restores health to maximum."), CreditsCost);
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

#undef LOCTEXT_NAMESPACE