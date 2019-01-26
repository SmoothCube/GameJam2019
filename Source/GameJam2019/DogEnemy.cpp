// Fill out your copyright notice in the Description page of Project Settings.

#include "DogEnemy.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "KidPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyController.h"
#include "Components/SphereComponent.h"
#include "Projectile.h"

// Sets default values
ADogEnemy::ADogEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LookForPlayerComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Look For Player"));
	LookForPlayerComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ADogEnemy::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ADogEnemy::BeginOverlap);


	LookForPlayerComponent->SetSphereRadius(LookForPlayerRadius);
	LookForPlayerComponent->OnComponentBeginOverlap.AddDynamic(this, &ADogEnemy::BeginTraceOverlap);
	LookForPlayerComponent->OnComponentEndOverlap.AddDynamic(this, &ADogEnemy::EndTraceOverlap);


	HomeLocation = GetActorLocation();
	EC = Cast<AEnemyController>(GetController());
}

// Called every frame
void ADogEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (bCanSeePlayer)
	{
		LastPlayerLocation = Player->GetActorLocation();
		EC->MoveToLocation(LastPlayerLocation, CloseEnoughToPlayer, true, true);
	}
}

// Called to bind functionality to input
void ADogEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADogEnemy::BeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	UE_LOG(LogTemp, Warning, TEXT("[DogEnemy] BeginOverlap: Overlapping!"));
	if (Cast<AProjectile>(OtherActor))
	{
		SpawnBloodParticle(OtherActor->GetActorLocation());

		Health -= 10;
		if (Health <= 0)
			Destroy();

	}
	else 
	{
		Player = (Cast<AKidPlayer>)(OtherActor);
		if (Player)
		{ 
	
			UE_LOG(LogTemp, Warning, TEXT("Player Overlapping dog!"));
			//GetMovementComponent()->AddRadialForce();
			Player->GetMovementComponent()->AddRadialImpulse(GetActorLocation(), 500, 20000, ERadialImpulseFalloff::RIF_Constant, true);
			Player->Health--;

			if (Player->Health <= 0)
				Player->Destroy();
		}
	}
}

void ADogEnemy::BeginTraceOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
	
	UE_LOG(LogTemp, Warning, TEXT("[DogEnemy] BeginTraceOverlap: Overlapping!"));
	Player = Cast<AKidPlayer>(OtherActor);

	if (Player) {
		UE_LOG(LogTemp, Warning, TEXT("[DogEnemy] BeginTraceOverlap: Found Player!"));
		bCanSeePlayer = true;
	}
	
}

void ADogEnemy::EndTraceOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("[DogEnemy] EndTraceOverlap: Overlapping!"));
	Player = Cast<AKidPlayer>(OtherActor);

	if (Player) {
		UE_LOG(LogTemp, Warning, TEXT("[DogEnemy] EndTraceOverlap: Lost Player!"));
		bCanSeePlayer = true;
	}
}

void ADogEnemy::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}
void ADogEnemy::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ADogEnemy::OnFire()
{

}