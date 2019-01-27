// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "SpawnPoint.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAM2019_API ASpawnPoint : public ATargetPoint
{
	GENERATED_BODY()
		ASpawnPoint();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void SpawnActor();
	bool firstSpawn = false;
	UPROPERTY(EditAnywhere)
	UClass* ActorToSpawn = nullptr;
	
};
