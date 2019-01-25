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

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> ProjectileClass;
	
};
