// Fill out your copyright notice in the Description page of Project Settings.

#include "KidPlayer.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"

#include "DogEnemy.h"
#include "Projectile.h"

// Sets default values
AKidPlayer::AKidPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FName weaponSocketName = TEXT("PLACE_GUN_HERE_JNTSocket");

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Arm = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Arm"));
	Arm->SetupAttachment(Camera);
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
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AKidPlayer::OnFire);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AKidPlayer::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AKidPlayer::Sprint);

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
		AddMovementInput(GetActorForwardVector(), Value);
	}
}
void AKidPlayer::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AKidPlayer::OnFire()
{
	/* needs to be uncommented when the animation is ready
	if (bFirstShot)
	{
		if(FirstShootAnim)
		{
			Arm->PlayAnimation(FirstShootAnim, false);
			bFirstShot = false;
		}
	}
	*/
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		if(ShootAnim)
		{
			Arm->PlayAnimation(ShootAnim, false);
		}
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			const FRotator SpawnRotation = GetControlRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation(MuzzleLocation);// = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// spawn the projectile at the muzzle
			World->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

		}
	}
}

void AKidPlayer::Sprint()
{
	bIsSprinting = !bIsSprinting;
	if (bIsSprinting)
		GetCharacterMovement()->MaxWalkSpeed = 1200;
	else
		GetCharacterMovement()->MaxWalkSpeed = 600;

}


