// Fill out your copyright notice in the Description page of Project Settings.

#include "DogEnemy.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "KidPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyController.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Projectile.h"

// Sets default values
ADogEnemy::ADogEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackPlayerComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Player Close Attack"));
	AttackPlayerComponent->SetupAttachment(RootComponent);

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

	AttackPlayerComponent->OnComponentBeginOverlap.AddDynamic(this, &ADogEnemy::BeginOverlapAttack);


	HomeLocation = GetActorLocation();
	EC = Cast<AEnemyController>(GetController());
}

// Called every frame
void ADogEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (bCanSeePlayer && bIsFighting)
	{
		LastPlayerLocation = Player->GetActorLocation();
		if (bCanWalk) {

		EC->MoveToLocation(LastPlayerLocation, CloseEnoughToPlayer, true, true);
		}
	}
}

// Called to bind functionality to input
void ADogEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
void ADogEnemy::BeginOverlapAttack(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (bIsFighting)
	{
		UE_LOG(LogTemp, Warning, TEXT("[DogEnemy] BeginOverlapAttack: Before Cast!"));
		Player = (Cast<AKidPlayer>)(OtherActor);
		if (Player)
		{
			UE_LOG(LogTemp, Warning, TEXT("[DogEnemy] BeginOverlapAttack: Found Player!"));
			bAttack = true;
		}
	}
}
void ADogEnemy::DealDamage()
{
	if (bAttack)
	{
		if (Player)
		{
			Player->RecieveDamage(1);
			UE_LOG(LogTemp, Warning, TEXT("[DogEnemy] DealDamage: AUUUU"));
			if (Player->Health <= 0)
			{
				Player->Destroy();
			}
		}
	}
}

void ADogEnemy::KnockBack()
{
	if (bAttack)
	{
		if (Player)
		{
			UE_LOG(LogTemp, Warning, TEXT("[DogEnemy] KnockBack: Found Player!"));
			Player->GetMovementComponent()->AddRadialImpulse(GetActorLocation(), 500, 20000, ERadialImpulseFalloff::RIF_Constant, true);
		}
	}
}
void ADogEnemy::BeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (bIsFighting)
	{
		UE_LOG(LogTemp, Warning, TEXT("[DogEnemy] BeginOverlap: Overlapping!"));
		if (Cast<AProjectile>(OtherActor))
		{
			UE_LOG(LogTemp, Warning, TEXT("[DogEnemy] BeginOverlap: Prjectile!"));

			SpawnBloodParticle(OtherActor->GetActorLocation());

			Health -= 10;
			if (Health <= 0 && bFirstDeath)
			{
				FTransform SpawnTransform = FTransform(FRotator(0, 0, 0), GetActorLocation() + FVector(0, 0, -50), FVector(1, 1, 1));
				if (DeathParticle)
				{
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathParticle, GetActorLocation(), GetActorRotation());
				}
				if (Player)
				{
					Player->Kills++;
				}
				Destroy();
				bFirstDeath = false;
				bIsFighting = false;
			}
		}
	}
}

void ADogEnemy::BeginTraceOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("[DogEnemy] BeginTraceOverlap: Overlapping!"));
	Player = Cast<AKidPlayer>(OtherActor);

	if (Player) {

		if (bFirstTimeSeePlayer)
		{
			bFirstTimeSeePlayer = false;
			ChangeMesh();
			LookForPlayerRadius = 3000.f;
			LookForPlayerComponent->SetSphereRadius(LookForPlayerRadius);

		}

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