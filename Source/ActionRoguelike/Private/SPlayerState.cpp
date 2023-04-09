// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"

#include "SSaveGame.h"

int32 ASPlayerState::GetCredits() const
{
	return Credits;
}

void ASPlayerState::AddCredits(int32 Delta)
{
	Credits += Delta;

	OnCreditsChanged.Broadcast(this, Credits, Delta);
}

bool ASPlayerState::RemoveCredits(int32 Delta)
{
	if (Credits < Delta)
	{
		return false;
	}
	
	Credits -= Delta;
	OnCreditsChanged.Broadcast(this, Credits, Delta);
	
	return true;
}

void ASPlayerState::SavePlayerState_Implementation(USSaveGame* SaveObject)
{
	if (SaveObject)
	{
		SaveObject->Credits = Credits;
	}
}

void ASPlayerState::LoadPlayerState_Implementation(USSaveGame* SaveObject)
{
	if (SaveObject)
	{
		Credits = SaveObject->Credits;
	}
}
