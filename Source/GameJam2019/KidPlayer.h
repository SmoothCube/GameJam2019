// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KidPlayer.generated.h"


class AProjectile;
UCLASS()
class GAMEJAM2019_API AKidPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKidPlayer();

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent * Arm;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	
	void MoveRight(float Value);

	void OnFire();
	void Sprint();

	int Health = 3;

	UPROPERTY(BlueprintReadWrite)
	bool bUsingStickGun = true;
	UPROPERTY(BlueprintReadWrite)
	bool bGunPickedUp = false;
	UPROPERTY(BlueprintReadWrite)
	bool bFired = false;
	UPROPERTY(BlueprintReadWrite)
	bool bCinematicDone = false;

	UPROPERTY(BlueprintReadWrite)
	FVector MuzzleLocation = FVector(0, 0, 0);

	UPROPERTY(EditAnywhere)
	class USoundBase* ShootSound = nullptr;

	UPROPERTY(EditAnywhere)
	class USoundBase* HurtSound = nullptr;

	void RecieveDamage(float Damage);

	UPROPERTY(BlueprintReadWrite)
	int Kills;

private:
	bool bIsSprinting = false;
	bool bFirstShot = false;


	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> ProjectileClass;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);
};
