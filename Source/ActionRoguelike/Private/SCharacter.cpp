// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"

#include "SInteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASCharacter::MoveForward(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0;
	ControlRot.Roll = 0;
	AddMovementInput(ControlRot.Vector(), value);
}

void ASCharacter::MoveRight(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0;
	ControlRot.Roll = 0;
	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, value);
}

void ASCharacter::PrimaryAttack()
{
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}

void ASCharacter::PrimaryInteract()
{
	InteractionComp->PrimaryInteract();
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Rotation Visualization
	const float DrawScale = 100.0f;
	const float Thickness = 5.0f;
	FVector LineStart = GetActorLocation();
	LineStart += GetActorRightVector() * 100.0f;
	FVector ActorDirection_LineEnd = LineStart + GetActorForwardVector() * 100.0f;
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ActorDirection_LineEnd, DrawScale, FColor::Yellow,
		false, 0.0f, 0, Thickness);
	FVector ControlDirection_LineEnd = LineStart + GetControlRotation().Vector() * 100.0f;
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ControlDirection_LineEnd, DrawScale, FColor::Green,
		false, 0.0f, 0, Thickness);
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);
}

