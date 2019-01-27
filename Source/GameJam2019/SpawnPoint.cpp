// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPoint.h"
#include "Engine/World.h"

#include "DogEnemy.h"
ASpawnPoint::ASpawnPoint()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	SpawnActor();
}

void ASpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (firstSpawn)
	{
		SpawnActor();
		firstSpawn = false;
	}
}

void ASpawnPoint::SpawnActor()
{
	if (ActorToSpawn)
	{
		GetWorld()->SpawnActor<AActor>(ActorToSpawn, GetActorLocation(), GetActorRotation());
	}
}
