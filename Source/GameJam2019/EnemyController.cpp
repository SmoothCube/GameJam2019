// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyController.h"
#include "KidPlayer.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"

AEnemyController::AEnemyController()
{

}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	
	HomeLocation = GetPawn()->GetActorLocation();
}

void AEnemyController::Tick(float DeltaTime)
 {
	 Super::Tick(DeltaTime);

	 // create tarray for hit results
	 TArray<FHitResult> OutHits;

	 // start and end locations
	 FVector SweepStart = GetPawn()->GetActorLocation();
	 FVector SweepEnd = GetPawn()->GetActorLocation();

	 // create a collision sphere
	 FCollisionShape MyColSphere = FCollisionShape::MakeSphere(1000.f);

	 // draw collision sphere
	 DrawDebugSphere(GetWorld(), GetPawn()->GetActorLocation(), MyColSphere.GetSphereRadius(), 50, FColor::Purple, true);

	 // check if something got hit in the sweep
	 bool isHit = GetWorld()->SweepMultiByChannel(OutHits, SweepStart, SweepEnd, FQuat::Identity, ECC_GameTraceChannel1, MyColSphere);

	 if (isHit)
	 {
	
		 // loop through TArray
		 for (auto& Hit : OutHits)
		 {
			 Player = Cast<AKidPlayer>(Hit.Actor);
			 if (Player)
			 {
				 LastPlayerLocation = Player->GetActorLocation();
				 MoveToLocation(LastPlayerLocation, 600.f, true, true);

				 GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Hit Result: %s"), *Player->GetName()));

			 }
			 if (GEngine)
			 {
				 // screen log information on what was hit
				 // uncommnet to see more info on sweeped actor
				 // GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("All Hit Information: %s"), *Hit.ToString()));
			 }
		 }
	 }
 }

