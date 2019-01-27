// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DogEnemy.generated.h"

class AKidPlayer;
class AEnemyController;

UCLASS()
class GAMEJAM2019_API ADogEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADogEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float value);
	void MoveRight(float value);
	void OnFire();


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void BeginOverlapAttack(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION(BlueprintCallable)
	void DealDamage();

	UFUNCTION(BlueprintCallable)
	void KnockBack();

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);

	UPROPERTY(VisibleAnywhere)
		class UCapsuleComponent* AttackPlayerComponent;

	UPROPERTY(VisibleAnywhere)
		class USphereComponent* LookForPlayerComponent;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* DeathParticle;

	UFUNCTION()
		void BeginTraceOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);

	UFUNCTION()
		void EndTraceOverlap(UPrimitiveComponent * OverlappedComponent,
			AActor * OtherActor,
			UPrimitiveComponent * OtherComp,
			int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent)
		void ChangeMesh();

	UPROPERTY(EditAnywhere)
		float LookForPlayerRadius = 1000.f;

	UPROPERTY(EditAnywhere)
		float CloseEnoughToPlayer = 100.f;

	UFUNCTION(BlueprintImplementableEvent)
		void SpawnBloodParticle(FVector Location);

	UPROPERTY(BlueprintReadWrite)
		bool bAttack = false;

	UPROPERTY(BlueprintReadWrite)
		bool bCanWalk = false;

private:

	FVector LastPlayerLocation;
	FVector HomeLocation;
	AKidPlayer* Player;
	AEnemyController* EC;

	bool bFirstTimeSeePlayer = true;
	bool bIsFighting = true;
	bool bFirstDeath = true;
	bool bCanSeePlayer = false;
	int Health = 25;
};
