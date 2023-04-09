// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemChest.h"

#include "Net/UnrealNetwork.h"

// Sets default values
ASItemChest::ASItemChest()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(BaseMesh);

	TargetPitch = 110;

	SetReplicates(true);
}

void ASItemChest::OnActorLoaded_Implementation()
{
	OnRep_LidOpened();
}

void ASItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	bLidOpened = !bLidOpened;
	OnRep_LidOpened(); // has to manually called from server
}

void ASItemChest::OnRep_LidOpened()
{
	float CurPitch = bLidOpened ? TargetPitch : 0;
	LidMesh->SetRelativeRotation(FRotator(CurPitch, 0, 0));
}

void ASItemChest::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASItemChest, bLidOpened);
}
