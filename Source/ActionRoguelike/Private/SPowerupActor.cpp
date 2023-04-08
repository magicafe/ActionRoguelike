// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerupActor.h"

#include "Components/SphereComponent.h"

// Sets default values
ASPowerupActor::ASPowerupActor()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Powerup");
	RootComponent = SphereComp;
	
 	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);

	RespawnTime = 10.0f;
	bIsActive = true;

	bReplicates = true;
}

void ASPowerupActor::Interact_Implementation(APawn* InstigatorPawn)
{
	ISGameplayInterface::Interact_Implementation(InstigatorPawn);
}

void ASPowerupActor::HideAndCooldown()
{
	SetPowerupState(false);

	GetWorldTimerManager().SetTimer(TimerHandle_Respawn, this, &ASPowerupActor::ShowPowerup, RespawnTime);
}

void ASPowerupActor::ShowPowerup()
{
	SetPowerupState(true);
}

void ASPowerupActor::SetPowerupState(bool newState)
{
	bIsActive = newState;
	SetActorEnableCollision(bIsActive);
	RootComponent->SetVisibility(bIsActive, true);
}


