// Fill out your copyright notice in the Description page of Project Settings.

#include "KidPlayer.h"
#include "Components/InputComponent.h"

// Sets default values
AKidPlayer::AKidPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AKidPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKidPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKidPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AKidPlayer::OnFire);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AKidPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AKidPlayer::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void AKidPlayer::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}
void AKidPlayer::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AKidPlayer::OnFire()
{

}