// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"


class AKidPlayer;

UCLASS()
class GAMEJAM2019_API AEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyController();

private:

	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	TSubclassOf<AKidPlayer> Player;
	FVector LastPlayerLocation;
	FVector HomeLocation;

};
