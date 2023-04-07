// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerup_Credits.h"

#include "SPlayerState.h"

ASPowerup_Credits::ASPowerup_Credits()
{
	CreditsAmount = 5;
}

void ASPowerup_Credits::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		UE_LOG(LogTemp, Warning, TEXT("None instigator pawn interact with the credits"));
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Actor %s try to get credits."), *GetNameSafe(InstigatorPawn));
	if (ASPlayerState* PS = InstigatorPawn->GetPlayerState<ASPlayerState>())
	{
		PS->AddCredits(CreditsAmount);
		HideAndCooldown();
	}
}
