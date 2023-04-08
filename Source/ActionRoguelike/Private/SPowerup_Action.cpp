// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerup_Action.h"

#include "SActionComponent.h"
#include "SAction.h"

void ASPowerup_Action::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn && ActionToGrant))
	{
		return;
	}

	USActionComponent* ActionComp = Cast<USActionComponent>(InstigatorPawn->GetComponentByClass(USActionComponent::StaticClass()));
	if (ActionComp)
	{
		if (ActionComp->GetAction(ActionToGrant))
		{
			FString DebugMsg = FString::Printf(TEXT("Action %s is already granted."), *GetNameSafe(ActionToGrant));
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, DebugMsg);
			return;
		}

		ActionComp->AddAction(InstigatorPawn, ActionToGrant);
		HideAndCooldown();
	}
}
