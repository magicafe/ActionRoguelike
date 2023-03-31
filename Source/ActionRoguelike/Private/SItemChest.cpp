// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemChest.h"

// Sets default values
ASItemChest::ASItemChest()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(BaseMesh);

	TargetPitch = 110;
}

void ASItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	ISGameplayInterface::Interact_Implementation(InstigatorPawn);
	LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
}	

