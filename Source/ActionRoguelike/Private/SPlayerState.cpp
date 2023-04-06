// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"

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
